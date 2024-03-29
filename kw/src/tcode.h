#ifndef TCODE_H
#define TCODE_H
/* -------------------------------------------------------------------
 * TCode クラス - T-Code 変換器
 */

#include <vector>
#include <map>
#include <algorithm>
#ifdef _MSC_VER //<OKA>
using std::vector;
#endif          //</OKA>

#include "block.h"
#include "bushu_dic.h"
#include "mg_table.h"
//<v127a - gg>
#include "gg_dic.h"
//</v127a - gg>
#include "moji.h"
#include "st_table.h"
#include "tc.h"

//<record>
struct STATENT {
    int direct;                 // 直接入力した回数
    int aux;                    // 補助入力で入力した回数
};

#define STAT_DIRECT 0
#define STAT_AUX    1

typedef std::map<MOJI, struct STATENT> StatMap;
//</record>

// 対象ウィンドウへの文字出力方法
#define OUT_DISABLE -1
#define OUT_WMCHAR 0
#define OUT_WMIMECHAR 1
#define OUT_WMKANCHOKUCHAR 2
#define OUT_WMUNICHAR 3
#define OUT_KEYEVENTFUNICODE 4

/* TCode クラス
 *
 * T-Code 変換器としてはたらく
 */
class TCode {
public:
    /* 変換テーブル類
     * --------------
     * 変換器生成時に初期化し、その後は定数のように用いるもの。
     */
    int *vkey;                  // TC_NKEYS 個の仮想キーの配列
    ControlBlock *table;        // ストローク漢字変換テーブル
    StTable *stTable;           // ストローク逆引きテーブル
    MgTable *mgTable;           // 交ぜ書き変換辞書
    BushuDic *bushuDic;         // 部首合成変辞
    //<v127a - gg>
    GgDic *ggDic;               // 熟語ガイド辞書
    //</v127a - gg>
    //int isReady;              // 初期化が完了しているか
    int mazeReady;              // 交ぜ書き変換が利用可能か
    int bushuReady;             // 部首合成が利用可能か
    //<v127a - gg>
    int ggReady;                // 熟語ガイドが利用可能か
    //</v127a - gg>
    //<v127a - shiftcheck>
    bool *isShiftKana;          // Shift状態のRegisterHotKeyが必要なキーか
                                // どうかを示すフラグを格納する配列
    //</v127a - shiftcheck>
    bool isAnyShiftSeq;         // テーブルファイルで何らかのシフト打鍵が定義されているか
    //<multishift2>
    DIR_TABLE dirTable;
    static void readDir(DIR_TABLE *, ifstream *);
    //</multishift2>

    /* オプション類
     * ------------
     * kanchoku.ini で設定するオプション
     * オプション一覧とデフォルト値は、table_window.c の initTC() を参照。
     */
    int OPT_hotKey;             // ON/OFF のキー
//<OKA> support unmodified hot key
    int OPT_unmodifiedHotKey;   // CTRLやSHIFTなどのmodifierなしでもHotKeyとして働く
//</OKA>
    char *OPT_keyboard;         // キーボード定義ファイル
    char *OPT_tableFile;        // テーブル定義ファイル

    char *OPT_bushu;            // 部首合成辞書ファイル
    char *OPT_mazegaki;         // 交ぜ書き変換辞書ファイル
    //<v127a - gg>
    char *OPT_gg;               // 熟語ガイド辞書ファイル
    //<gg-defg>
    char *OPT_defg;             // 配字案内文字リスト
    //</gg-defg>
    //</v127a - gg>
    int OPT_bushuAlgo;          // 部首合成変換のアルゴリズム
    int OPT_conjugationalMaze;  // 活用語の交ぜ書き変換
    int OPT_maze2gg;            // 強制練習モード初期状態
    STROKE *OPT_prefixautoassign; // 熟語ガイド中の外字にストローク割り振り

    int OPT_shiftKana;          // シフト打鍵でかたかな
    int OPT_shiftFallback;      // 一部でしかシフト打鍵を使わない配列の場合、
                                // シフト打鍵の定義がない場面でシフトなし打鍵の定義で代用
    int OPT_shiftLockStroke;    // Shiftによるストロークロック機能
    int OPT_enableHankakuKana;  // 半角かな変換

    int OPT_useWMIMECHAR;       // 出力メッセージ
    std::map<char *, int, ltstr> OPT_outputMethodMap; // 出力先ウィンドウ毎の出力方法
    //<v127a - outputsleep>
    long OPT_outputSleep;       // 仮想キーの output 時の Sleep 量 (ms)
    //</v127a - outputsleep>
    int OPT_outputVKeyMethod;
    int OPT_outputAlphabetAsVKey;
    int OPT_outputUnicode;

    int OPT_syncWithIME;        // IMEのON/OFFと漢直WinのON/OFFを連動させる
    int OPT_onoffLocal;         // ウィンドウを切り替えるときに各アプリのIME状態を優先
    int OPT_whatisimeon;        // 連動するIMEのON/OFFとはON/OFFである、NATIVE/ALNUMである
    int OPT_syncmaster;         // 漢直WinのhotkeyでIMEをどうする
    int OPT_syncslave;          // IMEの状態変化で漢直Winをどうする
    int OPT_considerIMEAction;  // WM_KANCHOKU_NOTIFYVKPROCESSKEY用

    int OPT_xLoc;               // ウィンドウ初期位置
    int OPT_yLoc;               // 〃
    int OPT_offHide;            // OFF 時にウィンドウ非表示
    int OPT_followCaret;        // カーソル追従
    int OPT_displayHelpDelay;   // 仮想鍵盤表示待ち時間(ms)

    int OPT_hardBS;             // BS で常に文字を消去
    int OPT_weakBS;             // BS で1ストロークだけ戻る
    int OPT_useCtrlKey;         // C-h などを BS などとして扱う
    int OPT_useTTCode;          // 三枚表 T-Code スタイルの文字ヘルプ
    int OPT_win95;              // win95 でのフォントのずれの補正
    char *OPT_offResetModes;    // 各種モードをリセット
    int OPT_strokeTimeOut;      // 打鍵が取り消されるまでの待ち時間(ms)

    //<record>
    // 記録用
    struct KWRECORD {
        char *OPT_record;       // kwrecord.txt ファイル名
        int nchar;              // 総直接入力文字数
        int nstroke;            // 総ストローク数
        int nbushu;             // 部首合成で入力した文字数
        int nmaze;              // 交ぜ書きで入力した文字数
        int nspecial;           // 特殊機能の使用回数
    } record;
    void recordSetup(const char *);
    void recordOutput();

    // 統計用
    struct KWSTAT {
        char *OPT_stat;         // kwstat.txt ファイル名
        StatMap map;
    } stat;
    void statSetup(const char *);
    void statOutput();
    void statCount(MOJI, int);
    void statCount(MOJI, int, int);
    //</record>

    /* モード類
     * --------
     * mode
     * ----
     * 主モード
     * - OFF    : OFF
     * - NORMAL : 通常のストローク入力。ミニバッファ入力も含む
     * - CAND   : 交ぜ書きの候補選択モード
     * - HIST   : ヒストリ入力 (ヒストリの候補選択モード)
     *
     * helpMode, helpModeSave
     * ----------------------
     * 文字ヘルプを表示するかどうか。
     * 文字ヘルプは、通常 mode == NORMAL 時にだけ発動する。
     *
     * hanzenMode, hirakataMode, punctMode
     * -----------------------------------
     * mode == NORMAL 時において、ストローク漢字変換した文字を、それぞれ、
     * ひらがな/かたかな変換、半角/全角変換、句読点変換するかどうか。
     */
    enum MODE { OFF, NORMAL, CAND, CAND1, HIST };
    MODE mode;
    int helpMode;
    int helpModeSave;
    int hanzenMode;
    int hirakataMode;
    int punctMode;
    //int hankanaMode;
    int maze2ggMode;

    /* ストローク入力の状態
     * --------------------
     * - currentBlock   : 変換テーブルの現在位置を示すポインタ。
     * - currentStroke  : 現在までのキーストロークを保持するベクタ。
     * - currentShift   : 現在までのストローク列にシフト打鍵があったか。
     * - lockedBlock      : ストロークロック機能で一時的にTCode::tableの代わりになるポインタ。
     * - lockedStroke     : ストロークロック機能でロックしたストローク。
     * - inputtedStroke   : displayHelpDelay でディレイ中の表示に使うストローク。
     */
    ControlBlock *currentBlock;
    std::vector<STROKE> *currentStroke;
    int currentShift;
    ControlBlock *lockedBlock;
    std::vector<STROKE> *lockedStroke;
    std::vector<STROKE> *inputtedStroke;

    /* 入力・変換用バッファ
     * --------------------
     * - preBuffer  : ストローク漢字変換した文字を一時的に保持するバッファ。
     *                必要に応じて、部首合成・交ぜ書き変換が行われた後、
     *                アプリケーションに出力される。
     * - postBuffer : アプリケーションに出力された (最近の) 文字を保持。
     *                後置型の変換で使用する。TableWindow::output() だけで更新。
     * - postDelete : 後置型の変換で、遅延デリートする文字数。
     * - helpBuffer : 文字ヘルプの対象となる文字 (補助変換で入力したもの) を
     *                保持するバッファ。
     * - helpOffset : helpBuffer 内で、現在文字ヘルプを表示する文字を指す。
     */
    MojiBuffer *preBuffer;
    MojiBuffer *postBuffer;
    int postDelete;
    //<v127c - postInPre>
    int postInPre;
    //</v127c>
    MojiBuffer *helpBuffer;
    int helpOffset;

    /* 交ぜ書き変換
     * ------------
     *
     * candOrder[], candSkip
     * ---------------------
     * 交ぜ書き変換の候補選択のキーの優先順位、および、
     * 前候補群/次候補群のスキップ量。tcode.c での定義を参照。
     *
     * currentCand, candOffset
     * -----------------------
     * 交ぜ書き変換の、現在の読みに対する全候補のベクタ、および、
     * 現在仮想鍵盤に表示している候補群のオフセット。
     *
     * - yomi       : 現在の交ぜ書き変換の読み
     * - yomiLen    : 現在の交ぜ書き変換の読みの長さ
     * - cand       : 選ばれた候補
     */
    static const int candOrder[TC_NKEYS];
    static const unsigned int candSkip;
    std::vector<char *> *currentCand;
    unsigned int candOffset;
    char yomi[TC_BUFFER_SIZE * 2 + 1];
    int yomiLen;
    int okuriLen;
    char *cand;

    /* ヒストリ入力
     * ------------
     * - hist[]     : 現在のヒストリ内の全候補
     * - histRef[]  : 各ヒストリ候補の参照ビット
     * - histPtr    : 直前に追加されたヒストリ候補の位置
     */
    char *hist[TC_NHIST];
    int histRef[TC_NHIST];
    int histPtr;

    /* 熟語ガイド、強制練習モード、外字自動割り振り
	 */
    std::vector<char *> *ggCand;
    int ggCHeaderLen;  // 入力済みとする文字数
    int ggCStart;  // preBuffer or postBufferでの変換結果開始位置
                   // ex. preBuffer == "◇一", [報方] → ggCStart == 1
                   //     preBuffer == "", postBuffer == "...一", [報方] → ggCStart == -1
    int ittaku;  // 一択
    char *explicitGG;
    MojiBuffer *assignedsBuffer;

    /* 仮想鍵盤
     * --------
     * - vkbFace[]  : 仮想鍵盤の各キーのフェイス
     * - vkbFG[]    : 仮想鍵盤の各キーの前景色。上記 TC_FG_* を参照。
     * - vkbBG[]    : 仮想鍵盤の各キーの背景色。上記 TC_BG_* を参照。
     * - waitKeytop : displayHelpDelay 経過前かどうか
     */
    char *vkbFace[TC_NKEYS*2];
    int vkbFG[TC_NKEYS*2];
    int vkbBG[TC_NKEYS];
    int vkbCorner[TC_NKEYS];
    int waitKeytop;

    /* コンストラクタとデストラクタ
     */
    //<v127a - gg>
    //TCode(int *, ControlBlock *, MgTable *, BushuDic *);
    TCode(int *, ControlBlock *, MgTable *, BushuDic *, GgDic *);
    //</v127a - gg>
    ~TCode();

    /* リセット
     */
    void reset();
    void resetBuffer();
    void lockStroke();
    void unlockStroke();

    /* キー入力
     * --------
     * NORMAL, CAND, HIST の各モードに対応する、キー入力処理ルーチン
     */
    void keyinNormal(int);
    void keyinCand(int);
    void keyinCand1(int);
    void keyinHist(int);

    /* バッファ管理
     * ------------
     * - postBufferDeleted()    : postBufferの末尾からpop()した（アプリにBackspaceを送った）とき。
     * - postBufferCount()      : preBufferの内容をpostBufferへ転送した（アプリに文字列を送った）とき。
     */
    void postBufferDeleted(int);
    void postBufferCount(int);

    /* 補助変換
     * --------
     * いずれも、preBuffer の内容に関するもの。
     * - isReducibleByBushu()   : 部首合成変換を実行すべき内容かどうか。
     * - isReducibleByMaze()    : 交ぜ書き変換を実行すべき内容かどうか。
     * - reduceByBushu()        : 部首合成変換を実行。
     * - reduceByMaze()         : 交ぜ書き変換を実行。
     * - nfer()                 : 無変換で確定。
     * - nferHirkata()          : ひらがな/かたかな変換を行い、確定。
     * - isComplete()           : 部首合成や交ぜ書き変換が完了したかどうか。
     */
    int isReducibleByBushu();
    int isReducibleByMaze();
    void reduceByBushu();
    void reduceByMaze();
    void finishCand(char *);
    void makeMazeYomiLonger();
    void makeMazeYomiShorter();
    void nfer();
    void nferHirakata();
    int isComplete();
    //<v127c - postInPre>
    void cancelPostInPre(int);
    //</v127c>

    void setCandGGHeader();
    void goCandGG();  // finishCand()相当
    void makeCandGG();  // output()後に呼ぶ
    void clearCandGG();
    int ggCInputted();

    /* 文字ヘルプ
     * ----------
     * 補助変換で入力した文字のうち、文字ヘルプの対象にすべきものだけを、
     * helpBuffer に追加する関数。
     * と、その下請け。
     */
    void addToHelpBuffer(MOJI);
    void addToHelpBufferMaybe(MOJI);
    void addToHelpBufferMaybe(char *, char *);

    /* ヒストリ入力
     * ------------
     * 補助変換で入力した文字のうち、ヒストリに残すべきものだけを、
     * hist に追加する関数。
     * ヒストリに残すべき文字の条件は、関数の定義を参照。
     */
    void addToHistMaybe(char *);
    void addToHistMaybe(MOJI);

    /* 文脈依存準備処理 (熟語ガイド等)
     */
    void updateContext();
    //<v127a - gg>
    //<gg-defg>
    //void makeGG(MOJI *);
    void makeGG(char *strGG, int start = 0, int protectOnConflict = 0);
    //</gg-defg>
    void clearGG(ControlBlock *);
    //</v127a - gg>/
    void assignStroke(char *);
    void assignStroke(MOJI);
    void clearAssignStroke();

    /* 仮想鍵盤
     * --------
     * - makeVKB()      : 仮想鍵盤を作成。
     *                    各キーのフェイス・前景色・背景色を設定。
     * - makeVKBBG()    : makeVKB の下請け。
     *                    ストロークに従って各キーの背景色を設定。
     */
    void makeVKB(bool unlock = false);
    void makeVKBBG(vector<STROKE> *);
    void makeVKBBG(STROKE *);

    //<v127a - shiftcheck>
    /* isShiftKana[]をセットする */
    bool checkShiftKana(ControlBlock *block);
    //</v127a - shiftcheck>
    void checkShiftSeq(ControlBlock *block);
};

// -------------------------------------------------------------------
#endif // TCODE_H

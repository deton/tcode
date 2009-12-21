#include "table_window.h"
#include "debug.h"
// -------------------------------------------------------------------

//BOOL CALLBACK CtlProc(HWND, UINT, WPARAM, LPARAM);

// -------------------------------------------------------------------
// �R���X�g���N�^
TableWindow::TableWindow(HINSTANCE i) {
    hFont = 0;
    hLFont = 0;
    instance = i;
    tc = 0;
}

// -------------------------------------------------------------------
// �f�X�g���N�^
TableWindow::~TableWindow() {
    DeleteObject(hFont);
    DeleteObject(hLFont);
    delete(tc);
}

// -------------------------------------------------------------------
// window procedure
int TableWindow::wndProc(HWND w, UINT msg, WPARAM wp, LPARAM lp) {
    // window handle �� message �̈���������Ă���
    hwnd = w;
    wParam = wp;
    lParam = lp;

    // �e���b�Z�[�W�� handler ���Ă�
    switch (msg) {
    case WM_CREATE:
        return handleCreate();

    case WM_PAINT:
        return handlePaint();

    case WM_LBUTTONUP:          // ���N���b�N�� ON/OFF
        wParam = ACTIVE_KEY;
        return handleHotKey();

    case WM_RBUTTONUP:          // �E�N���b�N�Ńo�[�W�������
                                // ���O�Ƃ�������Ă邯��
        return handleLButtonDown();

    case WM_DESTROY:
        return handleDestroy();

    //<record>
    case WM_QUERYENDSESSION:    // Windows �̏I���I�v�V�����I����
        if (tc != 0) {
            tc->recordOutput();
            tc->statOutput();
        }
        return TRUE;
    //</record>

    case KANCHOKU_ICONCLK:
        if (lParam == WM_LBUTTONDOWN) {
            wParam = ACTIVE_KEY;
            return handleHotKey();
        }
        return 0;

    case WM_HOTKEY:
        return handleHotKey();
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/* -------------------------------------------------------------------
 * �N���Ƒҋ@
 */

// -------------------------------------------------------------------
// �N��
void TableWindow::activate() {
    // �A�C�R��
    nid.hIcon = LoadIcon(instance, "kanmini1");
    Shell_NotifyIcon(NIM_MODIFY, &nid);

    // �\������
    //<hideOnStartup>
    //if (tc->OPT_offHide == 1) {
    if (tc->OPT_offHide != 2 && !IsWindowVisible(hwnd)) {
    //</hideOnStartup>
        ShowWindow(hwnd, SW_SHOWNA);
    }
    //<v127c - offHide2>
    // offHide=2 �̎��� (�Ƃ肠����) �\�����Ȃ�
    //</v127c>

    hotKeyMode = NORMAL;
    // HotKey �̊��t
    for (int i = 0; i < TC_NKEYS; i++) {
        RegisterHotKey(hwnd, i, 0, tc->vkey[i]);
    }
    // HotKey �̊��t (�V�t�g�Ō�)
    if (tc->OPT_shiftKana != 0) {
        for (int i = 0; i < TC_NKEYS; i++) {
            //<v127a - shiftcheck>
            //RegisterHotKey(hwnd, TC_SHIFT(i), MOD_SHIFT, tc->vkey[i]);
            if (tc->isShiftKana[i])
                RegisterHotKey(hwnd, TC_SHIFT(i), MOD_SHIFT, tc->vkey[i]);
            //</v127a - shiftcheck>
        }
    }

    RegisterHotKey(hwnd, ESC_KEY, 0, VK_ESCAPE);
    RegisterHotKey(hwnd, BS_KEY,  0, VK_BACK);
    RegisterHotKey(hwnd, RET_KEY, 0, VK_RETURN);
    RegisterHotKey(hwnd, TAB_KEY, 0, VK_TAB);
    if (tc->OPT_useCtrlKey) {
        RegisterHotKey(hwnd, CG_KEY, MOD_CONTROL, 'G');
        RegisterHotKey(hwnd, CH_KEY, MOD_CONTROL, 'H');
        RegisterHotKey(hwnd, CM_KEY, MOD_CONTROL, 'M');
        RegisterHotKey(hwnd, CJ_KEY, MOD_CONTROL, 'J');
        RegisterHotKey(hwnd, CI_KEY, MOD_CONTROL, 'I');
    }

    // �ʏ탂�[�h�ɂ���
    tc->mode = TCode::NORMAL;
    tc->preBuffer->clear();
    tc->postBuffer->clear();   //  ��u�^���������ϊ��p�̃o�b�t�@���N���A
    tc->helpMode = 0;          // �w���v��\��
}

// -------------------------------------------------------------------
// �ҋ@
void TableWindow::inactivate() {
    // �A�C�R��
    nid.hIcon = LoadIcon(instance, "kanmini0");
    Shell_NotifyIcon(NIM_MODIFY, &nid);

    // �B��
    //<v127c - offHide2>
    //if (tc->OPT_offHide == 1) {
    // offHide=2 �����B��
    if (tc->OPT_offHide) {
    //</v127c>
        ShowWindow(hwnd, SW_HIDE);
    }

    if (tc->OPT_conjugationalMaze == 2) setMazeHotKey(0);
    hotKeyMode = OFF;
    // HotKey �̉��
    for (int i = 0; i < TC_NKEYS; i++) {
        UnregisterHotKey(hwnd, i);
    }
    // HotKey �̉�� (�V�t�g�Ō�)
    if (tc->OPT_shiftKana != 0) {
        for (int i = 0; i < TC_NKEYS; i++) {
            //<v127a - shiftcheck>
            //UnregisterHotKey(hwnd, TC_SHIFT(i));
            if (tc->isShiftKana[i])
                UnregisterHotKey(hwnd, TC_SHIFT(i));
            //</v127a - shiftcheck>
        }
    }
    UnregisterHotKey(hwnd, ESC_KEY);
    UnregisterHotKey(hwnd, BS_KEY);
    UnregisterHotKey(hwnd, RET_KEY);
    UnregisterHotKey(hwnd, TAB_KEY);
    if (tc->OPT_useCtrlKey) {
        UnregisterHotKey(hwnd, CG_KEY);
        UnregisterHotKey(hwnd, CH_KEY);
        UnregisterHotKey(hwnd, CM_KEY);
        UnregisterHotKey(hwnd, CJ_KEY);
        UnregisterHotKey(hwnd, CI_KEY);
    }

    // �ʏ탂�[�h�ɂ���
    tc->mode = TCode::NORMAL;
    tc->mode = TCode::OFF;
}

// -------------------------------------------------------------------
// Esc��Bs�ACtrl-H�Ȃ�
//void TableWindow::setSpecialHotKey() {
//    if((tc->table == tc->currentBlock) &&
//       (tc->mode == TCode::NORMAL)) {
//        UnregisterHotKey(hwnd, ESC_KEY);
//        UnregisterHotKey(hwnd, BS_KEY);
//        UnregisterHotKey(hwnd, RET_KEY);
//        UnregisterHotKey(hwnd, TAB_KEY);
//    } else {
//        RegisterHotKey(hwnd, ESC_KEY, 0, VK_ESCAPE);
//        RegisterHotKey(hwnd, BS_KEY, 0, VK_BACK);
//        RegisterHotKey(hwnd, RET_KEY, 0, VK_RETURN);
//        RegisterHotKey(hwnd, TAB_KEY, 0, VK_TAB);
//    }
//}

void TableWindow::setMazeHotKey(int onoff) {
    if (!onoff) {
        if (hotKeyMode != EDITCLAUSE) return;
        hotKeyMode = NORMAL;
        if (tc->OPT_shiftKana == 0 || !tc->isShiftKana[tc_lt_key])
            UnregisterHotKey(hwnd, TC_SHIFT(tc_lt_key));
        if (tc->OPT_shiftKana == 0 || !tc->isShiftKana[tc_gt_key])
            UnregisterHotKey(hwnd, TC_SHIFT(tc_gt_key));
    } else {
        if (hotKeyMode == EDITCLAUSE) return;
        hotKeyMode = EDITCLAUSE;
        if (tc->OPT_shiftKana == 0 || !tc->isShiftKana[tc_lt_key])
            RegisterHotKey(hwnd, TC_SHIFT(tc_lt_key), MOD_SHIFT, tc->vkey[tc_lt_key]);
        if (tc->OPT_shiftKana == 0 || !tc->isShiftKana[tc_gt_key])
            RegisterHotKey(hwnd, TC_SHIFT(tc_gt_key), MOD_SHIFT, tc->vkey[tc_gt_key]);
    }
}

// -------------------------------------------------------------------
// �^�C�g���o�[�̕������Z�b�g
void TableWindow::setTitleText() {
    //<multishift2>
    char str[256];
    sprintf(str, "������");
    if (tc->dirTable[DIR_table_name]) {
        strcat(str, " ");
        strcat(str, tc->dirTable[DIR_table_name]);
    }
    //</multishift2>
    if (tc->mode == TCode::OFF) {
        //<multishift2>
        //SetWindowText(hwnd, "������ - OFF");
        strcat(str, " - OFF");
        SetWindowText(hwnd, str);
        //</multishift2>
    } else {
        //<multishift2>
        ///char str[256];
        //strcpy(str, "������ - ON");
        strcat(str, " - ON");
        //</multishift2>
        if (tc->hirakataMode || tc->hanzenMode || tc->punctMode) {
            strcat(str, " [");
            //<hankana>
            //strcat(str, (tc->hirakataMode ? "�A" : "�\"));
            //strcat(str, (tc->hanzenMode   ? "�S" : "�\"));
            //strcat(str, (tc->punctMode    ? "��" : "�\"));
            strcat(str, (tc->hirakataMode ? "�J�i" : "�\�\"));
            strcat(str, "|");
            strcat(str, (tc->hanzenMode   ? "�S��" : "�\�\"));
            strcat(str, "|");
            strcat(str, (tc->punctMode    ? "���" : "�\�\"));
            //</hankana>
            strcat(str, "]");
        }
        SetWindowText(hwnd, str);
    }
}

/* -------------------------------------------------------------------
 * ���b�Z�[�W�n���h��
 */

// -------------------------------------------------------------------
// WM_CREATE
int TableWindow::handleCreate() {
    // T-Code �ϊ���̏�����
    initTC();

    // �^�X�N�g���C�ɓo�^
    //NOTIFYICONDATA nid;
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 0;
    nid.uFlags = 7; // NIF_ICON | NIF_MESSAGE | NIF_TIP
    nid.uCallbackMessage = KANCHOKU_ICONCLK;
    nid.hIcon = LoadIcon(instance, "kanmini0");
    strcpy(nid.szTip, "������");
    Shell_NotifyIcon(0 /* NIM_ADD */, &nid);

    // �O�g�̑傫�����擾
    RECT winRect;
    GetWindowRect(hwnd, &winRect);

    // ���g�̑傫�����擾
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);

    // ����̍��W���擾
    int sX = winRect.left;
    int sY = winRect.top;

    // �O�g�ƒ��g�̍����擾
    int dX = (winRect.right - winRect.left)
        - (clientRect.right - clientRect.left);
    int dY = (winRect.bottom - winRect.top)
        - (clientRect.bottom - clientRect.top);

    // �傫�����X�V
    if (tc->OPT_xLoc != -1) { sX = tc->OPT_xLoc; }
    if (tc->OPT_yLoc != -1) { sY = tc->OPT_yLoc; }
    MoveWindow(hwnd, sX, sY, WIDTH + dX, HEIGHT + dY, TRUE);

    // �t�H���g��ݒ�
    LOGFONT lf;
    lf.lfHeight = CHAR_SIZE;
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = 0;
    lf.lfItalic = 0;
    lf.lfUnderline = 0;
    lf.lfStrikeOut = 0;
    lf.lfCharSet = SHIFTJIS_CHARSET;
    lf.lfOutPrecision = 0;
    lf.lfClipPrecision = 0;
    lf.lfQuality = 0;
    lf.lfPitchAndFamily = 0;
    strcpy(lf.lfFaceName, "�l�r �S�V�b�N");
    hFont = CreateFontIndirect(&lf);

    // �傫���t�H���g��ݒ�
    lf.lfHeight = LARGE_CHAR_SIZE;
    hLFont = CreateFontIndirect(&lf);

    //<v127c>
    // [�A�K�X��2:537-538]
    // �g���F���p���b�g�ɗp�ӂ��Ă���
    // !!! see also table_window.h
    COLORREF palent[] = {
//        COL_ON_LN,
//        COL_ON_K1,
//        COL_ON_K2,
//        COL_ON_M1,
//        COL_ON_M2,
//        COL_OFF_LN,
//        COL_OFF_K1,
//        COL_OFF_M1,
        COL_BLACK       ,
        COL_WHITE       ,
        COL_GRAY        ,
        COL_LT_GRAY     ,
        COL_LT_RED      ,
        COL_LT_GREEN    ,
        COL_LT_BLUE     ,
        COL_LT_YELLOW   ,
        COL_LT_CYAN     ,
        COL_RED         ,
        COL_DK_CYAN     ,
        COL_DK_MAGENTA  ,
        (COLORREF)-1
    };
    int i, n;
    for (n=0; palent[n]!=(COLORREF)-1; n++) ;
    char *work = new char[sizeof (LOGPALETTE) + (n-1) * sizeof (PALETTEENTRY)];
    LOGPALETTE *lpPalette = (LOGPALETTE *)work;
    lpPalette->palVersion = 0x0300;
    lpPalette->palNumEntries = n;
    for (i=0; i < n; i++) {
      lpPalette->palPalEntry[i].peRed = GetRValue(palent[i]);
      lpPalette->palPalEntry[i].peGreen = GetGValue(palent[i]);
      lpPalette->palPalEntry[i].peBlue = GetBValue(palent[i]);
      lpPalette->palPalEntry[i].peFlags = NULL;
    }
    hPalette = CreatePalette(lpPalette);
    delete [] work;
    //</v127c>

    // �N���̂��߂� HotKey ��o�^
    //<OKA> support unmodified hot key
    if (tc->OPT_hotKey)
        RegisterHotKey(hwnd, ACTIVE_KEY, MOD_CONTROL, tc->OPT_hotKey);
    if (tc->OPT_unmodifiedHotKey)
        RegisterHotKey(hwnd, ACTIVE2_KEY, 0, tc->OPT_unmodifiedHotKey);
    //</OKA>

    // �ҋ@��Ԃ�
    inactivate();

    return 0;
}

// -------------------------------------------------------------------
// WM_DESTROY
int TableWindow::handleDestroy() {

    inactivate();               // �ҋ@��Ԃɂ���
    //<OKA> support unmodified hot key
    if (tc->OPT_hotKey)
        UnregisterHotKey(hwnd, ACTIVE_KEY); // HotKey ���폜
    if (tc->OPT_unmodifiedHotKey)
        UnregisterHotKey(hwnd, ACTIVE2_KEY); // HotKey ���폜
    //</OKA>

    //<record>
    // �L�^���o��
    tc->recordOutput();

    // ���v���o��
    tc->statOutput();
    //</record>

    //<v127c>
    DeleteObject(hPalette);
    //</v127c>
    if (lpfnMyEndHook) {
        lpfnMyEndHook();
        FreeLibrary(hKanCharDLL);
        RemoveProp(hwnd, "KanchokuWin_KanCharDLL_NextHook");
    }

    // �^�X�N�g���C����폜
    NOTIFYICONDATA nid;
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 0;
    Shell_NotifyIcon(2 /* NIM_DELETE */, &nid);

    // �I��
    PostQuitMessage(0);
    return 0;
}

// -------------------------------------------------------------------
// WM_LBUTTONDOWN
int TableWindow::handleLButtonDown() {
    char s[1024];
    sprintf(s,
            "������ %s\n"
            "\n"
            "    �L�[�{�[�h  %s\n"
            "    �e�[�u��  %s\n"
            "    ���񍇐�  %s\n"
            //<v127a - gg>
            //"    ��������  %s",
            "    ��������  %s\n"
            "    �n��K�C�h  %s",
            //</v127a - gg>
            VERSION,
            tc->OPT_keyboard,
            tc->OPT_tableFile,
            (tc->OPT_bushu ? tc->OPT_bushu : "(���g�p)"),
            //<v127a - gg>
            //(tc->OPT_mazegaki ? tc->OPT_mazegaki : "(���g�p)"));
            (tc->OPT_mazegaki ? tc->OPT_mazegaki : "(���g�p)"),
            (tc->OPT_gg ? tc->OPT_gg : "(���g�p)"));
            //</v127a - gg>
    MessageBoxEx(hwnd,
                 s,
                 "�o�[�W�������",
                 MB_OK | MB_ICONINFORMATION, LANG_JAPANESE);

    //DialogBox(instance, "ControlBox", hwnd, CtlProc);
    return 0;
}

// -------------------------------------------------------------------
// WM_PAINT
int TableWindow::handlePaint() {
    PAINTSTRUCT ps;
    HDC hdc;

    // �`��J�n
    hdc = BeginPaint(hwnd, &ps);
    //<v127c>
    // �p���b�g���g�p
    SelectPalette(hdc, hPalette, FALSE);
    RealizePalette(hdc);
    //</v127c>
    // �^�C�g��������ݒ�
    setTitleText();

    // OFF ��
    if (tc->mode == TCode::OFF) {
        drawFrameOFF(hdc);
        goto END_PAINT;
    }

    // �����w���v�\�����[�h
    if (tc->helpMode) {
        drawFrame50(hdc);
        MojiBuffer mb(4);
        mb.clear(); mb.pushSoftN("�@", 2); // XXX �S�p�󔒂��l�߂�
        mb.pushSoft(tc->helpBuffer->moji(tc->helpOffset));
        drawMiniBuffer(hdc, 4, COL_LT_YELLOW, &mb);
        drawVKB50(hdc);
        goto END_PAINT;
    }

    // �q�X�g�����̓��[�h
    if (tc->mode == TCode::HIST) {
        drawFrame10(hdc);
        drawMiniBuffer(hdc, 5, COL_LT_BLUE, tc->preBuffer);
        drawVKB10(hdc);
        goto END_PAINT;
    }

    // �B����\�����[�h
    if (tc->mode == TCode::CAND1) {
        drawFrame10(hdc);
        MojiBuffer mb(strlen((*tc->currentCand)[0])+tc->okuriLen);
        mb.pushSoft((*tc->currentCand)[0]);
        if (tc->okuriLen) mb.pushSoft(tc->preBuffer->string(-tc->okuriLen));
        int ov = mb.length() - 5;
        if (ov > 0) mb.popN(ov);
        drawMiniBuffer(hdc, 5, COL_LT_BLUE, &mb);
        drawVKB10(hdc);
        goto END_PAINT;
    }

    // �������\�����[�h
    if (tc->mode == TCode::CAND && tc->currentCand->size() <= 10) {
        drawFrame10(hdc);
        drawMiniBuffer(hdc, 5, COL_LT_BLUE, tc->preBuffer);
        drawVKB10(hdc);
        goto END_PAINT;
    }

    // �������\�����[�h
    if (tc->mode == TCode::CAND && 10 < tc->currentCand->size()) {
        drawFrame50(hdc);
        drawMiniBuffer(hdc, 4, COL_LT_BLUE, tc->preBuffer);
        drawVKB50(hdc);
        goto END_PAINT;
    }

    // �ʏ���̓��[�h
    if (tc->mode == TCode::NORMAL) {
        drawFrame50(hdc);
        if (0 < tc->preBuffer->length()) {
            drawMiniBuffer(hdc, 4, COL_LT_GREEN, tc->preBuffer);
        }
        drawVKB50(hdc);
        goto END_PAINT;
    }

    // �`��I��
 END_PAINT:
    EndPaint(hwnd, &ps);
    return 0;
}

// -------------------------------------------------------------------
// WM_HOTKEY
int TableWindow::handleHotKey() {
    int key = wParam;

    // ON/OFF
    if (key == ACTIVE_KEY || key == ACTIVE2_KEY) { //<OKA> support unmodified hot key
        tc->reset();
        tc->preBuffer->clear();
        tc->postBuffer->clear();
        //<v127c - postInPre>
        tc->postInPre = 0;
        tc->postDelete = 0;
        //</v127c>
        if (tc->mode == TCode::OFF) {
            tc->mode = TCode::NORMAL;
            activate();
        } else {
            tc->mode = TCode::OFF;
            inactivate();
        }
        goto DRAW;
    }

    /* ---------------------------------------------------------------
     * ����
     */
    if (hotKeyMode == EDITCLAUSE) {
        if (key == TC_SHIFT(tc_lt_key)) key = LT_KEY;
        if (key == TC_SHIFT(tc_gt_key)) key = GT_KEY;
    }
    switch (tc->mode) {
    case TCode::NORMAL: tc->keyinNormal(key); break;
    case TCode::CAND:   tc->keyinCand(key);   break;
    case TCode::CAND1:  tc->keyinCand1(key);  break;
    case TCode::HIST:   tc->keyinHist(key);   break;
    default:                    // �����ɂ͗��Ȃ��͂�����
        goto DRAW; break;
    }

    /* ---------------------------------------------------------------
     * �ϊ�
     */
    int check;
    do {
        check = 0;
        while (tc->isReducibleByBushu()) { tc->reduceByBushu(); check = 1; }
        while (tc->isReducibleByMaze())  { tc->reduceByMaze();  check = 1; }
    } while (check != 0);

    if (tc->OPT_conjugationalMaze == 2) {
        setMazeHotKey(tc->mode == TCode::CAND || tc->mode == TCode::CAND1);
    }
    /* ---------------------------------------------------------------
     * �o��
     */
    output();

    /* ---------------------------------------------------------------
     * �`��
     */
 DRAW:
    //<v127c - offHide2>
    // offHide=2 - �⏕�@�\���p���ȊO�͉��z���Ղ��\��
    // * �\��   - �⏕�ϊ��E���I���E�����w���v�E�q�X�g������
    // * ��\�� - �ʏ�̃X�g���[�N����
    if (tc->OPT_offHide == 2) {
        if (tc->mode == TCode::OFF
            || tc->mode == TCode::NORMAL
            && tc->helpMode == 0    // helpMode �� mode �͓Ɨ�
            && tc->preBuffer->length() == 0) { // �⏕�ϊ����łȂ�
            ShowWindow(hwnd, SW_HIDE);
        } else {
            ShowWindow(hwnd, SW_SHOWNA);
        }
    }
    //</v127c>

    // ���z���Ղ��쐬
    tc->makeVKB();

    // �^�C�g����������X�V
    //setTitleText();

    // window���������� (�����ŉ��z���Ղ�\��)
    //<v127c>
    // [�A�K�X��2:517] �L�[���s�[�g���̖��
    //RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
    InvalidateRect(hwnd, NULL, TRUE);
    //</v127c>

    return 0;
}

/* -------------------------------------------------------------------
 * T-Code �֘A
 */

/* -------------------------------------------------------------------
 * initTC()
 * --------
 * �ݒ�t�@�C�� (kanchoku.ini) ����I�v�V������ǂ݂��݁A
 * T-Code �ϊ���𐶐�����B
 *
 * �I�v�V�����ꗗ - �f�t�H���g�l�ƈӖ�
 * -----------------------------------
 *
 * �t�@�C�� kanchoku.ini �� kanchoku �Z�N�V�����Ɏw�肷��I�v�V����
 *
 * - hotKey=<xx>            dc (C-\)    ON/OFF �̃L�[ (���z�L�[�R�[�h)
 * - unmodifiedHotKey=<xx>  (���w��)    ���C���̃z�b�g�L�[ <v127d/>
 * - keyboard="file"        106.key     �L�[�{�[�h��`�t�@�C��
 * - tableFile="file"       t.tbl       �e�[�u����`�t�@�C��
 *
 * - bushu="file"           (���w��)    ���񍇐������t�@�C�� (���w��ŕs�g�p)
 * - bushuAlgo={OKA,YAMANOBE}
 *                          (���w��)    ���񍇐��ϊ��A���S���Y�� (���w�� = OKA)
 * - mazegaki="file"        (���w��)    �������������t�@�C�� (���w��ŕs�g�p)
 * - conjugationalMaze=[012]
 *                          1           ���p����ꊲ�̓ǂ݂ŕϊ�
 * - gg="file"              (���w��)    �n��⊮�����t�@�C�� (���w��ŕs�g�p)
 *
 * - record="file"          (���w��)    ���͋L�^�̃t�@�C��
 * - stat="file"            (���w��)    ���͕����̓��v�̃t�@�C��
 *
 * - shiftKana=[01]         0           �V�t�g�Ō��łЂ炪��/�������ȕϊ�
 * - enableHankakuKana=[01] 0           �S/�����[�h���ɔ��p�������ȕϊ�
 * - outputMethod=[012]     0           �����̑��o���@
 *                                      - 0 (WM_CHAR)
 *                                      - 1 (WM_IME_CHAR)
 *                                      - 2 (WM_KANCHOKU_CHAR)
 *                                      -   (�t�b�N + ImmSetCompositionString)
 *                                      �A�v�����Ƃ̐ݒ���� (manual �Q��)
 * - useWMIMECHAR=[012]     0           outputMethod �̓��l (����݊�)
 * - outputSleep=n          0           ���z�L�[�� output ����Ƃ��� Sleep ��
 *
 * - xLoc=<n>               -1          �E�B���h�E�����ʒu (-1 �Ŗ��w��)
 * - yLoc=<n>               -1          �V
 * - offHide=[01]           0           OFF ���ɃE�B���h�E��\��
 *                                      //<v127c - offHide2>
 *                                      =2 �w��͒ʏ���͎�����\��
 *                                      //</v127c>
 * - followCaret=[01]       0           �E�B���h�E���J�[�\���ɒǏ]
 *
 * - hardBS=[01]            0           BS �͏�� (���Ō��ł�) ����������
 * - useCtrlKey=[01]        0           �Ⴆ�� C-h �� BS �Ƃ��Ĉ����Ȃ�
 * - useTTCode=[01]         0           �O���\ T-Code �X�^�C���̕����w���v
 * - win95=[01]             0           Windows95 �ł̃t�H���g�̂����␳
 */
void TableWindow::initTC() {
    // �ݒ�t�@�C�����J��
    char iniFile[MAX_PATH + 1];
    GetCurrentDirectory(sizeof(iniFile), iniFile);
    strcat(iniFile, "\\kanchoku.ini");

    ifstream *is = new ifstream();

    /* ---------------------------------------------------------------
     * ���͕����֘A
     */
    // hotkey
    char hotKey[255];
    GetPrivateProfileString("kanchoku", "hotkey", "dc",
                            hotKey, sizeof(hotKey), iniFile);
    int OPT_hotKey = (int)strtol(hotKey, NULL, 16);
    //<OKA> support unmodified hot key
    GetPrivateProfileString("kanchoku", "UnmodifiedHotKey", "",
                            hotKey, sizeof(hotKey), iniFile);
    int OPT_unmodifiedHotKey = (int)strtol(hotKey, NULL, 16);
    //</OKA>
    //<OKA> support unmodified hot key
    if (OPT_hotKey == 0 && OPT_unmodifiedHotKey == 0) {
        error("�uhotkey|unmodifiedHotKey=(16 �i�L�[�R�[�h)�v�̐ݒ肪�܂������Ă���悤�ł�");
    }
    //</OKA>

    // keyboard file
    char keyFile[255];      // �L�[�{�[�h�t�@�C����
    GetPrivateProfileString("kanchoku", "keyboard", "106.key",
                            keyFile, sizeof(keyFile), iniFile);
    if (keyFile[0] == 0) {
        error("�ukeyboard=(�t�@�C����)�v�̐ݒ肪�܂������Ă���悤�ł�");
    }

    // table file
    char tableFile[255];    // �e�[�u���t�@�C����
    GetPrivateProfileString("kanchoku", "tablefile", "t.tbl",
                            tableFile, sizeof(tableFile), iniFile);
    if (tableFile[0] == 0) {
        error("�utablefile=(�t�@�C����)�v�̐ݒ肪�܂������Ă���悤�ł�");
    }

    /* ---------------------------------------------------------------
     * �⏕�ϊ��֘A
     */
    // bushu dictionary
    char bushuFile[255];
    GetPrivateProfileString("kanchoku", "bushu", "",
                            bushuFile, sizeof(bushuFile), iniFile);
    int bushuReady;
    if (bushuFile[0] == 0) { bushuReady = 0; }
    else                   { bushuReady = 1; }
    
    // bushu algorithm
    char bushuAlgo[255];
    int OPT_bushuAlgo;
    GetPrivateProfileString("kanchoku", "bushuAlgo", "",
                            bushuAlgo, sizeof(bushuAlgo), iniFile);
    if (bushuAlgo[0] == '\0' ||  // default to OKA algorithm
        stricmp(bushuAlgo, "OKA") == 0) {
        OPT_bushuAlgo = TC_BUSHU_ALGO_OKA;
    } else if (stricmp(bushuAlgo, "YAMANOBE") == 0) {
        OPT_bushuAlgo = TC_BUSHU_ALGO_YAMANOBE;
    } else {
        warn("bushuAlgo �ɂ� OKA, YAMANOBE �̂����ꂩ���w�肵�Ă��������B");
        OPT_bushuAlgo = TC_BUSHU_ALGO_OKA; // �Ƃ肠���� OKA algorithm ��
    }

    // mazegaki dictionary
    char mazegakiFile[255];
    GetPrivateProfileString("kanchoku", "mazegaki", "",
                            mazegakiFile, sizeof(mazegakiFile), iniFile);
    int mazeReady;
    if (mazegakiFile[0] == 0) { mazeReady = 0; }
    else                      { mazeReady = 1; }

    // conjugationalMaze
    int OPT_conjugationalMaze =
        GetPrivateProfileInt("kanchoku", "conjugationalmaze", 1, iniFile);

    //<v127a - gg>
    // gg dictionary
    char ggFile[255];
    GetPrivateProfileString("kanchoku", "gg", "",
                            ggFile, sizeof(ggFile), iniFile);
    int ggReady;
    if (ggFile[0] == 0) { ggReady = 0; }
    else                { ggReady = 1; }
    //</v127a - gg>

    //<gg-defg>
    // defg
    char OPT_defg[255];
    GetPrivateProfileString("kanchoku", "defg", "",
                            OPT_defg, sizeof(OPT_defg), iniFile);
    //</gg-defg>

    //<record>
    // record
    char OPT_record[255];
    GetPrivateProfileString("kanchoku", "record", "",
                            OPT_record, sizeof(OPT_record), iniFile);

    // stat
    char OPT_stat[255];
    GetPrivateProfileString("kanchoku", "stat", "",
                            OPT_stat, sizeof(OPT_stat), iniFile);
    //</record>

    /* ---------------------------------------------------------------
     * �V�t�g�Ō�
     */
    int OPT_shiftKana =
        GetPrivateProfileInt("kanchoku", "shiftkana", 0, iniFile);
        
    /* ---------------------------------------------------------------
     * ���p���ȕϊ�
     */
    int OPT_enableHankakuKana =
        GetPrivateProfileInt("kanchoku", "enableHankakuKana", 
                             0, iniFile);

    /* ---------------------------------------------------------------
     * �o�̓��b�Z�[�W
     */
    // useWMIMECHAR
    int OPT_useWMIMECHAR =
        GetPrivateProfileInt("kanchoku", "usewmimechar", 0, iniFile);
    // outputMethod - useWMIMECHAR �� alias �� useWMIMECHAR ���D��
    // (�Ƃ������A useWMIMECHAR �̕��� OBSOLETE �ɂ���\��)
    char OPT_outputMethod[255];
    GetPrivateProfileString("kanchoku", "outputmethod", "",
                            OPT_outputMethod, sizeof(OPT_outputMethod),
                            iniFile);
    if (OPT_outputMethod[0] != '\0') {
        if (stricmp(OPT_outputMethod, "WMCHAR")  == 0 ||
            stricmp(OPT_outputMethod, "WM_CHAR") == 0 ||
            stricmp(OPT_outputMethod, "0")       == 0) {
            OPT_useWMIMECHAR = OUT_WMCHAR;
        } else if (stricmp(OPT_outputMethod, "WMIMECHAR")   == 0 ||
                   stricmp(OPT_outputMethod, "WM_IME_CHAR") == 0 ||
                   stricmp(OPT_outputMethod, "1")           == 0) {
            OPT_useWMIMECHAR = OUT_WMIMECHAR;
        } else if (stricmp(OPT_outputMethod, "WMKANCHOKUCHAR")   == 0 ||
                   stricmp(OPT_outputMethod, "WM_KANCHOKU_CHAR") == 0 ||
                   stricmp(OPT_outputMethod, "2")                == 0) {
            OPT_useWMIMECHAR = OUT_WMKANCHOKUCHAR;
        } else {
            warn("outputMethod�Ɏw�肳��Ă���l������������܂���B");
            OPT_useWMIMECHAR = OUT_WMCHAR; // �Ƃ肠���� WM_CHAR ��
        }
    }

    int OPT_enableWMKANCHOKUCHAR =
        GetPrivateProfileInt("kanchoku", "enablewmkanchokuchar", 0, iniFile);

    //<v127a - outputsleep>
    // outputSleep
    long OPT_outputSleep =
        GetPrivateProfileInt("kanchoku", "outputSleep", 0, iniFile);
    //</v127a - outputsleep>

    /* ---------------------------------------------------------------
     * �\���֘A
     */
    // offHide
    int OPT_offHide = GetPrivateProfileInt("kanchoku", "offhide", 0, iniFile);

    // xLoc, yLoc
    int OPT_xLoc = GetPrivateProfileInt("kanchoku", "xloc", -1, iniFile);
    int OPT_yLoc = GetPrivateProfileInt("kanchoku", "yloc", -1, iniFile);

    /* ---------------------------------------------------------------
     * �l�I�Ȏ�A����ю����R�[�h
     */
    // hardBS
    int OPT_hardBS = GetPrivateProfileInt("kanchoku", "hardbs", 0, iniFile);

    // useCtrlKkey
    int OPT_useCtrlKey = GetPrivateProfileInt("kanchoku", "usectrlkey", 0,
                                              iniFile);
    // useTTCode
    //<multishift>
    // !!! `useTTCode=1' option in "kanchoku.ini" is now obsolete.
    // !!! Use `#define prefix /*/*/*/*/' directive 
    // !!! in table file ("*.tbl") instead.
    //</multishift>
    int OPT_useTTCode = GetPrivateProfileInt("kanchoku", "usettcode", 0,
                                             iniFile);

    // win95
    int OPT_win95 = GetPrivateProfileInt("kanchoku", "win95", 0, iniFile);

    // followCaret
    int OPT_followCaret =
        GetPrivateProfileInt("kanchoku", "followcaret", 0, iniFile);

    /* ---------------------------------------------------------------
     */
    // �L�[�{�[�h�t�@�C���̓ǂݍ���
    int *vkey;
    vkey = new int[TC_NKEYS];
    FILE *fp = fopen(keyFile, "r");
    if (fp == 0) { error("�L�[�{�[�h�t�@�C�����J���܂���"); }
    for (int i = 0; i < TC_NKEYS; i++) {
        int vCode;
        fscanf(fp, "%x,", &vCode);
        vkey[i] = vCode;
    }
    fclose(fp);

    if (OPT_conjugationalMaze == 2) {
        for (int i = 0; i < TC_NKEYS; i++) {
            if (vkey[i] == 0xbc) tc_lt_key = i;
            if (vkey[i] == 0xbe) tc_gt_key = i;
        }
    }

    // �e�[�u���t�@�C���̓ǂݍ���
    is->open(tableFile, is->nocreate);
    if (is->fail()) { error("�e�[�u���t�@�C�����J���܂���"); }
    // �p�[�Y����
    Parser *parser = new Parser(is, hwnd);
    ControlBlock *table = parser->parse();
    is->close();
    delete(parser);

    // ���񍇐��ϊ������̓ǂݍ��� (�g�p����ꍇ�̂�)
    BushuDic *bushuDic = 0;
    if (bushuReady) {
        is->open(bushuFile,is->nocreate);
        if (is->fail()) {
            warn("���񍇐��ϊ��������J���܂���ł����B\n"
                 "���񍇐��ϊ��̋@�\�͎g���܂���B");
            bushuReady = 0;
        } else {
            bushuDic = new BushuDic;
            bushuDic->readFile(is);
            is->close();
        }
    }

    // �������������̓ǂݍ��� (�g�p����ꍇ�̂�)
    MgTable *mgTable = 0;
    if (mazeReady) {
        is->open(mazegakiFile, is->nocreate);
        if (is->fail()) {
            warn("���������ϊ��������J���܂���ł����B\n"
                 "���������ϊ��̋@�\�͎g���܂���B");
            mazeReady = 0;
        } else {
            mgTable = new MgTable(hwnd);
            mgTable->readFile(is);
            is->close();
        }
    }

    //<v127a - gg>
    // �n��K�C�h�����̓ǂݍ��� (�g�p����ꍇ�̂�)
    GgDic *ggDic = 0;
    if (ggReady) {
        is->open(ggFile, is->nocreate);
        if (is->fail()) {
            warn("�n��K�C�h�������J���܂���ł����B\n"
                 "�n��K�C�h�̋@�\�͎g���܂���B");
            ggReady = 0;
        } else {
            ggDic = new GgDic;
            ggDic->readFile(is);
            is->close();
        }
    }
    //</v127a - gg>

    // T-Code �ϊ���𐶐��E������
    //<v127a - gg>
    //tc = new TCode(vkey, table, mgTable, bushuDic);
    tc = new TCode(vkey, table, mgTable, bushuDic, ggDic);
    //</v127a - gg>
    tc->OPT_hotKey = OPT_hotKey;
    //<OKA> support unmodified hot key
    tc->OPT_unmodifiedHotKey = OPT_unmodifiedHotKey;
    //</OKA>
    tc->bushuReady = bushuReady;
    tc->mazeReady = mazeReady;
    //<v127a - gg>
    tc->ggReady = ggReady;
    //</v127a - gg>

#define STRDUP(dst, src) do {               \
        dst = new char[strlen(src) + 1];    \
        strcpy(dst, src);                   \
    } while (0)
    STRDUP(tc->OPT_keyboard, keyFile);
    STRDUP(tc->OPT_tableFile, tableFile);
    if (bushuReady != 0) { STRDUP(tc->OPT_bushu, bushuFile); }
    if (mazeReady != 0)  { STRDUP(tc->OPT_mazegaki, mazegakiFile); }
    //<v127a - gg>
    if (ggReady != 0)    { STRDUP(tc->OPT_gg, ggFile); }
    //</v127a - gg>
    //<multishift2>
    {
        is->open(tableFile, is->nocreate);
        if (!is->fail()) {
            TCode::readDir(&tc->dirTable, is);
            is->close();
        }
    }
    tc->stTable->setupPref(tc->dirTable[DIR_prefix]);
    //</multishift2>
    //<gg-defg>
    if (OPT_defg[0])     { STRDUP(tc->OPT_defg, OPT_defg); }
    //</gg-defg>
    //<multishift2>
    else if (tc->dirTable[DIR_defguide]) {
        STRDUP(tc->OPT_defg, tc->dirTable[DIR_defguide]);
    }
    //</multishift2>
//#undef STRDUP
    //<record>
    if (OPT_record[0]) {
        tc->recordSetup(OPT_record);
    }
    if (OPT_stat[0]) {
        tc->statSetup(OPT_stat);
    }
    //</record>

	tc->OPT_bushuAlgo = OPT_bushuAlgo;
    tc->OPT_conjugationalMaze = OPT_conjugationalMaze;
    tc->OPT_shiftKana = OPT_shiftKana;
    //<v127a - shiftcheck>
    if (OPT_shiftKana)
        tc->checkShiftKana(tc->table);
    //</v127a - shiftcheck>
    tc->OPT_enableHankakuKana = OPT_enableHankakuKana;
    tc->OPT_useWMIMECHAR = OPT_useWMIMECHAR;
    //<v127a - outputsleep>
    tc->OPT_outputSleep = OPT_outputSleep;
    //</v127a - outputsleep>
    tc->OPT_offHide = OPT_offHide;
    tc->OPT_xLoc = OPT_xLoc;
    tc->OPT_yLoc = OPT_yLoc;
    tc->OPT_hardBS = OPT_hardBS;
    tc->OPT_useCtrlKey = OPT_useCtrlKey;
    //<multishift>
    //tc->OPT_useTTCode = OPT_useTTCode;
    if (OPT_useTTCode) {
        tc->stTable->setupPref("/��/26,23/����/��/:/��/23,26/����/��/");
    }
    //</multishift>
    tc->OPT_win95 = OPT_win95;
    tc->OPT_followCaret = OPT_followCaret;

    WM_KANCHOKU_CHAR = 0;
    lpfnMySetHook = NULL;
    lpfnMyEndHook = NULL;
    if (OPT_enableWMKANCHOKUCHAR) {
        WM_KANCHOKU_CHAR = RegisterWindowMessage("WM_KANCHOKU_CHAR");
        hKanCharDLL = LoadLibrary("kanchar.dll");
        if (hKanCharDLL) {
            lpfnMySetHook = (HHOOK (*)(void))GetProcAddress(hKanCharDLL,
                "_MySetHook");
            lpfnMyEndHook = (int (*)(void))GetProcAddress(hKanCharDLL,
                "_MyEndHook");
        }
        if (lpfnMySetHook) {
            hNextHook = lpfnMySetHook();
            SetProp(hwnd, "KanchokuWin_KanCharDLL_NextHook",
                (HANDLE)hNextHook);
        }
        if (!hKanCharDLL) {
            warn("kanchar.dll���ǂݍ��߂܂���B");
        } else if (!lpfnMySetHook || !lpfnMyEndHook) {
            warn("GetProcAddress�Ɏ��s���܂����B");
        }
    }

    // �o�͐�E�B���h�E���Ƃ̐ݒ�̓ǂݍ���
    readTargetWindowSetting(iniFile);

    // �ҋ@��Ԃ�
    tc->mode = TCode::OFF;
    tc->preBuffer->clear();
    tc->postBuffer->clear();
    tc->helpBuffer->clear();
    tc->helpOffset = 0;
    tc->helpMode = 0;
    tc->hirakataMode = 0;
    tc->hanzenMode = 0;
    tc->punctMode = 0;
}

// -------------------------------------------------------------------
// �o�͐�E�B���h�E���Ƃ̐ݒ�̓ǂݍ���
void TableWindow::readTargetWindowSetting(char *iniFile) {
    char buf[BUFSIZ] = "";
    if (GetPrivateProfileSectionNames(buf, sizeof(buf), iniFile) >= sizeof(buf) - 2) {
        warn("[�Z�N�V������]���X�g�̓ǂݍ��ݎ��s(�����o�b�t�@���s��)�B\n"
             "�Z�N�V��������Z�����Ă݂Ă�������");
    }
    char className[BUFSIZ];
    char outputMethod[BUFSIZ];
    char *p;
    for (p = buf; *p != '\0' && p < buf + sizeof(buf); p += strlen(p) + 1) {
        if (stricmp(p, "kanchoku") == 0 || stricmp(p, "kansaku") == 0) {
            continue;
        }
        className[0] = '\0';
        GetPrivateProfileString(p, "className", "",
                                className, sizeof(className), iniFile);
        if (className[0] == '\0') {
            continue;
        }
        outputMethod[0] = '\0';
        GetPrivateProfileString(p, "outputMethod", "",
                                outputMethod, sizeof(outputMethod), iniFile);
        int m = tc->OPT_useWMIMECHAR;
        if (stricmp(outputMethod, "WMCHAR")  == 0 ||
            stricmp(outputMethod, "WM_CHAR") == 0 ||
            stricmp(outputMethod, "0")       == 0) {
            m = OUT_WMCHAR;
        } else if (stricmp(outputMethod, "WMIMECHAR")   == 0 ||
                   stricmp(outputMethod, "WM_IME_CHAR") == 0 ||
                   stricmp(outputMethod, "1")           == 0) {
            m = OUT_WMIMECHAR;
        } else if (stricmp(outputMethod, "WMKANCHOKUCHAR")   == 0 ||
                   stricmp(outputMethod, "WM_KANCHOKU_CHAR") == 0 ||
                   stricmp(outputMethod, "2")                == 0) {
            m = OUT_WMKANCHOKUCHAR;
        } else {
            warn("outputMethod�Ɏw�肳��Ă���l������������܂���B");
            continue;
        }
        char *q;
        STRDUP(q, className);
        tc->OPT_outputMethodMap[q] = m;
    }
}

// -------------------------------------------------------------------
// �o��
void TableWindow::output() {
    if (tc->isComplete() == 0) { return; }

    int len = tc->preBuffer->length();
    if(len == 0) { return; }

    // ���̓t�H�[�J�X�����E�B���h�E���擾
    HWND targetWin = GetForegroundWindow();
    DWORD targetThread = GetWindowThreadProcessId(targetWin, NULL);
    DWORD selfThread = GetCurrentThreadId();
    AttachThreadInput(selfThread, targetThread, TRUE);
    HWND activeWin = GetFocus();

    for (int i = 0; i < len; i++) {
        MOJI m = tc->preBuffer->moji(i);
        int h = MOJI2H(m);
        int l = MOJI2L(m);
        switch (mojitype(m)) {
        case MOJI_VKEY:
            //<v127c>
            // IE��1�s�t�H�[���̒���-�Ƃ�\�Ƃ��̒��ړ��� [���K�X��2:616]
            //PostMessage(activeWin, WM_KEYDOWN, l, 0);
            PostMessage(activeWin, WM_KEYDOWN, l, 1);
            //</v127c>
            Sleep(tc->OPT_outputSleep); // Firefox1.5��BS��2����������̂����
            PostMessage(activeWin, WM_KEYUP, l, 0xc0000001);
            //<v127a - outputSleep>
            //Sleep(0);               // ���VK_BACK���������Ăق���
            Sleep(tc->OPT_outputSleep); // ���VK_BACK���������Ăق���
            //</v127a - outputSleep>
            // XXX
            if (l == VK_BACK || l == 'H') { tc->postBuffer->pop(); }
            else                          { tc->postBuffer->pushHard(m); }
            break;

        case MOJI_ZENKAKU:
            switch (getOutputMethod(activeWin)) {
            case OUT_WMKANCHOKUCHAR:
                PostMessage(activeWin, WM_KANCHOKU_CHAR,
                            (((unsigned char)h << 8 ) | (unsigned char)l), 1);
                break;
            case OUT_WMIMECHAR:
                PostMessage(activeWin, WM_IME_CHAR,
                            (((unsigned char)h << 8 ) | (unsigned char)l), 1);
                break;
            case OUT_WMCHAR:
                PostMessage(activeWin, WM_CHAR, (unsigned char)h, 1);
                PostMessage(activeWin, WM_CHAR, (unsigned char)l, 1);
                break;
            }
            tc->postBuffer->pushHard(m);
            break;

        case MOJI_HANKANA:      // XXX
            switch (getOutputMethod(activeWin)) {
            case OUT_WMKANCHOKUCHAR:
                PostMessage(activeWin, WM_KANCHOKU_CHAR, (unsigned char)l, 1);
                break;
            case OUT_WMIMECHAR:
                PostMessage(activeWin, WM_IME_CHAR, (unsigned char)l, 1);
                break;
            case OUT_WMCHAR:
                PostMessage(activeWin, WM_CHAR, (unsigned char)l, 1);
                break;
            }
            tc->postBuffer->pushHard(m);
            break;

        case MOJI_ASCII:
            PostMessage(activeWin, WM_CHAR, (unsigned char)l, 1);
            tc->postBuffer->pushHard(m);
            break;

        default: // �����ɂ͗��Ȃ��͂�
            break;
        } // switch mojitype(m)
    } // for i
    tc->preBuffer->clear();

    // �J�[�\���ɒǏ]
    // thanx to 816 in �w�y�����zT-Code�A�K�}���\���y��`�z�x
    // <http://pc.2ch.net/test/read.cgi/unix/1014523030/>
    POINT ptCaret;
    if (tc->OPT_followCaret
        && GetCaretPos(&ptCaret)
        && (ptCaret.x || ptCaret.y)
        && ClientToScreen(activeWin, &ptCaret)) {
        // �O�g�̑傫�����擾
        RECT winRect;
        GetWindowRect(hwnd, &winRect);
        // ���g�̑傫�����擾
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        // �O�g�ƒ��g�̍����擾
        int dX = (winRect.right - winRect.left)
            - (clientRect.right - clientRect.left);
        int dY = (winRect.bottom - winRect.top)
            - (clientRect.bottom - clientRect.top);
        int sX = ptCaret.x - (winRect.right - winRect.left) / 2;
        int sY = ptCaret.y + (winRect.bottom - winRect.top) / 5;
        MoveWindow(hwnd, sX, sY, WIDTH + dX, HEIGHT + dY, TRUE);
    }

    // �X���b�h��؂藣��
    AttachThreadInput(selfThread, targetThread, FALSE);
}

// -------------------------------------------------------------------
// �w�肵���E�B���h�E�ɑ΂���outputMethod���擾
int TableWindow::getOutputMethod(HWND hWnd) {
    int om = tc->OPT_useWMIMECHAR;
    char s[BUFSIZ];
    GetClassName(hWnd, s, sizeof(s));
    if (tc->OPT_outputMethodMap.find(s) != tc->OPT_outputMethodMap.end()) {
        om = tc->OPT_outputMethodMap[s];
    }
    return om;
}

// -------------------------------------------------------------------
// �I���W�i���ł� TableWindow::outputString() �̒��̃R�����g
// -------------------------------------------------------------------
//   �Ƃ肠����imm���g�������͎��s�������A
//   ����IME�������ꍇ�́A���̕ӂ������邩���B
//    HIMC hImc = ImmGetContext(activeWin);
//    HIMC hImc = (HIMC)GetWindowLong(activeWin, 0); //0 = IMMGWL_IMC
//    HIMC hImc = ImmCreateContext();
//    if(hImc == NULL) {
//  exit(1);
//    }
//    ImmSetCompositionString(0, SCS_SETSTR,pt,strlen(pt), pt, strlen(pt));
//    HIMC oldImc = ImmAssociateContext(activeWin,hImc);
//    if(oldImc == NULL) {
//  exit(1);
//    }
//    ImmSetCompositionString(hImc, SCS_SETSTR,pt,strlen(pt), pt, strlen(pt));
//    if(oldImc == NULL) {
//  exit(1);
//    }
//    PostMessage(activeWin, WM_IME_COMPOSITION, 0, GCS_RESULTSTR);
// -------------------------------------------------------------------

/* -------------------------------------------------------------------
 * ���z���Ղ̕`��
 */

// drawFrame*() �Ƃ��A�Ă΂�邽�тɕ`�悷��񂶂�Ȃ�
// bitmap �ɕۑ����Ƃ��Ɠ]������悤�ɂ��ׂ�����

// -------------------------------------------------------------------
// ���z���Ղ̘g (OFF ��)
void TableWindow::drawFrameOFF(HDC hdc) {
    HBRUSH brK1 = CreateSolidBrush(COL_OFF_K1);
    HBRUSH brM1 = CreateSolidBrush(COL_OFF_M1);
    HPEN pnLN = CreatePen(PS_SOLID, 1, COL_OFF_LN);
    HPEN pnM1 = CreatePen(PS_SOLID, 1, COL_OFF_M1);
    int x, y;

    // �ۑ�
    HGDIOBJ pnSave = SelectObject(hdc, pnLN);
    HGDIOBJ brSave = SelectObject(hdc, brM1);

    // �O�g
    SelectObject(hdc, pnM1);
    SelectObject(hdc, brM1);
    Rectangle(hdc, 0, 0, WIDTH, HEIGHT);

    // ��
    SelectObject(hdc, pnLN);
    SelectObject(hdc, brM1);
    x = MARGIN_SIZE + BLOCK_SIZE * 5;
    y = MARGIN_SIZE;
    Rectangle(hdc, x, y, x + BLOCK_SIZE + 1, y + BLOCK_SIZE * 4 + 1);

    // �L�[
    for (int j = 0; j < 5; j++) {
        y = MARGIN_SIZE + BLOCK_SIZE * j;
        for (int i = 0; i < 10; i++) {
            x = MARGIN_SIZE + BLOCK_SIZE * i;
            if (j == 4) { x += BLOCK_SIZE / 2; }
            else if (4 < i) { x += BLOCK_SIZE; }
            SelectObject(hdc, pnLN);
            SelectObject(hdc, brK1);
            Rectangle(hdc, x, y, x + BLOCK_SIZE + 1, y + BLOCK_SIZE + 1);
        }
    }

    // ��n��
    SelectObject(hdc, brSave);
    SelectObject(hdc, pnSave);
    DeleteObject(brK1);
    DeleteObject(brM1);
    DeleteObject(pnLN);
    DeleteObject(pnM1);
}

// -------------------------------------------------------------------
// ���z���Ղ̘g (50 ��)
void TableWindow::drawFrame50(HDC hdc) {
    HBRUSH brK1 = CreateSolidBrush(COL_ON_K1);
    HBRUSH brM1 = CreateSolidBrush(COL_ON_M1);
    HPEN pnLN = CreatePen(PS_SOLID, 1, COL_ON_LN);
    HPEN pnK2 = CreatePen(PS_SOLID, 1, COL_ON_K2);
    HPEN pnM1 = CreatePen(PS_SOLID, 1, COL_ON_M1);
    HPEN pnM2 = CreatePen(PS_SOLID, 1, COL_ON_M2);
    int x, y;

    // �ۑ�
    HGDIOBJ pnSave = SelectObject(hdc, pnLN);
    HGDIOBJ brSave = SelectObject(hdc, brM1);

    // �O�g
    SelectObject(hdc, pnM1);
    SelectObject(hdc, brM1);
    Rectangle(hdc, 0, 0, WIDTH, HEIGHT);
    // �n�C���C�g
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    x = MARGIN_SIZE; y = MARGIN_SIZE + BLOCK_SIZE * 4;
    MoveToEx(hdc, x, y + 1, NULL);
    LineTo(hdc, x + BLOCK_SIZE / 2 - 1, y + 1);
    x = MARGIN_SIZE + BLOCK_SIZE / 2; y = MARGIN_SIZE + BLOCK_SIZE * 5;
    MoveToEx(hdc, x, y + 1, NULL);
    x += BLOCK_SIZE * 10;
    LineTo(hdc, x + 1, y + 1);
    y = MARGIN_SIZE + BLOCK_SIZE * 4;
    LineTo(hdc, x + 1, y + 1);
    x = MARGIN_SIZE + BLOCK_SIZE * 11;
    LineTo(hdc, x + 1, y + 1);
    y = MARGIN_SIZE;
    LineTo(hdc, x + 1, y - 1);
    // �e
    SelectObject(hdc, pnM2);
    x = MARGIN_SIZE + BLOCK_SIZE * 11; y = MARGIN_SIZE;
    MoveToEx(hdc, x, y - 1, NULL);
    x = MARGIN_SIZE;
    LineTo(hdc, x - 1, y - 1);
    y = MARGIN_SIZE + BLOCK_SIZE * 4;
    LineTo(hdc, x - 1, y + 1);
    x = MARGIN_SIZE + BLOCK_SIZE / 2; y = MARGIN_SIZE + BLOCK_SIZE * 4;
    MoveToEx(hdc, x - 1, y + 2, NULL);
    y = MARGIN_SIZE + BLOCK_SIZE * 5;
    LineTo(hdc, x - 1, y + 1);

    // ��
    SelectObject(hdc, pnLN);
    SelectObject(hdc, brM1);
    x = MARGIN_SIZE + BLOCK_SIZE * 5;
    y = MARGIN_SIZE;
    Rectangle(hdc, x, y, x + BLOCK_SIZE + 1, y + BLOCK_SIZE * 4 + 1);
    // �n�C���C�g
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    MoveToEx(hdc, x + BLOCK_SIZE - 2, y + 1, NULL);
    LineTo(hdc, x + 1, y + 1);
    LineTo(hdc, x + 1, y + BLOCK_SIZE * 4 - 1);
    // �e
    SelectObject(hdc, pnM2);
    MoveToEx(hdc, x + BLOCK_SIZE - 1, y + 2, NULL);
    LineTo(hdc, x + BLOCK_SIZE - 1, y + BLOCK_SIZE * 4 - 1);
    LineTo(hdc, x + 1, y + BLOCK_SIZE * 4 - 1);

    // �L�[
    for (int j = 0; j < 5; j++) {
        y = MARGIN_SIZE + BLOCK_SIZE * j;
        for (int i = 0; i < 10; i++) {
            x = MARGIN_SIZE + BLOCK_SIZE * i;
            if (j == 4) { x += BLOCK_SIZE / 2; }
            else if (4 < i) { x += BLOCK_SIZE; }
            SelectObject(hdc, pnLN);
            SelectObject(hdc, brK1);
            Rectangle(hdc, x, y, x + BLOCK_SIZE + 1, y + BLOCK_SIZE + 1);
            // �n�C���C�g
            SelectObject(hdc, GetStockObject(WHITE_PEN));
            MoveToEx(hdc, x + BLOCK_SIZE - 2, y + 1, NULL);
            LineTo(hdc, x + 1, y + 1);
            LineTo(hdc, x + 1, y + BLOCK_SIZE - 1);
            // �e
            SelectObject(hdc, pnK2);
            MoveToEx(hdc, x + BLOCK_SIZE - 1, y + 2, NULL);
            LineTo(hdc, x + BLOCK_SIZE - 1, y + BLOCK_SIZE - 1);
            LineTo(hdc, x + 1, y + BLOCK_SIZE - 1);
        }
    }

    // ��n��
    SelectObject(hdc, brSave);
    SelectObject(hdc, pnSave);
    DeleteObject(brK1);
    DeleteObject(brM1);
    DeleteObject(pnLN);
    DeleteObject(pnK2);
    DeleteObject(pnM1);
    DeleteObject(pnM2);
}

// -------------------------------------------------------------------
// ���z���Ղ̘g (10 ��)
void TableWindow::drawFrame10(HDC hdc) {
    HBRUSH brK1 = CreateSolidBrush(COL_ON_K1);
    HBRUSH brM1 = CreateSolidBrush(COL_ON_M1);
    HPEN pnLN = CreatePen(PS_SOLID, 1, COL_ON_LN);
    HPEN pnK2 = CreatePen(PS_SOLID, 1, COL_ON_K2);
    HPEN pnM1 = CreatePen(PS_SOLID, 1, COL_ON_M1);
    HPEN pnM2 = CreatePen(PS_SOLID, 1, COL_ON_M2);
    int x, y;

    // �ۑ�
    HGDIOBJ pnSave = SelectObject(hdc, pnLN);
    HGDIOBJ brSave = SelectObject(hdc, brM1);

    // �O�g
    SelectObject(hdc, pnM1);
    SelectObject(hdc, brM1);
    Rectangle(hdc, 0, 0, WIDTH, HEIGHT);
    // �n�C���C�g
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    x = MARGIN_SIZE; y = MARGIN_SIZE + BLOCK_SIZE * 5;
    MoveToEx(hdc, x, y + 1, NULL);
    x = MARGIN_SIZE + BLOCK_SIZE * 11;
    LineTo(hdc, x + 1, y + 1);
    y = MARGIN_SIZE;
    LineTo(hdc, x + 1, y - 1);
    // �e
    SelectObject(hdc, pnM2);
    x = MARGIN_SIZE + BLOCK_SIZE * 11; y = MARGIN_SIZE;
    MoveToEx(hdc, x, y - 1, NULL);
    x = MARGIN_SIZE;
    LineTo(hdc, x - 1, y - 1);
    y = MARGIN_SIZE + BLOCK_SIZE * 5;
    LineTo(hdc, x - 1, y + 1);

    // ��
    SelectObject(hdc, pnLN);
    SelectObject(hdc, brM1);
    x = MARGIN_SIZE + BLOCK_SIZE * 5;
    y = MARGIN_SIZE;
    Rectangle(hdc, x, y, x + BLOCK_SIZE + 1, y + BLOCK_SIZE * 5 + 1);
    // �n�C���C�g
    SelectObject(hdc, GetStockObject(WHITE_PEN));
    MoveToEx(hdc, x + BLOCK_SIZE - 2, y + 1, NULL);
    LineTo(hdc, x + 1, y + 1);
    LineTo(hdc, x + 1, y + BLOCK_SIZE * 5 - 1);
    // �e
    SelectObject(hdc, pnM2);
    MoveToEx(hdc, x + BLOCK_SIZE - 1, y + 2, NULL);
    LineTo(hdc, x + BLOCK_SIZE - 1, y + BLOCK_SIZE * 5 - 1);
    LineTo(hdc, x + 1, y + BLOCK_SIZE * 5 - 1);

    // �L�[
    for (int i = 0; i < 10; i++) {
        x = MARGIN_SIZE + BLOCK_SIZE * i;
        y = MARGIN_SIZE;
        if (4 < i) { x += BLOCK_SIZE; }
        SelectObject(hdc, pnLN);
        SelectObject(hdc, brK1);
        Rectangle(hdc, x, y, x + BLOCK_SIZE + 1, y + BLOCK_SIZE * 5 + 1);
        // �n�C���C�g
        SelectObject(hdc, GetStockObject(WHITE_PEN));
        MoveToEx(hdc, x + BLOCK_SIZE - 2, y + 1, NULL);
        LineTo(hdc, x + 1, y + 1);
        LineTo(hdc, x + 1, y + BLOCK_SIZE * 5 - 1);
        // �e
        SelectObject(hdc, pnK2);
        MoveToEx(hdc, x + BLOCK_SIZE - 1, y + 2, NULL);
        LineTo(hdc, x + BLOCK_SIZE - 1, y + BLOCK_SIZE * 5 - 1);
        LineTo(hdc, x + 1, y + BLOCK_SIZE * 5 - 1);
    }

    // ��n��
    SelectObject(hdc, brSave);
    SelectObject(hdc, pnSave);
    DeleteObject(brK1);
    DeleteObject(brM1);
    DeleteObject(pnLN);
    DeleteObject(pnK2);
    DeleteObject(pnM1);
    DeleteObject(pnM2);
}

// -------------------------------------------------------------------
// ���z���Ղ̃L�[ (50 ��)
void TableWindow::drawVKB50(HDC hdc) {
    HBRUSH brR = CreateSolidBrush(COL_LT_RED);
    HBRUSH brG = CreateSolidBrush(COL_LT_GREEN);
    HBRUSH brB = CreateSolidBrush(COL_LT_BLUE);
    HBRUSH brC = CreateSolidBrush(COL_LT_CYAN);
    HBRUSH brY = CreateSolidBrush(COL_LT_YELLOW);
    HBRUSH brL = CreateSolidBrush(COL_LT_GRAY);

    HGDIOBJ brSave = SelectObject(hdc, GetStockObject(NULL_BRUSH));
    HGDIOBJ pnSave = SelectObject(hdc, GetStockObject(NULL_PEN));
    HGDIOBJ fnSave = SelectObject(hdc, hFont);

    SetBkMode(hdc, TRANSPARENT);
    for (int y = 0; y < 5; y++) {
        int py = MARGIN_SIZE + BLOCK_SIZE * y;
        for (int x = 0; x < 10; x++) {
            int k = y * 10 + x;
            if (TC_NKEYS <= k) { goto END; }

            int px = MARGIN_SIZE + BLOCK_SIZE * x;
            if (y == 4) { px += BLOCK_SIZE / 2; }
            else if (5 <= x) { px += BLOCK_SIZE; }

            switch (tc->vkbBG[k]) {
            case TC_BG_ST1: SelectObject(hdc, brR); break;
            case TC_BG_ST2: SelectObject(hdc, brG); break;
            case TC_BG_ST3: SelectObject(hdc, brY); break;
            case TC_BG_STF: SelectObject(hdc, brL); break;
            case TC_BG_STW: SelectObject(hdc, brB); break;
            case TC_BG_STX: SelectObject(hdc, brC); break;
            //<multishift>
            //case TC_BG_ST1R: SelectObject(hdc, brR); break;
            //case TC_BG_ST2R: SelectObject(hdc, brG); break;
            //case TC_BG_STWR: SelectObject(hdc, brB); break;
            //case TC_BG_ST1L: SelectObject(hdc, brR); break;
            //case TC_BG_ST2L: SelectObject(hdc, brG); break;
            //case TC_BG_STWL: SelectObject(hdc, brB); break;
            //</multishift>
            default: SelectObject(hdc, GetStockObject(NULL_BRUSH)); break;
            }
            Rectangle(hdc, px + 2, py + 2, px + BLOCK_SIZE, py + BLOCK_SIZE);

            switch (tc->vkbFG[k]) {
            case TC_FG_SPECIAL: SetTextColor(hdc, COL_DK_CYAN); break;
            case TC_FG_STROKE:  SetTextColor(hdc, COL_DK_CYAN); break;
            //<v127a - gg>
            case TC_FG_GG:      SetTextColor(hdc, COL_DK_MAGENTA); break;
            //</v127a - gg>
            case TC_FG_NORMAL:
            default:            SetTextColor(hdc, COL_BLACK); break;
            }
            char *s = tc->vkbFace[k];
            if (s && *s) {
                int dx = tc->OPT_win95 ? 0 : 1;
                if (strlen(s) <= 1) {
                    TextOut(hdc, px + 3 + dx + (CHAR_SIZE / 4), py + 3, s, 1);
                } else {
                    TextOut(hdc, px + 3 + dx, py + 3, s, 2);
                }
            }
        }
    }
 END:
    SelectObject(hdc, brSave);
    SelectObject(hdc, pnSave);
    SelectObject(hdc, fnSave);

    DeleteObject(brR);
    DeleteObject(brG);
    DeleteObject(brB);
    DeleteObject(brC);
    DeleteObject(brY);
    DeleteObject(brL);
}

// -------------------------------------------------------------------
// ���z���Ղ̃L�[ (10 ��)
void TableWindow::drawVKB10(HDC hdc) {
    HBRUSH br = CreateSolidBrush(COL_LT_CYAN);

    HGDIOBJ brSave = SelectObject(hdc, br);
    HGDIOBJ pnSave = SelectObject(hdc, GetStockObject(NULL_PEN));
    HGDIOBJ fnSave = SelectObject(hdc, hFont);

    for (int x = 0; x < 10; x++) {
        int k = 20 + x;
        int px = MARGIN_SIZE + BLOCK_SIZE * x;
        int py = MARGIN_SIZE;
        if (5 <= x) { px += BLOCK_SIZE; }
        if (tc->vkbBG[k] == TC_BG_HISTPTR) {
            Rectangle(hdc, px + 2, py + 2,
                      px + BLOCK_SIZE, py + BLOCK_SIZE * 5);
        }
        if (tc->vkbFG[k] == TC_FG_HISTREF) {
            SetTextColor(hdc, COL_RED);
        } else {
            SetTextColor(hdc, COL_BLACK);
        }
        SetBkMode(hdc, TRANSPARENT);

        char *s = tc->vkbFace[k];
        int dx = tc->OPT_win95 ? 0 : 1;
        for (int y = 0; s && *s && y < 6; y++) {
            py = MARGIN_SIZE + (CHAR_SIZE + 1) * y + 5;
            if (IS_ZENKAKU(*s)) {
                TextOut(hdc, px + 3 + dx, py, s, 2); s += 2;
            } else {
                TextOut(hdc, px + 3 + dx + (CHAR_SIZE / 4), py, s, 1); s += 1;
            }
        }
    }

// END:
    SelectObject(hdc, brSave);
    SelectObject(hdc, pnSave);
    SelectObject(hdc, fnSave);

    DeleteObject(br);
}

// -------------------------------------------------------------------
// �~�j�o�b�t�@
void TableWindow::drawMiniBuffer(HDC hdc, int height, COLORREF col,
                                 MojiBuffer *mb) {
    HBRUSH br = CreateSolidBrush(col);

    HGDIOBJ brSave = SelectObject(hdc, br);
    HGDIOBJ pnSave = SelectObject(hdc, GetStockObject(NULL_PEN));
    HGDIOBJ fnSave = SelectObject(hdc, hLFont);

    // background
    int px = MARGIN_SIZE + BLOCK_SIZE * 5;
    int py = MARGIN_SIZE;
    Rectangle(hdc, px + 2, py + 2, px + BLOCK_SIZE, py + BLOCK_SIZE * height);

    // text
    px = MARGIN_SIZE + BLOCK_SIZE * 5 + 1;
    py = MARGIN_SIZE + BLOCK_SIZE * 0 + 1;
    SetTextColor(hdc, COL_BLACK);
    SetBkMode(hdc, TRANSPARENT);

    int offset = 0;
    if (height < mb->length()) { offset = mb->length() - height; }
    for (int y = 0; y < height && offset < mb->length();
         y++, offset++, py += BLOCK_SIZE) {
        char s[3]; s[0] = 0;
        MOJI m = mb->moji(offset);
        int dx = tc->OPT_win95 ? 0 : 1;
        switch (mojitype(m)) {
        case MOJI_SPECIAL:
            SetTextColor(hdc, COL_DK_CYAN);
            if (m == MOJI_BUSHU) {
                TextOut(hdc, px + dx, py + 1, "��", 2);
            } else if (m == MOJI_MAZE) {
                TextOut(hdc, px + dx, py + 1, "��", 2);
            }
            break;
        case MOJI_ZENKAKU:
            moji2strcat(s, m);
            SetTextColor(hdc, COL_BLACK);
            TextOut(hdc, px + dx, py + 1, s, 2);
            break;
        case MOJI_HANKANA:
        case MOJI_ASCII:
            moji2strcat(s, m);
            SetTextColor(hdc, COL_BLACK);
            TextOut(hdc, px + dx + (LARGE_CHAR_SIZE / 4), py + 1, s, 1);
            break;
        default:
            // XXX VKey �Ƃ�
            SetTextColor(hdc, COL_DK_CYAN);
            TextOut(hdc, px + dx, py + 1, "�E", 2);
            break;
        }
    }
    // under construction

    SelectObject(hdc, brSave);
    SelectObject(hdc, pnSave);
    SelectObject(hdc, fnSave);

    DeleteObject(br);
}

/* -------------------------------------------------------------------
 * �G���[����
 */

// -------------------------------------------------------------------
// �G���[��\�����A�I��
void TableWindow::error(char *mes) {
    MessageBoxEx(hwnd, mes, "������ - �G���[",
                 MB_OK | MB_ICONERROR, LANG_JAPANESE);
    PostQuitMessage(0);
}

// -------------------------------------------------------------------
// �x����\�����邪�A�p������
void TableWindow::warn(char *mes) {
    // �A�C�R���̑I���͐��������낤��?
    MessageBoxEx(hwnd, mes, "������ - �x��",
                 MB_OK | MB_ICONEXCLAMATION, LANG_JAPANESE);
}

// -------------------------------------------------------------------
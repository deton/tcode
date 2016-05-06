漢直 Win 1.28

# Introduction #

漢直 Win は、Windows で漢字直接入力を行うためのツールです。


# 概要 #

漢直Win 1.28 は、徳岡宏樹さんの 漢直 Win 1.26 および T-Code Laboratory で拡張された 漢直 Win 1.26eb をもとに、 T-Code メーリングリストや、 2ちゃんねるの漢直スレに投稿されたパッチなどをまとめたものです。主な特徴は次のとおりです。

  * WindowsXP など、Windows95 以降の Windows で動作します
  * T-Code, TUT-Code, G-Code に対応しています
  * Shift を併用する打鍵に対応し、「き」等にも対応可能です
  * 部首合成変換、交ぜ書き変換、文字ヘルプ、熟語ガイドなどの補助機能を提供します

# 変更点 #

## バージョン 1.28 の変更点 ##

  * シフト打鍵を用いる入力方式に対応
  * テーブルファイルの書式を拡張
  * 外字入力補助機能
  * 強制練習モード
  * シフト打鍵によるストロークロック機能
  * 漢直WinをOFFにしたときに各種モードを初期状態にリセットするオプション
  * offHide=2 の状態から一時的にウィンドウを表示する機能
  * BackSpace でストローク単位で消去するオプション
  * 仮想鍵盤の配色・フォントのカスタマイズ機能 (kwstyle.exe)
  * useCtrlKey=1 の場合や XKeymacs との同時使用時の問題を修正
  * C-h 等を XKeymacs と同様の方法で処理するオプション
  * BackSpace 等や @v のキー送出に keybd\_event() を用いるオプション
  * 文字送出方法に WM\_UNICHAR を追加
  * Unicode 文字への対応のテストコード (直接入力のみ、U+0080～U+3FFF限定)
  * タイトルバーのカタカナモード・全角モード・句読点モードの表示順を t.tbl での配置に合わせて修正
  * 直前の文字を入力してから仮想鍵盤を表示するまでの時間指定オプション
  * その他バグ修正

以前の変更点は、ドキュメントの「変更履歴」を参照してください。

# 使い方 #

## インストール ##

  * ダウンロードしたパッケージを解凍し、生成したフォルダを適当な場所に置きます。
  * TUT-Code を使う場合は、設定ファイル kanchoku.ini を開いて、 tableFile=t.tbl の部分を tableFile=tut.tbl と書きかえておきます。

## 起動 ##

  * kanchoku.exe 漢直Win のアイコン をダブルクリックして起動します。
  * Ctrl+\ で ON/OFF を切りかえます。

### T-Code の場合 ###

  * jf で部首合成変換、 fj で交ぜ書き変換 (前置型) です。
  * 第一打のあとに Space を押すと、そのキーを入力します。

### TUT-Code の場合 ###

  * : で交ぜ書き変換 (前置型)、 @ でかたかなモード切りかえです。
  * 第一打のあとに Tab を押すと、そのキーを入力します。

## アンインストール ##

  * インストールしたファイルを削除するだけです。レジストリは使用していません。

# 関連リンク #

## 漢直 Win 関連 ##

  * [T-code修行中 漢字直接入力のすすめ](http://t.pos.to/tc/)
> > 「漢直Win」の作者の徳岡宏樹さんのページ。

> → オリジナル版の[漢直 Win (ver1.26)](http://t.pos.to/tc/kanchoku.html)
> → [漢索板](http://t.pos.to/tc/kansaku.html)
  * [Home of T-Code](http://openlab.jp/tcode/)
> T-Code Laboratory。
> → T-Code メーリングリストで拡張された[漢直 Win (ver1.26eb)](http://openlab.jp/tcode/soft.html)
  * [T is for T-Code](http://www.sato.kuis.kyoto-u.ac.jp/~yuse/tcode/)
> 長期にわたりメンテナとなって頂いていたゆせ よしひろさんのページ。
> → [漢直Win 1.27\*](http://www.sato.kuis.kyoto-u.ac.jp/~yuse/tcode/kw/)

## 2ちゃんねる ##

  * 漢直スレ
    * [【漢直】T-Code/TUT-Codeスレ Lesson4【連習】](http://pc12.2ch.net/test/read.cgi/unix/1168873587/) (2007-01-16 〜 現行スレ)
    * [【漢直】T-Code/TUT-Codeスレ Lesson3【連習】](http://pc8.2ch.net/test/read.cgi/unix/1082032043/) (2004-04-15 〜 2007-01-23)
    * [【漢直】T-Code/TUT-Codeスレ Lesson2【連習】](http://pc.2ch.net/test/read.cgi/unix/1061936143/) (2003-08-27 〜 2004-04-18)
    * [【原理】T-Code連習マラソン【主義】](http://pc.2ch.net/test/read.cgi/unix/1014523030/) (2002-02-24 〜 2003-08-27)
  * [2ch\_log](http://homepage3.nifty.com/songs/tcode/2ch/index.html)
    * 漢直スレの過去ログ保管庫 (藤田泰裕さん)
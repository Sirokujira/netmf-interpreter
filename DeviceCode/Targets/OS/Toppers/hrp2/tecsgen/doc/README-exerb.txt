Exerb 版 TECS ジェネレータについて  (V1.0.2.33)

本書は Exerb 版 TECS ジェネレータを使用する場合の注意点について説明し
ます。Exerb 版をビルドする方法については、本書の末尾に記します。

【概要】

TECS ジェネレータは Ruby およびそのパーサジェネレータである Racc を利
用して作られています。通常 TECS ジェネレータをビルドする場合には、この
両方が必要です。また、TECS ジェネレータを使用するには、Ruby がインストー
ルされている必要があります。
しかし、Exerb 版ジェネレータを使用すると、これらのインストールは不要に
なります。

【動作の相違】

以下の点で、非 Exerb 版のジェネレータと動作が相違します。

・デフォルトの文字コードが SJIS である

ジェネレータ tecsgen の実装コードは EUC のままですが、CDL を解釈する際
の文字コード、および出力先の文字コードが SJIS となります。

【既知の問題】

tecsgen コマンドのファイル名に絶対パスを与えた場合、期待した動作になり
ません。

【プリプロセッサの指定】

import_C により C 言語のヘッダを取込む際に、プリプロセッサが呼出されま
す。cygwin が使用できる環境であれば（環境変数が設定されていれば）、gcc 
のプリプロセッサが使用されます。しかし、cygwin がインストールされてい
ない場合など、プリプロセッサを指定する必要があります。

プリプロセッサを、コマンド引き数で指定する例を以下に示します。
"TECS" は、デフォルトで定義されており、プリプロセッサコマンドを指定す
る場合にも、指定すべきです。

 % tecsgen -c "cpp.exe -D TECS"　-I header_path your_appl.cdl

V1.0.2: gcc.exe がシンボリックリンクの場合 gcc-3.exe, gcc-4.exe を探し
        ます。

【使用方法】

tecsgen は、通常コマンドプロンプトから起動します。環境変数 PATH が適切
に設定されている必要があります。
set_env.bat は PATH を設定します（set_env.bat が存在するディレクトリで
実行します）

【Exerb 版のビルド】

ここでは、Exerb 版のビルドおよびテストをする方法について説明します。
Exerb 版は ActiveScritpRuby を使用してビルドします。以下の URL から 
ActiveScritpRuby パッケージをダウンロードすることができます。

   http://www.artonx.org/data/asr/

このパッケージには Ruby, Racc, Exerb が同梱されており、このパッケージ
だけで tecsgen.exe をビルドできます。

ruby console を開いて、以下を実行します。

　% cd tecsgen               # tecsgen.exy のあるフォルダに移動
  % make_tecsgen_exerb.bat   # racc, exerb が実行されます

以下のコマンドでテストを実行できます（この実行には GNU make コマンドが
必要です。また、先に make clean する必要があるかもしれません）。

  % cd ../test; make test_exerb

【作成環境】

 OS: Windows 7
 Ruby: V1.8.7p299 (mswin32)
 Racc: 1.4.5
 exerb: 5.2.0

【Ruby インタプリタなどの入手先】

Ruby のインタプリタのソースは、以下の URL のホームページからダウンロー
ドできます。

  http://www.ruby-lang.org/

Exerb のソースは以下の URL のホームページからダウンロードできます。

  http://exerb.sourceforge.jp/

Racc のソースは、以下の URL のホームページからダウンロードできます。

  http://i.loveruby.net/ja/projects/racc/

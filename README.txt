新たに.cppや.hをフォルダに追加した場合は以下の設定が必要です。

プロジェクト→プロパティ→C/C++→全般
の中にある追加インクルードディレクトリにてソースのあるフォルダを指定してください。
なお指定する際には構成を”すべての構成”に指定してから作業を行ってください。（Relese・Debug両ビルドに対応させるため）

ディレクトリの指定方法ですがソリューションファイルを開始位置として登録します。
以下のディレクトリにおいて”debug_font.cpp””debug_font.h”を使用したい場合、そのファイルが格納されているフォルダを指定しください
今回はdebug_fontフォルダを指定します

2021-3-26_Spring-HACKATHON-
┃
┣━━2021-3-26_Spring-HACKATHON-.sln
┃
┗━━2021-3-26_Spring-HACKATHON-
      ┃
      ┣━━2021-3-26_Spring-HACKATHON-.vcxproj
      ┣━━2021-3-26_Spring-HACKATHON-.vcxproj.filters
      ┣━━2021-3-26_Spring-HACKATHON-.vcxproj.user
      ┣━━data
      ┗━━source
            ┃
            ┣━━debug_font
            ┃    ┃
            ┃    ┣━━debug_font.cpp
            ┃    ┗━━debug_font.h
            ┃
            ┣━━game
            ┃    ┃
            ┃    ┣━━game.cpp
                  ┗━━game.h


指定する際のパスの記載方法は

$(SolutionDir)/2021-3-26_Spring-HACKATHON-/source/debug_font

と記載してください

$(SolutionDir)/から始めるとソリューションファイルがあるところからフォルダの位置を探します。
$(ProjectDir)/から始めるとプロジェクトファイルがあるところからフォルダの位置を探します。



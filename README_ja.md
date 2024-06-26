[English](README.md) | [日本語](README_ja.md)

# [EV3を使ったLEGO Trainの製作](https://https://github.com/kuboaki/ev3_train/)

このリポジトリは、LEGO City Trainのレールを走る列車（あるいは機関車）と、その列車の運行を制御するための信号機などについて、ブロックの組立図や動かすプログラムを提供します。

## 製作の動機

電車の制御では、電灯を使った信号機が普及するまで、出発または停止を示す標識板を動かして信号に使っていました。

例えば、次の動画の冒頭で、標識板を使った信号が紹介されています。

* The Signal Engineers - 1962 - Electrical Engineering on the Railway

下記のサムネイルをクリックすると動画を再生します。

[![The Signal Engineers - 1962 - Electrical Engineering on the Railway](http://img.youtube.com/vi/6Oc_50DnGG0/hqdefault.jpg)](https://youtu.be/6Oc_50DnGG0?t=81)


列車を手元で動かしながら、信号で列車の制御を試めせたら面白いですよね。そこで、このビデオのような古い信号を使ってみることにしました。


## システムの全体像

このシステムには、2つのアクターが登場します。

* 列車（実のところ機関車だけです…）
* 閉塞信号機（信号表示部と列車通過監視部）


<img src="images/train_control_system_w_yellow_signal_w_cables_2.png" width="75%">


## 列車（実は機関車だけですが…）

列車は、LEGO Mindstorms EV3のキットとLEGO City Train のパーツを使って製作しました。

<img src="images/train_01_w_cables.png" width="75%">

### 走行ユニット

走行ユニットは、列車が線路に沿って走行する働きを提供しています。

* M-Motor(Medium Motor): 車輪の回転用

City Train用のモーターは、EV3と一緒に使うのは簡単ではありません。また、EV3RT（このプロジェクトで使用する開発環境）は City Train モーターをサポートしていません。以上の理由から、私は、EV3キットのMモーターを使用しています。

### 信号読み取り器

この列車には運転手がいないので、信号読み取り器は運転手に代わって信号を読み取ります。

* color sensor: 信号の読取り用

### 操作ボタン（進行・停止）

列車は、操作ボタンの操作によって、列車の進行・停止の指示を受け付けます。

* touch sensor: 列車にの進行・停止の指示の受け付け用

## 信号機

信号機は、LEGO Mindstorms EV3とその他のLEGO のパーツを組み合わせて製作しました。

この信号機は、信号表示部、手動スイッチ、列車通過監視部で構成してあります。

この信号機は、閉塞信号機と呼ばれているものです。
安全のために、この信号から先の区間に列車を通した後は、信号から先の区間から列車がいなくなるまで、他の列車が入れないよう信号の現示を「停止」にします。
このように信号で区切られた区間に1つの列車だけが走るようにする運行制御方式を、閉塞制御といいます。信号と次の信号の間を閉塞区間といいます。

### 信号表示部

信号表示部は、パレットを回転させて信号を切り替える機構を提供しています。

* L-Motor(Large Motor): 信号表示用のパレットの回転用
* touch sensor: 信号表示モーターの回転の監視用
* color sensor: 現在表示中の信号の読み取り器

注意：表示中の信号を読み取るためのブロックには、ステッカーを貼っています。色はLEGOブロックの青と黄色に似せています。

<img src="images/block_signal_05_w_cables.png" width="75%">

### 手動スイッチ

手動スイッチは、手動で信号を切り替えるのに使います。
手動スイッチには、タッチセンサーを使っています。

* touch sensor: 手動で信号を切り替える

### 列車通過監視部

列車通過監視部は、列車の通過を監視します。
列車通過監視部には、超音波センサーを使っています。

* ultrasonic sensor: 列車の通過を監視する

<img src="images/train_detector_02.png" width="75%">


## 組立図

用意できていません。

ですが、 `images` ディレクトリにある `.io` ファイルを見れば、かなりのことがわかるでしょう。

## 開発環境

開発にはTOPPERS/EV3RT(Real-Time platform for EV3) とCを使っています。
使用しているEV3RTのバージョンは「1.1-release」です。これより古い環境で動かすには、既存のコードに調整が必要です（1.1に更新したほうがよいでしょう）。
もちろん、EV3をサポートしている他のプログラミング言語でも、うまく動作するでしょう。

[EV3RT on TOPPERS](https://dev.toppers.jp/trac_user/ev3pf/wiki/WhatsEV3RT)


NOTE: hakoniwa-ros2sim環境でシミュレーションする場合は、[シミュレーションの方法](hakoniwa-ros2sim_simulation.md) を参照してください。


## コンテンツの構造


```
├── images: LEGO Studio, Blender, png
├── models: system design model(uml)
├── block_signal: coes for block signal
├── train_slow_stop: codes for train slow down stop
└── train: codes for train
```

## プログラムをビルドする

### リポジトリをEV3RTのワークスペースに展開する

EV3RTをインストールしたディレクトリには、ビルド用のワークスペース `workspace` があります。
その並びに `ev3_train` をclone します。

```shell
$ cd {インストール場所}/ev3rt-1.1-release/hrp3/sdk
$ git clone https://github.com/kuboaki/ev3_train.git
```

### 列車のプログラムをビルドする

`ev3_train` ディレクトリに移動して、列車のプログラムをビルドします。

```shell
$ cd ev3_train
$ pwd
{インストール場所}/ev3rt-1.1-release/hrp3/sdk/ev3_train
$ make app=train
$ ls -l app
-rw-r--r--  1 kuboaki  staff  102204  8  9 17:48 app
```

この `app` ファイルを、列車のEV3に転送します。
転送方法は、EV3RTのWebサイトを参照してください。

### 信号機のプログラムをビルドする

同じく、`ev3_train` ディレクトリで、信号機のプログラムをビルドします。

```shell
$ pwd
{インストール場所}/ev3rt-1.1-release/hrp3/sdk/ev3_train
$ make app=block_signal
$ ls -l app
-rw-r--r--  1 kuboaki  staff  104932  8  9 17:49 app
```

ビルドした `app` ファイルを、信号機のEV3に転送します。
転送方法は、EV3RTのWebサイトを参照してください。

## システムを実行する

![EV3 Train System Desc](images/train_control_system_w_yellow_signal_w_memo.png)

### 列車を走行する

1. 転送したプログラムを起動します。起動方法はEV3RTのWebサイトを参照してください。
1. 起動すると、警告音が鳴り、走行指示待ちになります。
1. 列車を線路の上に置き、車輪をレールに載せます。
1. 運転ボタンを押すと、確認音が鳴り、走行します。
1. 信号読取り部（上向きに装備したカラーセンサー）が、停止信号（赤）を読み取ると、到着音が鳴り、停止します。
1. 信号読取り部が、進行信号（緑）を読み取ると、確認音が鳴り、走行を再開します。
1. 運転ボタンを押すと、運転終了状態で停止します。

### 信号機を操作する

1. 転送したプログラムを起動します。
1. 起動すると、確認音が鳴り、モーターが回転して準備動作に入ります。
1. 停止信号（赤が下向き）を現示すると、モーターが停止します。
1. 列車が信号まで来ると、停止信号を読み取って停車します。
1. 手動スイッチを押すと、モーターが回転して、信号機が進行信号（線路側が緑）を現示します。
1. 列車通過監視部（線路脇に設置した超音波センサー）が走行した列車を認識すると、信号機が停止信号に変わります。

列車と信号機が動作している様子。サムネイルをクリックすると動画を再生します。

[![EV3 Train normal](https://img.youtube.com/vi/k168I_5-GNs/hq3.jpg)](https://youtu.be/k168I_5-GNsef)

Trainクラスのrunメソッドのステートマシン図（詳細は [models](./models) ディレクトリを参照）。

![Train classs run method state machine diagram](models/Train_class_run_method_stm.png)


BlockSignalクラスのrunメソッドのステートマシン図（詳細は [models](./models) ディレクトリを参照）。

![BlockSignal classs run method state machine diagram](models/BlockSignal_classs_run_method_stm_2.png)

## 信号機前で徐行する列車の運転

`ev3_train` ディレクトリで、 `train_slow_stop` のプログラムをビルドします。
この列車は、信号機の前にある警告表示を認識したら徐行します。

```shell
$ cd ev3_train
$ pwd
{インストール場所}/ev3rt-1.1-release/hrp3/sdk/ev3_train
$ make app=train_slow_stop
$ ls -l app
-rw-r--r--  1 kuboaki  staff  102552  8  9 18:35 app
```

この `app` ファイルを、列車のEV3に転送します。
転送するときに別の名前にしておけば、最初のプログラムと併存できます。

転送できたら、走らせてみましょう。

列車が信号の手前で徐行している様子。サムネイルをクリックすると動画を再生します。

[![EV3 Train slow down](https://img.youtube.com/vi/71gXzo7RDiw/hq2.jpg)](https://youtu.be/71gXzo7RDiw)

列車のステートマシン図には「減速走行中」の状態を追加しました。

Train_slow_down_クラスののrunメソッドのステートマシン図（詳細は [models](./models) ディレクトリを参照）。

![Train SLow Stopclasss run method state machine diagram](models/Train_Slow_Stop_class_run_method_stm.png)

# EV3を使ったLEGO Trainの制作

このリポジトリは、LEGO City Trainのレールを走る列車（あるいは機関車）と、その列車の運行を制御するための信号機などについて、ブロックの組立図や動かすプログラムを提供します。

## 制作の動機

電車の制御では、電灯を使った信号機が普及するまで、出発または停止を示す標識板を動かして信号に使っていました。

例えば、次の動画の冒頭で、標識板を使った信号が紹介されています。

* The Signal Engineers - 1962 - Electrical Engineering on the Railway

[![The Signal Engineers - 1962 - Electrical Engineering on the Railway](http://img.youtube.com/vi/6Oc_50DnGG0/mqdefault.jpg)](https://www.youtube.com/watch?v=6Oc_50DnGG0)


列車を手元で動かしながら、信号で列車の制御を試めせたら面白いですよね。そこで、このビデオのような古い信号を使ってみることにしました。


## システムの全体像

このシステムには、2つのアクターが登場します。

* 列車（実のところ機関車だけです…）
* 閉塞信号機（信号表示部と列車通過監視部）


![ev3_train_system_overview](images/train_control_system_03_w_cables.png)


## 列車（実は機関車だけですが…）

列車は、LEGO Mindstorms EV3とLEGO City Train のパーツを使って制作しました。

* M-Motor(Medium Motor): 走行ユニット
* color sensor: 信号読取り器
* touch sensor: 操作ボタン（進行・停止）

![ev3_train_locomotive_image](images/train_01_w_cables.png)


モーターには、EV3のキットに付属するM-Motorを使っています。
モーターにCity Train のパーツを使うと簡便なのですが、EV3から使うには、カスタマイズしたケーブルが必要になります。また、このプロジェクトで使う開発環境（EV3RT）ではCity Trainのモーターがサポートされていま
せん。

## 信号機

信号機は、LEGO Mindstorms EV3とその他のLEGO のパーツを組み合わせて制作しました。

信号機は、閉塞信号機というものです。

安全のために、その信号から先の区間に列車を通した後は、信号から先の区間から列車がいなくなるまで、他の列車が入れないようにします。このように信号で区切られた区間に1つの列車だけが走るようにする運行制御方式を、閉塞制御といいます。信号と次の信号の間を閉塞区間といいます。


閉塞信号機では、列車が信号を通過すると、信号の現示を「停止」にします。

この信号機は、信号表示部と列車通過監視部で構成してあります。

### 信号表示部

* L-Motor(Large Motor): 信号表示用のパレットの回転用
* touch sensor: 信号表示モーターの回転の監視用
* color sensor: 現在表示中の信号の読み取り器

![ev3_train_block_signal](images/block_signal_03_w_cables.png)

### 手動スイッチ

手動スイッチは、手動で信号を切り替えるのに使います。
手動スイッチには、タッチセンサーを使っています。

* touch sensor: 手動で信号を切り替える

### 列車通過監視部

列車の通過を監視します。
列車通過監視部には、超音波センサーを使っています。

* ultrasonic sensor: 列車の通過を監視する

![ev3_train_train_detector](images/train_detector_02.png)


## 動作環境

開発にはTOPPERS/EV3RT(Real-Time platform for EV3) とCを使っています。
もちろん、EV3をサポートしている他のプログラミング言語でも、うまく動作するでしょう。

[EV3RT on TOPPERS](https://dev.toppers.jp/trac_user/ev3pf/wiki/WhatsEV3RT)

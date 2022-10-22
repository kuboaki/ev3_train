# EV3_Trainのhakoniwa-ros2simシミュレーション手順

## 準備

### hakoniwa-ros2simを導入する

[hakoniwa-ros2sim](https://github.com/toppers/hakoniwa-ros2sim) を参照して、Hakoniwa ROS Simulatorの環境を用意します。

### ev3_train用Unityアプリを入手する

ev3_train用Unityアプリを下記リンク先から入手します。

NOTE: ファイルサイスが 100MB 以上あることに注意してください。

[ev3_train.zip](https://drive.google.com/file/d/1RKGehkiDCf-20MXGKu5TRopbBFDv5pS7/view?usp=sharing)

展開して得られる `ev3_train` フォルダを、 `ros2/unity` フォルダの中に配置します。

```shell
ros2/unity/ev3_train
├── MonoBleedingEdge
├── UnityCrashHandler64.exe
├── UnityPlayer.dll
├── core_config.json
├── ev3_train.exe
├── ev3_train_Data
（略）
└── writer_connectors.json
```

### Dockerが起動していることを確認する

1. dockerが動作していることを確認する
   - servcie docker status
   -  * Docker is running
1. dockerが動作していないなら、起動する
   - sudo service docker start

## ターミナルAの準備

ターミナルを起動して、hakoniwa-ros2simをCloneしたディレクトリへ移動します。

たとえば、ユーザー`kuboaki` のホームディレクトリの中に `v1.1.3` をCloneした場合だと次のようになります。

```shell
$ cd /mnt/c/Users/kuboaki/
$ git clone --recursive -b v1.1.3 https://github.com/toppers/hakoniwa-ros2sim.git
$ cd hakoniwa-ros2sim
$ pwd
/mnt/c/Users/kuboaki/hakoniwa-ros2sim
```

コンテナを起動すると、コンテナのシェルに切り替わり、プロンプトの表示も変わります。

```shell
$ bash docker/run.bash
root@jake64:~/workspace/hakoniwa-ros2sim/ros2/workspace#
```

コンテナのシェルが起動したら、 `hako-install.bash` スクリプトを実行して、シミュレーションに必要なパッケージをインストールします。

```shell
$ bash hako-install.bash
###Phase1(msg): Parsing ros_msgs from settings/tb3/RosTopics.json
（略）
###Phase2(json): Creating ros_json from settings/tb3/ros_msgs.txt
（略）
###Phase3(config): Creating core_config
（略）
###Phase4(code): Success
```
## Unityアプリを起動する


Windows エクスプローラーから、Unityアプリを起動します。
`ev3_train.exe` は、hakoniwa-ros2simのインストールディレクトリの `ros2\unity\ev3_train`  フォルダの中にあります。

WARNING: アプリが起動しても画面の中の「開始」ボタンは、まだ押さないでください。

IMPORTANT: 初めて起動するときは、Windows Defenderのファイアウォールの警告ダイアログが表示されるので、許可する。別のセキュリティアプリを使っている場合には、そのアプリのファイアウォール設定を調整する。

![ev3_train.exe のネットワークアクセスを許可する](images/GSW-20221022-232105.png)

## シユレーションを実行する

### ターミナルA

ターミナルAで、先程起動したコンテナのシェルで、 `launch.bash` スクリプトを起動してUnityと接続するEndpointを用意します。

```shell
root@DESKTOP-7UPRUP4:~/workspace/hakoniwa-ros2sim/ros2/workspace# bash launch.bash
IP_ADDR is 172.20.124.194 (eth0)
[INFO] [1666450685.299013000] [UnityEndpoint]: Starting server on 172.20.124.194:10000
[INFO] [1666450685.792383900] [UnityEndpoint]: Connection from 172.20.112.1
[INFO] [1666450693.049375000] [UnityEndpoint]: RegisterSubscriber(EV3TrainModel_ev3_actuator, <class 'ev3_msgs.msg._ev3_pdu_actuator.Ev3PduActuator'>) OK
[INFO] [1666450693.292221500] [UnityEndpoint]: RegisterSubscriber(EV3SignalModel_ev3_actuator, <class 'ev3_msgs.msg._ev3_pdu_actuator.Ev3PduActuator'>) OK
[INFO] [1666450695.137317400] [UnityEndpoint]: RegisterSubscriber(/tf, <class 'tf2_msgs.msg._tf_message.TFMessage'>) OK
[INFO] [1666450695.611106900] [UnityEndpoint]: RegisterPublisher(EV3TrainModel_ev3_sensor, <class 'ev3_msgs.msg._ev3_pdu_sensor.Ev3PduSensor'>) OK
[INFO] [1666450695.945027500] [UnityEndpoint]: RegisterPublisher(EV3SignalModel_ev3_sensor, <class 'ev3_msgs.msg._ev3_pdu_sensor.Ev3PduSensor'>) OK
```

### ターミナルB

別のターミナルを起動して、hakoniwa-ros2simをCloneしたディレクトリに移動します。
ここで、 `attach.bash` スクリプトを使って、ターミナルAで起動したコンテナに接続します。

```shell
/mnt/c/Users/kuboaki/hakoniwa-ros2sim (main *)$ bash docker/attach.bash
```

コンテナのシェルが起動したら、 `run.bash` スクリプトを使って、信号機のシミュレータを起動します。

```shell
root@jake64:~/workspace/hakoniwa-ros2sim/ros2/workspace# bash run.bash ev3 EV3SignalModel signal
START: EV3SignalModel ctrl=signal
```

信号機は、Unityアプリからのイベント待ちになります。

### ターミナルC

別のターミナルを起動して、hakoniwa-ros2simをCloneしたディレクトリに移動します。
ここで、 `attach.bash` スクリプトを使って、ターミナルAで起動したコンテナに接続します。

```shell
/mnt/c/Users/kuboaki/hakoniwa-ros2sim (main *)$ bash docker/attach.bash
```

コンテナのシェルが起動したら、 `run.bash` スクリプトを使って、信号機のシミュレータを起動します。

```shell
root@jake64:~/workspace/hakoniwa-ros2sim/ros2/workspace# bash run.bash ev3 EV3TrainModel train
START: EV3TrainModel ctrl=train
train
TR_INIT
TR_W_F_DEP1
```
列車は、Unityアプリからのイベント待ちになります。

### Unityアプリでシミュレーションを開始する

「開始」ボタンをクリックすると、Unityアプリと、信号機と列車のシミュレータがやりとりを始めます。

* 信号機は「停止」表示になるまでパレットを回転します。
* 列車は、運転ボタンが押されるのを待っています。

![シミュレーションの実行](images/GSW-20221022-225656.png)


1. 列車の運転スイッチをクリックすると、列車が走行します。
1. 列車は、信号機に差し掛かると、徐行します。
1. 列車は、信号機が「停止」を現示していると停止し、「進行」を現示するのを待ちます。
1. 信号機の手動スイッチをクリックすると、信号のパレットが回転し、「進行」を現示します。
1. 列車は、信号機が「進行」を現示するのを待ちます。
1. 列車通過監視部が列車の通過を検知すると、信号機は「停止」を現示します。
1. 列車の運転スイッチをクリックすると、列車は停止して、動作を終了します（もう一度押して走行できるようにしていないのは、実機の安全対策となっているからです）。

列車と信号機が動作している様子。サムネイルをクリックすると動画を再生します。

[![EV3 Train hakoniwa simulation](images/thumnail_hakoniwa_simulation.jpg)](https://www.youtube.com/watch?v=RjOkDsPNOg0)

[English](README.md) | [日本語](README_ja.md)

# Building LEGO Train with Mindstorms EV3

This repository provides building instructions and programs for train and signal using LEGO Mindstorms EV3 running on the LEGO City Train rails.


## Motivation

In train control, until signals using electric lights became popular, people used moving sign boards to indicate departure or stop.

For example, at the beginning of the following video, a traffic signal using a sign board is introduced.

* The Signal Engineers - 1962 - Electrical Engineering on the Railway


Click the thumbnail below to play the video.

[![The Signal Engineers - 1962 - Electrical Engineering on the Railway](http://img.youtube.com/vi/6Oc_50DnGG0/hqdefault.jpg)](https://youtu.be/6Oc_50DnGG0?t=81)


It is interesting that if we could test the train control with signal while moving it at hand.
So I decided to try using an old sign board signal, like the shown this video.

## System Overview

<img src="images/train_control_system_03_w_cables.png" width="75%">

## Train(Sorry, Locomotive only yet...)

Train uses M-Motor, color sensor and touch sensor.

* M-Motor(Medium Motor): drive unit.
* color sensor: reading signal.
* touch sensor: oparation button(departure/stop).

<img src="images/train_01_w_cables.png" width="75%">

## Block signal

This signal consists of a signal display unit, operation switch and a train detector.

### Signal display unit

Signal display unit uses L-Motor, touch sensors, color sensor.

* L-Motor(Large Motor): rotating signal pallets for displaying signal.
* touch sensor: detecting signal display motor rotation.
* color sensor: detecting current signal for present.

Note: Stickers are attached on the bricks for reading the displayed signal. The colors are similar to the blue and yellow of LEGO blocks.

<img src="images/block_signal_05_w_cables.png" width="75%">

### Manual switch

Manual switch uses touch sensor.

* touch sensor: manual switch.

### Train detector

Train detector uses ultrasonic sensor.

* ultrasocnic sensor: manual switch.

<img src="images/train_detector_02.png" width="75%">


## Building Instructions

Not ready yet.

Please see `.io` files in `images` directory.

## Development Environment

TOPPERS/EV3RT (Real-Time platform for EV3) and C are used for program development.
Of course, any other programming language that supports the EV3 will work just fine.

[EV3RT on TOPPERS](https://dev.toppers.jp/trac_user/ev3pf/wiki/WhatsEV3RT)

## Contents Tree

```
├── images: LEGO Studio, Blender, png
├── models: system design model(uml)
├── block_signal: coes for block signal
├── train_slow_stop: coes for train slow down stop
└── train: codes for train
```

## Build Program

### Clone this ripository in your EV3RT workspace

EV3RT has a default `workspace` for building programs.
Clone the `ev3_train` repository in the same hierarchy as workspace.

```shell
$ cd {install_dir}/ev3rt-1.1-release/hrp3/sdk
$ git clone https://github.com/kuboaki/ev3_train.git
```

### Build train's program

Move to `ev3_train` directory. And then build train program.

```shell
$ cd ev3_train
$ pwd
{install_dir}/ev3rt-1.1-release/hrp3/sdk/ev3_train
$ make app=train
$ ls -l app
-rw-r--r--  1 kuboaki  staff  102204  8  9 17:48 app
```
Transfer this `app` file to the train's EV3.
For transfer instructions, see the EV3RT website.


### Build signal's program

Also in the `ev3_train` directory, build the signal's program.

```shell
$ pwd
{install_dir}/ev3rt-1.1-release/hrp3/sdk/ev3_train
$ make app=block_signal
$ ls -l app
-rw-r--r--  1 kuboaki  staff  104932  8  9 17:49 app
```

Transfer this `app` file to the signal's EV3.
For transfer instructions, see the EV3RT website.

## Operate the entire system

### Run the train

1. Launch the transferred program. (See the EV3RT website for how to start.)
1. When activated, a warning horn sounds and the vehicle waits for an instruction to start running.
1. Place the train on the tracks and put the wheels on the rails.
1. When you press the operation button, a confirmation horn sounds and the vehicle starts running.
1. When the signal reader unit (using color sensor mounted upward) reads the stop signal (red), an arrival horn sounds and the train stops.
1. When the signal reader unit reads the departure signal (green), a confirmation horn sounds and the train resumes running.
1. When the operation button is pressed, the train stops in the operation end state.


### Oparate the singal

1. Launch the transferred program.
1. When activated, a confirmation horn sounds, the motor rotates, and the preparatory operation begins.
1. When the stop signal appears (red saide down), the motor will stop.
1. When the train comes under the signal, it reads the stop signal and stops.
1. When you press the manual switch, the motor rotates and the signal shows the departure signal (green side down).
1. When the train detector (using ultrasonic sensor) recognizes a running train, the signal changes to a stop signal.

The video below shows the behavior of trains and signal.
Click the thumbnail below to play the video.

[![EV3 Train normal](https://img.youtube.com/vi/k168I_5-GNs/hq3.jpg)](https://youtu.be/k168I_5-GNs)

State Machine of BlockSignal class (see more detail in [models](./models) directory).

![BlockSignal classs run method state machine diagram](models/BlockSignal_classs_run_method_stm.png)

## Train slowing down before the signal

Move to `ev3_train` directory. And then build `train_slow_stop`  program.
This train slows down when it recognizes the warning sign near the signal.

```shell
$ cd ev3_train
$ pwd
{install_dir}/ev3rt-1.1-release/hrp3/sdk/ev3_train
$ make app=train_slow_stop
$ ls -l app
-rw-r--r--  1 kuboaki  staff  102552  8  9 18:35 app
```
Transfer this `app` file to the train's EV3.

You can save the first one as well if you give it a different name (e.g. "app_slow") when transferring.

If you can transfer it, let's run it.

The video below shows the train slowing down before the signal.
Click the thumbnail below to play the video.

[![EV3 Train slow down](https://img.youtube.com/vi/71gXzo7RDiw/hq2.jpg)](https://youtu.be/71gXzo7RDiw)

State Machine of Train class (see more detail in [models](./models) directory).

![Train classs run method state machine diagram](models/Train_class_run_method_stm.png)

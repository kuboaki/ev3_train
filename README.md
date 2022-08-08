[English](README.md) | [日本語](README_ja.md)

# Building LEGO Train with Mindstorms EV3

This repository provides building instructions and programs for train and signal using LEGO Mindstorms EV3 running on the LEGO City Train rails.


## Motivation

In train control, until signals using electric lights became popular, people used moving sign boards to indicate departure or stop.

For example, at the beginning of the following video, a traffic signal using a sign board is introduced.

* The Signal Engineers - 1962 - Electrical Engineering on the Railway

[![The Signal Engineers - 1962 - Electrical Engineering on the Railway](http://img.youtube.com/vi/6Oc_50DnGG0/mqdefault.jpg)](https://www.youtube.com/watch?v=6Oc_50DnGG0)

It is interesting that if we could test the train control with signal while moving it at hand.
So I decided to try using an old sign board signal, like the shown this video.

## System Overview


![ev3_train_system_overview](images/train_control_system_03_w_cables.png)

## Train(Sorry, Locomotive only yet...)

Train uses M-Motor, color sensor and touch sensor.

* M-Motor(Medium Motor): drive unit.
* color sensor: reading signal.
* touch sensor: oparation button(departure/stop).

![ev3_train_locomotive_image](images/train_01_w_cables.png)

## Block signal

This signal consists of a signal display unit, operation switch and a train detector.

### Signal display unit

Signal display unit uses L-Motor, touch sensors, color sensor.

* L-Motor(Large Motor): rotating signal pallets for displaying signal.
* touch sensor: detecting signal display motor rotation.
* color sensor: detecting current signal for present.

Note: Stickers are attached on the bricks for reading the displayed signal. The colors are similar to the blue and yellow of LEGO blocks.

![ev3_train_block_signal](images/block_signal_05_w_cables.png)

### Manual switch

Manual switch uses touch sensor.

* touch sensor: manual switch.

### Train detector

Train detector uses ultrasonic sensor.

* ultrasocnic sensor: manual switch.

![ev3_train_train_detector](images/train_detector_02.png)


## Building Instructions

Not ready yet.

Please see `.io` files in images directory.

## Development

TOPPERS/EV3RT (Real-Time platform for EV3) and C are used for program development.
Of course, any other programming language that supports the EV3 will work just fine.

[EV3RT on TOPPERS](https://dev.toppers.jp/trac_user/ev3pf/wiki/WhatsEV3RT)

# Building LEGO Train with Mindstorms EV3

This repository provides building instructions and programs for train and signal using LEGO Mindstorms EV3 running on the LEGO City Train rails.

## System Overview

![ev3_train_system_overview](images/train_control_system_overview_01.png)

## Train(Locomotive)

Train uses M-Motor, color sensor and touch sensor.

* M-Motor(Medium Motor): drive unit.
* color sensor: reading signal.
* touch sensor: emergency stop button.

![ev3_train_locomotive_image](images/train_01.png)

## Block signal

Block signal uses L-Motor, touch sensors, color sensor.

* L-Motor(Large Motor): rotating signal pallets for displaying signal.
* touch sensor: detecting signal display motor rotation.
* touch sensor: manual switch.
* color sensor: detecting current signal for present.

![ev3_train_block_signal](images/block_signal_02.png)

![ev3_train_train_detector](images/train_detector_02.png)

## Building Instructions

Please see `.io` files in images directory.

## Development

TOPPERS/EV3RT (Real-Time platform for EV3) and C are used for program development.
Of course, any other programming language that supports the EV3 will work just fine.

[EV3RT on TOPPERS](https://dev.toppers.jp/trac_user/ev3pf/wiki/WhatsEV3RT)

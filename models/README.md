# Software Design Model

In the  software design of the "EV3 Train", we use UML.
"class diagrams" and "state machine diagrams" are used.

We use Change Vision com's  "Astah Professional" to making UML models.

[Astah Professional (Change Vision Inc.)[(https://astah.net/products/astah-professional/)

## Model to Code

Our code are written in a Single-Instance Module Method.
The single instance module method is a simple code creation method that omits the mechanism for handling multiple instances when there is only one instance of a class.

[Test Driven Development for Embedded C, Grenning](https://pragprog.com/titles/jgade/test-driven-development-for-embedded-c/)

In this project, we will create one file per class.
The method (function in C) corresponding to the state machine diagram uses a simple implementation rule using the Switch statement.

## Contents

NOTE: Sorry, Some file names uses Japanese.

models
├── train_control_system
│   ├── BlockSignal
│   │   ├── BlockSignal
│   │   │   └── BlockSignalクラスのrunのステートマシン図.png
│   │   ├── Blocksignalサブシステムのクラス図.png
│   │   ├── Rotator
│   │   │   └── Rotatorクラスのrunメソッドのステートマシン図.png
│   │   └── SignalDisplay
│   │       └── SignalDisplayクラスのrunのステートマシン図.png
│   ├── System
│   │   └── Systemのクラス図.png
│   └── Train
│       ├── Train
│       │   └── Trainクラスのrunのステートマシン図.png
│       └── Trainサブシステムのクラス図.png
└── train_control_system.asta

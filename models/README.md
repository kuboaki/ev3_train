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

NOTE: Sorry, contents of all diagrams use Japanese.

* [Train Control System Model file (modeling tool astah's model file)](train_control_system.asta)
* [System Class Diagram](System_class_diagram.png)
* [Block Signal subsystem class diagram](BlockSignal_subsystem_class_diagram.png)
* [BlockSignal classs run method state machine diagram](BlockSignal_classs_run_method_stm.png)
* [Rotator class run method state Machine diagram](Rotator_class_run_method_stm.png)

* [SignalDisplay class run method state machine diagram](SignalDisplay_class_run_method_stm.png)
* [Train subsystem class diagram](Train_subsystem_class_diagram.png)
* [Train class run methodstate machine diagram](Train_class_run_method_stm.png)

# Arduino Lab 2: Robot Logic Control

## Project Objective
This project focuses on developing the foundational control logic for a future robot. Using an Arduino, the system interprets inputs from multiple sensors (simulated by push buttons) to determine movement and collision avoidance behavior.

## Skills and Technology Used
* **Language:** C++ (Arduino Sketch)
* **Hardware:** GPIO Pin Mapping, Pull-up/Pull-down Resistors, LED Logic Indicators
* **Tools:** Arduino IDE, Circuit Breadboarding

## Code Highlight: Finite State Machine Logic
To ensure the robot prioritizes safety without blocking other operations, the logic relies on a Finite State Machine (FSM) architecture. Below is the collision detection state machine, which overrides standard movement if an obstacle is detected.

```cpp
void fsmCollisionDetection() {
  static int collisionDetectionState = 0; 

  switch (collisionDetectionState) {
    case 0: // Collision Detected
      ActionCollision = COLLISION_ON; 
      ActionRobotDrive = DRIVE_STOP; 

      if (SensedCollision == DETECTION_NO) {
        collisionDetectionState = 1; // Transition to safe state
      }
      break;

    case 1: // No Collision
      ActionCollision = COLLISION_OFF; 
      fsmSteerRobot(); // Proceed with normal navigation

      if (SensedCollision == DETECTION_YES) {
        collisionDetectionState = 0; // Transition to halt state
      }
      break;
  }
}
```

## How It Works
The logic is divided into three primary zones to simulate sensor input:
* **Middle Button:** Acts as a collision override. When triggered, it halts other operations to prioritize safety logic.
* **Left & Right Buttons:** Control the primary directional logic, representing the light sensors or proximity triggers.
* **Far-Left & Far-Right:** Handle extreme-angle detection for tighter maneuvering.

## Requirements
* 1x Arduino Uno (or compatible board)
* 5x Push Buttons
* 5x Resistors (330 Ohm)
* 5x Resistors (150 Ohm)
* LED Indicators
* Breadboard and Jumper Wires

## Circuit Documentation
![Robot Logic Circuit 1](images/RobotLogicCircuit1.jpg)
![Robot Logic Circuit 2](images/RobotLogicCircuit2.jpg)
![Robot Logic Circuit 3](images/RobotLogicCircuit3.jpg)

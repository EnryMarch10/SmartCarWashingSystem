# Assignment \#2 - Smart Car-Washing System

Second assignment developed on Arduino using vscode with PlatformIO of
[Embedded Systems and IoT - a.y. 2023-2024](https://www.unibo.it/en/teaching/course-unit-catalogue/course-unit/2023/400396)
([Computer Science and Engineering](https://corsi.unibo.it/1cycle/ComputerScienceEngineering)).

## Author

[@EnryMarch10](https://github.com/EnryMarch10)

## Behavior

We want to realize an embedded system called Smart Car-Washing System.
The prototype is meant to simulate a simple smart system for car washing.

![example of circuit layout](img/assignment-2%20result.png)

Hardware components:
- CAR PRESENCE DETECTOR is a PIR, to detect the presence of vehicles in Check In/Out Area;
- CAR DISTANCE DETECTOR is a sonar, to measure the distance of vehicles entering in the Washing Area;
- GATE is a servo-motor, simulating a gate, between the Check In/Out Area and the Washing Area;
- USER LCD is a I2C LCD, used to interact with users;
- START is a tactile button;
- L1 and L3 are two green leds, L2 is a red led;
- TEMP is an analog temperature sensor.

The embedded subsystem is meant to communicate by means of the serial line with a PC, running a PC Console Dashboard
(for maintainers).

### Detailed Behavior

The simulated environment involves two main areas:

- a Check-In/Out Area, welcoming vehicles that aim at being washed (one by one); 
- a Washing Area, which is where the washing process occurs;

When no one is around, the system is off, sleeping.

When a vehicle is detected by the CAR PRESENCE DETECTOR in the Check In/Out Area, the light L1 is turned on and on the USER LCD
the message: _"Welcome"_ is displayed.

After N1 seconds that a vehicle is in the Check In/Out Area, the gate GATE is opened to allow the vehicle to proceed to the
Washing Area and the light L2 starts blinking with a period equals to 0.1 secs. On the USER LCD the message _"Proceed to the Washing Area"_
is displayed.

The entrance of a vehicle in the Washing Area is tracked by the CAR DISTANCE DETECTOR: when the measured distance is less than
MINDIST for N2 secs, the vehicle is considered fully entered.
The gate GATE is then closed and the light L2 stops blinking and is turned on.
On the USER LCD the message: _"Ready to Wash"_ is displayed.

When the user presses the button START, the simulated washing process begins and lasts for N3 secs.
During this time, the light L2 blinks with a period equal to 0.5 secs.
On the USER LCD a countdown is displayed–either using numbers or a bar changing dimensions.

After N3 secs, the washing process ends: L2 is turned off, L3 is turned on, the message _"Washing complete, you can leave the area"_
is displayed on the USER LCD and the gate GATE is opened to allow the vehicle to move away from the Washing Area.
In this stage, the leaving process can be considered completed when the CAR DISTANCE DETECTOR measures a distance greater than
MAXDIST for N4 secs. At that point, the gate GATE is closed, L3 is turned off.

The PC Console Dashboard is meant to be a simple GUI used by car-washing maintainers to monitor the state and functioning of the
washing system and intervene if necessary:

- In particular, It visualizes the total number of washes done so far and  the current state of the washing machine.
To this purpose, during the washing process the temperature is monitored by means of the TEMP sensor, reporting the ongoing
value on the PC Console Dashboard;
- if the temperature becomes greater than MAXTEMP for N4 seconds, then the washing process is suspended and a message
_"Maintenance required"_ is displayed on the PC Console Dashboard, along with the message _"Detected a Problem - Please Wait"_
on the USER LCD;
- then, the PC Console Dashboard must provide a button _"Maintenance done"_ to notify that the problem has been verified
(and solved) and the washing process can go on.

Develop the embedded software on Arduino + PC connected through the serial line, implementing the Arduino part in C++/Wiring and
the PC part in Java or in another favorite language. The Arduino program must be designed and implemented using task-based
architectures and synchronous Finite State Machines.

For any aspect not specified, you are free to choose the approach you consider more useful or valuable.

## License

[MIT](https://choosealicense.com/licenses/mit/)

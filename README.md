\# Arduino Advanced Multimeter



!\[Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?logo=arduino)

!\[Language](https://img.shields.io/badge/Language-C++-00599C?logo=cplusplus)

!\[Platform](https://img.shields.io/badge/IDE-Arduino\_IDE-00979D)

!\[Status](https://img.shields.io/badge/Status-Completed-success)



A multifunction \*\*Arduino UNO-based electronic component tester\*\* capable of measuring and identifying commonly used electronic components through a menu-driven \*\*16×2 LCD interface\*\*.



The project demonstrates analog measurements, component identification, ADC interfacing, and embedded systems programming using Arduino.



\---



\# Features



\- Measure unknown resistor values

\- Measure capacitor values

\- Measure inductance

\- Detect Silicon, Germanium and Zener diodes

\- Identify LEDs using forward voltage

\- Detect NPN and PNP BJTs

\- Continuity testing

\- LDR resistance measurement

\- LCD-based user interface

\- Push-button menu navigation



\---



\# Hardware Used



\- Arduino UNO

\- 16×2 LCD Display

\- Breadboard

\- Push Buttons

\- Resistors

\- Capacitors

\- Inductors

\- Diodes

\- LEDs

\- BJTs

\- LDR

\- Jumper Wires



\---



\# Software Used



\- Arduino IDE

\- Tinkercad Circuit Simulator



\---



\# Folder Structure



```text

Arduino-Component-Tester/

│

├── README.md

├── LICENSE

├── .gitignore

├── code/

│   └── Advanced\_Multimeter.ino

├── circuit/

│   └── Schematic.pdf

└── images/

&#x20;   ├── hardware/

&#x20;   └── simulation/

```



\---



\# Working Principle



The user selects a measurement mode using push buttons. Depending on the selected mode, the Arduino performs voltage measurements or timing analysis to calculate the required electrical parameter.



The measured value or identified component is displayed on the 16×2 LCD.



\---



\# Measurement Modes



| Mode | Description |

|------|-------------|

| 1 | Resistor Measurement |

| 2 | Inductor Measurement |

| 3 | Capacitor Measurement |

| 4 | Diode Detection |

| 5 | LED Identification |

| 6 | BJT Detection |

| 7 | Continuity Test |

| 8 | LDR Measurement |



\---



\# Pin Configuration



| Arduino Pin | Function |

|-------------|----------|

| A0 | Resistor / LDR |

| A1 | Inductor |

| A2 | Capacitor |

| A3 | Diode / LED / Continuity |

| A4 | BJT Emitter |

| A5 | BJT Collector |

| D0 | Next Button |

| D10 | OK Button |

| D6 | BJT Base |

| D7 | MOSFET Control |

| D8 | Inductor Charge |

| D9 | Capacitor Discharge |

| D13 | Capacitor Charge |

| D12, D11, D5, D4, D3, D2 | LCD Interface |



\---



# Tinkercad Simulation

You can explore the complete circuit and interact with the simulation on Tinkercad.

**🔗 [Open the Tinkercad Simulation](https://www.tinkercad.com/things/6FzkCr1LbFs-advanced-multimeter?sharecode=Vx-necX7GMrY8QaXz7o8Sx1Pgvu9k-Aa0CUvpKsUsqs)**

![](images/simulation/resistor.png)



\---



\# Circuit Diagram



The complete schematic is available in:



```

circuit/Schematic.pdf

```



\---



\# Demonstration



\## Capacitor Measurement



| Hardware | Simulation |

|----------|------------|

| !\[](images/hardware/capacitor.jpeg) | !\[](images/simulation/capacitor.png) |



\---



\## Continuity Test



| Open Circuit | Short Circuit |

|--------------|---------------|

| !\[](images/hardware/continuity-open.jpeg) | !\[](images/hardware/continuity-short.jpeg) |



\---



\## Diode Detection



| Hardware | Simulation |

|----------|------------|

| !\[](images/hardware/diode.jpeg) | !\[](images/simulation/diode.png) |



\---



\## LED Identification



| Hardware | Simulation |

|----------|------------|

| !\[](images/hardware/led.jpeg) | !\[](images/simulation/led.png) |



\---



\## NPN Transistor Detection



| Hardware | Simulation |

|----------|------------|

| !\[](images/hardware/bjt-npn.jpeg) | !\[](images/simulation/bjt-npn.png) |



\---



\## PNP Transistor Detection



| Hardware | Simulation |

|----------|------------|

| !\[](images/hardware/bjt-pnp.jpeg) | !\[](images/simulation/bjt-pnp.png) |



\---



\## Zener Diode Detection



| Hardware | Simulation |

|----------|------------|

| !\[](images/hardware/zener-diode.jpeg) | !\[](images/simulation/zener-diode.png) |



\---



\## Resistor Measurement



!\[](images/simulation/resistor.png)



\---



\## Inductor Measurement



!\[](images/simulation/inductor.png)



\---



\## LDR Measurement



!\[](images/simulation/ldr.png)



\---



\# Learning Outcomes



Through this project I gained practical experience in:



\- Arduino Programming

\- Embedded Systems

\- Analog Electronics

\- ADC Interfacing

\- Electronic Component Testing

\- LCD Interfacing

\- Instrumentation Basics

\- Circuit Design



\---



\# Future Improvements



\- Automatic component recognition

\- Auto-ranging measurements

\- OLED/TFT graphical display

\- PCB implementation

\- Battery-powered operation

\- ESR measurement

\- MOSFET characterization



\---



\# Author



\*\*Akshay Patankar\*\*



BE Electronics \& Telecommunication Engineering  

Honours in Artificial Intelligence \& Machine Learning



Pune Institute of Computer Technology (PICT)



\---



\# License



This project is licensed under the MIT License.


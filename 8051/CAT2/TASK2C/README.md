# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 2

**DATE:** 20/09/2026

**NAME OF EXP:** 8051 Tool Chain Setup – Development Board – AT89S52

**HARDWARE SETUP / PLATFORM:** AT89S52 development kit (8051 core, 11.0592 MHz crystal) — Keil µVision 5 (C51), progisp + USBasp ISP programmer

---

## TASK 3 : Custom Library Function for Delay

### 1. Circuit Diagram

| Signal | Pin | Notes |
|---|---|---|
| User LED | P1.0 | on-board, **active-LOW** (0 = ON) |
| ISP | P1.5 MOSI, P1.6 MISO, P1.7 SCK, RST | USBasp 10-pin header |
| Supply | VCC pin 40, GND pin 20 | 5 V |

![Circuit Diagram](circuit.png)

*Drawn on [Wokwi](https://wokwi.com). To edit it: start a new project on wokwi.com, paste [`wokwi/diagram.json`](wokwi/diagram.json) into its diagram.json tab, and add any `wokwi/*.chip.json` files using **New file**. Custom chips are used for the AT89S52, USB-TTL, ULN2003, USBasp, and ST-LINK boards (with pin names added as labels). The ESP-01 stands in for the Wemos D1 mini, the BMP180 stands in for the BME280, and the Nucleo-64 graphic represents the F401RE.*

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Instead of keeping the delay loop inside `main.c`, we move it into its own separate library files (`delay.h` and `delay.c`). 
- **`delay_ms(n)`** creates an accurate 1 millisecond pause and repeats it `n` times. It uses two inner loops of 50 steps each with a `volatile` counter so the compiler does not skip or optimize the empty loop away. One full run takes 922 machine cycles, which equals about 1.000 ms on an 11.0592 MHz crystal (tested in uCsim; it may vary by a couple of percent in Keil).
- **`delay_50us()`** creates a quick 50-microsecond pause, which will be useful later when working with an LCD screen.

**Pseudocode:**

1. Declare the `delay_ms()` and `delay_50us()` functions inside `delay.h`.
2. Write the actual delay loop code inside `delay.c`.
3. Include `"delay.h"` at the top of `main.c`.
4. Turn the LED ON, then wait using `delay_ms(500)`; turn the LED OFF, then wait using `delay_ms(500)`.
5. Repeat this forever.

**Code Base:**

- **Project files:** `TASK2C.uvproj` (Keil µVision project), `STARTUP.A51`, and the compiled `Objects/TASK2C.hex` file.
- **`delay.h`:** Lists the delay functions and notes on how the timing works.
- **`delay.c`:** Contains the tuned delay loops.
- **`main.c`:** Blinks the LED at 1 Hz by calling `delay_ms(BLINK_HALF_MS)`.

### 3. Inference

Putting the delay code into its own reusable library makes the main program much cleaner—we can simply ask for a pause in exact milliseconds, and we can easily reuse this same delay library in upcoming experiments (CAT 3 through 7).

# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 8

**DATE:** 18/09/2026

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** Blue Pill STM32F103C6T6 (Cortex-M3, 72 MHz) + push-button — STM32CubeMX + Keil MDK-ARM (STM32CubeIDE project also included), STM32 HAL

---

## TASK 8A : GPIO Input/Output

### 1. Circuit Diagram

| Pin | CubeMX setting | Connected to |
|---|---|---|
| PC13 | GPIO_Output, push-pull | On-board LED (**active-LOW**, 0 = ON) |
| PA15 | GPIO_Input, pull-up | Push-button connected to GND |
| PA13 / PA14 | SYS: Debug = Serial Wire | ST-LINK debugger (also frees PA15 from default JTAG pins) |
| RCC | HSE crystal → PLL ×9 | Set system clock to 72 MHz |

![Circuit Diagram](circuit.png)

*Drawn on [Wokwi](https://wokwi.com). To open and edit it: start a new project on wokwi.com, paste [`wokwi/diagram.json`](wokwi/diagram.json) into its diagram.json tab, and add the `wokwi/*.chip.json` files (if any) with **New file**. Custom chips are used for the development boards and hardware blocks.*

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The push-button uses an internal pull-up resistor, meaning it reads `1` when released and drops to `0` when pressed. The program checks the button state inside an infinite loop and updates the LED right away.

**Pseudocode:**

1. Initialize HAL, system clocks, and GPIO pins.
2. Keep the LED off initially.
3. Continuously read the button pin (PA15):
   - When pressed, set PC13 to `0` (turn LED ON).
   - When released, set PC13 to `1` (turn LED OFF).
4. Repeat.

**Code Base:**

- **Project Files:** `CAT08A_GPIO_Input_Output.ioc` (CubeMX configuration file), `MDK-ARM/CAT08A_GPIO_Input_Output.uvprojx` (Keil project).
- **Main Code:** Written inside `Core/Src/main.c` using standard STM32 HAL library functions:
  - `HAL_GPIO_ReadPin()` reads the button status.
  - `HAL_GPIO_WritePin()` drives the LED pin using active-low logic.

### 3. Inference

The LED responds directly to the push-button clicks, which proves that our input pull-up setup and active-low output configuration are working correctly.

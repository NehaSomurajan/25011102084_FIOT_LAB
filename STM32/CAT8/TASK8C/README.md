# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 8

**DATE:** 18/09/2026

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** Blue Pill STM32F103C6T6 (Cortex-M3, 72 MHz) + push-button — STM32CubeMX + Keil MDK-ARM (STM32CubeIDE project also included), STM32 HAL

---

## TASK 8C : Short Press vs Long Press

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

To tell a short press apart from a long press, the program records the start time when the button goes down. When it is released, it calculates the duration (`release_time - press_time`). If it's held for less than 1 second, it's counted as a short press; if it's 1 second or more, it's a long press. The decision happens *upon release*, so blinking starts right after you let go of a long press rather than forcing you to watch it happen mid-hold.

| Action | Response |
|---|---|
| Short press | Toggle the LED state once |
| Long press | Start continuous blinking (every 200 ms) |
| Short press while blinking | Stop the blinking |
| Long press again | Start blinking again |

**Pseudocode:**

1. On a confirmed press edge, save the current tick value into `press_start_ms`.
2. On the release edge, calculate how long the button was held down.
3. If it was a long press, set the `blinking` flag to active.
4. If it was a short press, toggle the LED or stop the blinking if it was already running.
5. If the blinking mode is active, toggle the LED every 200 ms using non-blocking timer checks (`HAL_GetTick()`).

**Code Base:**

- **Project Files:** `CAT08C_Short_vs_Long_Press.ioc` (CubeMX configuration), `MDK-ARM/CAT08C_Short_vs_Long_Press.uvprojx` (Keil project).
- **Main Code:** Written inside `Core/Src/main.c`:
  - `classify_press()` to check duration.
  - `HAL_GetTick()` handles both press timing tracking and blink intervals without using any blocking `HAL_Delay()` functions.

### 3. Inference

Using timestamps instead of blocking delays allows the microcontroller to accurately measure press duration while keeping the LED blinking smoothly in the background.

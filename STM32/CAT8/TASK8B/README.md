# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 8

**DATE:** 18/09/2026

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED

**HARDWARE SETUP / PLATFORM:** Blue Pill STM32F103C6T6 (Cortex-M3, 72 MHz) + push-button — STM32CubeMX + Keil MDK-ARM (STM32CubeIDE project also included), STM32 HAL

---

## TASK 8B : Event-Based Control

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

Mechanical button contacts bounce for a few milliseconds when pressed, which can accidentally look like multiple rapid presses to the microcontroller. The `debounce_update()` function fixes this by accepting a new input state only after the raw signal remains completely steady for 25 ms (tracked using `HAL_GetTick()`). It then detects the exact press or release edge, allowing the LED to toggle precisely once per press without using any blocking delays.

**Pseudocode:**

1. Read the raw button state and the current tick value inside the main loop.
2. If the raw input level changes, reset the stability timer.
3. If the signal stays stable for 25 ms and differs from the last accepted state, update it and return a valid edge event.
4. On a confirmed press edge, toggle the state of PC13 and increment the `toggle_count`.

**Code Base:**

- **Project Files:** `CAT08B_Event_Toggle_Debounce.ioc` (CubeMX configuration file), `MDK-ARM/CAT08B_Event_Toggle_Debounce.uvprojx` (Keil project).
- **Main Code:** Written inside `Core/Src/main.c`:
  - `debounce_t` structure tracking stable state, last raw reading, and last change time.
  - `debounce_update()` function returning `BTN_PRESS_EDGE` or `BTN_RELEASE_EDGE`.
  - `HAL_GPIO_TogglePin()` to switch the LED state and `toggle_count` for viewing via Live Expressions.

### 3. Inference

Each physical button press toggles the LED cleanly and exactly once, proving that contact bounce is successfully eliminated without pausing the CPU execution.

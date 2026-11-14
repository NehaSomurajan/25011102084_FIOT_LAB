# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 9

**DATE:** 28/09/2026

**NAME OF EXP:** STM32 UART Command Controlled LED

**HARDWARE SETUP / PLATFORM:** Blue Pill STM32F103C6T6 (Cortex-M3, 72 MHz) + USB-to-TTL + PuTTY — STM32CubeMX + Keil MDK-ARM (STM32CubeIDE project also included), STM32 HAL, PuTTY

---

## TASK 9A : Basic UART Communication

### 1. Circuit Diagram

| STM32 | USB-to-TTL |
|---|---|
| PA9 USART1_TX | RX |
| PA10 USART1_RX | TX |
| GND | GND |

USART1 asynchronous, **115200-8-N-1**. 

![Circuit Diagram](circuit.png)

*Drawn on [Wokwi](https://wokwi.com). To open and edit it: start a new project on wokwi.com, paste [`wokwi/diagram.json`](wokwi/diagram.json) into its diagram.json tab, and add the `wokwi/*.chip.json` files (if any) with **New file**.*

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The microcontroller repeatedly transmits the character `'A'` through the UART port every 1 second using the `HAL_UART_Transmit()` function, creating a simple heartbeat signal that can be monitored on a computer terminal.

**Pseudocode:**

1. Initialize system clock, GPIO, and UART1 (115200 baud).
2. Set character variable to `'A'`.
3. In an infinite loop:
   - Send the character over UART.
   - Wait for 1 second (`HAL_Delay(1000)`).

**Code Base:**

- Project files: `CAT09A_Basic_UART_Communication.ioc` (CubeMX configuration), `MDK-ARM/CAT09A_Basic_UART_Communication.uvprojx` (Keil MDK), `.project` / `.cproject` (STM32CubeIDE); application code in `Core/Src/main.c`.

### 3. Inference

Data transmission works reliably at the configured baud rate, allowing the connected computer terminal to receive the periodic character stream successfully.

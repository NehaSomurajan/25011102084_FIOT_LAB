# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 9

**DATE:** 28/09/2026

**NAME OF EXP:** STM32 UART Command Controlled LED

**HARDWARE SETUP / PLATFORM:** Blue Pill STM32F103C6T6 (Cortex-M3, 72 MHz) + USB-to-TTL + PuTTY — STM32CubeMX + Keil MDK-ARM (STM32CubeIDE project also included), STM32 HAL, PuTTY

---

## TASK 9B : String-Based Application Logic

### 1. Circuit Diagram

| STM32 | USB-to-TTL |
|---|---|
| PA9 USART1_TX | RX |
| PA10 USART1_RX | TX |
| GND | GND |

USART1 asynchronous, **115200-8-N-1**. LED on PC13.

![Circuit Diagram](circuit.png)

*Drawn on [Wokwi](https://wokwi.com). To open and edit it: start a new project on wokwi.com, paste [`wokwi/diagram.json`](wokwi/diagram.json) into its diagram.json tab, and add the `wokwi/*.chip.json` files (if any) with **New file**.*

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The microcontroller listens for typing from the computer. Characters are echoed back and saved into a buffer until you press Enter (newline). Once a full command is entered, the program cleans it up (trims spaces and converts it to uppercase) and checks what you asked it to do:

| Command | Action |
|---|---|
| `LED ON` / `LED OFF` / `LED TOGGLE` | Controls the onboard LED (PC13) |
| `STATUS` | Reports whether the LED is currently ON or OFF |
| `CRLF TEST` | Demonstrates how newlines (`\r` and `\n`) behave on the screen |
| `HELP` | Lists all available commands |

| String | PuTTY Result |
|---|---|
| `"HELLO\r\n"` | Moves to a new line |
| `"HELLO\r"` | Returns to the start of the current line (overwrites text) |
| `"HELLO\n"` | Moves down one line in the same column |
| `"HELLO\r\nWORLD\r\n"` | Prints two separate lines |

**Pseudocode:**

1. Initialize system clock, GPIO, and UART1 (115200 baud). Ensure LED is OFF and print a welcome message.
2. Continuously read incoming characters one by one.
3. If the Enter key (CR/LF) is pressed and the command buffer has text:
   - Terminate the string, clean and uppercase it, run `handle_command()`, and then clear the buffer for the next command.
4. If the Backspace key is pressed:
   - Remove the last character from the buffer.
5. Otherwise:
   - Save the typed character into the buffer and echo it back to the screen.

**Code Base:**

- Project files: `CAT09B_String_Command_LED.ioc` (CubeMX configuration), `MDK-ARM/CAT09B_String_Command_LED.uvprojx` (Keil MDK), `.project` / `.cproject` (STM32CubeIDE); application code in `Core/Src/main.c`.
- Key custom functions: `normalise()` (trims spaces and makes text uppercase), `handle_command()`, and `crlf_demo()`.

### 3. Inference

Processing characters line-by-line successfully turns a basic serial port into an interactive text command interface, allowing users to control hardware directly using simple English words.
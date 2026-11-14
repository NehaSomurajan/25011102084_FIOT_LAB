# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 10

**DATE:** 05/10/2026 (Tasks 10C/10d: 12/10/2026)

**NAME OF EXP:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands + HTTP Server

**HARDWARE SETUP / PLATFORM:** Blue Pill STM32F103C8T6 (Cortex-M3, 72 MHz) + Wemos D1 mini (ESP8266 AT firmware) + USB-to-TTL — STM32CubeMX + Keil MDK-ARM (STM32CubeIDE project also included), STM32 HAL, PuTTY

---

## TASK 9A : Establish STM32 ↔ Wemos UART Communication

> The CAT 10 lab sheet numbers this task **9A**; it is stored in folder `TASK10A`.

### 1. Circuit Diagram

| STM32 | Connected to | Purpose |
|---|---|---|
| PA9 USART1_TX | Wemos RX | Sends AT commands |
| PA10 USART1_RX | Wemos TX | Receives replies |
| PA2 USART2_TX / PA3 USART2_RX | USB-to-TTL RX / TX | Connects to PC terminal |
| GND | All GNDs | Common ground |

Both UARTs use **115200-8-N-1**. Wi-Fi passwords go in `Core/Inc/wifi_secrets.h` (ignored by git; check `wifi_config.h` for the layout).

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

After waiting 2 seconds for the module to boot up, the STM32 sends `AT` and reads reply lines until it sees `OK`, `ERROR`, or `FAIL` (or times out), showing them on your screen. It then switches to a pass-through bridge mode connecting PuTTY directly to the ESP8266 so you can type and test other commands by hand.

**Pseudocode:**

1. Print a welcome message on USART2.
2. `esp_startup()`: wait for boot, try sending `AT` up to 3 times, and turn off echo with `ATE0`.
3. `at_show("AT")` → prints `>> AT` and `<< OK`.
4. `at_bridge_start()`: switch both UARTs to background interrupts using 256-byte receive buffers (255 usable bytes); if an interrupt ever stops, the main loop restarts it.
5. Sending also uses interrupts with 512-byte transmit buffers (511 usable bytes) via `HAL_UART_Transmit_IT` so data moves smoothly without freezing the loop; full transmit buffers are tracked separately from missed incoming bytes.
6. Main loop: `at_bridge_poll()` passes data back and forth in batches (turning Enter/CR from PuTTY into CR LF for the ESP) and warns if any bytes were dropped or failed to send.

**Code Base:**

- Project files: `CAT10A_STM32_Wemos_UART_Link.ioc` (CubeMX configuration), `MDK-ARM/CAT10A_STM32_Wemos_UART_Link.uvprojx` (Keil MDK), `.project` / `.cproject` (STM32CubeIDE); application code in `Core/Src/main.c`.
- `esp_read_line()` — reads a line with a timeout
- `at_command()` — collects replies until a final status word appears
- `at_show()` — prints the sent command and its replies

**Expected Output:**
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 10

**DATE:** 05/10/2026 (Tasks 10C/10d: 12/10/2026)

**NAME OF EXP:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands + HTTP Server

**HARDWARE SETUP / PLATFORM:** Blue Pill STM32F103C8T6 (Cortex-M3, 72 MHz) + Wemos D1 mini (ESP8266 AT firmware) + USB-to-TTL — STM32CubeMX + Keil MDK-ARM (STM32CubeIDE project also included), STM32 HAL, PuTTY

---

## TASK 9B : Explore the ESP8266 AT Command Interface

### 1. Circuit Diagram

| STM32 | Connected to | Purpose |
|---|---|---|
| PA9 USART1_TX | Wemos RX | Sends AT commands |
| PA10 USART1_RX | Wemos TX | Receives responses |
| PA2 USART2_TX / PA3 USART2_RX | USB-to-TTL RX / TX | Connects to PC terminal |
| GND | All GNDs | Common ground |

Both UARTs use **115200-8-N-1**. Wi-Fi passwords go in `Core/Inc/wifi_secrets.h` (ignored by git; check `wifi_config.h` for the layout).

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Every command you send must end with a new line (CR LF), and every reply from the modem finishes with a final status word (like `OK`). 

| Requirement | Command | Action |
|---|---|---|
| Modem response | `AT` | Checks if the Wi-Fi module is alive and responding |
| Firmware | `AT+GMR` | Checks the software/firmware version |
| Station mode | `AT+CWMODE=1` | Sets the ESP8266 to work as a Wi-Fi client (Station) |
| Scan | `AT+CWLAP` | Scans for nearby Wi-Fi networks |
| Join AP | `AT+CWJAP="ssid","pwd"` | Connects to your Wi-Fi router |
| Network info | `AT+CIFSR` | Displays local IP address details |
| TCP connection | `AT+CIPSTART="TCP","host",port` | Opens a TCP network connection to a server |
| Send data | `AT+CIPSEND=<len>` | Sends a specific number of bytes over TCP |

**Pseudocode:**

1. Start up the system (similar to Task 10A).
2. Automatically send basic configuration commands (`AT`, `AT+GMR`, `AT+CWMODE=1`, `AT+CWLAP`), collect their replies, and print them out.
3. Print a quick reference table of the commands.
4. Switch to bridge mode so you can type your own commands.

**Code Base:**

- Project files: `CAT10B_ESP8266_AT_Command_Explorer.ioc` (CubeMX configuration), `MDK-ARM/CAT10B_ESP8266_AT_Command_Explorer.uvprojx` (Keil MDK), `.project` / `.cproject` (STM32CubeIDE); application code in `Core/Src/main.c`.
- Incoming replies are temporarily saved in a 1 KB buffer before printing so that no data from the ESP is lost while writing text out to PuTTY.

**Expected Output:**

AT+GMR
<< AT version:...
<< SDK version:...
<< OK
AT+CWLAP
<< +CWLAP:(3,"SNUC",-58,...)
<< OK

```markdown
# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 10

**DATE:** 05/10/2026 (Tasks 10C/10d: 12/10/2026)

**NAME OF EXP:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands + HTTP Server

**HARDWARE SETUP / PLATFORM:** Blue Pill STM32F103C8T6 (Cortex-M3, 72 MHz) + Wemos D1 mini (ESP8266 AT firmware) + USB-to-TTL — STM32CubeMX + Keil MDK-ARM (STM32CubeIDE project also included), STM32 HAL, PuTTY

---

## TASK 9B : Explore the ESP8266 AT Command Interface

### 1. Circuit Diagram

| STM32 | Connected to | Purpose |
|---|---|---|
| PA9 USART1_TX | Wemos RX | Sends AT commands |
| PA10 USART1_RX | Wemos TX | Receives responses |
| PA2 USART2_TX / PA3 USART2_RX | USB-to-TTL RX / TX | Connects to PC terminal |
| GND | All GNDs | Common ground |

Both UARTs use **115200-8-N-1**. Wi-Fi passwords go in `Core/Inc/wifi_secrets.h` (ignored by git; check `wifi_config.h` for the layout).

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Every command you send must end with a new line (CR LF), and every reply from the modem finishes with a final status word (like `OK`). 

| Requirement | Command | Action |
|---|---|---|
| Modem response | `AT` | Checks if the Wi-Fi module is alive and responding |
| Firmware | `AT+GMR` | Checks the software/firmware version |
| Station mode | `AT+CWMODE=1` | Sets the ESP8266 to work as a Wi-Fi client (Station) |
| Scan | `AT+CWLAP` | Scans for nearby Wi-Fi networks |
| Join AP | `AT+CWJAP="ssid","pwd"` | Connects to your Wi-Fi router |
| Network info | `AT+CIFSR` | Displays local IP address details |
| TCP connection | `AT+CIPSTART="TCP","host",port` | Opens a TCP network connection to a server |
| Send data | `AT+CIPSEND=<len>` | Sends a specific number of bytes over TCP |

**Pseudocode:**

1. Start up the system (similar to Task 10A).
2. Automatically send basic configuration commands (`AT`, `AT+GMR`, `AT+CWMODE=1`, `AT+CWLAP`), collect their replies, and print them out.
3. Print a quick reference table of the commands.
4. Switch to bridge mode so you can type your own commands.

**Code Base:**

- Project files: `CAT10B_ESP8266_AT_Command_Explorer.ioc` (CubeMX configuration), `MDK-ARM/CAT10B_ESP8266_AT_Command_Explorer.uvprojx` (Keil MDK), `.project` / `.cproject` (STM32CubeIDE); application code in `Core/Src/main.c`.
- Incoming replies are temporarily saved in a 1 KB buffer before printing so that no data from the ESP is lost while writing text out to PuTTY.

**Expected Output:**


```

> > AT+GMR
> > << AT version:...
> > << SDK version:...
> > << OK
> > AT+CWLAP
> > << +CWLAP:(3,"SNUC",-58,...)
> > << OK
> 
> 

```

### 3. Inference

Simple request-and-response loops are fully sufficient to check the status of the Wi-Fi modem, read its firmware details, configure it into station mode, and scan for available wireless networks.

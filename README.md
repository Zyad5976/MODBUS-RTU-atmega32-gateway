# Modbus RTU Temperature Monitoring & Relay Control Gateway

Embedded systems project — an ATmega32-based Modbus RTU slave device that monitors temperature and controls a relay-driven load, communicating with a Modbus Master over an RS-485 bus.


---

## Overview

This project implements a **Modbus RTU slave device** on an ATmega32 microcontroller, communicating over an RS-485 physical layer via a **MAX485** transceiver. The device continuously monitors ambient temperature through an onboard ADC channel, drives a relay-controlled load (e.g. a cooling fan or motor) based on a configurable temperature threshold, and exposes both the live temperature reading and the threshold value as Modbus registers accessible to a remote Master.

A 16x2 character LCD provides local, human-readable status independently of the Modbus link, making the device usable as a standalone monitor as well as a networked slave node.

## Key Objectives

- Implement the Modbus RTU frame format (Slave ID, Function Code, Data, CRC16) **from scratch** at the byte level, with no third-party Modbus stack.
- Support two operating modes: read-only **Input Register** mode and read/write **Holding Register** mode, selectable at compile time.
- Drive a half-duplex RS-485 bus correctly via the MAX485's Driver-Enable/Receiver-Enable control line, synchronized with UART transmission.
- Apply a consistent layered driver architecture (**LIB / MCAL / HAL / APP**) for reuse of existing DIO/UART/TIM0/ADC drivers.

## Operating Modes

| Mode | Macro | Behavior |
|---|---|---|
| Input Register Mode | `MODBUS_INPUT_REG_MODE` | Temperature is read-only. Threshold is hardcoded at 35°C. Uses Function Code `0x04` (Read Input Registers). |
| Holding Register Mode | `MODBUS_HOLDING_REG_MODE` | Threshold becomes a writable register. Master can read (`0x03`) and write (`0x06`) the threshold remotely for dynamic reconfiguration. |

Selected via a compile-time macro in `MODBUS_CFG.h`.

## System Architecture

The firmware follows a four-layer architecture, letting existing DIO/UART/TIM0/ADC drivers be reused without modification:

| Layer | Responsibility | Modules |
|---|---|---|
| **LIB** | Shared types, bit-manipulation macros, interrupt vector definitions | `STD_TYPES.h`, `BIT_MATH.h`, `VECTOR_TABLE.h` |
| **MCAL** | Register-level control of on-chip peripherals | DIO, UART, TIM0, ADC |
| **HAL** | Drivers for external hardware, built on MCAL | MAX485, Relay, LCD, LED, BTN |
| **MODBUS** | Protocol engine: frame parsing, CRC16 validation, function-code dispatch | `MODBUS_voidInit()`, `MODBUS_voidTask()` |
| **APP** | Top-level application logic | `main.c` — temperature polling, relay control loop, LCD updates |

The MODBUS module sits above HAL/MCAL and below APP: it depends on MAX485 (physical link) and Relay/ADC (executing requested actions), but exposes only two functions upward, keeping framing and CRC logic fully encapsulated.

### RS-485 Half-Duplex Transmission

Unlike RS-232 or a direct point-to-point UART link, RS-485 is a shared, half-duplex bus — only one device may drive the line at any instant:

```c
MAX485_VoidSendByte(u8 copy_u8data)
{
    DE/RE pin -> HIGH   // enable transmitter, disable receiver
    UART_VoidSendData(copy_u8data)
    DE/RE pin -> LOW    // disable transmitter, enable receiver
}
```

This driver-enable toggling is why MAX485 exists as its own HAL module built on top of the UART MCAL driver, rather than being used directly.

## Modbus RTU Protocol Implementation

### Frame Format (8 bytes)

| Byte Offset | Field | Description |
|---|---|---|
| 0 | Slave Address | Fixed at `0x01` (`MODBUS_SLAVE_ID`) |
| 1 | Function Code | `0x03` / `0x04` / `0x05` |
| 2–5 | Data | Register/coil address and value fields, per standard Modbus RTU framing |
| 6–7 | CRC16 | Little-endian CRC16 (low byte first) covering bytes 0–5 |

### Supported Function Codes

| Code | Name | Behavior |
|---|---|---|
| `0x03` | Read Holding Registers | Returns current temperature or threshold as a 2-byte value |
| `0x04` | Read Input Registers | Returns live temperature computed from the ADC as a 2-byte value |
| `0x05` | Write Single Coil | Turns the relay ON (`0xFF00`) / OFF (`0x0000`); echoes the request frame as confirmation |

### CRC16 Validation

Every incoming frame is validated with the standard Modbus CRC16 algorithm (polynomial `0xA001`, initial value `0xFFFF`) before any function code is processed. Frames that fail Slave ID matching or CRC verification are silently discarded — correct behavior for a slave sharing a multi-drop bus.

```c
static u16 MODBUS_u16ClacCRC(u8 *pu8data, u8 u8length)
{
    u16 crc = 0xFFFF;
    for each byte:
        crc ^= byte
        for 8 bits:
            if (crc & 0x0001) crc = (crc >> 1) ^ 0xA001;
            else               crc = (crc >> 1);
    return crc;
}
```

### Frame Reception Strategy

Incoming bytes are accumulated non-blocking (`UART_u8ReceiveNoBlock()`) inside `MODBUS_voidTask()`, polled continuously from the main loop — keeping the Modbus engine cooperative with the rest of the application (temperature polling, LCD updates) instead of blocking the CPU. The first received byte is checked against the expected Slave ID; mismatched frames are discarded immediately. Once 8 bytes are accumulated, the frame is handed to `MODBUS_VoidProcessFrame()` for CRC validation and dispatch.

## Temperature Sensing & Relay Control

The ADC (channel 2) is polled every main-loop iteration and the raw 10-bit reading converted to °C:

```
Temp (°C) = (ADC_Value × 500) / 1024
```

This assumes a linear analog sensor with a 5V reference producing 10mV/°C (consistent with sensors like the LM35). The relay is switched based on comparison against the threshold — fixed at 35°C in Input Register mode, or the runtime-adjustable threshold in Holding Register mode. State transitions are reflected on the LCD, with a guard flag preventing redundant writes when the state hasn't changed.

## Bill of Materials

| Component | Qty | Role |
|---|---|---|
| ATmega32 Microcontroller | 1 | Main processing unit |
| MAX485 RS-485 Transceiver | 1 | Physical layer for Modbus RTU bus |
| Relay Module | 1 | Switches the temperature-controlled load |
| Analog Temperature Sensor | 1 | Input to ADC channel 2 |
| 16x2 Character LCD (HD44780-compatible) | 1 | Local status display |
| RS-485 Bus Termination / Wiring | As needed | Connects the slave to the Modbus Master |

## Hardware Interfaces

| Peripheral | Interface | Purpose |
|---|---|---|
| MAX485 Transceiver | UART (PD0/PD1) + DIO (PD2) | Converts UART TTL ↔ RS-485 differential bus; DE/RE pin toggled for TX/RX |
| Temperature Sensor | ADC Channel 2 | Raw analog voltage proportional to temperature |
| Relay Module | DIO (PC3) | Switches the controlled load ON/OFF |
| 16x2 LCD | DIO | Local display of temperature and relay status |

## Toolchain & Testing

- **IDE:** Atmel Studio
- **Simulation:** Proteus / SimulIDE
- **Master-side validation:** [Modbus Poll](https://www.modbustools.com/modbus_poll.html) as the Modbus Master, with **VSPE** (Virtual Serial Ports Emulator) creating a virtual COM port pair to bridge Modbus Poll to the target's UART on a PC without a physical RS-485 adapter — confirming correct read/write behavior against the Input and Holding Registers.

## Known Limitations

- CRC bytes in the local UART key-based simulation (`'r'`/`'w'` in `main.c`) are static placeholders for that fixed test payload; the real protocol path (`MODBUS_PRog.c`) computes CRC dynamically.
- Only Slave ID `0x01` is currently supported (constant-driven, easily extended to configurable/multi-slave).
- Master-side validation with Modbus Poll + VSPE used a virtual COM port; testing over a physical USB-to-RS485 adapter is still pending.

## Future Work

- [x] Integrate with a PC-based Modbus Master tool (Modbus Poll + VSPE) for end-to-end protocol validation
- [ ] Repeat validation over a physical USB-to-RS485 adapter
- [ ] Extend the addressable register map to support multiple sensors/relays per slave
- [ ] Add Modbus exception responses (Illegal Function, Illegal Data Address) for malformed/unsupported requests
- [ ] Support multi-slave addressing on a shared RS-485 bus

## Author

**Zyad Hussein** — Mechatronics Engineer
[LinkedIn](https://www.linkedin.com/in/zyad-hussien-35a790199)
# ESP32 Dual LED Controller

ESP32 project demonstrating advanced button control with two LEDs using OneButton library.

## 🎯 Features

- **Single Click**: Toggle current LED on/off
- **Double Click**: Switch control between LED1 and LED2  
- **Long Press (1s)**: Make current LED blink at 200ms interval
- **Serial Monitor**: Real-time status updates

## 🔌 Hardware Setup

### Components Required:
- ESP32 DevKit v1
- 1x External LED
- 1x 220Ω Resistor (for external LED)
- 1x Push Button
- Breadboard and jumper wires

### Pin Connections:
```
ESP32 Pin  | Component        | Notes
-----------|------------------|------------------
GPIO 2     | LED1 (Built-in)  | On-board LED
GPIO 32    | LED2 (External)  | Through 220Ω resistor
GPIO 34    | Button           | Input-only pin, internal pull-up
GND        | Button & LED2    | Common ground
3.3V       | LED2 Anode       | Through resistor
```

### Circuit Diagram:
```
ESP32                     External Components
                         
GPIO 2 ──── LED1 (built-in)
                         
GPIO 32 ──── 220Ω ──── LED2(+)
                         │
GND ─────────────────────┴─── LED2(-)

GPIO 34 ──── Button ──── GND
     │
   (Internal Pull-up)
```

## 💻 Software Features

### Button Functions:
| Action | Function | Description |
|--------|----------|-------------|
| **Single Click** | Toggle LED | Turn current LED on/off |
| **Double Click** | Switch Control | Change between LED1 ⟷ LED2 |
| **Long Press** | Blink Mode | Current LED blinks every 200ms |

### Serial Output Example:
```
=== ESP32 Dual LED Controller ===
Hardware Setup:
- LED1 (Built-in): GPIO 2
- LED2 (External): GPIO 32
- Button: GPIO 34 (internal pull-up)

Controls:
- Single Click: Toggle current LED
- Double Click: Switch LED control
- Hold (1s): Blink current LED

Current Control: LED1 | LED1: OFF | LED2: OFF
Single Click - Toggled LED1 - State: ON
Double Click - Switched to LED2 control
```

## 🚀 Getting Started

### Prerequisites:
- PlatformIO IDE
- ESP32 DevKit v1
- Hardware components listed above

### Installation:
```bash
# Clone repository
git clone https://github.com/Dao-Anh-Phuc/B2_Blink_2_led.git
cd B2_Blink_2_led

# Build project
pio run

# Upload to ESP32
pio run --target upload

# Monitor serial output
pio device monitor
```

## 📊 Project Structure

```
B2_Blink_2_led/
├── src/
│   └── main.cpp          # Main application code
├── platformio.ini        # PlatformIO configuration
├── README.md            # Project documentation
└── .gitignore           # Git ignore rules
```

## 🔧 Configuration

### Pin Definitions (in platformio.ini):
```ini
build_flags =
    '-D LED1_PIN=2U'      ; Built-in LED
    '-D LED2_PIN=32U'     ; External LED  
    '-D BUTTON_PIN=34U'   ; External button
```

### Button Timing:
- **Click Timeout**: 250ms
- **Debounce Time**: 50ms  
- **Long Press**: 1000ms (1 second)
- **Blink Interval**: 200ms

## 📝 Code Highlights

- ✅ **ESP32 GPIO 34** - properly configured for input-only pin with internal pull-up
- ✅ **Non-blocking blink** - using millis() for timing
- ✅ **State management** - clean separation of LED states
- ✅ **OneButton library** - advanced button handling with debouncing
- ✅ **Serial debugging** - comprehensive status reporting

## 🎓 Learning Objectives

This project demonstrates:
- OneButton library advanced usage
- ESP32 GPIO configuration (input-only pins)
- State machine programming
- Non-blocking timing techniques
- Serial communication for debugging

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

## 👨‍💻 Author

Created by Dao Anh Phuc as part of ESP32 learning series.

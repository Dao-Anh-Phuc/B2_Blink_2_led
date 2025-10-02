#include <Arduino.h>
#include <OneButton.h>

// Note: Pin definitions are in platformio.ini build_flags
// LED1_PIN = 2 (Built-in LED)
// LED2_PIN = 32 (External LED) 
// BUTTON_PIN = 34 (External button)

// LED control variables
bool led1_active = true;  // true = controlling LED1, false = controlling LED2
bool led1_state = false;
bool led2_state = false;
bool blink_mode = false;
unsigned long last_blink_time = 0;
const unsigned long BLINK_INTERVAL = 200;

// Button object with internal pull-up (GPIO35 input-only, needs pull-up)
OneButton button(BUTTON_PIN, true, true);  // pin, activeLow, pullupActive

// Function declarations
void singleClick();
void doubleClick();
void longPressStart();
void longPressStop();
void updateLEDs();
void toggleCurrentLED();
void switchLEDControl();
void startBlink();
void stopBlink();
void printStatus();

void setup() {
    Serial.begin(115200);
    delay(1000);  // Wait for serial to initialize
    
    Serial.println("=== ESP32 Dual LED Controller ===");
    Serial.println("Hardware Setup:");
    Serial.printf("- LED1 (Built-in): GPIO %d\n", LED1_PIN);
    Serial.printf("- LED2 (External): GPIO %d\n", LED2_PIN);
    Serial.printf("- Button: GPIO %d (internal pull-up)\n", BUTTON_PIN);
    Serial.println("\nControls:");
    Serial.println("- Single Click: Toggle current LED");
    Serial.println("- Double Click: Switch LED control");
    Serial.println("- Hold (1s): Blink current LED");
    Serial.println("=====================================\n");
    
    // Initialize LED pins
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    
    // Turn off both LEDs initially
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    
    // Configure button callbacks
    button.attachClick(singleClick);
    button.attachDoubleClick(doubleClick);
    button.attachLongPressStart(longPressStart);
    button.attachLongPressStop(longPressStop);
    
    // Configure button timing
    button.setClickMs(250);       // Max time for single click
    button.setDebounceMs(50);     // Debounce time
    button.setPressMs(1000);      // Long press time (1 second)
    
    printStatus();
}

void loop() {
    // Handle button events
    button.tick();
    
    // Handle LED blinking
    if (blink_mode) {
        unsigned long current_time = millis();
        if (current_time - last_blink_time >= BLINK_INTERVAL) {
            toggleCurrentLED();
            last_blink_time = current_time;
        }
    }
    
    // Update LED states
    updateLEDs();
}

void singleClick() {
    if (!blink_mode) {  // Only toggle if not in blink mode
        toggleCurrentLED();
        Serial.printf("Single Click - Toggled LED%d - State: %s\n", 
                     led1_active ? 1 : 2, 
                     (led1_active ? led1_state : led2_state) ? "ON" : "OFF");
    }
}

void doubleClick() {
    stopBlink();  // Stop blinking when switching
    switchLEDControl();
    Serial.printf("Double Click - Switched to LED%d control\n", led1_active ? 1 : 2);
    printStatus();
}

void longPressStart() {
    startBlink();
    Serial.printf("Long Press - LED%d blinking started (200ms interval)\n", 
                 led1_active ? 1 : 2);
}

void longPressStop() {
    stopBlink();
    Serial.printf("Long Press Released - LED%d blinking stopped\n", 
                 led1_active ? 1 : 2);
}

void toggleCurrentLED() {
    if (led1_active) {
        led1_state = !led1_state;
    } else {
        led2_state = !led2_state;
    }
}

void switchLEDControl() {
    led1_active = !led1_active;
}

void startBlink() {
    blink_mode = true;
    last_blink_time = millis();
}

void stopBlink() {
    blink_mode = false;
}

void updateLEDs() {
    digitalWrite(LED1_PIN, led1_state ? HIGH : LOW);
    digitalWrite(LED2_PIN, led2_state ? HIGH : LOW);
}

void printStatus() {
    Serial.printf("Current Control: LED%d | LED1: %s | LED2: %s\n", 
                 led1_active ? 1 : 2,
                 led1_state ? "ON" : "OFF",
                 led2_state ? "ON" : "OFF");
}
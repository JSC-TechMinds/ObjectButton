/**
 * @brief Single analog button, click example.
 *
 * This sketch demonstrates using ObjectButton library with single analog button,
 * which will turn built-in LED on or off after being clicked.
 *
 * ObjectButton library: https://github.com/JSC-electronics/ObjectButton
 * 
 * Copyright © JSC electronics
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ObjectButton.h>
using namespace jsc;

constexpr static byte BUTTON_ID = 1;
constexpr static byte INPUT_PIN = A1;
constexpr static int ON_PRESS_VOLTAGE = 1000;
constexpr static byte LED_PIN = LED_BUILTIN;

class ToggleLedOnClick : private virtual IOnClickListener {
public:
    ToggleLedOnClick() = default;

    void init();

    void update();

private:
    void onClick(Button& button) override;

    AnalogButton button = AnalogButton(BUTTON_ID, INPUT_PIN, ON_PRESS_VOLTAGE);
    byte ledState = LOW;
};

void ToggleLedOnClick::onClick(Button& button) {
    if (button.getId() == BUTTON_ID) {
        Serial.println("Button clicked!");

        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}

void ToggleLedOnClick::init() {
    // Setup the Serial port. See http://arduino.cc/en/Serial/IfSerial
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for Leonardo only
    }
    pinMode(LED_PIN, OUTPUT);
    button.setDebounceTicks(10);
    button.setOnClickListener(this);
}

void ToggleLedOnClick::update() {
    button.tick();
}

ToggleLedOnClick toggleLedOnClick = ToggleLedOnClick();

void setup() {
    toggleLedOnClick.init();
}

void loop() {
    toggleLedOnClick.update();
}

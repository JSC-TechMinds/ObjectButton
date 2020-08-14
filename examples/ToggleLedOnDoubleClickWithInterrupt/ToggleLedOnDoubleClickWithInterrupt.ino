/**
 * @brief Single digital button, double click with interrupt example.
 *
 * This sketch demonstrates using ObjectButton library with single digital button,
 * which will turn built-in LED on or off after being double-clicked.
 *
 * This example is almost identical to ToggleLedOnDoubleClick.ino, except
 * button state refresh is bound to interrupt.
 *
 * Copyright 2019-2020 JSC electronics
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

constexpr static byte INTERRUPT_PIN = 2;
constexpr static byte LED_PIN = LED_BUILTIN;

class ToggleLedOnDoubleClick : private virtual IOnDoubleClickListener {
public:
    ToggleLedOnDoubleClick() = default;

    void init();

    void update();

private:
    void onDoubleClick(Button& button) override;

    DigitalButton button = DigitalButton(INTERRUPT_PIN);
    volatile byte ledState = LOW;
};

void ToggleLedOnDoubleClick::onDoubleClick(Button& button) {
    if (button.getId() == INTERRUPT_PIN) {
        Serial.println("Button double-clicked!");

        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}

void ToggleLedOnDoubleClick::init() {
    // Setup the Serial port. See http://arduino.cc/en/Serial/IfSerial
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for Leonardo only
    }
    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    button.setDebounceTicks(10);
    button.setOnDoubleClickListener(this);
}

void ToggleLedOnDoubleClick::update() {
    button.tick();
}

ToggleLedOnDoubleClick toggleLedOnDoubleClick = ToggleLedOnDoubleClick();

void refreshButton() {
    toggleLedOnDoubleClick.update();
}

void setup() {
    toggleLedOnDoubleClick.init();
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), refreshButton, CHANGE);
}

void loop() {
    // Do some work
    delay(10);
}

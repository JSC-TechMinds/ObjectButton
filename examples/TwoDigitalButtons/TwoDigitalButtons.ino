/**
 * @brief Two distinct digital buttons example.
 *
 * This sketch demonstrates using ObjectButton library with two distinct digital buttons.
 *
 * In this example we receive all events produced by buttons and print
 * which event occurred on which button to the serial monitor.
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

constexpr static byte INPUT_PIN_BUTTON1 = A1;
constexpr static byte INPUT_PIN_BUTTON2 = A2;

class TwoButtons : private virtual IOnClickListener,
                   private virtual IOnDoubleClickListener, private virtual IOnPressListener {
public:
    TwoButtons() = default;

    void init();

    void update();

private:
    void onClick(Button& button) override;

    void onDoubleClick(Button& button) override;

    void onPress(Button& button) override;

    void onRelease(Button& button) override;

    void onLongPressStart(Button& button) override;

    void onLongPressEnd(Button& button) override;

    DigitalButton button1 = DigitalButton(INPUT_PIN_BUTTON1);
    DigitalButton button2 = DigitalButton(INPUT_PIN_BUTTON2);
};

void TwoButtons::onClick(Button& button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Button 1 clicked!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Button 2 clicked!");
            break;
    }
}

void TwoButtons::onDoubleClick(Button& button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Button 1 double-clicked!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Button 2 double-clicked!");
            break;
    }
}

void TwoButtons::onPress(Button& button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Button 1 pressed!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Button 2 pressed!");
            break;
    }
}

void TwoButtons::onRelease(Button& button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Button 1 released!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Button 2 released!");
            break;
    }
}

void TwoButtons::onLongPressStart(Button& button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Long press started on button 1!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Long press started on button 2!");
            break;
    }
}

void TwoButtons::onLongPressEnd(Button& button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Long press ended on button 1!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Long press ended on button 2!");
            break;
    }
}

void TwoButtons::init() {
    // Setup the Serial port. See http://arduino.cc/en/Serial/IfSerial
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("Starting TwoButtons...");

    button1.setDebounceTicks(10);
    button1.setOnClickListener(this);
    button1.setOnDoubleClickListener(this);
    button1.setOnPressListener(this);

    button2.setDebounceTicks(10);
    button2.setOnClickListener(this);
    button2.setOnDoubleClickListener(this);
    button2.setOnPressListener(this);
}

void TwoButtons::update() {
    button1.tick();
    button2.tick();
}

TwoButtons twoButtons = TwoButtons();

void setup() {
    twoButtons.init();
}

void loop() {
    twoButtons.update();
}

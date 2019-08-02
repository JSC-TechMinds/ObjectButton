/**
 * Copyright 2019 JSC electronics
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
#include <interfaces/IOnClickListener.h>

constexpr static byte INPUT_PIN_BUTTON1 = A1;
constexpr static byte INPUT_PIN_BUTTON2 = A2;

class TwoButtons : private virtual IOnClickListener,
                   private virtual IOnDoubleClickListener, private virtual IOnPressListener {
public:
    TwoButtons() = default;

    void init();
    void update();

private:
    void onClick(ObjectButton &button) override;

    void onDoubleClick(ObjectButton &button) override;

    void onPress(ObjectButton &button) override;

    void onRelease(ObjectButton &button) override;

    void onLongPressStart(ObjectButton &button) override;

    void onLongPressEnd(ObjectButton &button) override;

    ObjectButton button1 = ObjectButton(INPUT_PIN_BUTTON1, /* activeLow */ true);
    ObjectButton button2 = ObjectButton(INPUT_PIN_BUTTON2, /* activeLow */ true);
};

void TwoButtons::onClick(ObjectButton &button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Button 1 clicked!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Button 2 clicked!");
            break;
    }
}

void TwoButtons::onDoubleClick(ObjectButton &button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Button 1 double-clicked!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Button 2 double-clicked!");
            break;
    }
}

void TwoButtons::onPress(ObjectButton &button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Button 1 pressed!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Button 2 pressed!");
            break;
    }
}

void TwoButtons::onRelease(ObjectButton &button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Button 1 released!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Button 2 released!");
            break;
    }
}

void TwoButtons::onLongPressStart(ObjectButton &button) {
    switch (button.getId()) {
        case INPUT_PIN_BUTTON1:
            Serial.println("Long press started on button 1!");
            break;
        case INPUT_PIN_BUTTON2:
            Serial.println("Long press started on button 2!");
            break;
    }
}

void TwoButtons::onLongPressEnd(ObjectButton &button) {
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
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
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

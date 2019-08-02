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
#include <interfaces/IOnPressListener.h>

constexpr static int INPUT_PIN = A1;
constexpr static int LED_PIN = LED_BUILTIN;

class TurnLedOnLongPress : private virtual IOnPressListener {
public:
    TurnLedOnLongPress() = default;

    void init();
    void update();

private:
    void onPress(ObjectButton& button) override {};
    void onRelease(ObjectButton& button) override {};
    void onLongPressStart(ObjectButton& button) override;
    void onLongPressEnd(ObjectButton& button) override;

    ObjectButton button = ObjectButton(INPUT_PIN, /* activeLow */ true);
};

void TurnLedOnLongPress::onLongPressStart(ObjectButton &button){
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button long press started, turning LED on!");
        digitalWrite(LED_PIN, HIGH);
    }
}

void TurnLedOnLongPress::onLongPressEnd(ObjectButton &button){
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button long press ended, turning LED off!");
        digitalWrite(LED_PIN, LOW);
    }
}

void TurnLedOnLongPress::init() {
    // Setup the Serial port. see http://arduino.cc/en/Serial/IfSerial
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    pinMode(LED_PIN, OUTPUT);
    button.setDebounceTicks(10);
    button.setOnPressListener(this);
}

void TurnLedOnLongPress::update() {
    button.tick();
}

TurnLedOnLongPress turnLedOnLongPress = TurnLedOnLongPress();

void setup() {
    turnLedOnLongPress.init();
}

void loop() {
    turnLedOnLongPress.update();
}

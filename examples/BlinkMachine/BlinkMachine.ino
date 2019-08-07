/**
 *
 * @brief A more complicated blink state machine example.
 *
 * - Turn built-in LED on or off with a click gesture.
 * - Toggle built-in LED blinking between steady, slow and fast state with a double click gesture.
 *
 * This example is heavily inspired by a sketch from OneButton library:
 * https://github.com/mathertel/OneButton/blob/master/examples/BlinkMachine/BlinkMachine.ino
 * See their sketch for more details on internal workings, if it's not clear for your from this code.
 *
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
#include <interfaces/IOnDoubleClickListener.h>

constexpr static byte INPUT_PIN = A1;
constexpr static byte LED_PIN = LED_BUILTIN;

class BlinkMachine : private virtual IOnClickListener,
                     private virtual IOnDoubleClickListener {
public:
    BlinkMachine() = default;

    void init();

    void update();

private:
    void onClick(ObjectButton &button) override;

    void onDoubleClick(ObjectButton &button) override;

    enum class Action {
        ACTION_OFF,
        ACTION_ON,
        ACTION_SLOW,
        ACTION_FAST
    };

    Action m_nextAction = Action::ACTION_OFF;
    ObjectButton button = ObjectButton(INPUT_PIN, /* activeLow */ true);
};

void BlinkMachine::onClick(ObjectButton &button) {
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button clicked!");
        m_nextAction = m_nextAction == Action::ACTION_OFF ?
                       Action::ACTION_ON : Action::ACTION_OFF;
    }
}

void BlinkMachine::onDoubleClick(ObjectButton &button) {
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button double-clicked!");

        switch (m_nextAction) {
            case Action::ACTION_ON:
                m_nextAction = Action::ACTION_SLOW;
                break;
            case Action::ACTION_SLOW:
                m_nextAction = Action::ACTION_FAST;
                break;
            case Action::ACTION_FAST:
                m_nextAction = Action::ACTION_ON;
                break;
            default:
                // No-OP
                break;
        }
    }
}

void BlinkMachine::init() {
    // Setup the Serial port. See http://arduino.cc/en/Serial/IfSerial
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for Leonardo only
    }
    pinMode(LED_PIN, OUTPUT);
    button.setDebounceTicks(80);
    button.setOnClickListener(this);
    button.setOnDoubleClickListener(this);
}

void BlinkMachine::update() {
    unsigned long now = millis();
    button.tick();

    switch (m_nextAction) {
        case Action::ACTION_OFF:
            // do nothing.
            digitalWrite(LED_PIN, LOW);
            break;
        case Action::ACTION_ON:
            // turn LED on
            digitalWrite(LED_PIN, HIGH);
            break;
        case Action::ACTION_SLOW:
            // do a slow blinking
            digitalWrite(LED_PIN, now % 1000 < 500 ? LOW : HIGH);
            break;
        case Action::ACTION_FAST:
            // do a fast blinking
            digitalWrite(LED_PIN, now % 200 < 100 ? LOW : HIGH);
            break;
    }
}

BlinkMachine blinkMachine = BlinkMachine();

void setup() {
    blinkMachine.init();
}

void loop() {
    blinkMachine.update();
}

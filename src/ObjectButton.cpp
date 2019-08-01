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

#include <Arduino.h>
#include "ObjectButton.h"

ObjectButton::ObjectButton(uint8_t pin, bool activeLow) {
    m_pin = pin;
    m_buttonPressed = activeLow ? LOW : HIGH;
    m_buttonReleased = activeLow ? HIGH : LOW;
    pinMode(m_pin, activeLow ? INPUT_PULLUP : INPUT);
}

int ObjectButton::getId() {
    return m_pin;
}

void ObjectButton::setOnClickListener(IOnClickListener* listener) {
    m_onClickListener = listener;
}

void ObjectButton::setOnDoubleClickListener(IOnDoubleClickListener* listener) {
    m_onDoubleClickListener = listener;
}

void ObjectButton::setOnPressListener(IOnPressListener *listener) {
    m_onPressListener = listener;
}

void ObjectButton::setDebounceTicks(uint8_t ticks) {
    m_debounceTicks = ticks;
}

void ObjectButton::setClickTicks(uint16_t ticks) {
    m_clickTicks = ticks;
}

void ObjectButton::setPressTicks(uint16_t ticks) {
    m_longPressTicks = ticks;
}

bool ObjectButton::isLongPressed() {
    return m_state == State::BUTTON_LONG_PRESSED;
}

void ObjectButton::reset(void){
    m_state = State::BUTTON_NOT_PRESSED; // restart.
    m_buttonPressedTime = 0L;
    m_buttonReleasedTime = 0L;
}

void ObjectButton::tick() {
    // Detect the input information
    int buttonLevel = digitalRead(m_pin); // current button signal
    unsigned long now = millis(); // current (relative) time in milliseconds

    switch (m_state) {
        case State::BUTTON_NOT_PRESSED: {
            if (buttonLevel == m_buttonPressed) {
                m_state = State::BUTTON_PRESSED;
                m_buttonPressedTime = now;
            }
            break;
        }
        case State::BUTTON_PRESSED: {
            if (buttonLevel == m_buttonPressed) {
                if ((now - m_buttonPressedTime) > m_longPressTicks) {
                    m_state = State::BUTTON_LONG_PRESSED;
                }
            } else if (buttonLevel == m_buttonReleased) {
                if ((now - m_buttonPressedTime) < m_debounceTicks) {
                    m_state = State::BUTTON_NOT_PRESSED;
                } else {
                    notifyOnButtonRelease();

                    /* FIXME: Disable this code until it is properly tested
                    if ((now - m_buttonPressedTime) > m_clickTicks) {
                        m_state = State::BUTTON_CLICKED;
                    } else {
                        m_state = State::BUTTON_RELEASED;
                    } */
                    m_state = State::BUTTON_NOT_PRESSED;
                }

                m_buttonReleasedTime = now;
            }
            break;
        }
        case State::BUTTON_LONG_PRESSED: {
            if (buttonLevel == m_buttonReleased) {
                m_state = State::BUTTON_NOT_PRESSED;
                m_buttonReleasedTime = now;
                notifyOnButtonRelease();
            }
            break;
        }
        case State::BUTTON_RELEASED: {
            if (buttonLevel == m_buttonPressed && (now - m_buttonReleasedTime) > m_debounceTicks) {
                m_state = State::BUTTON_DOUBLE_CLICKED;
                m_buttonPressedTime = now;
            }
            break;
        }
        case State::BUTTON_CLICKED: {
            m_state = State::BUTTON_NOT_PRESSED;
            notifyOnDoubleClick();
            break;
        }
        case State::BUTTON_DOUBLE_CLICKED: {
            if (buttonLevel == m_buttonReleased && (now - m_buttonPressedTime) > m_debounceTicks) {
                // double-click detected
                m_state = State::BUTTON_NOT_PRESSED;
            }
            break;
        }
    }
}

void ObjectButton::notifyOnClick(void) {
    if (m_onClickListener != nullptr)
        m_onClickListener->onClick(*this);
}

void ObjectButton::notifyOnDoubleClick(){
    if (m_onDoubleClickListener != nullptr)
        m_onDoubleClickListener->onDoubleClick(*this);
}

void ObjectButton::notifyOnButtonPress(){
    if (m_onPressListener != nullptr)
        m_onPressListener->onPress(*this);
}

void ObjectButton::notifyOnButtonRelease(){
    if (m_onPressListener != nullptr)
        m_onPressListener->onRelease(*this);
}

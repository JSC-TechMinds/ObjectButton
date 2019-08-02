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

void ObjectButton::setLongPressTicks(uint16_t ticks) {
    m_longPressTicks = ticks;
}

bool ObjectButton::isPressed() {
    return m_state == State::BUTTON_PRESSED;
}

bool ObjectButton::isLongPressed() {
    return m_state == State::BUTTON_PRESSED && m_isLongButtonPress;
}

void ObjectButton::reset() {
    m_state = State::BUTTON_NOT_PRESSED; // restart.
    m_isLongButtonPress = false;
    m_buttonPressNotified = false;
    m_buttonPressedTime = 0L;
    m_buttonReleasedTime = 0L;
}

void ObjectButton::tick() {
    // Detect the input information
    int buttonLevel = digitalRead(m_pin); // current button signal
    unsigned long now = millis();
    unsigned long timeDelta = now - m_buttonPressedTime; // relative time difference between button press and release

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
                if (timeDelta > m_debounceTicks && !m_buttonPressNotified) {
                    m_buttonPressNotified = true;
                    notifyOnButtonPress();
                }

                if (timeDelta > m_longPressTicks && !m_isLongButtonPress) {
                    m_isLongButtonPress = true;
                    notifyOnLongPressStart();
                }
            } else {
                if (timeDelta <= m_debounceTicks) {
                    m_state = State::BUTTON_NOT_PRESSED;
                } else {
                    m_state = State::BUTTON_RELEASED;
                    m_buttonPressNotified = false;
                    notifyOnButtonRelease();
                }
                m_buttonReleasedTime = now;
            }
            break;
        }
        case State::BUTTON_RELEASED: {
            if (buttonLevel == m_buttonPressed && (now - m_buttonReleasedTime) > m_debounceTicks) {
                m_buttonPressedTime = now;
                m_state = State::BUTTON_DOUBLE_CLICKED;
            } else if (m_clickTicks < timeDelta && timeDelta < m_longPressTicks) {
                m_state = State::BUTTON_NOT_PRESSED;
                notifyOnClick();
            } else if (timeDelta > m_longPressTicks) {
                m_isLongButtonPress = false;
                m_state = State::BUTTON_NOT_PRESSED;
                notifyOnLongPressEnd();
            }
            break;
        }
        case State::BUTTON_DOUBLE_CLICKED: {
            if (buttonLevel != m_buttonPressed && timeDelta > m_debounceTicks) {
                m_state = State::BUTTON_NOT_PRESSED;
                notifyOnDoubleClick();
            }
            break;
        }
    }
}

void ObjectButton::notifyOnClick() {
    if (m_onClickListener != nullptr)
        m_onClickListener->onClick(*this);
}

void ObjectButton::notifyOnDoubleClick() {
    if (m_onDoubleClickListener != nullptr)
        m_onDoubleClickListener->onDoubleClick(*this);
}

void ObjectButton::notifyOnButtonPress() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onPress(*this);
}

void ObjectButton::notifyOnButtonRelease() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onRelease(*this);
}

void ObjectButton::notifyOnLongPressStart(){
    if (m_onPressListener != nullptr)
        m_onPressListener->onLongPressStart(*this);
}

void ObjectButton::notifyOnLongPressEnd(){
    if (m_onPressListener != nullptr)
        m_onPressListener->onLongPressEnd(*this);
}

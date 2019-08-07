/**
 *  @file       ObjectButton.cpp
 *  Project     ObjectButton
 *  @brief      An Arduino library for processing GPIO inputs as button actions
 *  @author     Vladimír Záhradník
 *  @license    Apache-2.0 - Copyright (c) 2019 JSC electronics
 *
 *  @section license License
 *
 *  Copyright (c) 2019 JSC electronics
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

/**
 * @brief Constructor for the class.
 * @param pin an input pin to use for the button.
 * @param activeLow determines pin state after button press. Set to <code>true</code> if voltage level
 * on input pin is <code>LOW</code> after button is pressed. Otherwise set to <code>false</code>.
 */
ObjectButton::ObjectButton(uint8_t pin, bool activeLow) {
    m_pin = pin;
    m_buttonPressed = activeLow ? LOW : HIGH;
    pinMode(m_pin, activeLow ? INPUT_PULLUP : INPUT);
}

/**
 * @brief Get button identifier.
 *
 * Each ObjectButton has its own identification. This allows us to receive events from multiple buttons
 * in one common method and based on button ID do different actions. Button ID corresponds to input
 * pin number.
 *
 * @return button ID as an integer.
 */
int ObjectButton::getId() {
    return m_pin;
}

/**
 * @brief Set a listener to receive an event after a button is clicked.
 *
 * This listener gets notified each time a button is clicked. A click gesture
 * occurs when a button is pressed and released once within <code>m_clickTicks</code> period.
 * Until this period elapses, we cannot tell that click event occurred, because user could
 * still perform a double-click gesture.
 *
 * In cases where you work on a project requiring event notifications as soon as they happen,
 * we do recommend to handle <code>onPress</code> and <code>onRelease</code> events defined
 * in <code>IOnPressListener</code>. These events fire almost immediately (after debounce time elapses).
 *
 * Button press and release should not occur sooner than defined in <code>m_debounceTicks</code>. This would
 * signal random signal changes on input pin, not an user action.
 *
 *
 * @param listener object implementing <code>IOnClickListener</code> interface.
 *
 * @see IOnClickListener.h
 * @see void setDebounceTicks(uint8_t ticks)
 */
void ObjectButton::setOnClickListener(IOnClickListener *listener) {
    m_onClickListener = listener;
}

/**
 * @brief Set a listener to receive an event after a button is double-clicked.
 *
 * This listener gets notified each time a button is double-clicked. A double-click gesture
 * occurs when a button is rapidly pressed and released two times in a very short time period,
 * which does not exceed <code>m_clickTicks</code>.
 *
 * Button press and release should not occur sooner than defined in <code>m_debounceTicks</code>. This would
 * signal random signal changes on input pin, not an user action.
 *
 * @param listener object implementing <code>IOnDoubleClickListener</code> interface.
 *
 * @see IOnDoubleClickListener.h
 * @see uint16_t m_clickTicks
 * @see void setDebounceTicks(uint8_t ticks)
 */
void ObjectButton::setOnDoubleClickListener(IOnDoubleClickListener *listener) {
    m_onDoubleClickListener = listener;
}

/**
 * @brief Set a listener to receive event on button press and release.
 *
 * This listener gets notified on each button press and release. Additionally it gets notified that
 * a button was long pressed and released afterwards. After which time is a press declared as a long press
 * is user-configurable.
 *
 * <code>onPress</code> and <code>onRelease</code> events fire almost immediately (after debounce time elapses)
 * and are suitable for use cases where you need to get event notification as soon as an event occurs.
 *
 * Button press and release should not occur sooner than defined in <code>m_debounceTicks</code>. This would
 * signal random signal changes on input pin, not an user action.
 *
 *
 * @param listener object implementing <code>IOnPressListener</code> interface.
 *
 * @see IOnPressListener.h
 * @see uint16_t m_longPressTicks
 * @see void setDebounceTicks(uint8_t ticks)
 */
void ObjectButton::setOnPressListener(IOnPressListener *listener) {
    m_onPressListener = listener;
}

/**
 * @brief Set debounce time interval.
 *
 * To prevent random signal changes on input pin to trigger an event, we define a debounce interval.
 * Only when the button is pressed for longer than debounce, it is assumed to be a user action.
 *
 * Default value is defined in <code>DEFAULT_DEBOUNCE_TICKS_MS</code>.
 *
 * @param ticks a debounce time interval in milliseconds.
 */
void ObjectButton::setDebounceTicks(uint8_t ticks) {
    m_debounceTicks = ticks;
}

/**
 * @brief Set time interval to detect a click event.
 *
 * Sets a time interval, after which it is safe to assume that a click event has occurred.
 * Default value is defined in <code>DEFAULT_CLICK_TICKS_MS</code>.
 *
 * @param ticks a click time interval in milliseconds.
 */
void ObjectButton::setClickTicks(uint16_t ticks) {
    m_clickTicks = ticks;
}

/**
 * @brief Set time interval to detect a long press event.
 *
 * Sets a time interval, after which it is safe to assume that a long press event has occurred.
 * Default value is defined in <code>DEFAULT_LONG_PRESS_TICKS_MS</code>.
 *
 * @param ticks a long press time interval in milliseconds.
 */
void ObjectButton::setLongPressTicks(uint16_t ticks) {
    m_longPressTicks = ticks;
}

/**
 * @brief Tell the user if the button is pressed at a given moment.
 * @return <code>true</code> is the button is pressed, <code>false</code> otherwise.
 */
bool ObjectButton::isPressed() {
    return m_state == State::BUTTON_PRESSED;
}

/**
 * @brief Tell the user if the button is long pressed at a given moment.
 *
 * A button is considered to be long pressed after it is held for longer than <code>m_longPressTicks</code>.
 *
 * @return <code>true</code> is the button is long pressed, <code>false</code> otherwise.
 */
bool ObjectButton::isLongPressed() {
    return m_state == State::BUTTON_PRESSED && m_isLongButtonPress;
}

/**
 * @brief Reset button state.
 *
 * This method resets internal state machine and all the flags to their default values.
 * If you set custom debounce, click or long press intervals, these will also be reset to their
 * default values.
 */
void ObjectButton::reset() {
    m_state = State::BUTTON_NOT_PRESSED;
    m_isLongButtonPress = false;
    m_buttonPressNotified = false;
    m_buttonPressedTime = 0L;
    m_buttonReleasedTime = 0L;

    m_debounceTicks = DEFAULT_DEBOUNCE_TICKS_MS;
    m_clickTicks = DEFAULT_CLICK_TICKS_MS;
    m_longPressTicks = DEFAULT_LONG_PRESS_TICKS_MS;
}

/**
 * @brief Update internal state machine.
 *
 * This method is responsible for updating internal state machine
 * responsible for handling button events and should be called periodically
 * in your <code>loop()</code> function.
 */
void ObjectButton::tick() {
    // Detect the input information
    int buttonLevel = digitalRead(m_pin);
    unsigned long now = millis();

    // Relative time difference between button press and release
    unsigned long timeDelta = now - m_buttonPressedTime;

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
            } else if (timeDelta > m_longPressTicks) {
                m_isLongButtonPress = false;
                m_state = State::BUTTON_NOT_PRESSED;
                notifyOnLongPressEnd();
            } else if (timeDelta > m_clickTicks) {
                m_state = State::BUTTON_NOT_PRESSED;
                notifyOnClick();
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

/**
 * @brief Notify listener on click event.
 */
void ObjectButton::notifyOnClick() {
    if (m_onClickListener != nullptr)
        m_onClickListener->onClick(*this);
}

/**
 * @brief Notify listener on double-click event.
 */
void ObjectButton::notifyOnDoubleClick() {
    if (m_onDoubleClickListener != nullptr)
        m_onDoubleClickListener->onDoubleClick(*this);
}

/**
 * @brief Notify listener on button press event.
 */
void ObjectButton::notifyOnButtonPress() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onPress(*this);
}

/**
 * @brief Notify listener on button release event.
 */
void ObjectButton::notifyOnButtonRelease() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onRelease(*this);
}

/**
 * @brief Notify listener on long press start event.
 */
void ObjectButton::notifyOnLongPressStart() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onLongPressStart(*this);
}

/**
 * @brief Notify listener on long press end event.
 */
void ObjectButton::notifyOnLongPressEnd() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onLongPressEnd(*this);
}

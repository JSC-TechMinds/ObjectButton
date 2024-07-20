/**
 *  @file       Button.cpp
 *  Project     ObjectButton
 *  @brief      An Arduino library for detecting button actions.
 *  @author     JSC TechMinds
 *  License     Apache-2.0 - Copyright (c) 2019-2024 JSC TechMinds
 *
 *  @section License
 *
 *  Copyright (c) 2019-2024 JSC TechMinds
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

#include "Button.h"
using namespace jsc;

/**
 * @brief Constructor for the class.
 * @param pin an input pin to use for the button.
 * @param inputPullUp determines pin state after button press. Set to <code>true</code> if voltage level
 * on input pin is <code>LOW</code> after button is pressed. Otherwise set to <code>false</code>.
 */
Button::Button(uint8_t pin, bool inputPullUp) : m_pin(pin) {
    pinMode(pin, inputPullUp ? INPUT_PULLUP : INPUT);
}

/**
 * @brief Set a listener to receive an event after a button is clicked.
 *
 * This listener gets notified each time a button is clicked. A click gesture
 * occurs when a button is pressed and released once within <code>m_clickTicks</code> period.
 * Until this period elapses, we cannot tell that click event has occurred, because user could
 * still perform a double-click gesture.
 *
 * In cases where you work on a project requiring notifications on events as soon as they happen,
 * we do recommend to handle <code>onPress</code> and <code>onRelease</code> events defined
 * in IOnPressListener instead. These events fire almost immediately (after debounce time has elapsed).
 *
 * Button press and release should not occur sooner than defined in <code>m_debounceTicks</code>. This would
 * signal random signal changes on input pin, not an user action.
 *
 *
 * @param listener object implementing IOnClickListener interface.
 *
 * @see IOnClickListener.h
 * @see IOnPressListener.h
 * @see setDebounceTicks(uint8_t ticks)
 */
void Button::setOnClickListener(IOnClickListener *listener) {
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
 * signal random signal changes on input pin, not a user action.
 *
 * @param listener object implementing IOnDoubleClickListener interface.
 *
 * @see IOnDoubleClickListener.h
 * @see Button#m_clickTicks
 * @see setDebounceTicks(uint8_t ticks)
 */
void Button::setOnDoubleClickListener(IOnDoubleClickListener *listener) {
    m_onDoubleClickListener = listener;
}

/**
 * @brief Set a listener to receive event on button press and release.
 *
 * This listener gets notified on each button press and release. Additionally it gets notified that
 * a button was long pressed and released afterwards. Time after which a button press is declared as a long press
 * is user-configurable.
 *
 * <code>onPress</code> and <code>onRelease</code> events fire almost immediately (after debounce time elapses)
 * and are suitable for use cases where you need to get event notification as soon as an event occurs.
 *
 * Button press and release should not occur sooner than defined in <code>m_debounceTicks</code>. This would
 * signal random signal changes on input pin, not a user action.
 *
 * @param listener object implementing IOnPressListener interface.
 *
 * @see IOnPressListener.h
 * @see Button#m_longPressTicks
 * @see setDebounceTicks(uint8_t ticks)
 */
void Button::setOnPressListener(IOnPressListener *listener) {
    m_onPressListener = listener;
}

/**
 * @brief Set debounce time interval.
 *
 * To prevent random signal changes on input pin to trigger an event, we define a debounce interval.
 * Only when the button is pressed for longer than debounce, it is assumed to be a user action.
 *
 * Default value is defined in #DEFAULT_DEBOUNCE_TICKS_MS.
 *
 * @param ticks a debounce time interval in milliseconds.
 */
void Button::setDebounceTicks(uint8_t ticks) {
    m_debounceTicks = ticks;
}

/**
 * @brief Set time interval to detect a click event.
 *
 * Sets a time interval, after which it is safe to assume that a click event has occurred.
 * Default value is defined in #DEFAULT_CLICK_TICKS_MS.
 *
 * @param ticks a click time interval in milliseconds.
 */
void Button::setClickTicks(uint16_t ticks) {
    m_clickTicks = ticks;
}

/**
 * @brief Set time interval to detect a long press event.
 *
 * Sets a time interval, after which it is safe to assume that a long press event has occurred.
 * Default value is defined in #DEFAULT_LONG_PRESS_TICKS_MS.
 *
 * @param ticks a long press time interval in milliseconds.
 */
void Button::setLongPressTicks(uint16_t ticks /* ms */) {
    m_longPressTicks = ticks;
}

/**
 * @brief Tell the user if the button is pressed at a given moment.
 * @return <code>true</code> is the button is pressed, <code>false</code> otherwise.
 */
bool Button::isPressed() {
    return m_state == State::BUTTON_PRESSED;
}

/**
 * @brief Tell the user if the button is long pressed at a given moment.
 *
 * A button is considered to be long pressed after it is held for longer than <code>m_longPressTicks</code>.
 *
 * @return <code>true</code> is the button is long pressed, <code>false</code> otherwise.
 */
bool Button::isLongPressed() {
    return m_state == State::BUTTON_PRESSED && m_isLongButtonPress;
}

/**
 * @brief Reset button state.
 *
 * This function resets internal state machine and all the flags to their default values.
 * If you set custom debounce, click or long press intervals, these will also be reset to their
 * default values.
 */
void Button::reset() {
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
 * This function is responsible for updating internal state machine
 * responsible for handling button events and should be called periodically
 * in your <code>loop()</code> function.
 */
void Button::tick() {
    unsigned long now = millis();

    /**
     * Relative time difference between button press and release
     * Note: millis() counter overflows in approx. 50 days. When this happens, m_buttonPressedTime will be set to
     * near-to-max unsigned long value (high positive number), and our check whether this value is higher than
     * timeDelta will pass. Such situation will trigger false event.
     */
    unsigned long timeDelta = now - m_buttonPressedTime;

    switch (m_state) {
        case State::BUTTON_NOT_PRESSED: {
            if (isButtonPressed()) {
                m_state = State::BUTTON_PRESSED;
                m_buttonPressedTime = now;
            }
            break;
        }
        case State::BUTTON_PRESSED: {
            if (isButtonPressed()) {
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
            if (isButtonPressed() && (now - m_buttonReleasedTime) > m_debounceTicks) {
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
            if (!isButtonPressed() && timeDelta > m_debounceTicks) {
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
void Button::notifyOnClick() {
    if (m_onClickListener != nullptr)
        m_onClickListener->onClick(*this);
}

/**
 * @brief Notify listener on double-click event.
 */
void Button::notifyOnDoubleClick() {
    if (m_onDoubleClickListener != nullptr)
        m_onDoubleClickListener->onDoubleClick(*this);
}

/**
 * @brief Notify listener on button press event.
 */
void Button::notifyOnButtonPress() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onPress(*this);
}

/**
 * @brief Notify listener on button release event.
 */
void Button::notifyOnButtonRelease() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onRelease(*this);
}

/**
 * @brief Notify listener on long press start event.
 */
void Button::notifyOnLongPressStart() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onLongPressStart(*this);
}

/**
 * @brief Notify listener on long press end event.
 */
void Button::notifyOnLongPressEnd() {
    if (m_onPressListener != nullptr)
        m_onPressListener->onLongPressEnd(*this);
}

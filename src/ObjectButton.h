/**
 *  @file       ObjectButton.h
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

#pragma once

#include <inttypes.h>
#include <Arduino.h>
#include "interfaces/IOnPressListener.h"
#include "interfaces/IOnClickListener.h"
#include "interfaces/IOnDoubleClickListener.h"

/** Milliseconds that have to pass by before a button press is assumed safe */
constexpr static int DEFAULT_DEBOUNCE_TICKS_MS = 50;

/** Milliseconds that have to pass by before a click is detected */
constexpr static int DEFAULT_CLICK_TICKS_MS = 250;

/** Milliseconds that have to pass by before a long button press is detected */
constexpr static int DEFAULT_LONG_PRESS_TICKS_MS = 500;

/**
 * Main component for handling click, double-click and press gestures.
 */
class ObjectButton {
public:
    ObjectButton(uint8_t pin, bool activeLow = true);

    int getId();

    void setOnClickListener(IOnClickListener *listener);

    void setOnDoubleClickListener(IOnDoubleClickListener *listener);

    void setOnPressListener(IOnPressListener *listener);

    void setDebounceTicks(uint8_t ticks);

    void setClickTicks(uint16_t ticks);

    void setLongPressTicks(uint16_t ticks);

    bool isPressed();

    bool isLongPressed();

    void reset();

    void tick();

private:
    void notifyOnClick();

    void notifyOnDoubleClick();

    void notifyOnButtonPress();

    void notifyOnButtonRelease();

    void notifyOnLongPressStart();

    void notifyOnLongPressEnd();

    /**
     * Pointer to object listening to click events. If event listener is not set,
     * such event won't be broadcast.
     *
     * @see void setOnClickListener(IOnClickListener *listener)
     */
    IOnClickListener *m_onClickListener = nullptr;

    /**
     * Pointer to object listening to double-click events. If event listener is not set,
     * such event won't be broadcast.
     *
     * @see void setOnDoubleClickListener(IOnDoubleClickListener *listener)
     */
    IOnDoubleClickListener *m_onDoubleClickListener = nullptr;

    /**
     * Pointer to object listening to press, release and long-press events.
     * If event listener is not set, such event won't be broadcast.
     *
     * @see void setOnPressListener(IOnPressListener *listener)
     */
    IOnPressListener *m_onPressListener = nullptr;

    uint8_t m_pin; /**< Input pin bound with this button instance */

    /*
     * Following variables are used to define time constraints necessary to properly detect events.
     * These values can be overridden using dedicated methods.
     */
    uint8_t m_debounceTicks = DEFAULT_DEBOUNCE_TICKS_MS; /**< Sets debounce time to default [milliseconds] */
    uint16_t m_clickTicks = DEFAULT_CLICK_TICKS_MS; /**< Sets time to detect click event to default [milliseconds] */
    uint16_t m_longPressTicks = DEFAULT_LONG_PRESS_TICKS_MS; /**< Sets time to detect long press event to default [milliseconds] */

    /**
     * Signal levels as read from <code>digitalRead()</code> function, can be either <code>HIGH</code> or
     * <code>LOW</code>. When you create a new button instance, you specify <code>activeLow</code> boolean parameter.
     * This variable represents a mapping from the boolean to actual value expected on input pin.
     *
     * @see ObjectButton(uint8_t pin, bool activeLow = true)
     */
    byte m_buttonPressed;

    /**
     * After you press a button for longer than <code>longPressTicks</code>, a button is considered long pressed.
     * Our state machine does not have separate long press state. Instead it just sets this flag to <code>true</code>.
     *
     * @see m_longPressTicks
     * @see bool isLongPressed()
     */
    bool m_isLongButtonPress = false;

    /**
     * This flag helps us determine if an <code>onPress</code> event was already sent. It is necessary
     * to avoid sending this event each time our state machine's <code>tick()</code> method is called.
     *
     * @see void tick()
     */
    bool m_buttonPressNotified = false;

    /**
     * @brief States into which our state machine could transition into.
     */
    enum class State {
        BUTTON_NOT_PRESSED,
        BUTTON_PRESSED,
        BUTTON_RELEASED,
        BUTTON_DOUBLE_CLICKED
    };

    /**
     * This variable holds current state of our state machine. By default it's "button not pressed".
     *
     * @see enum class State
     */
    State m_state = State::BUTTON_NOT_PRESSED;

    unsigned long m_buttonPressedTime = 0L; /**< Captures timestamp when the button was pressed [milliseconds] */
    unsigned long m_buttonReleasedTime = 0L; /**< Captures timestamp when the button was released [milliseconds] */
};

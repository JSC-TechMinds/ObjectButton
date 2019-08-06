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
    /**
     * @brief Constructor for the class.
     * @param pin an input pin to use for the button.
     * @param activeLow determines pin state after button press. Set to <code>true</code> if voltage level
     * on input pin is <code>LOW</code> after button is pressed. Otherwise set to <code>false</code>.
     */
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

    /* Signal levels as read from digitalRead() function, can be either HIGH or LOW */
    byte m_buttonPressed;


    bool m_isLongButtonPress = false;
    bool m_buttonPressNotified = false;

    /* These variables hold information across the upcoming tick calls.
     * They are initialized once on program start and are updated every
     * time the tick function is called.
     */
    enum class State {
        BUTTON_NOT_PRESSED,
        BUTTON_PRESSED,
        BUTTON_RELEASED,
        BUTTON_DOUBLE_CLICKED
    };

    State m_state = State::BUTTON_NOT_PRESSED;

    unsigned long m_buttonPressedTime = 0L;
    unsigned long m_buttonReleasedTime = 0L;
};




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

/* Milliseconds that have to pass by before a click is assumed safe */
constexpr static int DEFAULT_DEBOUNCE_TICKS_MS = 50;

/* Milliseconds that have to pass by before a click is detected */
constexpr static int DEFAULT_CLICK_TICKS_MS = 250;

/* Milliseconds that have to pass by before a long button press is detected */
constexpr static int DEFAULT_LONG_PRESS_TICKS_MS = 500;

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

    // Call this function to update state machine for handling button events
    void tick();

private:
    void notifyOnClick();

    void notifyOnDoubleClick();

    void notifyOnButtonPress();

    void notifyOnButtonRelease();

    void notifyOnLongPressStart();

    void notifyOnLongPressEnd();

    IOnClickListener *m_onClickListener = nullptr;
    IOnDoubleClickListener *m_onDoubleClickListener = nullptr;
    IOnPressListener *m_onPressListener = nullptr;
    uint8_t m_pin;
    uint8_t m_debounceTicks = DEFAULT_DEBOUNCE_TICKS_MS;
    uint16_t m_clickTicks = DEFAULT_CLICK_TICKS_MS;
    uint16_t m_longPressTicks = DEFAULT_LONG_PRESS_TICKS_MS;

    /* Signal levels as read from digitalRead() function, can be either HIGH or LOW */
    int m_buttonPressed = 0;
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




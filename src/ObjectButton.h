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

class ObjectButton {
public:
    ObjectButton(uint8_t pin, bool activeLow = true);

    int getId();

    void setOnClickListener(IOnClickListener* listener);

    void setOnDoubleClickListener(IOnDoubleClickListener* listener);

    void setOnPressListener(IOnPressListener* listener);

    // Set number of milliseconds that have to pass by before a click is assumed as safe
    void setDebounceTicks(uint8_t ticks);

    // Set number of milliseconds that have to pass by before a click is detected
    void setClickTicks(uint16_t ticks);

    // Set number of milliseconds that have to pass by before a press is detected
    void setPressTicks(uint16_t ticks);

    bool isLongPressed();

    void reset(void);

    // Call this function to update state machine for handling button events
    void tick();

private:
    void notifyOnClick(void);
    void notifyOnDoubleClick(void);
    void notifyOnButtonPress(void);
    void notifyOnButtonRelease(void);

    IOnClickListener* m_onClickListener = nullptr;
    IOnDoubleClickListener* m_onDoubleClickListener = nullptr;
    IOnPressListener* m_onPressListener = nullptr;
    int m_buttonId = -1;
    uint8_t m_pin = 0; // hardware pin number
    uint8_t m_debounceTicks = 50; // milliseconds that have to pass by before a click is assumed as safe
    uint16_t m_clickTicks = 600; // milliseconds that have to pass by before a click is detected
    uint16_t m_longPressTicks = 1000; // milliseconds that have to pass by before a long button press is detected

    /* Signal levels as read from digitalRead() function, can be either HIGH or LOW */
    int m_buttonReleased = 0;
    int m_buttonPressed = 0;

    /* These variables hold information across the upcoming tick calls.
     * They are initialized once on program start and are updated every
     * time the tick function is called.
     */
    enum class State {
        BUTTON_NOT_PRESSED,
        BUTTON_PRESSED,
        BUTTON_RELEASED,
        BUTTON_LONG_PRESSED,
        BUTTON_CLICKED,
        BUTTON_DOUBLE_CLICKED
    };

    State m_state = State::BUTTON_NOT_PRESSED;

    unsigned long m_buttonPressedTime = 0L;
    unsigned long m_buttonReleasedTime = 0L;
};




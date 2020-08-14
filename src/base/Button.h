/**
 *  @file       Button.h
 *  Project     ObjectButton
 *  @brief      An Arduino library for detecting button actions.
 *  @author     Vladimír Záhradník
 *  License     Apache-2.0 - Copyright (c) 2019-2020 JSC electronics
 *
 *  @section License
 *
 *  Copyright (c) 2019-2020 JSC electronics
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

#ifndef ABSTRACT_BUTTON_H
#define ABSTRACT_BUTTON_H

#include <inttypes.h>
#include <Arduino.h>
#include "../interfaces/IOnPressListener.h"
#include "../interfaces/IOnClickListener.h"
#include "../interfaces/IOnDoubleClickListener.h"

namespace jsc {
    /** Milliseconds that have to pass by before a button press is assumed safe */
    constexpr static int DEFAULT_DEBOUNCE_TICKS_MS = 50;

    /** Milliseconds that have to pass by before a click is detected */
    constexpr static int DEFAULT_CLICK_TICKS_MS = 250;

    /** Milliseconds that have to pass by before a long button press is detected */
    constexpr static int DEFAULT_LONG_PRESS_TICKS_MS = 500;

    /**
     * Main component for handling click, double-click and press gestures.
     */
    class Button {
    public:
        virtual ~Button() {}

        virtual int getId() = 0;

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

    protected:
        /* Avoid initializing this class */
        Button(uint8_t pin, bool inputPullUp);

        uint8_t m_pin; /**< Input pin bound with this button instance */

    private:
        virtual bool isButtonPressed() = 0;

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
         * @see setOnClickListener(IOnClickListener *listener)
         */
        IOnClickListener *m_onClickListener = nullptr;

        /**
         * Pointer to object listening to double-click events. If event listener is not set,
         * such event won't be broadcast.
         *
         * @see setOnDoubleClickListener(IOnDoubleClickListener *listener)
         */
        IOnDoubleClickListener *m_onDoubleClickListener = nullptr;

        /**
         * Pointer to object listening to press, release and long-press events.
         * If event listener is not set, such event won't be broadcast.
         *
         * @see setOnPressListener(IOnPressListener *listener)
         */
        IOnPressListener *m_onPressListener = nullptr;

        /*
        * Following variables are used to define time constraints necessary to properly detect events.
        * These values can be overridden using dedicated functions.
        */
        uint8_t m_debounceTicks = DEFAULT_DEBOUNCE_TICKS_MS; /**< Sets debounce time to default [milliseconds] */
        uint16_t m_clickTicks = DEFAULT_CLICK_TICKS_MS; /**< Sets time to detect click event to default [milliseconds] */
        uint16_t m_longPressTicks = DEFAULT_LONG_PRESS_TICKS_MS; /**< Sets time to detect long press event to default [milliseconds] */

        /**
         * After you press a button for longer than <code>longPressTicks</code>, a button is considered long pressed.
         * Our state machine does not have separate long press state. Instead it just sets this flag to <code>true</code>.
         *
         * @see Button::m_longPressTicks
         * @see isLongPressed()
         */
        bool m_isLongButtonPress = false;

        /**
         * This flag helps us determine if an <code>onPress</code> event was already sent. It is necessary
         * to avoid sending this event each time our state machine's <code>tick()</code> function is called.
         *
         * @see tick()
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
}

#endif // ABSTRACT_BUTTON_H

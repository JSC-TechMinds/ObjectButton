/**
 *  @file       IOnPressListener.h
 *  Project     ObjectButton
 *  @brief      An Arduino library for detecting button actions.
 *  @author     Vladimír Záhradník
 *  License     Apache-2.0 - Copyright (c) 2019-2020 JSC electronics
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

#ifndef I_ON_PRESS_LISTENER_H
#define I_ON_PRESS_LISTENER_H

namespace jsc {
    class Button;

    /**
    * @brief Callback interface for button press/release events.
    *
    * Each object passed to ObjectButton instance as an OnPressListener should inherit
    * this class and implement virtual functions. See Examples for more details.
    */
    class IOnPressListener {
    public:
        /**
         * Destructor
         */
        virtual ~IOnPressListener() = default;

        /**
         * Callback function to be called when a button is pressed.
         * @param button is a reference to the instance which called the listener.
         */
        virtual void onPress(Button& button) = 0;

        /**
         * Callback function to be called when a button is released.
         * @param button is a reference to the instance which called the listener.
         */
        virtual void onRelease(Button& button) = 0;

        /**
         * Callback function to be called when button long press started.
         * @param button is a reference to the instance which called the listener.
         */
        virtual void onLongPressStart(Button& button) = 0;

        /**
         * Callback function to be called when button long press ended.
         * @param button is a reference to the instance which called the listener.
         */
        virtual void onLongPressEnd(Button& button) = 0;
    };
}

#endif // I_ON_PRESS_LISTENER_H

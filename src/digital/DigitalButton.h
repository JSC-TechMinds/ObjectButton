/**
 *  @file       DigitalButton.h
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

#ifndef DIGITAL_BUTTON_H
#define DIGITAL_BUTTON_H

#include "../base/Button.h"

namespace jsc {
    class DigitalButton : public Button {
    public:
        DigitalButton(uint8_t pin, bool inputPullUp = true);

        int getId() override;

    private:
        bool isButtonPressed() override;

        /**
         * Signal levels as read from <code>digitalRead()</code> function, can be either <code>HIGH</code> or
         * <code>LOW</code>. When you create a new button instance, you specify <code>inputPullUp</code> boolean parameter.
         * This variable represents a mapping from the boolean to actual value expected on input pin.
         *
         * @see DigitalButton(uint8_t pin, bool inputPullUp)
         */
        byte m_buttonPressed;
    };
}

#endif // DIGITAL_BUTTON_H

/**
 *  @file       AnalogButton.h
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

#ifndef ANALOG_BUTTON_H
#define ANALOG_BUTTON_H

#include "../base/Button.h"

namespace jsc {
    /** Voltage margin to detect button presses */
    constexpr static int DEFAULT_VOLTAGE_MARGIN = 50;

    class AnalogButton : public Button {
    public:
        AnalogButton(uint8_t buttonId,
                    uint8_t pin,
                    uint16_t voltage,
                    bool inputPullUp = true);

        int getId() override;

        void setVoltageMargin(uint16_t margin);

    private:
        bool isButtonPressed() override;

        /**
         * @brief ID of a button.
         * 
         * Single analog pin might have more analog buttons attached to it. In order to differentiate
         * buttons, user needs to specify a unique button ID. This parameter is mandatory.
         * 
         * Accepted values: 0 - 255.
         * 
         * Note: If user gives two buttons the same ID, the code will work, except user won't be able to
         * tell, which button was triggered.
         */
        int m_buttonId;

        /**
         * @brief Voltage present on the pin after button was pressed.
         * 
         * Voltage on the pin returned by the analogRead() function. Typical range is 0 - 1023.
         */
        uint16_t m_voltage;

        /**
         * @brief Margin for voltage detection.
         * 
         * Measured voltage slightly changes over time. In order to detect it reliably,
         * user can set a voltage margin. If current voltage is in a range value +- margin,
         * a button press is detected.
         */
        uint16_t m_margin = DEFAULT_VOLTAGE_MARGIN;
    };
}

#endif // ANALOG_BUTTON_H

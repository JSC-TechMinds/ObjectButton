/**
 *  @file       AnalogButton.cpp
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

#include "AnalogButton.h"
using namespace jsc;

/**
 * @brief Constructor for the class.
 * @param buttonId a unique button ID. Accepted values: 0 - 255.
 * @param pin an input pin to use for the button.
 * @param voltage a voltage returned by the analogRead() function.
 * @param inputPullUp determines pin state after button press. Set to <code>true</code> if voltage level
 * on input pin is <code>LOW</code> after button is pressed. Otherwise set to <code>false</code>.
 * This parameter is optional and defaults to <code>true</code>.
 */
AnalogButton::AnalogButton(uint8_t buttonId,
                          uint8_t pin,
                          uint16_t voltage,
                          bool inputPullUp) : Button(pin, inputPullUp),
                                              m_buttonId(buttonId), m_voltage(voltage) {}


/**
 * @brief Get button identifier.
 *
 * Each ObjectButton has its own identification. This allows us to receive events from multiple buttons
 * in one common function and based on button ID do different actions. Button ID corresponds to input
 * pin number.
 *
 * @return button ID as an integer.
 */
int AnalogButton::getId() {
    return m_buttonId;
}

/**
 * @brief Evaluate wheter a button is pressed.
 * 
 * This is a private method called from the state machine. It evaluates whether a button is pressed.
 */
bool AnalogButton::isButtonPressed() {
    return abs(analogRead(m_pin) - m_voltage) < m_margin;
}

/**
 * @brief Set voltage margin.
 *
 * Sets a voltage margin. Default value is defined in #DEFAULT_VOLTAGE_MARGIN.
 *
 * @param margin voltage margin.
 */
void AnalogButton::setVoltageMargin(uint16_t margin) {
    m_margin = margin;
}

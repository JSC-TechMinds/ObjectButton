/**
 *  @file       DigitalButton.cpp
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

#include "DigitalButton.h"
using namespace jsc;

/**
 * @brief Constructor for the class.
 * @param pin an input pin to use for the button.
 * @param inputPullUp determines pin state after button press. Set to <code>true</code> if voltage level
 * on input pin is <code>LOW</code> after button is pressed. Otherwise set to <code>false</code>.
 * This parameter is optional and defaults to <code>true</code>.
 */
DigitalButton::DigitalButton(uint8_t pin, bool inputPullUp) : Button(pin, inputPullUp) {
    m_buttonPressed = inputPullUp ? LOW : HIGH;
}

/**
 * @brief Get button identifier.
 *
 * Each ObjectButton has its own identification. This allows us to receive events from multiple buttons
 * in one common function and based on button ID do different actions. Button ID corresponds to input
 * pin number.
 *
 * @return button ID as an integer.
 */
int DigitalButton::getId() {
    return m_pin;
}

/**
 * @brief Invert input logic.
 * 
 * This function allows the user to dynamically change the logic while the program is running.
 * Inverted logic means that if the input voltage level is high (e.g. 5 V DC), it will be treated as logic 0. 
 * Therefore, a low voltage level (0 V DC) will be represented as log 1.
 */
void DigitalButton::invertInputLogic() {
    m_buttonPressed = (m_buttonPressed == LOW) ? HIGH : LOW;
}

/**
 * @brief Check if input logic is inverted.
 *
 * Inverted logic means that if the input voltage level is high (e.g. 5 V DC), it will be treated as logic 0. 
 * Therefore, a low voltage level (0 V DC) will be represented as log 1.
 *
 * @return True if logic is inverted.
 */
bool DigitalButton::isInputLogicInverted() {
    return (m_buttonPressed == LOW);
}
/**
 * @brief Evaluate wheter a button is pressed.
 * 
 * This is a private method called from the state machine. It evaluates whether a button is pressed.
 */
bool DigitalButton::isButtonPressed() {
    return (digitalRead(m_pin) == m_buttonPressed);
}

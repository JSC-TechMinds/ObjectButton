/**
 *  @file       DigitalSensor.cpp
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

#include "DigitalSensor.h"
using namespace jsc;

/**
 * @brief Constructor for the class.
 * @param pin an input pin to use for the sensor.
 * @param inputPullUp determines pin state after sensor detection. Set to <code>true</code> if voltage level
 * on input pin is <code>LOW</code> after sensor detects an object. Otherwise set to <code>false</code>.
 * This parameter is optional and defaults to <code>true</code>.
 */
DigitalSensor::DigitalSensor(uint8_t pin, bool inputPullUp) : DigitalButton(pin, inputPullUp) {}

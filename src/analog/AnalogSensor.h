/**
 *  @file       AnalogSensor.h
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

#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#include "AnalogButton.h"

namespace jsc {
    class AnalogSensor : public AnalogButton {
    public:
        AnalogSensor(uint8_t sensorId,
                    uint8_t pin,
                    uint16_t voltage,
                    bool inputPullUp = true);
    };
}

#endif // ANALOG_SENSOR_H

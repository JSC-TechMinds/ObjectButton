/**
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

#include <ArduinoUnitTests.h>
#include "../src/ObjectButton.h"
using namespace jsc;

DigitalButton digitalButton = DigitalButton(10, /*inputPullUp*/ true);
AnalogButton analogButton = AnalogButton(/*buttonId*/ 1, 10, /*voltage*/ 1000, /* inputPullUp */ true);

unittest(digital_button_id_matches_input_pin) {
    assertEqual(10, digitalButton.getId());
    assertEqual(1, analogButton.getId());

    DigitalButton digitalButton2 = DigitalButton(1, false);
    assertEqual(1, digitalButton2.getId());

    AnalogButton analogButton2 = AnalogButton(10, 1, 1000, false);
    assertEqual(10, analogButton2.getId());
}

unittest(button_not_pressed) {
    assertEqual(false, digitalButton.isLongPressed());
    assertEqual(false, analogButton.isLongPressed());
}

unittest(button_not_pressed_after_reset) {
    digitalButton.reset();
    assertEqual(false, digitalButton.isLongPressed());

	analogButton.reset();
    assertEqual(false, analogButton.isLongPressed());
}

unittest_main()
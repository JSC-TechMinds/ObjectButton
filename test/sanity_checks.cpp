/**
 *  Copyright (c) 2019 JSC electronics
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

ObjectButton button = ObjectButton(10, /* activeLow */ true);

unittest(button_id_matches_input_pin) {
    assertEqual(10, button.getId());

    ObjectButton button2 = ObjectButton(1, false);
    assertEqual(1, button2.getId());
}

unittest(button_not_pressed) {
    assertEqual(false, button.isLongPressed());
}

unittest(button_not_pressed_after_reset) {
    button.reset();
    assertEqual(false, button.isLongPressed());
}

unittest_main()
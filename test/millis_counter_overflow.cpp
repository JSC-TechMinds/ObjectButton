/**
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

#include <ArduinoUnitTests.h>
#include "../src/ObjectButton.h"
#include "mocks/ListenerMock.h"
using namespace jsc;

constexpr static byte INPUT_PIN = 10;

GodmodeState* state = GODMODE();

unittest_setup() {
    state->reset();
}

unittest(millis_counter_overflow) {
        DigitalButton digitalButton = DigitalButton(INPUT_PIN, true);
        ListenerMock testMock = ListenerMock(digitalButton);

        // Set millis() one millisecond before counter overflow
        state->micros = -1000;

        // press button
        state->digitalPin[INPUT_PIN] = LOW;
        testMock.getButton().tick();

        // Set millis() one millisecond after counter overflow
        state->micros = 1000;
        testMock.getButton().tick();

        // validate click event -- note: false positive
        assertEqual(1, testMock.getPressEventsReceivedCount());
}

unittest_main()
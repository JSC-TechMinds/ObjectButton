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

unittest(exact_analog_voltage_match_should_fire_press_event) {
        AnalogButton analogButton = AnalogButton(10, INPUT_PIN, 1000, true);
        ListenerMock testMock = ListenerMock(analogButton);

        // press button
        state->analogPin[INPUT_PIN] = 1000;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(1, testMock.getPressEventsReceivedCount());
}

unittest(analog_voltage_within_positive_default_margin_should_fire_press_event) {
        AnalogButton analogButton = AnalogButton(10, INPUT_PIN, 1000, true);
        ListenerMock testMock = ListenerMock(analogButton);

        // press button
        state->analogPin[INPUT_PIN] = 1000 + DEFAULT_VOLTAGE_MARGIN - 1;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(1, testMock.getPressEventsReceivedCount());
}

unittest(analog_voltage_outside_of_positive_default_margin_should_not_fire_press_event) {
        AnalogButton analogButton = AnalogButton(10, INPUT_PIN, 1000, true);
        ListenerMock testMock = ListenerMock(analogButton);

        // press button
        state->analogPin[INPUT_PIN] = 1000 + DEFAULT_VOLTAGE_MARGIN;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(0, testMock.getPressEventsReceivedCount());
}

unittest(analog_voltage_within_negative_default_margin_should_fire_press_event) {
        AnalogButton analogButton = AnalogButton(10, INPUT_PIN, 1000, true);
        ListenerMock testMock = ListenerMock(analogButton);

        // press button
        state->analogPin[INPUT_PIN] = 1000 - DEFAULT_VOLTAGE_MARGIN + 1;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(1, testMock.getPressEventsReceivedCount());
}

unittest(analog_voltage_outside_of_negative_default_margin_should_not_fire_press_event) {
        AnalogButton analogButton = AnalogButton(10, INPUT_PIN, 1000, true);
        ListenerMock testMock = ListenerMock(analogButton);

        // press button
        state->analogPin[INPUT_PIN] = 1000 - DEFAULT_VOLTAGE_MARGIN;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(0, testMock.getPressEventsReceivedCount());
}

unittest(analog_voltage_within_positive_custom_margin_should_fire_press_event) {
        constexpr int voltageMargin = 100;
        AnalogButton analogButton = AnalogButton(10, INPUT_PIN, 1000, true);
        analogButton.setVoltageMargin(voltageMargin);
        ListenerMock testMock = ListenerMock(analogButton);

        // press button
        state->analogPin[INPUT_PIN] = 1000 + voltageMargin - 1;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(1, testMock.getPressEventsReceivedCount());
}

unittest(analog_voltage_outside_of_positive_custom_margin_should_not_fire_press_event) {
        constexpr int voltageMargin = 100;
        AnalogButton analogButton = AnalogButton(10, INPUT_PIN, 1000, true);
        analogButton.setVoltageMargin(voltageMargin);
        ListenerMock testMock = ListenerMock(analogButton);

        // press button
        state->analogPin[INPUT_PIN] = 1000 + voltageMargin;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(0, testMock.getPressEventsReceivedCount());
}

unittest(analog_voltage_within_negative_custom_margin_should_fire_press_event) {
        constexpr int voltageMargin = 100;
        AnalogButton analogButton = AnalogButton(10, INPUT_PIN, 1000, true);
        analogButton.setVoltageMargin(voltageMargin);
        ListenerMock testMock = ListenerMock(analogButton);

        // press button
        state->analogPin[INPUT_PIN] = 1000 - voltageMargin + 1;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(1, testMock.getPressEventsReceivedCount());
}

unittest(analog_voltage_outside_of_negative_custom_margin_should_not_fire_press_event) {
        constexpr int voltageMargin = 100;
        AnalogButton analogButton = AnalogButton(10, INPUT_PIN, 1000, true);
        analogButton.setVoltageMargin(voltageMargin);
        ListenerMock testMock = ListenerMock(analogButton);

        // press button
        state->analogPin[INPUT_PIN] = 1000 - voltageMargin;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(0, testMock.getPressEventsReceivedCount());
}

unittest_main()

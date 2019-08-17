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
#include "mocks/ListenerMock.h"

constexpr static byte INPUT_PIN = 10;

ListenerMock testMock = ListenerMock(INPUT_PIN, true);
GodmodeState* state = GODMODE();

unittest_setup() {
    testMock.resetState();
    state->reset();
}

unittest(do_not_receive_on_click_event_before_default_click_ticks) {
        // press button
        state->digitalPin[INPUT_PIN] = LOW;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // release button
        state->digitalPin[INPUT_PIN] = HIGH;
        state->micros = DEFAULT_CLICK_TICKS_MS * 1000;
        testMock.getButton().tick();

        // refresh state machine to get click event
        testMock.getButton().tick();

        // validate click event
        assertEqual(1, testMock.getPressEventsReceivedCount());
        assertEqual(1, testMock.getReleaseEventsReceivedCount());
        assertEqual(0, testMock.getClickEventsReceivedCount());
        assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
        assertEqual(0, testMock.getLongPressStartEventsReceivedCount());
        assertEqual(0, testMock.getLongPressEndEventsReceivedCount());
}

unittest(receive_on_click_event_after_default_click_ticks) {
    // press button
    state->digitalPin[INPUT_PIN] = LOW;
    testMock.getButton().tick();

    // fire press event after debounce period elapses
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // release button
    state->digitalPin[INPUT_PIN] = HIGH;
    state->micros = (DEFAULT_CLICK_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // refresh state machine to get click event
    testMock.getButton().tick();

    // validate click event
    assertEqual(1, testMock.getPressEventsReceivedCount());
    assertEqual(1, testMock.getReleaseEventsReceivedCount());
    assertEqual(1, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(0, testMock.getLongPressStartEventsReceivedCount());
    assertEqual(0, testMock.getLongPressEndEventsReceivedCount());
}

unittest(do_not_receive_on_click_event_before_custom_click_ticks) {
    constexpr static int CLICK_TICKS_MS = 300;
    testMock.getButton().setClickTicks(CLICK_TICKS_MS);

    // press button
    state->digitalPin[INPUT_PIN] = LOW;
    testMock.getButton().tick();

    // fire press event after debounce period elapses
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // release button
    state->digitalPin[INPUT_PIN] = HIGH;
    state->micros = CLICK_TICKS_MS * 1000;
    testMock.getButton().tick();

    // refresh state machine to get click event
    testMock.getButton().tick();

    // validate click event
    assertEqual(1, testMock.getPressEventsReceivedCount());
    assertEqual(1, testMock.getReleaseEventsReceivedCount());
    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(0, testMock.getLongPressStartEventsReceivedCount());
    assertEqual(0, testMock.getLongPressEndEventsReceivedCount());
}

unittest(receive_on_click_event_after_custom_click_ticks) {
    constexpr static int CLICK_TICKS_MS = 300;
    testMock.getButton().setClickTicks(CLICK_TICKS_MS);

    // press button
    state->digitalPin[INPUT_PIN] = LOW;
    testMock.getButton().tick();

    // fire press event after debounce period elapses
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // release button
    state->digitalPin[INPUT_PIN] = HIGH;
    state->micros = (CLICK_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // refresh state machine to get click event
    testMock.getButton().tick();

    // validate click event
    assertEqual(1, testMock.getPressEventsReceivedCount());
    assertEqual(1, testMock.getReleaseEventsReceivedCount());
    assertEqual(1, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(0, testMock.getLongPressStartEventsReceivedCount());
    assertEqual(0, testMock.getLongPressEndEventsReceivedCount());
}

/*
 * When the button is released, we can't tell if it's because user
 * clicked on it or if there will follow a second click (double-click gesture).
 * Therefore to be absolutely sure, we'll emit onClick() after a specified timeout
 * defined in CLICK_TICKS. If user clicks on a button and this timeout is not yet
 * elapsed, state machine will be refreshed until this timeout does occur and
 * onClick() event will be sent.
 */
unittest(receive_on_click_event_if_button_was_released_before_click_ticks_due_to_click_timeout) {
        // press button
        state->digitalPin[INPUT_PIN] = LOW;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // release button
        state->digitalPin[INPUT_PIN] = HIGH;
        state->micros = DEFAULT_CLICK_TICKS_MS * 1000;
        testMock.getButton().tick();

        // refresh state machine to get click event
        testMock.getButton().tick();


        // keep button released and refresh state machine. due to click timeout, click event should be sent.
        // in this phase we are absolutely sure that user won't press button again for double-click
        state->micros = (DEFAULT_CLICK_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // validate click event
        assertEqual(1, testMock.getPressEventsReceivedCount());
        assertEqual(1, testMock.getReleaseEventsReceivedCount());
        assertEqual(1, testMock.getClickEventsReceivedCount());
        assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
        assertEqual(0, testMock.getLongPressStartEventsReceivedCount());
        assertEqual(0, testMock.getLongPressEndEventsReceivedCount());
}

unittest_main()
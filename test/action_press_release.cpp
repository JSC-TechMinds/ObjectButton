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

unittest(properly_detect_button_press_in_active_low_mode) {
    // press button
    state->digitalPin[INPUT_PIN] = LOW;

    testMock.getButton().tick();
    assertEqual(true, testMock.getButton().isPressed());
}

unittest(properly_detect_button_press_in_active_high_mode) {
    ObjectButton button = ObjectButton(INPUT_PIN, false);

    // press button
    state->digitalPin[INPUT_PIN] = HIGH;

    button.tick();
    assertEqual(true, button.isPressed());
}

unittest(button_not_pressed_handled_correctly) {
    // make sure button is not pressed
    state->digitalPin[INPUT_PIN] = HIGH;

    testMock.getButton().tick();
    assertEqual(false, testMock.getButton().isPressed());
}

unittest(button_pressed_and_released_after_default_debounce_limit_emits_events) {
    // make sure button is pressed
    state->digitalPin[INPUT_PIN] = LOW;
    testMock.getButton().tick();
    assertEqual(true, testMock.getButton().isPressed());

    // make sure it is still pressed after debounce limit
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // release button
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 10) * 1000;
    state->digitalPin[INPUT_PIN] = HIGH;
    testMock.getButton().tick();
    testMock.getButton().tick();

    assertEqual(false, testMock.getButton().isPressed());
    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(1, testMock.getPressEventsReceivedCount());
    assertEqual(1, testMock.getReleaseEventsReceivedCount());
}

unittest(button_pressed_and_released_after_custom_debounce_limit_emits_events) {
    constexpr static int DEBOUNCE_CLICKS_MS = 30;
    testMock.getButton().setDebounceTicks(DEBOUNCE_CLICKS_MS);

    // make sure button is pressed
    state->digitalPin[INPUT_PIN] = LOW;
    testMock.getButton().tick();
    assertEqual(true, testMock.getButton().isPressed());

    // make sure it is still pressed after debounce limit
    state->micros = (DEBOUNCE_CLICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // release button
    state->micros = (DEBOUNCE_CLICKS_MS + 10) * 1000;
    state->digitalPin[INPUT_PIN] = HIGH;
    testMock.getButton().tick();
    testMock.getButton().tick();

    assertEqual(false, testMock.getButton().isPressed());
    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(1, testMock.getPressEventsReceivedCount());
    assertEqual(1, testMock.getReleaseEventsReceivedCount());
}

unittest(button_pressed_and_released_within_default_debounce_does_not_emit_an_event) {
    // make sure button is pressed
    state->digitalPin[INPUT_PIN] = LOW;

    testMock.getButton().tick();
    assertEqual(true, testMock.getButton().isPressed());
    testMock.getButton().tick();

    // release button within debounce limit
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS - 1) * 1000;
    state->digitalPin[INPUT_PIN] = HIGH;
    testMock.getButton().tick();
    testMock.getButton().tick();

    assertEqual(false, testMock.getButton().isPressed());
    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(0, testMock.getPressEventsReceivedCount());
    assertEqual(0, testMock.getReleaseEventsReceivedCount());
}

unittest(button_pressed_and_released_within_custom_debounce_does_not_emit_an_event) {
    constexpr static int DEBOUNCE_CLICKS_MS = 30;
    testMock.getButton().setDebounceTicks(DEBOUNCE_CLICKS_MS);

    // make sure button is pressed
    state->digitalPin[INPUT_PIN] = LOW;

    testMock.getButton().tick();
    assertEqual(true, testMock.getButton().isPressed());

    // release button within debounce limit
    state->micros = (DEBOUNCE_CLICKS_MS - 1) * 1000;
    state->digitalPin[INPUT_PIN] = HIGH;

    testMock.getButton().tick();
    assertEqual(false, testMock.getButton().isPressed());
    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(0, testMock.getPressEventsReceivedCount());
    assertEqual(0, testMock.getReleaseEventsReceivedCount());
}

unittest(button_long_press_not_detected_before_default_limit) {
    // make sure button is pressed
    state->digitalPin[INPUT_PIN] = LOW;

    testMock.getButton().tick();
    assertEqual(true, testMock.getButton().isPressed());

    // keep button pressed
    state->micros = DEFAULT_LONG_PRESS_TICKS_MS * 1000;
    testMock.getButton().tick();

    assertEqual(true, testMock.getButton().isPressed());
    assertEqual(false, testMock.getButton().isLongPressed());
    assertEqual(0, testMock.getLongPressStartEventsReceivedCount());

    // release button
    state->digitalPin[INPUT_PIN] = HIGH;
    testMock.getButton().tick();

    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(0, testMock.getLongPressStartEventsReceivedCount());
    assertEqual(0, testMock.getLongPressEndEventsReceivedCount());
}

unittest(button_press_is_notified_only_once_per_action) {
    // press button
    state->digitalPin[INPUT_PIN] = LOW;
    testMock.getButton().tick();

    // fire press event after debounce period elapses
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;

    // now, simulate tick() being called periodically in loop(). Make sure notify() gets called only once.
    testMock.getButton().tick();
    testMock.getButton().tick();
    testMock.getButton().tick();
    testMock.getButton().tick();
    testMock.getButton().tick();

    // release button
    state->digitalPin[INPUT_PIN] = HIGH;
    state->micros = (DEFAULT_CLICK_TICKS_MS - 10) * 1000;
    testMock.getButton().tick();
    testMock.getButton().tick();

    // validate click event
    assertEqual(1, testMock.getPressEventsReceivedCount());
    assertEqual(1, testMock.getReleaseEventsReceivedCount());
    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(0, testMock.getLongPressStartEventsReceivedCount());
    assertEqual(0, testMock.getLongPressEndEventsReceivedCount());
}

unittest(receive_long_press_start_and_end_events_when_button_is_held_longer_than_default_long_press_ticks) {
    // press button
    state->digitalPin[INPUT_PIN] = LOW;
    testMock.getButton().tick();

    // fire press event after debounce period elapses
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // long press
    state->micros = (DEFAULT_LONG_PRESS_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // release button
    state->digitalPin[INPUT_PIN] = HIGH;
    state->micros = (DEFAULT_LONG_PRESS_TICKS_MS + DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();
    testMock.getButton().tick();

    // validate click event
    assertEqual(1, testMock.getPressEventsReceivedCount());
    assertEqual(1, testMock.getReleaseEventsReceivedCount());
    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(1, testMock.getLongPressStartEventsReceivedCount());
    assertEqual(1, testMock.getLongPressEndEventsReceivedCount());
}

unittest(receive_long_press_start_and_end_events_when_button_is_held_longer_than_custom_long_press_ticks) {
        // press button
        state->digitalPin[INPUT_PIN] = LOW;
        testMock.getButton().tick();

        // fire press event after debounce period elapses
        state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // long press
        state->micros = (DEFAULT_LONG_PRESS_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();

        // release button
        state->digitalPin[INPUT_PIN] = HIGH;
        state->micros = (DEFAULT_LONG_PRESS_TICKS_MS + DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
        testMock.getButton().tick();
        testMock.getButton().tick();

        // validate click event
        assertEqual(1, testMock.getPressEventsReceivedCount());
        assertEqual(1, testMock.getReleaseEventsReceivedCount());
        assertEqual(0, testMock.getClickEventsReceivedCount());
        assertEqual(0, testMock.getDoubleClickEventsReceivedCount());
        assertEqual(1, testMock.getLongPressStartEventsReceivedCount());
        assertEqual(1, testMock.getLongPressEndEventsReceivedCount());
}

unittest_main()
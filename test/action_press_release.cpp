#include <ArduinoUnitTests.h>
#include "../src/ObjectButton.h"
#include "mocks/ListenerMock.h"

constexpr static int INPUT_PIN = 10;

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

unittest_main()
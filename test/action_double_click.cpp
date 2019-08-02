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

unittest(receive_on_double_click_event_when_button_is_quickly_pressed_before_click_ticks) {
    // press button
    state->digitalPin[INPUT_PIN] = LOW;
    testMock.getButton().tick();

    // fire press event after debounce period elapses
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // release button
    state->digitalPin[INPUT_PIN] = HIGH;
    state->micros = 2 * DEFAULT_DEBOUNCE_TICKS_MS * 1000;
    testMock.getButton().tick();
    testMock.getButton().tick();

    // press button again
    state->digitalPin[INPUT_PIN] = LOW;
    state->micros = (3 * DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();
    testMock.getButton().tick();

    // release button again
    state->digitalPin[INPUT_PIN] = HIGH;
    state->micros = (4 * DEFAULT_DEBOUNCE_TICKS_MS + 10) * 1000;
    testMock.getButton().tick();
    testMock.getButton().tick();

    // validate click event
    assertEqual(1, testMock.getPressEventsReceivedCount());
    assertEqual(1, testMock.getReleaseEventsReceivedCount());
    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(1, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(0, testMock.getLongPressStartEventsReceivedCount());
    assertEqual(0, testMock.getLongPressEndEventsReceivedCount());
}

unittest(receive_on_double_click_event_when_button_is_quickly_pressed_after_click_ticks) {
    // press button
    state->digitalPin[INPUT_PIN] = LOW;
    testMock.getButton().tick();

    // fire press event after debounce period elapses
    state->micros = (DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();

    // release button
    state->digitalPin[INPUT_PIN] = HIGH;
    state->micros = (DEFAULT_CLICK_TICKS_MS - 10) * 1000;
    testMock.getButton().tick();
    testMock.getButton().tick();

    // press button again
    state->digitalPin[INPUT_PIN] = LOW;
    state->micros = (DEFAULT_CLICK_TICKS_MS + DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();
    testMock.getButton().tick();

    // release button again
    state->digitalPin[INPUT_PIN] = HIGH;
    state->micros = (DEFAULT_CLICK_TICKS_MS + 3 * DEFAULT_DEBOUNCE_TICKS_MS + 1) * 1000;
    testMock.getButton().tick();
    testMock.getButton().tick();

    // validate click event
    assertEqual(1, testMock.getPressEventsReceivedCount());
    assertEqual(1, testMock.getReleaseEventsReceivedCount());
    assertEqual(0, testMock.getClickEventsReceivedCount());
    assertEqual(1, testMock.getDoubleClickEventsReceivedCount());
    assertEqual(0, testMock.getLongPressStartEventsReceivedCount());
    assertEqual(0, testMock.getLongPressEndEventsReceivedCount());
}

unittest_main()
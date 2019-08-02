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

unittest_main()
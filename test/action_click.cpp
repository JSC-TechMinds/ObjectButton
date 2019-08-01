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

//unittest(receive_on_click_event_after_default_click_ticks) {
//    // press button
//    state->digitalPin[INPUT_PIN] = LOW;
//    testMock.getButton().tick();
//
//    // release button
//    state->digitalPin[INPUT_PIN] = HIGH;
//    state->micros = DEFAULT_CLICK_TICKS_MS * 1000 + 1;
//    testMock.getButton().tick();
//
//    // validate click event
//    assertEqual(true, testMock.didReceiveOnClickEvent());
//}
//
//unittest(receive_on_click_event_after_custom_click_ticks) {
//    constexpr static int CLICK_TICKS_MS = 300;
//    testMock.getButton().setClickTicks(CLICK_TICKS_MS);
//
//    // press button
//    state->digitalPin[INPUT_PIN] = LOW;
//    testMock.getButton().tick();
//
//    // release button
//    state->digitalPin[INPUT_PIN] = HIGH;
//    state->micros = CLICK_TICKS_MS * 1000 + 1;
//    testMock.getButton().tick();
//
//    // validate click event
//    assertEqual(true, testMock.didReceiveOnClickEvent());
//}

unittest_main()
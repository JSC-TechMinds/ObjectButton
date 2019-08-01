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
    ObjectButton button = ObjectButton(INPUT_PIN, true);

    // press button
    state->digitalPin[INPUT_PIN] = LOW;

    assertEqual(true, button.isPressed());
}

unittest(properly_detect_button_press_in_active_high_mode) {
    ObjectButton button = ObjectButton(INPUT_PIN, false);

    // press button
    state->digitalPin[INPUT_PIN] = HIGH;

    assertEqual(true, button.isPressed());
}

//unittest(receive_on_click_event_after_default_click_ticks) {
//    GodmodeState* state = GODMODE();
//    // press button
//    state->digitalPin[INPUT_PIN] = LOW;
//    testMock.update();
//
//    // release button
//    state->digitalPin[INPUT_PIN] = HIGH;
//    state->micros = 601000;
//
//    // validate click event
//    assertEqual(true, testMock.didReceiveOnCliEvent());
//}

unittest_main()
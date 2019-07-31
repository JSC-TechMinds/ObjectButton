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
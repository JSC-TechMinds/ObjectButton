/**
 * @mainpage ObjectButton Arduino Library
 *
 * See the documentation of the main class, ObjectButton, or browse the modules
 * and examples using the sidebar on the left.
 *
 * The latest development version is available on [GitHub](https://github.com/JSC-electronics/ObjectButton).
 */

/**
 * @example ToggleLedOnClick.ino
 *
 * This sketch demonstrates using ObjectButton library with single digital button,
 * which will turn built-in LED on or off after being clicked.
 */

/**
 * @example AnalogButtonToggleLedOnClick.ino
 *
 * This sketch demonstrates using ObjectButton library with single analog button,
 * which will turn built-in LED on or off after being clicked.
 */

/**
 * @example AnalogSensorToggleLedOnDetect.ino
 *
 * This sketch demonstrates using ObjectButton library with single analog sensor,
 * which will turn built-in LED on or off after being clicked.
 */

/**
 * @example ToggleLedOnDoubleClick.ino
 *
 * This sketch demonstrates using ObjectButton library with single digital button,
 * which will turn built-in LED on or off after being double-clicked.
 */

/**
 * @example ToggleLedOnDoubleClickWithInterrupt.ino
 *
 * This sketch demonstrates using ObjectButton library with single digital button,
 * which will turn built-in LED on or off after being double-clicked.
 *
 * This example is almost identical to ToggleLedOnDoubleClick.ino, except
 * button state refresh is bound to interrupt.
 */

/**
 * @example TurnLedOnLongPress.ino
 *
 * This sketch demonstrates using ObjectButton library with single digital button,
 * which will turn built-in LED on when it's long-pressed.
 */

/**
 * @example TwoDigitalButtons.ino
 *
 * This sketch demonstrates using ObjectButton library with two distinct digital buttons.
 *
 * In this example we receive all events produced by buttons and print
 * which event occurred on which button to the serial monitor.
 */

/**
 * @example TwoAnalogButtonsOnTheSamePin.ino
 *
 * This sketch demonstrates using ObjectButton library with two distinct analog buttons sharing the same pin.
 *
 * In this example we receive all events produced by buttons and print
 * which event occurred on which button to the serial monitor.
 */

/**
 * @example TwoAnalogSensorsOnTheSamePin.ino
 *
 * This sketch demonstrates using ObjectButton library with two distinct analog sensors sharing the same pin.
 *
 * In this example we receive a click event, which simulates motion detection.
 */

/**
 * @example BlinkMachine.ino
 *
 * A more complicated blink state machine example.
 *
 * - Turn built-in LED on or off with a click gesture.
 * - Toggle built-in LED blinking between steady, slow and fast state with a double click gesture.
 *
 * This example is heavily inspired by a sketch from OneButton library:
 *
 * https://github.com/mathertel/OneButton/blob/master/examples/BlinkMachine/BlinkMachine.ino
 *
 * See their sketch for more details on internal workings, if it's not clear for your from this code.
 */

/**
 * @example ClassNameConflictResolution.ino
 * 
 * By default, all classes in C++ are in global namespace. It means that
 * each class name has to be unique inside your projects. Otherwise, you'll
 * have linker issues, when you include header files from two libraries,
 * which define classes with the same name.
 * 
 * In this example, we'll show you how to deal with naming collision
 * issues using M5stack library and ObjectButton library, where both
 * define a class called Button.
 */
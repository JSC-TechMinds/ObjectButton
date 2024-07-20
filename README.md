# ObjectButton
[![Arduino_CI](https://github.com/JSC-TechMinds/ObjectButton/actions/workflows/arduino_ci.yml/badge.svg)](https://github.com/JSC-TechMinds/ObjectButton/actions/workflows/arduino_ci.yml)
[![Documentation](https://github.com/JSC-TechMinds/ObjectButton/actions/workflows/doxygen.yml/badge.svg)](https://github.com/JSC-TechMinds/ObjectButton/actions/workflows/doxygen.yml)
[![License: Apache 2.0](https://img.shields.io/badge/license-Apache--2.0-green.svg)](https://github.com/JSC-TechMinds/ObjectButton/blob/main/LICENSE)
[![GitHub release](https://img.shields.io/github/release/JSC-TechMinds/ObjectButton.svg?maxAge=3600)](https://github.com/JSC-TechMinds/ObjectButton/releases)
[![JSC TechMinds](https://img.shields.io/badge/JSC-TechMinds-green.svg)](https://www.jsctm.cz/)
[![Donate](https://img.shields.io/badge/donate-PayPal-blueviolet.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=SESX9ABM7V8KA&source=url)

ObjectButton is an Arduino library for detecting common button actions. Because of it, you can map different functions into a single button, i.e. turn on the light on a button click and play an alarm sound on double-click.

## Rationale
This library was inspired by an existing Arduino library, [OneButton][OneButton]. It allows you to attach a callback function to a specific action. This callback function is basically a pointer to a function. Following approach works great for C-like functions, but not for [C++ object member functions][so-object-member]. Also, if your function gets called, it has no idea, which button called it.

To sum up:
- Only C-like functions can be called back
- Function does not know, which button called it
- If you have more buttons, neccesity to map actions to different functions

### Listeners
Approach used in this library was inspired by [Android][android-listener]. Instead of passing a function callback, you'll implement listeners inside your class and pass a reference to your object. Our library can call all the functions defined in the listener, no need to pass callbacks to individual functions anymore! Also, each callback function has one input parameter - a reference to `ObjectButton` instance. This way we can differentiate, which button produced an event and have code for all the buttons in one place.

Supported listeners:
- [IOnClickListener](src/interfaces/IOnClickListener.h)
- [IOnDoubleClickListener](src/interfaces/IOnDoubleClickListener.h)
- [IOnPressListener](src/interfaces/IOnPressListener.h)

Check out the [examples](examples) for an inspiration.

## Actions
At the moment, following actions are detected:
- Click
- Double-click
- Button press
- Button release
- Button long press
- Button release after a long press

## Analog and digital buttons
At the moment, we suppport both analog and digital buttons:
- Each digital button needs to be connected to a unique pin
- You can distinguish digital buttons based on their button ID, which matches pin number
- Analog buttons can share the same pin. We detect actions based on different voltage levels
- In order to distinguish analog buttons among themselves, each button requires to set up a button ID as a mandatory parameter. It's an arbitrary number from 0 - 255, and it should be unique. If you use the same button ID on two analog buttons, your code will work, but you won't distinguish, which button triggered an action. At the moment, we don't validate user input. You should know what you're doing.

> Note: Detection of simultaneous press of two analog buttons sharing the same pin is not supported.

## Analog and digital sensors
Sensors are rebranded buttons; they have exactly the same functionality. While buttons react to click, double-click, and press actions, sensors react to motion or other visual changes.

> Note: While we defined sensor types, listeners stay the same. It means you can hook up onClickListener to a sensor. Maybe we'll think of a more elegant solution in the future.

### Tweaking action recognition
This library comes with reasonable defaults for detecting all the actions. However, you can tweak the values to better fit your project. First, create a new `ObjectButton` instance. Then, call one of these functions:
- `setDebounceTicks()` to adjust the debounce interval for more reliable pattern recognition
- `setClickTicks()` to adjust the time to detect a click action
- `setLongPressTicks()` to adjust the time to detect a long press action

## Documentation
- [GitHub Wiki][object-button-wiki]
- [Extended Doxygen Documentation][object-button-doxygen]
- [Examples](examples)

## Contributing
There are many ways in which you can participate in the project, for example:

* [Submit bugs and feature requests](https://github.com/JSC-TechMinds/ObjectButton/issues), and help us verify as they are checked in
* Review [source code changes](https://github.com/JSC-TechMinds/ObjectButton/pulls)
* Review the [documentation](https://github.com/JSC-TechMinds/ObjectButton/wiki) and make pull requests for anything from typos to new content

Please read [contributing rules](CONTRIBUTING.md) for more details.

## License

Copyright (c) JSC TechMinds. All rights reserved.

Licensed under the [Apache-2.0](LICENSE) license.

## Support

We hope our library helped to speed up your project development. You can support our effort to convert coffe and pizza into a code with a small donation. Any support is much appreciated.

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=SESX9ABM7V8KA&source=url)

[//]: # (Used references)
[OneButton]: https://github.com/mathertel/OneButton
[so-object-member]: https://stackoverflow.com/questions/8865766/get-a-pointer-to-objects-member-function
[android-listener]: https://developer.android.com/reference/android/view/View.OnClickListener
[object-button-wiki]: https://github.com/JSC-TechMinds/ObjectButton/wiki
[object-button-doxygen]: https://JSC-TechMinds.github.io/ObjectButton

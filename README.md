# ObjectButton
[![Build Status](https://travis-ci.com/JSC-electronics/ObjectButton.svg?branch=master)](https://travis-ci.com/JSC-electronics/ObjectButton)
[![GitHub release](https://img.shields.io/github/release/JSC-electronics/ObjectButton.svg?maxAge=3600)](https://github.com/JSC-electronics/ObjectButton/releases)
[![License: Apache 2.0](https://img.shields.io/badge/license-Apache--2.0-green.svg)](https://github.com/JSC-electronics/android-phone-field/blob/master/LICENSE)

ObjectButton is an Arduino library for detecting common button actions. Because of it, you can map different functions into a single button, i.e. turn on the light on a button click and play an alarm sound on double-click.

## Rationale
This library was inspired by an existing Arduino library, [OneButton][OneButton]. It allow you to attach a callback function to a specific action. This callback function is basically a pointer to a function. Following approach works great for C-like functions, but not for [C++ methods inside objects][so-object-member]. Also, if your function gets called, it has no idea, which button called it.

To sum up:
- Only C-like functions can be called back
- Function does not know, which button called it
- If you have more buttons, neccesity to map actions to different functions

### Listeners
Approach used in this library was inspired by [Android][android-listener]. Instead of passing a function callback, you'll implement listeners inside your class and pass a reference to your object. Our library can call all the methods defined in the listener, no need to pass callbacks to individual methods anymore! Also, each callback method has one input parameter - a reference to `ObjectButton` instance. This way we can differentiate, which button produced an event and have code for all the buttons in one place.

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

### Tweaking action recognition
This library comes with reasonable defaults for detecting all the actions. However, you can tweak the values to better fit your project. First, create a new `ObjectButton` instance. Then, call one of these methods:
- `setDebounceTicks()` to adjust the debounce interval for more reliable pattern recognition
- `setClickTicks()` to adjust the time to detect a click action
- `setLongPressTicks()` to adjust the time to detect a long press action

## Documentation
- [GitHub Wiki][object-button-wiki]
- [Extended Doxygen Documentation][object-button-doxygen]
- [Examples](examples)

## License

Copyright (c) JSC electronics. All rights reserved.

Licensed under the [Apache-2.0](LICENSE.md) license.


[//]: # (Used references)
[OneButton]: https://github.com/mathertel/OneButton
[so-object-member]: https://stackoverflow.com/questions/8865766/get-a-pointer-to-objects-member-function
[android-listener]: https://developer.android.com/reference/android/view/View.OnClickListener
[object-button-wiki]: https://github.com/JSC-electronics/ObjectButton/wiki
[object-button-doxygen]: https://jsc-electronics.github.io/ObjectButton
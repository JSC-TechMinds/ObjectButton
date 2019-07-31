#pragma once

class ObjectButton;

/**
 * Callback interface for button press/release events
 */
class IOnPressListener {
public:
    virtual ~IOnPressListener() = default;

    virtual void onPress(ObjectButton& button) = 0;

    virtual void onRelease(ObjectButton& button) = 0;
};


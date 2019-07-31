#pragma once

class OneButton;

/**
 * Callback interface for button press/release events
 */
class IOnPressListener {
public:
    virtual ~IOnPressListener() = default;

    virtual void onPress(OneButton& button) = 0;

    virtual void onRelease(OneButton& button) = 0;
};


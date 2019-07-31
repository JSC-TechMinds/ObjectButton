#pragma once

class ObjectButton;

/**
 * Callback interface for click events
 */
class IOnClickListener {
public:
    virtual ~IOnClickListener() = default;

    virtual void onClick(ObjectButton& button) = 0;
};


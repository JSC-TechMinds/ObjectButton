#pragma once

class OneButton;

/**
 * Callback interface for click events
 */
class IOnClickListener {
public:
    virtual ~IOnClickListener() = default;

    virtual void onClick(OneButton& button) = 0;
};


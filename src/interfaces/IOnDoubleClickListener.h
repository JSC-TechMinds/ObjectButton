#pragma once

class OneButton;

/**
 * Callback interface for double-click events
 */
class IOnDoubleClickListener {
public:
    virtual ~IOnDoubleClickListener() = default;

    virtual void onDoubleClick(OneButton& button) = 0;
};


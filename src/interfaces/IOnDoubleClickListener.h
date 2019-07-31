#pragma once

class ObjectButton;

/**
 * Callback interface for double-click events
 */
class IOnDoubleClickListener {
public:
    virtual ~IOnDoubleClickListener() = default;

    virtual void onDoubleClick(ObjectButton& button) = 0;
};


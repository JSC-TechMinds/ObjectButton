/**
 * Copyright 2019 JSC electronics
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "../src/ObjectButton.h"
#include "../src/interfaces/IOnClickListener.h"
#include "../src/interfaces/IOnDoubleClickListener.h"
#include "../src/interfaces/IOnPressListener.h"

class ListenerMock : private virtual IOnClickListener,
        private virtual IOnDoubleClickListener, private virtual IOnPressListener {
public:
    explicit ListenerMock(int inputPin, bool activeLow);
    ObjectButton& getButton();
    bool didReceiveOnClickEvent();
    bool didReceiveOnDoubleClickEvent();
    bool didReceiveOnPressEvent();
    bool didReceiveOnReleaseEvent();
    void resetState();

private:
    void onClick(ObjectButton &button) override;
    void onDoubleClick(ObjectButton& button) override;
    void onPress(ObjectButton& button) override;
    void onRelease(ObjectButton& button) override;

    ObjectButton m_button;
    bool m_onClickEventReceived = false;
    bool m_onDoubleClickEventReceived = false;
    bool m_onPressEventReceived = false;
    bool m_onReleaseEventReceived = false;
};

ListenerMock::ListenerMock(int inputPin, bool activeLow): m_button(inputPin, activeLow) {
    m_button.setOnClickListener(this);
    m_button.setOnDoubleClickListener(this);
    m_button.setOnPressListener(this);
}

ObjectButton& ListenerMock::getButton() {
    return m_button;
}

bool ListenerMock::didReceiveOnClickEvent() {
    return m_onClickEventReceived;
};

bool ListenerMock::didReceiveOnDoubleClickEvent() {
    return m_onDoubleClickEventReceived;
};

bool ListenerMock::didReceiveOnPressEvent(){
    return m_onPressEventReceived;
};

bool ListenerMock::didReceiveOnReleaseEvent(){
    return m_onReleaseEventReceived;
};

void ListenerMock::resetState() {
    m_button.reset();
    m_onClickEventReceived = false;
    m_onDoubleClickEventReceived = false;
    m_onPressEventReceived = false;
    m_onReleaseEventReceived = false;
}

void ListenerMock::onClick(ObjectButton &button) {
    m_onClickEventReceived = true;
}

void ListenerMock::onDoubleClick(ObjectButton &button) {
    m_onDoubleClickEventReceived = true;
}

void ListenerMock::onPress(ObjectButton &button){
    m_onPressEventReceived = true;
}

void ListenerMock::onRelease(ObjectButton &button){
    m_onReleaseEventReceived = true;
}

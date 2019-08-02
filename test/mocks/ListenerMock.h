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

    ObjectButton &getButton();

    int getClickEventsReceivedCount();

    int getDoubleClickEventsReceivedCount();

    int getPressEventsReceivedCount();

    int getReleaseEventsReceivedCount();

    int getLongPressStartEventsReceivedCount();

    int getLongPressEndEventsReceivedCount();

    void resetState();

private:
    void onClick(ObjectButton &button) override;

    void onDoubleClick(ObjectButton &button) override;

    void onPress(ObjectButton &button) override;

    void onRelease(ObjectButton &button) override;

    void onLongPressStart(ObjectButton &button) override;

    void onLongPressEnd(ObjectButton &button) override;

    ObjectButton m_button;
    int m_onClickEventsReceived = 0;
    int m_onDoubleClickEventsReceived = 0;
    int m_onPressEventsReceived = 0;
    int m_onReleaseEventsReceived = 0;
    int m_onLongPressStartEventsReceived = 0;
    int m_onLongPressEndEventsReceived = 0;
};

ListenerMock::ListenerMock(int inputPin, bool activeLow) : m_button(inputPin, activeLow) {
    m_button.setOnClickListener(this);
    m_button.setOnDoubleClickListener(this);
    m_button.setOnPressListener(this);
}

ObjectButton &ListenerMock::getButton() {
    return m_button;
}

int ListenerMock::getClickEventsReceivedCount() {
    return m_onClickEventsReceived;
};

int ListenerMock::getDoubleClickEventsReceivedCount() {
    return m_onDoubleClickEventsReceived;
};

int ListenerMock::getPressEventsReceivedCount() {
    return m_onPressEventsReceived;
};

int ListenerMock::getReleaseEventsReceivedCount() {
    return m_onReleaseEventsReceived;
};

int ListenerMock::getLongPressStartEventsReceivedCount() {
    return m_onLongPressStartEventsReceived;
};

int ListenerMock::getLongPressEndEventsReceivedCount() {
    return m_onLongPressEndEventsReceived;
};

void ListenerMock::resetState() {
    m_button.reset();
    m_onClickEventsReceived = 0;
    m_onDoubleClickEventsReceived = 0;
    m_onPressEventsReceived = 0;
    m_onReleaseEventsReceived = 0;
    m_onLongPressStartEventsReceived = 0;
    m_onLongPressEndEventsReceived = 0;
}

void ListenerMock::onClick(ObjectButton &button) {
    m_onClickEventsReceived++;
}

void ListenerMock::onDoubleClick(ObjectButton &button) {
    m_onDoubleClickEventsReceived++;
}

void ListenerMock::onPress(ObjectButton &button) {
    m_onPressEventsReceived++;
}

void ListenerMock::onRelease(ObjectButton &button) {
    m_onReleaseEventsReceived++;
}

void ListenerMock::onLongPressStart(ObjectButton &button) {
    m_onLongPressStartEventsReceived++;
}

void ListenerMock::onLongPressEnd(ObjectButton &button) {
    m_onLongPressEndEventsReceived++;
}

/**
 *  @file       ListenerMock.h
 *  Project     ObjectButton
 *  @brief      An Arduino library for detecting button actions.
 *  @author     Vladimír Záhradník
 *  License     Apache-2.0 - Copyright (c) 2019 JSC electronics
 *
 *  Copyright (c) 2019 JSC electronics
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

/**
 * @brief Helper class used in unit tests.
 *
 * Purpose of this class is to serve as a listener for all button events and count all
 * button events as they happen. In our unit tests we can check if a specific
 * event occurred and compare counted occurrences with expected value.
 */
class ListenerMock : private virtual IOnClickListener,
                     private virtual IOnDoubleClickListener, private virtual IOnPressListener {
public:
    /**
     * Constructor
     * @param inputPin is a pin to which a button is attached. In this case a pin is mocked and controlled by a test.
     * @param activeLow passes activeLow value to ObjectButton constructor
     *
     * @see ObjectButton(uint8_t pin, bool activeLow = true)
     */
    explicit ListenerMock(int inputPin, bool activeLow);

    /**
     * @brief Get reference to button created inside this mock.
     *
     * Getting a reference to the internal button allows us to have full control
     * over behavior, which is very important in a test. With this approach we do not need to create
     * custom methods, which call button methods. Instead we call button methods directly.
     * @return a reference to internal button instance inside the mock.
     */
    ObjectButton &getButton();

    /**
     * @brief Get number of click events which occurred since this mock was reset.
     * @return a number of click events.
     */
    int getClickEventsReceivedCount();

    /**
     * @brief Get number of double-click events which occurred since this mock was reset.
     * @return a number of double-click events.
     */
    int getDoubleClickEventsReceivedCount();

    /**
     * @brief Get number of press events which occurred since this mock was reset.
     * @return a number of press events.
     */
    int getPressEventsReceivedCount();

    /**
     * @brief Get number of release events which occurred since this mock was reset.
     * @return a number of release events.
     */
    int getReleaseEventsReceivedCount();

    /**
     * @brief Get number of long press start events which occurred since this mock was reset.
     * @return a number of long press start events.
     */
    int getLongPressStartEventsReceivedCount();

    /**
     * @brief Get number of long press end events which occurred since this mock was reset.
     * @return a number of long press end events.
     */
    int getLongPressEndEventsReceivedCount();

    /**
     * @brief Reset this mock listener to default state, including counters.
     */
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

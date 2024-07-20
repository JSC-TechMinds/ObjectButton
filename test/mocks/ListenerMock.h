/**
 *  @file       ListenerMock.h
 *  Project     ObjectButton
 *  @brief      An Arduino library for detecting button actions.
 *  @author     JSC TechMinds
 *  License     Apache-2.0 - Copyright (c) 2019-2024 JSC TechMinds
 *
 *  @section License
 *
 *  Copyright (c) 2019-2024 JSC TechMinds
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
using namespace jsc;

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
     * @param inputPullUp passes inputPullUp value to Button constructor
     *
     * @see Button(uint8_t pin, bool inputPullUp = true)
     */
    explicit ListenerMock(Button& button);

    /**
     * @brief Get reference to button created inside this mock.
     *
     * Getting a reference to the internal button allows us to have full control
     * over behavior, which is very important in a test. With this approach we do not need to create
     * custom functions, which pass call to button functions. Instead we call button functions directly.
     * @return a reference to internal button instance inside the mock.
     */
    Button& getButton();

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
    void onClick(Button& button) override;

    void onDoubleClick(Button& button) override;

    void onPress(Button& button) override;

    void onRelease(Button& button) override;

    void onLongPressStart(Button& button) override;

    void onLongPressEnd(Button& button) override;

    Button& m_button;
    int m_onClickEventsReceived = 0;
    int m_onDoubleClickEventsReceived = 0;
    int m_onPressEventsReceived = 0;
    int m_onReleaseEventsReceived = 0;
    int m_onLongPressStartEventsReceived = 0;
    int m_onLongPressEndEventsReceived = 0;
};

ListenerMock::ListenerMock(Button& button) : m_button(button) {
    m_button.setOnClickListener(this);
    m_button.setOnDoubleClickListener(this);
    m_button.setOnPressListener(this);
}

Button& ListenerMock::getButton() {
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

void ListenerMock::onClick(Button& button) {
    m_onClickEventsReceived++;
}

void ListenerMock::onDoubleClick(Button& button) {
    m_onDoubleClickEventsReceived++;
}

void ListenerMock::onPress(Button& button) {
    m_onPressEventsReceived++;
}

void ListenerMock::onRelease(Button& button) {
    m_onReleaseEventsReceived++;
}

void ListenerMock::onLongPressStart(Button& button) {
    m_onLongPressStartEventsReceived++;
}

void ListenerMock::onLongPressEnd(Button& button) {
    m_onLongPressEndEventsReceived++;
}

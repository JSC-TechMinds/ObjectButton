/**
 *  @file       IOnDoubleClickListener.h
 *  Project     ObjectButton
 *  @brief      An Arduino library for processing GPIO inputs as button actions
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

class ObjectButton;

/**
 * @brief Callback interface for double-click events.
 *
 * Each object passed to ObjectButton instance as an OnDoubleClickListener should inherit
 * this class and implement virtual methods. See Examples for more details.
 */
class IOnDoubleClickListener {
public:
    /**
     * Destructor
     */
    virtual ~IOnDoubleClickListener() = default;

    /**
     * Callback method to be called when a double-click event occurs.
     * @param button is a reference to the instance which called the listener.
     */
    virtual void onDoubleClick(ObjectButton &button) = 0;
};


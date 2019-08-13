/**
 *  @file       IOnClickListener.h
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

class ObjectButton;

/**
 * @brief Callback interface for click events.
 *
 * Each object passed to ObjectButton instance as an OnClickListener should inherit
 * this class and implement virtual functions. See Examples for more details.
 */
class IOnClickListener {
public:
    /**
     * Destructor
     */
    virtual ~IOnClickListener() = default;

    /**
     * Callback function to be called when a click event occurs.
     * @param button is a reference to the instance which called the listener.
     */
    virtual void onClick(ObjectButton &button) = 0;
};


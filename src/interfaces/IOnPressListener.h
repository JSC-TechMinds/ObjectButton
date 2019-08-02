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

class ObjectButton;

/**
 * Callback interface for button press/release events
 */
class IOnPressListener {
public:
    virtual ~IOnPressListener() = default;

    virtual void onPress(ObjectButton& button) = 0;

    virtual void onRelease(ObjectButton& button) = 0;

    virtual void onLongPressStart(ObjectButton& button) = 0;

    virtual void onLongPressEnd(ObjectButton& button) = 0;
};


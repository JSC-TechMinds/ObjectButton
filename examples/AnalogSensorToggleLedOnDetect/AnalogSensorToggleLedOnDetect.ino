/**
 * @brief Single analog sensor, detection (click) example.
 *
 * This sketch demonstrates using ObjectButton library with single analog sensor,
 * which will turn built-in LED on or off after some motion is being detected.
 *
 * Copyright 2019-2020 JSC electronics
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

#include <ObjectButton.h>
using namespace jsc;

constexpr static byte SENSOR_ID = 1;
constexpr static byte INPUT_PIN = A1;
constexpr static int ON_DETECT_VOLTAGE = 1000;
constexpr static byte LED_PIN = LED_BUILTIN;

class ToggleLedOnDetect : private virtual IOnClickListener {
public:
    ToggleLedOnDetect() = default;

    void init();

    void update();

private:
    void onClick(Button& button) override;

    AnalogSensor sensor = AnalogSensor(SENSOR_ID, INPUT_PIN, ON_DETECT_VOLTAGE);
    byte ledState = LOW;
};

void ToggleLedOnDetect::onClick(Button& button) {
    if (sensor.getId() == SENSOR_ID) {
        Serial.println("Sensor detected some movement!");

        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}

void ToggleLedOnDetect::init() {
    // Setup the Serial port. See http://arduino.cc/en/Serial/IfSerial
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for Leonardo only
    }
    pinMode(LED_PIN, OUTPUT);
    sensor.setDebounceTicks(10);
    sensor.setOnClickListener(this);
}

void ToggleLedOnDetect::update() {
    sensor.tick();
}

ToggleLedOnDetect toggleLedOnDetect = ToggleLedOnDetect();

void setup() {
    toggleLedOnDetect.init();
}

void loop() {
    toggleLedOnDetect.update();
}

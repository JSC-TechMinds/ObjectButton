/**
 * @brief Two distinct analog sensors example.
 *
 * This sketch demonstrates using ObjectButton library with two distinct analog sensors.
 *
 * In this example we receive onClick() event, which simulates a motion detection.
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

constexpr static byte INPUT_PIN = A1;
constexpr static byte SENSOR_1_ID = 100;
constexpr static byte SENSOR_1_ON_PRESS_VOLTAGE = 1000;
constexpr static byte SENSOR_2_ID = 200;
constexpr static byte SENSOR_2_ON_PRESS_VOLTAGE = 400;

class TwoSensors : private virtual IOnClickListener {
public:
    TwoSensors() = default;

    void init();

    void update();

private:
    void onClick(Button& button) override;

    AnalogSensor sensor1 = AnalogSensor(SENSOR_1_ID, INPUT_PIN, SENSOR_1_ON_PRESS_VOLTAGE);
    AnalogSensor sensor2 = AnalogSensor(SENSOR_2_ID, INPUT_PIN, SENSOR_2_ON_PRESS_VOLTAGE);
};

void TwoSensors::onClick(Button& button) {
    switch (button.getId()) {
        case SENSOR_1_ID:
            Serial.println("Sensor 1 detected some movement!");
            break;
        case SENSOR_2_ID:
            Serial.println("Sensor 2 detected some movement!");
            break;
    }
}

void TwoSensors::init() {
    // Setup the Serial port. See http://arduino.cc/en/Serial/IfSerial
    Serial.begin(9600);
    while (!Serial) { ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("Starting TwoSensors...");

    sensor1.setDebounceTicks(10);
    sensor1.setOnClickListener(this);

    sensor2.setDebounceTicks(10);
    sensor2.setOnClickListener(this);
}

void TwoSensors::update() {
    sensor1.tick();
    sensor2.tick();
}

TwoSensors twoSensors = TwoSensors();

void setup() {
    twoSensors.init();
}

void loop() {
    twoSensors.update();
}

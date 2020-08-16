/**
 * @brief Resolving linker issues when two libraries have classes with the same name.
 * 
 * By default, all classes in C++ are in global namespace. It means that
 * each class name has to be unique inside your projects. Otherwise, you'll
 * have linker issues, when you include header files from two libraries,
 * which define classes with the same name.
 * 
 * In this example, we use M5stack library and ObjectButton library.
 * Both libraries originally defined a class Button in a global namespace. 
 * In other words, if you use M5stack Core, it will be difficult for you 
 * to build your project.
 * 
 * To solve this and potentionally other issues, we moved our code into JSC
 * namespace. Instead of referencing our class Button like this:
 * Button someButton;
 * 
 * You'll reference it like this:
 * jsc::Button someButton
 * 
 * With the namespace, linker can distinguish between our and other class 
 * with the same name.
 * 
 * If you don't use other libraries with conflicting names, you can
 * declare using our namespace after include statements, like so:
 * 
 * #include <...>
 * #using namespace jsc;
 * 
 * In which case, you'll reference our code as if there was no namespace.
 * All our examples have the "using namespace jsc" statement.
 * 
 * In this example, we'll show you, how to write your code, when you
 * have class name conflicts.
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

#include <M5Stack.h>
#include <ObjectButton.h>

constexpr static byte INPUT_PIN = BUTTON_A_PIN;
constexpr static byte LED_PIN = TFT_LED_PIN;

namespace jsc {
  class ToggleLedOnClick : private virtual IOnClickListener {
  public:
      ToggleLedOnClick() = default;
  
      void init();
  
      void update();
  
  private:
      void onClick(Button& button) override;
  
      DigitalButton button = DigitalButton(INPUT_PIN);
      byte ledState = LOW;
  };
  
  void ToggleLedOnClick::onClick(Button& button) {
      if (button.getId() == INPUT_PIN) {
          Serial.println("Button clicked!");
  
          ledState = !ledState;
          digitalWrite(LED_PIN, ledState);
      }
  }
  
  void ToggleLedOnClick::init() {
      // Setup the Serial port. See http://arduino.cc/en/Serial/IfSerial
      Serial.begin(9600);
      while (!Serial) { ; // wait for serial port to connect. Needed for Leonardo only
      }
      pinMode(LED_PIN, OUTPUT);
      button.setDebounceTicks(10);
      button.setOnClickListener(this);
  }

  void ToggleLedOnClick::update() {
      button.tick();
  }
}

jsc::ToggleLedOnClick toggleLedOnClick;

void setup() {
    toggleLedOnClick.init();
}

void loop() {
    toggleLedOnClick.update();
}

#include <ObjectButton.h>
#include <interfaces/IOnClickListener.h>

#define INPUT_PIN A1
#define LED_PIN LED_BUILTIN

class Blink : private virtual IOnClickListener {
public:
    Blink() = default;

    void init();

    void update();

private:
    void onClick(ObjectButton &button) override;

    ObjectButton button = ObjectButton(INPUT_PIN, /* activeLow */ true);
    int ledState = LOW;
};

void Blink::onClick(ObjectButton &button) {
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button clicked!");
      
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}

void Blink::init() {
    button.setDebounceTicks(10);
    button.setOnClickListener(this);
}

void Blink::update() {
    button.tick();
}

Blink blink = Blink();

void setup() {
    Serial.begin(9600);
  
    pinMode(LED_PIN, OUTPUT);
    blink.init();
}

void loop() {
    blink.update();
}

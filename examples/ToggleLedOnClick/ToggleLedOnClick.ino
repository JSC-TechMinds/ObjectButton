#include <ObjectButton.h>
#include <interfaces/IOnClickListener.h>

#define INPUT_PIN A1
#define LED_PIN LED_BUILTIN

class ToggleLedOnClick : private virtual IOnClickListener {
public:
    ToggleLedOnClick() = default;

    void init();
    void update();

private:
    void onClick(ObjectButton &button) override;

    ObjectButton button = ObjectButton(INPUT_PIN, /* activeLow */ true);
    int ledState = LOW;
};

void ToggleLedOnClick::onClick(ObjectButton &button) {
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button clicked!");
      
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}

void ToggleLedOnClick::init() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    button.setDebounceTicks(10);
    button.setOnClickListener(this);
}

void ToggleLedOnClick::update() {
    button.tick();
}

ToggleLedOnClick toggleLedOnClick = ToggleLedOnClick();

void setup() {
    toggleLedOnClick.init();
}

void loop() {
    toggleLedOnClick.update();
}

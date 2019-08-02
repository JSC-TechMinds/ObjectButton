#include <ObjectButton.h>
#include <interfaces/IOnDoubleClickListener.h>

#define INPUT_PIN A1
#define LED_PIN LED_BUILTIN

class ToggleLedOnDoubleClick : private virtual IOnDoubleClickListener {
public:
    ToggleLedOnDoubleClick() = default;

    void init();
    void update();

private:
    void onDoubleClick(ObjectButton &button) override;

    ObjectButton button = ObjectButton(INPUT_PIN, /* activeLow */ true);
    int ledState = LOW;
};

void ToggleLedOnDoubleClick::onDoubleClick(ObjectButton &button) {
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button double-clicked!");
      
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}

void ToggleLedOnDoubleClick::init() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    button.setDebounceTicks(10);
    button.setOnDoubleClickListener(this);
}

void ToggleLedOnDoubleClick::update() {
    button.tick();
}

ToggleLedOnDoubleClick toggleLedOnDoubleClick = ToggleLedOnDoubleClick();

void setup() {
    toggleLedOnDoubleClick.init();
}

void loop() {
    toggleLedOnDoubleClick.update();
}

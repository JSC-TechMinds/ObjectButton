#include <ObjectButton.h>
#include <interfaces/IOnDoubleClickListener.h>

#define INPUT_PIN A1
#define LED_PIN LED_BUILTIN

class BlinkOnDoubleClick : private virtual IOnDoubleClickListener {
public:
    BlinkOnDoubleClick() = default;

    void init();
    void update();

private:
    void onDoubleClick(ObjectButton &button) override;

    ObjectButton button = ObjectButton(INPUT_PIN, /* activeLow */ true);
    int ledState = LOW;
};

void BlinkOnDoubleClick::onDoubleClick(ObjectButton &button) {
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button double-clicked!");
      
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}

void BlinkOnDoubleClick::init() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    button.setDebounceTicks(10);
    button.setOnDoubleClickListener(this);
}

void BlinkOnDoubleClick::update() {
    button.tick();
}

BlinkOnDoubleClick blinkOnDoubleClick = BlinkOnDoubleClick();

void setup() {
    blinkOnDoubleClick.init();
}

void loop() {
    blinkOnDoubleClick.update();
}

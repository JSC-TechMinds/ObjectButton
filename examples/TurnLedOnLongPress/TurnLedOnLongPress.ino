#include <ObjectButton.h>
#include <interfaces/IOnPressListener.h>

#define INPUT_PIN A1
#define LED_PIN LED_BUILTIN

class TurnLedOnLongPress : private virtual IOnPressListener {
public:
    TurnLedOnLongPress() = default;

    void init();
    void update();

private:
    void onPress(ObjectButton& button) override {};
    void onRelease(ObjectButton& button) override {};
    void onLongPressStart(ObjectButton& button) override;
    void onLongPressEnd(ObjectButton& button) override;

    ObjectButton button = ObjectButton(INPUT_PIN, /* activeLow */ true);
};

void TurnLedOnLongPress::onLongPressStart(ObjectButton &button){
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button long press started, turning LED on!");
        digitalWrite(LED_PIN, HIGH);
    }
}

void TurnLedOnLongPress::onLongPressEnd(ObjectButton &button){
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button long press ended, turning LED off!");
        digitalWrite(LED_PIN, LOW);
    }
}

void TurnLedOnLongPress::init() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    button.setDebounceTicks(10);
    button.setOnPressListener(this);
}

void TurnLedOnLongPress::update() {
    button.tick();
}

TurnLedOnLongPress turnLedOnLongPress = TurnLedOnLongPress();

void setup() {
    turnLedOnLongPress.init();
}

void loop() {
    turnLedOnLongPress.update();
}

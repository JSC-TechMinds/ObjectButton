#include <ObjectButton.h>
#include <interfaces/IOnPressListener.h>

#define INPUT_PIN A1
#define LED_PIN LED_BUILTIN

class TurnLedOnPress : private virtual IOnPressListener {
public:
    TurnLedOnPress() = default;

    void init();
    void update();

private:
    void onPress(ObjectButton& button) override;
    void onRelease(ObjectButton& button) override;

    ObjectButton button = ObjectButton(INPUT_PIN, /* activeLow */ true);
};

void TurnLedOnPress::onPress(ObjectButton &button) {
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button pressed, turning LED on!");
        digitalWrite(LED_PIN, HIGH);
    }
}

void TurnLedOnPress::onRelease(ObjectButton &button){
    if (button.getId() == INPUT_PIN) {
        Serial.println("Button released, turning LED off!");
        digitalWrite(LED_PIN, LOW);
    }
}

void TurnLedOnPress::init() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    button.setDebounceTicks(10);
    button.setOnPressListener(this);
}

void TurnLedOnPress::update() {
    button.tick();
}

TurnLedOnPress turnLedOnPress = TurnLedOnPress();

void setup() {
    turnLedOnPress.init();
}

void loop() {
    turnLedOnPress.update();
}

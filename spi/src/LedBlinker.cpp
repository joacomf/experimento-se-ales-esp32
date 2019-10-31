#include <LedBlinker.h>

void LedBlinker::blink(u_int times, u_int delayBetween, u_int activeDuration){
    pinMode(LED_BUILTIN, OUTPUT);
    for (size_t i = 0; i < times; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(activeDuration);
        digitalWrite(LED_BUILTIN, LOW);
        delay(delayBetween);
    }
}

#ifndef LedBlinker_h
#define LedBlinker_h

#include <Arduino.h>

class LedBlinker {
    public:
        static void blink(u_int times, u_int delayBetween, u_int activeDuration);
};

#endif

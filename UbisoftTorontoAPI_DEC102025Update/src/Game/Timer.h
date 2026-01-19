#ifndef TIMER_H
#define TIMER_H

#include "AppSettings.h"

// Timer class to handle timing events in the game, time is measured in seconds

class Timer{
    public:
        Timer(float duration);
        // time duration for the timer, measured in seconds
        float time_duration;
        // current time this timer has last
        float curr_time;
        // set true when timer has started
        bool started;
        // return 1 if the timer has finished i.e reached its duration, else return 0
        void timer_increment_time(bool* time_up);
        void timer_start();
        void timer_end();
};
#endif
#ifndef TIMER_H
#define TIMER_H

#include "AppSettings.h"

// Timer class to handle timing events in the game, time is measured in seconds

class Timer{
    public:
        Timer(float duration);

        float time_duration; // time duration for the timer, measured in seconds

        float curr_time; // current time this timer has last

        bool started; // set true when timer has started

        void timer_increment_time(bool* time_up); // return 1 if the timer has finished i.e reached its duration, else return 0

        void timer_start(); // start the timer
        
        void timer_end(); // end the timer
};
#endif
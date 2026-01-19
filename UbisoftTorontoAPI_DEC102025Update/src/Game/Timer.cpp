
#include "Timer.h"

    Timer::Timer(float duration){
        time_duration = duration * APP_MAX_FRAME_RATE; // convert duration from frames to seconds
        curr_time = 0.0f;
        started = false;
    }

    void Timer::timer_increment_time(bool* time_up){
        if (!started){
            return;
        }
        curr_time += 1.0f;
        if(curr_time >= time_duration){  // only change time_up when the timer has finished current loop
            curr_time = 0.0f;
            *time_up = true;
            return;
        }
        return;
    }

    void Timer::timer_start(){
        started = true;
        curr_time = 0.0f;
    }

    void Timer::timer_end(){
        started = false;
        curr_time = 0.0f;
    }


//
// Created by connor on 8/4/18.
//

#include "Timer.h"

namespace Sova
{
    Timer::Timer(std::function<void()> updateFunction, int msStart, int msRepeat)
    {
        this->updateFunction = updateFunction;
        this->timeRepeatMs = msRepeat;
        this->nextUpdateTimeMs = msStart;
        this->frameDeltaCap = this->timeRepeatMs*2;
        this->timePassedRollover = this->timeRepeatMs*10;
        this->frameDeltas = 0;
        this->frameDeltaAvgMs = 0;
        this->timePassedMs = 0;
    }

    void Timer::update(double delta)
    {
        if (delta > this->frameDeltaCap) delta = this->frameDeltaCap;
        if (frameDeltas < this->minFramesToAvg)
        {
            frameDeltaAvgMs = delta;
        }
        else
        {
            frameDeltaAvgMs = ((frameDeltaAvgMs*frameDeltas)+delta)/(frameDeltas+1);
        }
        if (frameDeltas < this->maxFramesToAvg) { frameDeltas += 1; }
        else
        {
            timePassedMs += delta;
            if(timePassedMs + (frameDeltaAvgMs/2) > nextUpdateTimeMs)
            {
                this->updateFunction();
                nextUpdateTimeMs += timeRepeatMs;
                if (timePassedMs > this->timePassedRollover)
                {
                    nextUpdateTimeMs -= this->timePassedRollover;
                    timePassedMs -= this->timePassedRollover;
                }
            }
        }
    }
}
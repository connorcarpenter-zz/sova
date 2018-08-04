#pragma once

//
// Created by connor on 8/4/18.
//

#include <Sova/References/Refable.h>
#include <functional>

namespace Sova
{
    class Timer : public Sova::Refable
    {
    public:
        Timer(std::function<void()> updateFunction, int msStart, int msRepeat);
        void update(double frameDelta);
    private:
        std::function<void()> updateFunction;

        int frameDeltas;
        double frameDeltaAvgMs;
        double timePassedMs;
        int timeRepeatMs;
        int nextUpdateTimeMs;
        int frameDeltaCap;
        const int minFramesToAvg = 10;
        const int maxFramesToAvg = 30;
        int timePassedRollover;
    };
}
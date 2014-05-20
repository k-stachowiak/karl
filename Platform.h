#ifndef PLATFORM_H
#define PLATFORM_H

#include <memory>

#include <allegro5/allegro.h>

#include "Auto.h"
#include "State.h"

struct Platform {

    double m_current_time;
    double m_time_accumulator;
    AlDisplay m_display;
    AlEvQueue m_queue;

public:
    Platform();
    StateTransition ProcessEvents(State& state);
    StateTransition LoopStep(State& state);
};

#endif

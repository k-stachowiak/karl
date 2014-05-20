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
    state::StTransition ProcessEvents(state::State& state);
    state::StTransition LoopStep(state::State& state);
};

#endif

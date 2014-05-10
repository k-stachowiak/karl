#ifndef PLATFORM_H
#define PLATFORM_H

#include <memory>

#include <allegro5/allegro.h>

#include "auto.h"
#include "state.h"

struct Platform {

	double m_current_time;
	double m_time_accumulator;
	AlDisplay m_display;
	AlEvQueue m_queue;

public:
	Platform();
	Transition ProcessEvents(State& state);
	Transition LoopStep(State& state);
};

#endif

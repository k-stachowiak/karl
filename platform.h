#ifndef PLATFORM_H
#define PLATFORM_H

#include <memory>

#include <allegro5/allegro.h>

#include "auto.h"

struct State {
	virtual ~State() {}
	virtual void Tick(double dt) = 0;
	virtual void Draw(double weight) = 0;
	virtual void KeyDown(int key) {};
	virtual void KeyUp(int key) {};
	virtual void KeyTyped(int key) {};
};

struct Platform {

	bool m_done_flag;
	AlDisplay m_display;
	AlEvQueue m_queue;

	void m_CommonHandleEvent(const ALLEGRO_EVENT &ev, State& state);

public:
	Platform();
	~Platform();
	void Loop(std::unique_ptr<State> initialState);
};

#endif

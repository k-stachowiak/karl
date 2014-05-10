#ifndef STATE_GAME_H
#define STATE_GAME_H

#include <allegro5/allegro.h>

#include "common.h"
#include "resources.h"
#include "sys_drawing.h"
#include "sys_physics.h"
#include "ent.h"
#include "state.h"

class StateGame : public State {

	sys::Drawing m_drawing_system;
	sys::Physics m_physics_system;

	bool m_keys[ALLEGRO_KEY_MAX];
	struct EntGround m_ground;
	struct EntTank m_tank;

	void m_DriveCamera(FLOATING dx, FLOATING dy, FLOATING dpitch, FLOATING dyaw, double dt);
	void m_DriveTank(FLOATING boost, FLOATING turn);

public:
	StateGame(Resources& resources);
	Transition Tick(double dt) override;
	void Draw(double weight) override;
	void KeyDown(int key) override;
	void KeyUp(int key) override;
};

#endif

#ifndef GAME_H
#define GAME_H

#include "platform.h"
#include "sys.h"
#include "ent.h"

class StateGame : public State {

	sys::Drawing m_drawing_system;
	sys::Physics m_physics_system;

	bool m_keys[ALLEGRO_KEY_MAX];
	struct EntGround m_ground;
	struct EntTank m_tank;

	void m_DriveCamera(FLOATING dx, FLOATING dy, double dt);
	void m_DriveTank(FLOATING boost, FLOATING turn);

public:
	StateGame(Resources& resources);
	void Tick(double dt);
	void Draw(double weight);
	void KeyDown(int key);
	void KeyUp(int key);
};

#endif

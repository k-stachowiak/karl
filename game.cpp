#include <allegro5/allegro.h>

#include "game.h"
#include "ent.h"
#include "sys.h"

void StateGame::m_DriveCamera(FLOATING dx, FLOATING dy, double dt)
{
	const FLOATING cam_speed = 2.0;
	m_drawing_system.CameraWalk(dx * cam_speed * dt, dy * cam_speed * dt);
}

void StateGame::m_DriveTank(FLOATING boost, FLOATING turn)
{
	const FLOATING boost_force = 25;
	FLOATING rot_x, rot_y, rot_z;
	FLOATING tank_lfx, tank_lfy, tank_rfx, tank_rfy;

	m_tank.phys.GetRotationAngles(rot_x, rot_y, rot_z);

	cast_rotated_coords(boost + turn, 0, rot_z, tank_rfx, tank_rfy);
	cast_rotated_coords(boost - turn, 0, rot_z, tank_lfx, tank_lfy);

	dBodyAddForce(
		m_tank.phys.GetRTrackBody(),
		tank_rfx * boost_force,
		tank_rfy * boost_force,
		0);

	dBodyAddForce(
		m_tank.phys.GetLTrackBody(),
		tank_lfx * boost_force,
		tank_lfy * boost_force,
		0);
}

StateGame::StateGame(Resources& resources) :
	m_drawing_system { resources },
	m_ground { m_physics_system.GetWorld(), m_physics_system.GetSpace() },
	m_tank { m_physics_system.GetWorld(), m_physics_system.GetSpace() }
{
	memset(m_keys, 0, ALLEGRO_KEY_MAX * sizeof(*m_keys));

	m_physics_system.nodes.push_back(m_ground.MakePhysicsNode());
	m_drawing_system.nodes.push_back(m_ground.MakeDrawingNode());

	m_physics_system.nodes.push_back(m_tank.MakePhysicsNode());
	m_drawing_system.nodes.push_back(m_tank.MakeDrawingNode());
}

void StateGame::Tick(double dt)
{
	FLOATING cam_dx = 0;
	FLOATING cam_dy = 0;
	FLOATING tank_boost = 0;
	FLOATING tank_turn = 0;

	if (m_keys[ALLEGRO_KEY_UP]) cam_dy += 1;
	if (m_keys[ALLEGRO_KEY_DOWN]) cam_dy -= 1;
	if (m_keys[ALLEGRO_KEY_LEFT]) cam_dx -= 1;
	if (m_keys[ALLEGRO_KEY_RIGHT]) cam_dx += 1;
	m_DriveCamera(cam_dx, cam_dy, dt);

	if (m_keys[ALLEGRO_KEY_A]) tank_turn -= 1;
	if (m_keys[ALLEGRO_KEY_D]) tank_turn += 1;
	if (m_keys[ALLEGRO_KEY_S]) tank_boost -= 1;
	if (m_keys[ALLEGRO_KEY_W]) tank_boost += 1;
	m_DriveTank(tank_boost, tank_turn);

	m_physics_system.Perform(dt);
}

void StateGame::Draw(double)
{
	// TODO: Incorporate weight.
	m_drawing_system.Perform();
}

void StateGame::KeyDown(int key)
{
	m_keys[key] = true;
}

void StateGame::KeyUp(int key)
{
	m_keys[key] = false;
}


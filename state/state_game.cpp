#include "state_game.h"

void StateGame::m_DriveCamera(
		FLOATING dx, FLOATING dy,
		FLOATING dpitch, FLOATING dyaw,
		double dt)
{
	const FLOATING cam_move_speed = 2.0;
	const FLOATING cam_rotate_speed = 1.0;

	m_drawing_system.CameraRotate(
		dpitch * cam_rotate_speed * dt,
		dyaw * cam_rotate_speed * dt,
		0);

	m_drawing_system.CameraWalk(
		dx * cam_move_speed * dt,
		dy * cam_move_speed * dt);
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

	m_physics_system.AddNode(m_ground.MakePhysicsNode());
	m_drawing_system.AddNode(m_ground.MakeDrawingNode());

	m_physics_system.AddNode(m_tank.MakePhysicsNode());
	m_drawing_system.AddNode(m_tank.MakeDrawingNode());
}

Transition StateGame::Tick(double dt)
{
	FLOATING cam_dx = 0;
	FLOATING cam_dy = 0;
	FLOATING cam_dpitch = 0;
	FLOATING cam_dyaw = 0;
	FLOATING tank_boost = 0;
	FLOATING tank_turn = 0;

	if (m_keys[ALLEGRO_KEY_UP]) cam_dy += 1;
	if (m_keys[ALLEGRO_KEY_DOWN]) cam_dy -= 1;
	if (m_keys[ALLEGRO_KEY_LEFT]) cam_dx -= 1;
	if (m_keys[ALLEGRO_KEY_RIGHT]) cam_dx += 1;
	if (m_keys[ALLEGRO_KEY_H]) cam_dyaw += 1;
	if (m_keys[ALLEGRO_KEY_J]) cam_dpitch -= 1;
	if (m_keys[ALLEGRO_KEY_K]) cam_dpitch += 1;
	if (m_keys[ALLEGRO_KEY_L]) cam_dyaw -= 1;
	m_DriveCamera(cam_dx, cam_dy, cam_dpitch, cam_dyaw, dt);

	if (m_keys[ALLEGRO_KEY_A]) tank_turn -= 1;
	if (m_keys[ALLEGRO_KEY_D]) tank_turn += 1;
	if (m_keys[ALLEGRO_KEY_S]) tank_boost -= 1;
	if (m_keys[ALLEGRO_KEY_W]) tank_boost += 1;
	m_DriveTank(tank_boost, tank_turn);

	m_physics_system.Perform(dt);

	return { Transition::State::THIS_STATE };
}

void StateGame::Draw(double weight)
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

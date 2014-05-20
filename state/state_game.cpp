#include "state_game.h"

void StateGame::m_DriveCamera(
        FLOATING dright, FLOATING dfront,
        FLOATING dpitch, FLOATING dyaw,
        double dt)
{
    const FLOATING cam_move_speed = 2.0;
    const FLOATING cam_rotate_speed = 0.125;

    m_drawing_system.CameraRotate(
        dpitch * cam_rotate_speed * dt,
        dyaw * cam_rotate_speed * dt);

    m_drawing_system.CameraWalk(
        dfront * cam_move_speed * dt,
        dright * cam_move_speed * dt);
}

void StateGame::m_DriveTank(FLOATING boost, FLOATING turn)
{
    const FLOATING boost_force = 25;
    FLOATING tank_lfx, tank_lfy, tank_rfx, tank_rfy;

    glm::vec3 rot = m_tank.phys.GetRotationAngles();

    cast_rotated_coords(boost + turn, 0, rot.z, tank_rfx, tank_rfy);
    cast_rotated_coords(boost - turn, 0, rot.z, tank_lfx, tank_lfy);

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
    m_keys(ALLEGRO_KEY_MAX, false),
    m_done { false },
    m_ground { m_physics_system.GetWorld(), m_physics_system.GetSpace() },
    m_tank { m_physics_system.GetWorld(), m_physics_system.GetSpace() }
{
    m_physics_system.AddNode(m_ground.MakePhysicsNode());
    m_drawing_system.AddNode(m_ground.MakeDrawingNode());

    m_physics_system.AddNode(m_tank.MakePhysicsNode());
    m_drawing_system.AddNode(m_tank.MakeDrawingNode());
}

Transition StateGame::Tick(double dt)
{
    FLOATING cam_dright = 0;
    FLOATING cam_dfront = 0;
    FLOATING tank_boost = 0;
    FLOATING tank_turn = 0;

    if (m_keys[ALLEGRO_KEY_UP]) cam_dfront += 1;
    if (m_keys[ALLEGRO_KEY_DOWN]) cam_dfront -= 1;
    if (m_keys[ALLEGRO_KEY_LEFT]) cam_dright -= 1;
    if (m_keys[ALLEGRO_KEY_RIGHT]) cam_dright += 1;
    m_DriveCamera(
        cam_dright, cam_dfront,
        -m_mouse_move.dy, -m_mouse_move.dx,
        dt);

    if (m_keys[ALLEGRO_KEY_A]) tank_turn -= 1;
    if (m_keys[ALLEGRO_KEY_D]) tank_turn += 1;
    if (m_keys[ALLEGRO_KEY_S]) tank_boost -= 1;
    if (m_keys[ALLEGRO_KEY_W]) tank_boost += 1;
    m_DriveTank(tank_boost, tank_turn);

    m_physics_system.Perform(dt);

    m_mouse_move.dx = 0;
    m_mouse_move.dy = 0;

    return m_done
        ? Transition { Transition::State::END }
        : Transition { Transition::State::THIS_STATE };
}

void StateGame::Draw(double weight)
{
    m_drawing_system.Perform(weight);
}

void StateGame::KeyDown(int key)
{
    m_keys[key] = true;
}

void StateGame::KeyUp(int key)
{
    m_keys[key] = false;

    if (key == ALLEGRO_KEY_ESCAPE) {
        m_done = true;
    }
}

void StateGame::MouseMove(int dx, int dy)
{
    m_mouse_move.dx = dx;
    m_mouse_move.dy = dy;
}

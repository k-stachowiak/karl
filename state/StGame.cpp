#include "Config.h"
#include "StGame.h"

namespace state {

void StGame::m_DriveCamera(
        FLOATING dright, FLOATING dfront,
        FLOATING dpitch, FLOATING dyaw,
        double dt)
{
    const FLOATING cam_rotate_speed = 0.125;

    // Update flying camera.
    const FLOATING cam_move_speed = 2.0;
    m_cam_flying.Rotate(
        dpitch * cam_rotate_speed * dt,
        dyaw * cam_rotate_speed * dt);

    m_cam_flying.Walk(
        dfront * cam_move_speed * dt,
        dright * cam_move_speed * dt);

    // Update bound camera.
    m_cam_bound.Rotate(
        dpitch * cam_rotate_speed * dt,
        dyaw * cam_rotate_speed * dt);

    glm::vec3 tank_location = m_tank.phys.GetLocation();
    m_cam_bound.SetLocation(tank_location[0], tank_location[1]);
}

StGame::StGame(res::Resources& resources) :
    m_cam_bound { FLOATING(cfg_view_offset), FLOATING(cfg_view_altitude) },
    m_drawing_system { resources },
    m_ground { m_physics_system.GetWorld(),
               m_physics_system.GetSpace(),
               resources.res_debug_shader->coord_loc,
               resources.res_debug_shader->color_loc },
    m_tank { m_physics_system.GetWorld(),
             m_physics_system.GetSpace(),
             resources.res_debug_shader->coord_loc,
             resources.res_debug_shader->color_loc },
    m_keys(ALLEGRO_KEY_MAX, false),
    m_done { false }
{
    m_drawing_system.SetCamera(&m_cam_bound);

    m_physics_system.RegisterEntity(m_ground);
    m_drawing_system.RegisterDebugEntity(m_ground);

    m_physics_system.RegisterEntity(m_tank);
    m_drawing_system.RegisterDebugEntity(m_tank);
}

StTransition StGame::Tick(double dt)
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
    m_tank.phys.ApplyDriveForces(tank_boost, tank_turn);

    m_physics_system.Perform(dt);

    m_mouse_move.dx = 0;
    m_mouse_move.dy = 0;

    return m_done
        ? StTransition { StTransition::State::END }
        : StTransition { StTransition::State::THIS_STATE };
}

void StGame::Draw(double weight)
{
    m_drawing_system.Perform(weight);
}

void StGame::KeyDown(int key)
{
    m_keys[key] = true;

    switch (key) {
    case ALLEGRO_KEY_ESCAPE:
        m_done = true;
        break;
    case ALLEGRO_KEY_F1:
        m_drawing_system.SetCamera(&m_cam_bound);
        break;
    case ALLEGRO_KEY_F2:
        m_drawing_system.SetCamera(&m_cam_flying);
        break;
    }
}

void StGame::KeyUp(int key)
{
    m_keys[key] = false;
}

bool StGame::MouseMove(int dx, int dy)
{
    m_mouse_move.dx = dx;
    m_mouse_move.dy = dy;
    return true; // reset mouse.
}

}

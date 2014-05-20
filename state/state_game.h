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

    std::vector<bool> m_keys;
    struct { int dx = 0, dy = 0; } m_mouse_move;

    bool m_done;

    EntGround m_ground;
    EntTank m_tank;

    void m_DriveCamera(FLOATING dx, FLOATING dy, FLOATING dpitch, FLOATING dyaw, double dt);
    void m_DriveTank(FLOATING boost, FLOATING turn);

public:
    StateGame(Resources& resources);
    Transition Tick(double dt) override;
    void Draw(double weight) override;
    void KeyDown(int key) override;
    void KeyUp(int key) override;
    void MouseMove(int dx, int dy) override;
};

#endif

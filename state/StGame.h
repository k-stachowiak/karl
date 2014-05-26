#ifndef ST_GAME_H
#define ST_GAME_H

#include <allegro5/allegro.h>

#include "Common.h"
#include "Resources.h"
#include "SysDrawing.h"
#include "SysPhysics.h"
#include "CamFlying.h"
#include "CamBound.h"
#include "Ent.h"
#include "State.h"

namespace state {

class StGame : public State {

    CamFlying m_cam_flying;
    CamBound m_cam_bound;

    sys::Drawing m_drawing_system;
    sys::Physics m_physics_system;

    ent::EntGround m_ground;
    ent::EntTank m_tank;

    std::vector<bool> m_keys;
    struct { int dx = 0, dy = 0; } m_mouse_move;

    bool m_done;

    void m_DriveCamera(FLOATING dx, FLOATING dy, FLOATING dpitch, FLOATING dyaw, double dt);

public:
    StGame(res::Resources& resources);
    StTransition Tick(double dt) override;
    void Draw(double weight) override;
    void KeyDown(int key) override;
    void KeyUp(int key) override;
    bool MouseMove(int dx, int dy) override;
};

}

#endif

#ifndef SYS_DRAWING_H
#define SYS_DRAWING_H

#include <vector>

#include "Common.h"
#include "Resources.h"
#include "CmpPhysics.h"
#include "CmpApprDebug.h"
#include "CmpApprTank.h"
#include "Camera.h"

namespace sys {

struct NdDrawingDebug {
    long id;
    cmp::CmpPhysics *phys;
    cmp::CmpApprDebug *appr;
};

struct NdDrawingTank {
    long id;
    cmp::CmpPhysics *phys;
    cmp::CmpApprTank *appr;
};

class Drawing {

    res::Resources& m_resources;

    Camera* m_camera;

    std::vector<NdDrawingDebug> m_nodes_debug;
    std::vector<NdDrawingTank> m_nodes_tank;

    void m_CameraApply(const res::ResShader &shader, FLOATING weight);

    static void m_FrameBegin();
    static void m_FrameEnd();

    void m_DrawDebugNode(const NdDrawingDebug& node, FLOATING weight);
    void m_DrawTankNode(const NdDrawingTank& node, FLOATING weight);

public:
    Drawing(res::Resources& resources);
    void SetCamera(Camera* camera) { m_camera = camera; }
    void Perform(double weight);

    template <class Entity>
    void RegisterDebugEntity(Entity& entity)
    {
        m_nodes_debug.push_back({
            entity.id,
            &entity.phys,
            &entity.apprd
        });
    }

    template <class Entity>
    void RegisterTankEntity(Entity& entity)
    {
        m_nodes_tank.push_back({
            entity.id,
            &entity.phys,
            &entity.apprt
        });
    }
};

}

#endif

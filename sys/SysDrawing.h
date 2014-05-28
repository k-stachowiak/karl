#ifndef SYS_DRAWING_H
#define SYS_DRAWING_H

#include <vector>

#include "Common.h"
#include "Resources.h"
#include "CmpPhysics.h"
#include "CmpApprDebugInd.h"
#include "CmpApprTankVex.h"
#include "Camera.h"

namespace sys {

struct NdDrawingDebug {
    long id;
    cmp::CmpPhysics *phys;
    cmp::CmpApprDebugInd *appr;
};

struct NdDrawingTank {
    long id;
    cmp::CmpPhysics *phys;
    cmp::CmpApprTankVex *appr;
};

class Drawing {

    res::Resources& m_resources;

    Camera* m_camera;

    std::vector<NdDrawingDebug> m_nodes_debug;
    std::vector<NdDrawingTank> m_nodes_tank;

    void m_CameraApply(const res::ResShader &shader, FLOATING weight);

    static void m_FrameBegin();
    static void m_FrameEnd();

    static void m_ComputeModelMatrix(
            const cmp::CmpPhysics& phys,
            glm::mat4& model,
            FLOATING weight);

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
            &entity.appr
        });
    }

    template <class Entity>
    void RegisterTankEntity(Entity& entity)
    {
        m_nodes_tank.push_back({
            entity.id,
            &entity.phys,
            &entity.appr
        });
    }
};

}

#endif

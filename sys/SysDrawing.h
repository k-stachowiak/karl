#ifndef SYS_DRAWING_H
#define SYS_DRAWING_H

#include <vector>

#include "Common.h"
#include "Resources.h"
#include "CmpPhysics.h"
#include "CmpAppearance.h"
#include "CmpApprDebug.h"
#include "Camera.h"

namespace sys {

struct NdDrawing {
    long id;
    cmp::CmpPhysics *phys;
    cmp::CmpAppearance *appr;
};

struct NdDrawingDebug {
    long id;
    cmp::CmpPhysics *phys;
    cmp::CmpApprDebug *appr;
};

class Drawing {

    res::Resources& m_resources;

    Camera* m_camera;

    std::vector<NdDrawing> m_nodes;
    std::vector<NdDrawingDebug> m_nodes_debug;

    void m_CameraApply(const res::ResShader &shader, FLOATING weight);

    static void m_ShaderBegin(const res::ResShaderDebug &shader);
    static void m_ShaderEnd(const res::ResShaderDebug &shader);

    static void m_FrameBegin();
    static void m_FrameEnd();

    static void m_ComputeModelMatrix(
            const cmp::CmpPhysics& phys,
            glm::mat4& model,
            FLOATING weight);

    static void m_DrawMesh(
            const res::ResShaderDebug &shader,
            const NdDrawing& node,
            FLOATING weight);

    void m_DrawDebugNode(const NdDrawingDebug& node, FLOATING weight);

public:
    Drawing(res::Resources& resources);
    void SetCamera(Camera* camera) { m_camera = camera; }
    void Perform(double weight);

    template <class Entity>
    void RegisterEntity(Entity& entity)
    {
        m_nodes.push_back({
            entity.id,
            &entity.phys,
            &entity.appr
        });
    }

    template <class Entity>
    void RegisterDebugEntity(Entity& entity)
    {
        m_nodes_debug.push_back({
            entity.id,
            &entity.phys,
            &entity.appr
        });
    }
};

}

#endif

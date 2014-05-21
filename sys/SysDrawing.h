#ifndef SYS_DRAWING_H
#define SYS_DRAWING_H

#include <vector>

#include "Common.h"
#include "Resources.h"
#include "CmpPhysics.h"
#include "CmpAppearance.h"
#include "Camera.h"

namespace sys {

struct NdDrawing {
    long id;
    cmp::CmpPhysics *phys;
    cmp::CmpAppearance *appr;
};

class Drawing {

    Resources& m_resources;

    Camera* m_camera;

    std::vector<NdDrawing> m_nodes;

    void m_CameraApply(const Shader &shader, FLOATING weight);

    static void m_ShaderBegin(const Shader &shader);
    static void m_ShaderEnd(const Shader &shader);

    static void m_FrameBegin();
    static void m_FrameEnd();

    static void m_ComputeModelMatrix(const NdDrawing& node, glm::mat4& model, FLOATING weight);
    static void m_DrawMesh(const Shader &shader, const NdDrawing& node, FLOATING weight);

public:
    Drawing(Resources& resources);
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
};

}

#endif

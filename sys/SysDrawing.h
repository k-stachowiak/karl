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

    std::vector<NdDrawing> m_nodes;

    struct Camera {
        glm::vec3 location;
        glm::vec3 prev_location;
        glm::vec3 rotation;
        glm::vec3 prev_rotation;

        glm::mat4 view;
        glm::mat4 projection;

        Camera();

        void Move(FLOATING dx, FLOATING dy);
        void Walk(FLOATING front, FLOATING right);
        void Rotate(FLOATING pitch, FLOATING yaw);

    } m_camera;

    void m_CameraUpdateViewMatrix(FLOATING weight);
    void m_CameraApply(const Shader &shader, FLOATING weight);

    static void m_ShaderBegin(const Shader &shader);
    static void m_ShaderEnd(const Shader &shader);

    static void m_FrameBegin();
    static void m_FrameEnd();

    static void m_ComputeModelMatrix(const NdDrawing& node, glm::mat4& model, FLOATING weight);
    static void m_DrawMesh(const Shader &shader, const NdDrawing& node, FLOATING weight);

public:
    Drawing(Resources& resources);

    void AddNode(const NdDrawing& node) { m_nodes.push_back(node); }

    void CameraMove(FLOATING dx, FLOATING dy);
    void CameraWalk(FLOATING front, FLOATING right);
    void CameraRotate(FLOATING pitch, FLOATING yaw);

    void Perform(double weight);
};

}

#endif

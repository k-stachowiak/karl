#ifndef CMP_PHYSICS_TANK_H
#define CMP_PHYSICS_TANK_H

#include <vector>

#include "Common.h"
#include "CmpPhysics.h"

namespace cmp {

class CmpPhysicsTank : public CmpPhysics {

    struct TriMeshPiece {
        std::vector<glm::vec3> vex;
        std::vector<unsigned> ind;
        OdeTriMeshData tmd;
        OdeGeom geom;
        OdeBody body;
        glm::mat4 prev_transform;

        TriMeshPiece(
            dWorldID world, dSpaceID space,
            FLOATING cx, FLOATING cy, FLOATING cz,
            const std::vector<glm::vec3>& vertexes);

        void StoreTransform();
    };

    TriMeshPiece m_ltrack_piece;
    TriMeshPiece m_rtrack_piece;
    TriMeshPiece m_chassis_piece;

    OdeJoint m_ljoint;
    OdeJoint m_rjoint;

public:
    CmpPhysicsTank(
        dWorldID world, dSpaceID space,
        FLOATING cx, FLOATING cy, FLOATING cz,
        const std::vector<glm::vec3>& ltrack_vertexes,
        const std::vector<glm::vec3>& rtrack_vertexes,
        const std::vector<glm::vec3>& body_vertexes);

    dBodyID GetBody() const override { return m_chassis_piece.body.get(); }

    bool HasTrack(dBodyID body) const override;

    void UpdateFrame() override;

    void ApplyDriveForces(FLOATING boost, FLOATING turn);
};

}

#endif

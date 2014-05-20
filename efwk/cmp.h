#ifndef CMP_H
#define CMP_H

#include <memory>
#include <vector>

#include <ode/ode.h>

#include "auto.h"
#include "common.h"

namespace cmp {

struct Appearance {

    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> colors;

    static Appearance MakeFlat(
        int lx, int ly,
        FLOATING r, FLOATING g, FLOATING b,
        FLOATING (*altitude)(int, int));

    static Appearance MakeBox(
        FLOATING lx, FLOATING ly, FLOATING lz,
        FLOATING r, FLOATING g, FLOATING b);

    static Appearance MakeCar();

    unsigned GetVertexCount() const { return vertexes.size(); }
};

struct Physics {

    glm::vec3 prev_location;
    glm::quat prev_rotation;

    virtual ~Physics() {}

    virtual bool HasBody() const = 0;
    virtual glm::vec3 GetLocation() const = 0;
    virtual glm::quat GetRotation() const = 0;

    virtual bool HasTrack(dBodyID) const { return false; }

    glm::vec3 GetDirection() const;
    glm::vec3 GetRotationAngles() const;
};

struct PhysicsSimple : public Physics {

    OdeBody body;
    OdeGeom geom;

    static PhysicsSimple MakePlane(dSpaceID space);
    static PhysicsSimple MakeBox(
        dWorldID world, dSpaceID space,
        FLOATING mass,
        FLOATING x, FLOATING y, FLOATING z,
        FLOATING lx, FLOATING ly, FLOATING lz);

    bool HasBody() const { return (bool)body; }

    glm::vec3 GetLocation() const
    {
        const FLOATING *pos = dBodyGetPosition(body.get());
        return { pos[0], pos[1], pos[2] };
    }

    glm::quat GetRotation() const
    {
        const FLOATING* q = dBodyGetQuaternion(body.get());
        return { q[0], q[1], q[2], q[3] };
    }
};

struct PhysicsCar : public Physics {

    OdeBody chassis_body;
    OdeGeom chassis_geom;
    OdeBody rtrack_body;
    OdeGeom rtrack_geom;
    OdeBody ltrack_body;
    OdeGeom ltrack_geom;
    OdeJoint rjoint;
    OdeJoint ljoint;

    PhysicsCar(
        dWorldID world, dSpaceID space,
        FLOATING cx, FLOATING cy, FLOATING cz);

    bool HasTrack(dBodyID maybe_track) const;

    bool HasBody() const { return true; }

    glm::vec3 GetLocation() const
    {
        const FLOATING *pos = dBodyGetPosition(chassis_body.get());
        return { pos[0], pos[1], pos[2] };
    }

    glm::quat GetRotation() const
    {
        const FLOATING* q = dBodyGetQuaternion(chassis_body.get());
        return { q[0], q[1], q[2], q[3] };
    }

    dBodyID GetLTrackBody() const { return ltrack_body.get(); }
    dBodyID GetRTrackBody() const { return rtrack_body.get(); }
};

}

#endif

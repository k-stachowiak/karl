#ifndef SYS_PHYSICS_H
#define SYS_PHYSICS_H

#include <vector>

#include <ode/ode.h>

#include "Auto.h"
#include "Common.h"
#include "CmpPhysics.h"

namespace sys {

struct NdPhysics {
    long id;
    cmp::CmpPhysics *phys;
};

class Physics {

    OdeWorld m_world;
    OdeSpace m_space;
    OdeJointGroup m_contact_group;

    std::vector<NdPhysics> m_nodes;

    struct HasTrack {
        dBodyID maybe_track;
        HasTrack(dBodyID new_maybe_track) : maybe_track { new_maybe_track } {}
        bool operator()(const NdPhysics& node)
        {
            return node.phys->HasTrack(maybe_track);
        }
    };

    static void m_ComputeFDir1(
        FLOATING dir_x, FLOATING dir_y,
        FLOATING nor_x, FLOATING nor_y, FLOATING nor_z,
        FLOATING &fdir1_x, FLOATING &fdir1_y, FLOATING &fdir1_z);

    void m_StoreNodesState();

    void m_OnTrackNonTrackContact(
        dBodyID track, struct NdPhysics track_node,
        dBodyID nontrack, dContact &contact);

    void m_OnDefaultContact(dBodyID b1, dBodyID b2, dContact &contact);

public:
    Physics();
    ~Physics();

    // TODO: Remember to remove geoms from space, because the deleters don't do it.

    void OnCollision(dGeomID geom_1, dGeomID geom_2);
    void Perform(double dt);

    template <class Entity>
    void RegisterEntity(Entity& entity)
    {
        m_nodes.push_back({
            entity.id,
            &entity.phys,
        });
    }

    dWorldID GetWorld() const;
    dSpaceID GetSpace() const;
};

}

#endif

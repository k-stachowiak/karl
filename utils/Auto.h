#ifndef AUTO_H
#define AUTO_H

#include <memory>
#include <ode/ode.h>
#include <allegro5/allegro_font.h>

struct OdeWorldDeleter { void operator()(dxWorld *world) { dWorldDestroy(world); } };
struct OdeSpaceDeleter { void operator()(dxSpace *world) { dSpaceDestroy(world); } };
struct OdeBodyDeleter { void operator()(dxBody *body) { dBodyDestroy(body); } };
struct OdeGeomDeleter { void operator()(dxGeom *geom) { dGeomDestroy(geom); } };
struct OdeJointGroupDeleter { void operator()(dxJointGroup *joint_group) { dJointGroupDestroy(joint_group); } };
struct OdeJointDeleter { void operator()(dxJoint *joint) { dJointDestroy(joint); } };
struct OdeTriMeshDataDeleter { void operator()(dxTriMeshData *data) { dGeomTriMeshDataDestroy(data); } };

using OdeWorld = std::unique_ptr<dxWorld, OdeWorldDeleter>;
using OdeSpace = std::unique_ptr<dxSpace, OdeSpaceDeleter>;
using OdeBody = std::unique_ptr<dxBody, OdeBodyDeleter>;
using OdeGeom = std::unique_ptr<dxGeom, OdeGeomDeleter>;
using OdeJointGroup = std::unique_ptr<dxJointGroup, OdeJointGroupDeleter>;
using OdeJoint = std::unique_ptr<dxJoint, OdeJointDeleter>;
using OdeTriMeshData = std::unique_ptr<dxTriMeshData, OdeTriMeshDataDeleter>;

struct AlDisplayDeleter { void operator()(ALLEGRO_DISPLAY *display) { al_destroy_display(display); } };
struct AlEvQueueDeleter { void operator()(ALLEGRO_EVENT_QUEUE *queue) { al_destroy_event_queue(queue); } };
struct AlFontDeleter { void operator()(ALLEGRO_FONT *font) { al_destroy_font(font); } };
struct AlBitmapDeleter { void operator()(ALLEGRO_BITMAP *bitmap) { al_destroy_bitmap(bitmap); } };

using AlDisplay = std::unique_ptr<ALLEGRO_DISPLAY, AlDisplayDeleter>;
using AlEvQueue = std::unique_ptr<ALLEGRO_EVENT_QUEUE, AlEvQueueDeleter>;
using AlFont = std::unique_ptr<ALLEGRO_FONT, AlFontDeleter>;
using AlBitmap = std::unique_ptr<ALLEGRO_BITMAP, AlBitmapDeleter>;

#endif

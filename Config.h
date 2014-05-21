#ifndef CONFIG_H
#define CONFIG_H

#include <string>

extern double cfg_screen_w;
extern double cfg_screen_h;
extern double cfg_fps;

extern double cfg_cam_fovy;
extern double cfg_cam_near;
extern double cfg_cam_far;

extern double cfg_chassis_lx;
extern double cfg_chassis_ly;
extern double cfg_chassis_lz;

extern double cfg_track_lx;
extern double cfg_track_ly;
extern double cfg_track_lz;

extern double cfg_view_altitude;
extern double cfg_view_offset;

extern double cfg_tank_boost_force;
extern double cfg_tank_turn_force;
extern double cfg_tank_dir1_mu;
extern double cfg_tank_dir2_mu;
extern double cfg_tank_max_ang_speed;

void CfgInit();

#endif

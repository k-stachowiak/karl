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

void CfgInit();

#endif

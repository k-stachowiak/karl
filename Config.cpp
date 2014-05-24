#include "Diagnostics.h"
#include "Moon.h"

double cfg_screen_w;
double cfg_screen_h;
double cfg_fps;

double cfg_cam_fovy;
double cfg_cam_near;
double cfg_cam_far;

double cfg_chassis_lx;
double cfg_chassis_ly;
double cfg_chassis_lz;

double cfg_track_lx;
double cfg_track_ly;
double cfg_track_lz;

double cfg_view_altitude;
double cfg_view_offset;

double cfg_tank_boost_force;
double cfg_tank_turn_force;
double cfg_tank_dir1_mu;
double cfg_tank_dir2_mu;
double cfg_tank_max_ang_speed;

namespace {

    double CfgRead(moon::itpr::CInterpreter& itpr, const std::string& symbol)
    {
        moon::itpr::CValue script_value = itpr.GetValue("config", symbol);
        DIAG_ASSERT(IsReal(script_value));
        return script_value.GetReal();
    }

}

void CfgInit()
{
    moon::itpr::CInterpreter itpr;

    try {
        itpr.LoadUnitFile("config.moon");

    } catch(const moon::ExFileNotFound& e) {
        DIAG_ERROR_EXIT("Failed loading configuration file.\n");

    } catch(const moon::ExParsingError& e) {
        DIAG_ERROR_EXIT("Failed parsing config file. Message:\n%s", e.what());
    }

    try {
        cfg_screen_w = CfgRead(itpr, "screen_w");
        cfg_screen_h = CfgRead(itpr, "screen_h");
        cfg_fps =      CfgRead(itpr, "fps");

        cfg_cam_fovy = CfgRead(itpr, "cam_fovy");
        cfg_cam_near = CfgRead(itpr, "cam_near");
        cfg_cam_far =  CfgRead(itpr, "cam_far");

        cfg_chassis_lx = CfgRead(itpr, "chassis_lx");
        cfg_chassis_ly = CfgRead(itpr, "chassis_ly");
        cfg_chassis_lz = CfgRead(itpr, "chassis_lz");

        cfg_track_lx = CfgRead(itpr, "track_lx");
        cfg_track_ly = CfgRead(itpr, "track_ly");
        cfg_track_lz = CfgRead(itpr, "track_lz");

        cfg_view_altitude = CfgRead(itpr, "view_altitude");
        cfg_view_offset =   CfgRead(itpr, "view_offset");

        cfg_tank_boost_force =   CfgRead(itpr, "tank_boost_force");
        cfg_tank_turn_force =    CfgRead(itpr, "tank_turn_force");
        cfg_tank_dir1_mu =       CfgRead(itpr, "tank_dir1_mu");
        cfg_tank_dir2_mu =       CfgRead(itpr, "tank_dir2_mu");
        cfg_tank_max_ang_speed = CfgRead(itpr, "tank_max_ang_speed");

    } catch(const moon::ExInterpretationError& e) {
        DIAG_ERROR_EXIT("Interpreter error. Message:\n%s", e.what());
    }
}

#include "diagnostics.h"
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

double cfg_tank_boost_force;
double cfg_tank_turn_force;
double cfg_tank_dir1_mu;
double cfg_tank_dir2_mu;

namespace {

    void CfgRead(moon::itpr::CInterpreter& itpr,
                 double& value,
                 const std::string& symbol)
    {
        moon::itpr::CValue script_value = itpr.GetValue("config", symbol);
        DIAG_ASSERT(IsReal(script_value));
        value = script_value.GetReal();
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
        CfgRead(itpr, cfg_screen_w, "screen_w");
        CfgRead(itpr, cfg_screen_h, "screen_h");
        CfgRead(itpr, cfg_fps, "fps");

        CfgRead(itpr, cfg_cam_fovy, "cam_fovy");
        CfgRead(itpr, cfg_cam_near, "cam_near");
        CfgRead(itpr, cfg_cam_far, "cam_far");

        CfgRead(itpr, cfg_chassis_lx, "chassis_lx");
        CfgRead(itpr, cfg_chassis_ly, "chassis_ly");
        CfgRead(itpr, cfg_chassis_lz, "chassis_lz");

        CfgRead(itpr, cfg_track_lx, "track_lx");
        CfgRead(itpr, cfg_track_ly, "track_ly");
        CfgRead(itpr, cfg_track_lz, "track_lz");

        CfgRead(itpr, cfg_tank_boost_force, "tank_boost_force");
        CfgRead(itpr, cfg_tank_turn_force, "tank_turn_force");
        CfgRead(itpr, cfg_tank_dir1_mu, "tank_dir1_mu");
        CfgRead(itpr, cfg_tank_dir2_mu, "tank_dir2_mu");

    } catch(const moon::ExInterpretationError& e) {
        DIAG_ERROR_EXIT("Interpreter error. Message:\n%s", e.what());
    }
}

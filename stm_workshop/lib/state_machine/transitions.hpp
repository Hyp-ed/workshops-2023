#pragma once

#include "state.hpp"

#include "../data/data.hpp"

namespace hyped::state_machine {

/* we would normally use data from all other sub-modules here */
using hyped::data::Telemetry;
using hyped::data::Navigation;

class State;  // Forward declaration

//--------------------------------------------------------------------------------------
// Emergency
//--------------------------------------------------------------------------------------

/*
 * @brief   Returns the FailureStopped if there's an emergency and nullptr otherwise.
 */
bool checkEmergency(const data::Navigation &navigation_data, const data::Telemetry &telemetry_data);

//--------------------------------------------------------------------------------------
// Module Status
//--------------------------------------------------------------------------------------

/*
 * @brief    Returns true iff all modules are ready.
 */
bool checkModulesReady(const data::Navigation &navigation_data, const data::Telemetry &telemetry_data);


//--------------------------------------------------------------------------------------
// Telemetry Commands
//--------------------------------------------------------------------------------------

/*
 * @brief   Returns true iff the calibrate command has been received.
 */
bool checkCalibrateCommand(const data::Telemetry &telemetry_data);

/*
 * @brief   Returns true iff the launch command has been received.
 */
bool checkLaunchCommand(const data::Telemetry &telemetry_data);

/*
 * @brief   Returns true iff the shutdown command has been received.
 */
bool checkShutdownCommand(const data::Telemetry &telemetry_data);

//--------------------------------------------------------------------------------------
// Navigation Commands
//--------------------------------------------------------------------------------------

/*
 * @brief   Returns true iff the pod is close enough to the end of the track.
 */
bool checkEnteredBrakingZone(const data::Navigation &navigation_data);

/*
 * @brief   Returns true iff the pod has ???
 */
bool checkPodStopped(const data::Navigation &navigation_data);

}  // namespace hyped::state_machine

#include "state.hpp"

namespace hyped::state_machine {

//--------------------------------------------------------------------------------------
//  General State
//--------------------------------------------------------------------------------------

State::State() : data_(data::Data::getInstance())
{
}

void State::updateModuleData()
{
  nav_data_       = data_.getNavigationData();
  telemetry_data_ = data_.getTelemetryData();
}

//--------------------------------------------------------------------------------------
//  Idle State
//--------------------------------------------------------------------------------------

Idle Idle::instance_;
data::State Idle::enum_value_       = data::State::kIdle;
char Idle::string_representation_[] = "Idle";

State *Idle::checkTransition()
{
  updateModuleData();

  return nullptr;
}


//--------------------------------------------------------------------------------------
//  Calibrating
//--------------------------------------------------------------------------------------

/*
    6. Referring to the other states already implemented, create the Calibrating state.
       Be sure to add relevant transitions TO and FROM this state.
       (the state machine diagram can be handy here)

       *Hint: Do have a close look at the related header file if things don't seem to be working
*/

//--------------------------------------------------------------------------------------
//  Ready
//--------------------------------------------------------------------------------------

Ready Ready::instance_;
data::State Ready::enum_value_       = data::State::kReady;
char Ready::string_representation_[] = "Ready";

State *Ready::checkTransition()
{
  updateModuleData();

  return nullptr;
}

//--------------------------------------------------------------------------------------
//  Accelerating
//--------------------------------------------------------------------------------------

/*
    7. Referring to the other states already implemented, create the Accelerating state.
       Be sure to add relevant transitions TO and FROM this state.
       (the state machine diagram can be handy here)
*/

//--------------------------------------------------------------------------------------
//  Nominal Braking
//--------------------------------------------------------------------------------------

NominalBraking NominalBraking::instance_;
data::State NominalBraking::enum_value_       = data::State::kNominalBraking;
char NominalBraking::string_representation_[] = "NominalBraking";

State *NominalBraking::checkTransition()
{
  updateModuleData();

  bool emergency = checkEmergency(nav_data_, telemetry_data_);
  if (emergency) { return FailureBraking::getInstance(); }

  bool stopped = checkPodStopped(nav_data_);
  if (stopped) { return Finished::getInstance(); }
  return nullptr;
}

//--------------------------------------------------------------------------------------
//  Finished
//--------------------------------------------------------------------------------------

Finished Finished::instance_;
data::State Finished::enum_value_       = data::State::kFinished;
char Finished::string_representation_[] = "Finished";

State *Finished::checkTransition()
{
  // We only need to update telemetry data.
  telemetry_data_ = data_.getTelemetryData();

  bool received_shutdown_command = checkShutdownCommand(telemetry_data_);
  if (received_shutdown_command) { return Off::getInstance(); }
  return nullptr;
}

//--------------------------------------------------------------------------------------
//  FailureBraking
//--------------------------------------------------------------------------------------

FailureBraking FailureBraking::instance_;
data::State FailureBraking::enum_value_       = data::State::kFailureBraking;
char FailureBraking::string_representation_[] = "FailureBraking";

State *FailureBraking::checkTransition()
{
  // We only need to update navigation data.
  nav_data_ = data_.getNavigationData();

  return nullptr;
}

//--------------------------------------------------------------------------------------
//  FailureStopped
//--------------------------------------------------------------------------------------

/*
    8. Referring to the other states already implemented, create the FailureStopped state.
       Be sure to add relevant transitions TO and FROM this state.
       (the state machine diagram can be handy here)
*/

//--------------------------------------------------------------------------------------
//  Off
//--------------------------------------------------------------------------------------

Off Off::instance_;
data::State Off::enum_value_       = data::State::kOff;
State *Off::checkTransition()
{
  return nullptr;
}

}  // namespace hyped::state_machine

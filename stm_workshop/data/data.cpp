#include "data.hpp"

namespace hyped {

// imports
using utils::concurrent::ScopedLock;

namespace data {

static const std::unordered_map<State, std::string> state_names = {
  {State::kIdle, "Idle"},
  {State::kCalibrating, "Calibrating"},
  {State::kReady, "Ready"},
  {State::kAccelerating, "Accelerating"},
  {State::kNominalBraking, "NominalBraking"},
  {State::kFailureBraking, "EmergencyBraking"},
  {State::kFailureStopped, "FailureStopped"},
  {State::kFinished, "Finished"},
  {State::kInvalid, "Invalid"},
};

static const std::unordered_map<std::string, State> states_by_name = {
  {"Idle", State::kIdle},
  {"Calibrating", State::kCalibrating},
  {"Ready", State::kReady},
  {"Accelerating", State::kAccelerating},
  {"NominalBraking", State::kNominalBraking},
  {"EmergencyBraking", State::kFailureBraking},
  {"FailureStopped", State::kFailureStopped},
  {"Finished", State::kFinished},
  {"Invalid", State::kInvalid},
};

std::optional<std::string> stateToString(const State state)
{
  const auto it = state_names.find(state);
  if (it == state_names.end()) { return std::nullopt; }
  return it->second;
}

std::optional<State> stateFromString(const std::string &state_name)
{
  const auto it = states_by_name.find(state_name);
  if (it == states_by_name.end()) { return std::nullopt; }
  return it->second;
}

Data &Data::getInstance()
{
  static Data d;
  return d;
}

Navigation Data::getNavigationData()
{
  ScopedLock L(&lock_navigation_);
  return navigation_;
}

void Data::setNavigationData(const Navigation &nav_data)
{
  ScopedLock L(&lock_navigation_);
  navigation_ = nav_data;
}

StateMachine Data::getStateMachineData()
{
  ScopedLock L(&lock_state_machine_);
  return state_machine_;
}

void Data::setStateMachineData(const StateMachine &sm_data)
{
  ScopedLock L(&lock_state_machine_);
  state_machine_ = sm_data;
}

Telemetry Data::getTelemetryData()
{
  ScopedLock L(&lock_telemetry_);
  return telemetry_;
}

void Data::setTelemetryData(const Telemetry &telemetry_data)
{
  ScopedLock L(&lock_telemetry_);
  telemetry_ = telemetry_data;
}

}  // namespace data
}  // namespace hyped

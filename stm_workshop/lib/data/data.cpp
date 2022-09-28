#include "data.hpp"

namespace hyped::data {

Data &Data::getInstance()
{
  static Data d;
  return d;
}

Navigation Data::getNavigationData()
{
  return navigation_;
}

void Data::setNavigationData(const Navigation &navigation_data)
{
  navigation_ = navigation_data;
}

StateMachine Data::getStateMachineData()
{
  return state_machine_;
}

void Data::setStateMachineData(const StateMachine &state_machine_data)
{
  state_machine_ = state_machine_data;
}

Telemetry Data::getTelemetryData()
{
  return telemetry_;
}

void Data::setTelemetryData(const Telemetry &telemetry_data)
{
  telemetry_ = telemetry_data;
}

}  // namespace hyped::data

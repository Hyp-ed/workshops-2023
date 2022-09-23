#include "data.hpp"

namespace hyped {

namespace data {

Data &Data::getInstance()
{
  static Data d;
  return d;
}

Navigation Data::getNavigationData()
{
  return navigation_;
}

void Data::setNavigationData(const Navigation &nav_data)
{
  navigation_ = nav_data;
}

StateMachine Data::getStateMachineData()
{
  return state_machine_;
}

void Data::setStateMachineData(const StateMachine &sm_data)
{
  state_machine_ = sm_data;
}

Telemetry Data::getTelemetryData()
{
  return telemetry_;
}

void Data::setTelemetryData(const Telemetry &telemetry_data)
{
  telemetry_ = telemetry_data;
}

}  // namespace data
}  // namespace hyped

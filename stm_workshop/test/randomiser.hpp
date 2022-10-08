#pragma once

#include <fcntl.h>
#include <cstdlib>

#include <random>
#include <string>
#include <vector>

#include <gtest/gtest.h>
                    
#include <data/data.hpp>
#include <state_machine/state.hpp>
#include <state_machine/transitions.hpp>

namespace hyped::testing {

//---------------------------------------------------------------------------
// Randomiser
//---------------------------------------------------------------------------

/**
 * Randomises entries in data that are used by various modules to check
 * different conditions and to test state behaviour in different scenarios.
 */
class Randomiser {
 public:
  // Generates a random floating point number in the inverval [0.0, 1.0].
  static data::nav_t randomDecimal()
  {
    static std::default_random_engine generator;
    static std::uniform_real_distribution<data::nav_t> distribution(0.0, 1.0);
    return distribution(generator);
  }

  static data::nav_t randomInRange(const data::nav_t lower, const data::nav_t upper)
  {
    static std::default_random_engine random_engine;
    std::uniform_real_distribution<> distribution(lower, upper);
    return distribution(random_engine);
  }

  // Randomises a module status to any of the possible values.
  static void randomiseModuleStatus(data::ModuleStatus &module_status)
  {
    // Randomises the module status.
    constexpr int num_statuses = 4;
    module_status              = static_cast<data::ModuleStatus>(rand() % num_statuses);
  }

  //---------------------------------------------------------------------------
  // Navigation data
  //---------------------------------------------------------------------------

  // Randomises the entries in a hyped::data::Navigation struct.
  static void randomiseNavigation(data::Navigation &nav_data)
  {
    randomiseModuleStatus(nav_data.module_status);

    // Generates a displacement length between 0 and 100.
    nav_data.displacement = static_cast<data::nav_t>((rand() % 100) + randomDecimal());

    // Generates a velocity length between -10 and 100.
    nav_data.velocity = static_cast<data::nav_t>((rand() % 110 - 10) + randomDecimal());

    // Generates a braking distance length between 10 and 29.
    // Initially declared braking distance = 750
    nav_data.braking_distance = static_cast<data::nav_t>((rand() % 19 + 10) + randomDecimal());
  }

  //---------------------------------------------------------------------------
  // Telemetry data
  //---------------------------------------------------------------------------

  // Randomises the entries in a hyped::data::Telemetry struct.
  static void randomiseTelemetry(data::Telemetry &telemetry_data)
  {
    randomiseModuleStatus(telemetry_data.module_status);

    // Generates a random bool value for all telemetry commands.
    telemetry_data.calibrate_command       = static_cast<bool>(rand() > (RAND_MAX / 2));
    telemetry_data.launch_command          = static_cast<bool>(rand() > (RAND_MAX / 2));
    telemetry_data.shutdown_command        = static_cast<bool>(rand() > (RAND_MAX / 2));
    telemetry_data.emergency_stop_command  = static_cast<bool>(rand() > (RAND_MAX / 2));
    telemetry_data.nominal_braking_command = static_cast<bool>(rand() > (RAND_MAX / 2)); 
  }

  //---------------------------------------------------------------------------
  // State Machine States
  //---------------------------------------------------------------------------

  // Randomises the entries in a hyped::data::StateMachine struct.
  static void randomiseStateMachine(data::StateMachine &stm_data)
  {
    stm_data.critical_failure = static_cast<bool>(rand() > (RAND_MAX / 2));
  }
};
}  // namespace hyped::testing

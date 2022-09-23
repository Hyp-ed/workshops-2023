#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

namespace hyped::data {

// -------------------------------------------------------------------------------------------------
// Global Module States
// -------------------------------------------------------------------------------------------------
enum class ModuleStatus {
  kCriticalFailure,  // state machine transitions to EmergencyBraking/FailureStopped
  kStart,            // Initial module state
  kInit,   // state machine transistions to Calibrating if all modules have Init or Ready status.
  kReady,  // state machine transistions to Ready if all modules have Ready status.
};

struct Module {
  ModuleStatus module_status = ModuleStatus::kStart;
};

// -------------------------------------------------------------------------------------------------
// Navigation
// -------------------------------------------------------------------------------------------------
using nav_t            = float;
struct Navigation : public Module {
  static constexpr nav_t kMaximumVelocity    = 100;        // m/s
  static constexpr nav_t kRunLength          = 1250.0;     // m
  static constexpr nav_t kBrakingBuffer      = 20.0;       // m
  nav_t displacement;                                      // m
  nav_t velocity;                                          // m/s
  nav_t braking_distance = 750;                            // m
};


// -------------------------------------------------------------------------------------------------
// Telemetry data
// -------------------------------------------------------------------------------------------------

struct Telemetry : public Module {
  bool calibrate_command       = false;
  bool launch_command          = false;
  bool shutdown_command        = false;
  bool emergency_stop_command  = false;
  bool nominal_braking_command = true;
};


// -------------------------------------------------------------------------------------------------
// State Machine States
// -------------------------------------------------------------------------------------------------
enum class State {
  kIdle,
  kCalibrating,
  kReady,
  kAccelerating,
  kNominalBraking,
  kFailureBraking,
  kFailureStopped,
  kFinished,
  kInvalid
};

struct StateMachine {
  bool critical_failure;
  State current_state;
};

// -------------------------------------------------------------------------------------------------
// Common Data structure/class
// -------------------------------------------------------------------------------------------------
/**
 * @brief      A singleton class managing the data exchange between sub-team
 * threads.
 */
class Data {
 public:
  /**
   * @brief      Always returns a reference to the only instance of `Data`.
   */
  static Data &getInstance();

  /**
   * @brief      Retrieves data produced by navigation sub-team.
   */
  Navigation getNavigationData();

  /**
   * @brief      Should be called by navigation sub-team whenever they have new data.
   */
  void setNavigationData(const Navigation &nav_data);

  /**
   * @brief      Retrieves data related to the state machine. Data has high priority.
   */
  StateMachine getStateMachineData();

  /**
   * @brief      Should be called by state machine team to update data.
   */
  void setStateMachineData(const StateMachine &sm_data);

  /**
   * @brief      Retrieves data on whether stop/kill power commands have been issued.
   */
  Telemetry getTelemetryData();

  /**
   * @brief      Should be called to update communications data.
   */
  void setTelemetryData(const Telemetry &telemetry_data);

 private:
  StateMachine state_machine_;
  Telemetry telemetry_;
  Navigation navigation_;

  Data() {}

 public:
  Data(const Data &) = delete;
  Data &operator=(const Data &) = delete;
  Data(Data &&)                 = delete;
  Data &operator=(Data &&) = delete;
};

}  // namespace hyped::data

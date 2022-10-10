#include "randomiser.hpp"

#include <random>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <data/data.hpp>

namespace hyped::testing {

class RunTest : public ::testing::Test {
protected:
  static constexpr int kTestSize = 10;

  // ---- Data ----- ------------

  data::Data &data_ = data::Data::getInstance();

  data::Navigation nav_data_;
  data::Telemetry telemetry_data_;
  data::StateMachine stm_data_;

  void randomiseInternally() {
    Randomiser::randomiseNavigation(nav_data_);
    Randomiser::randomiseTelemetry(telemetry_data_);
  }

  /**
   *  This method is used to force the emergency case.
   */
  void forceEmergency() {
    nav_data_.module_status = data::ModuleStatus::kCriticalFailure;
  }

  /**
   *  The updated data is written.
   */
  void writeData() {
    data_.setNavigationData(nav_data_);
    data_.setTelemetryData(telemetry_data_);
    data_.setStateMachineData(stm_data_);
  }

  /**
   *  The written data is read.
   */
  void readData() {
    stm_data_ = data_.getStateMachineData();
    nav_data_ = data_.getNavigationData();
    telemetry_data_ = data_.getTelemetryData();
  }

  // ---- Run steps --------------

  /**
   * Simulating program start up and making sure undesired transitions from Idle
   * are being prevented.
   */
  void initialiseData() {
    readData();

    // Randomise data
    randomiseInternally();

    // Starting with Idle
    stm_data_.current_state = hyped::data::State::kIdle;

    // Prevent Idle -> FailureStopped
    telemetry_data_.emergency_stop_command = false;

    // Prevent Idle -> Calibrating
    nav_data_.module_status = data::ModuleStatus::kStart;
    telemetry_data_.module_status = data::ModuleStatus::kStart;
    telemetry_data_.calibrate_command = false;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_calibrate_command =
        state_machine::checkCalibrateCommand(telemetry_data_);

    ASSERT_EQ(false, has_emergency);
    ASSERT_EQ(false, has_calibrate_command);

    // Let STM do its thing
    writeData();
    readData();
  }

  /**
   * Modifies data such that the Idle -> Calibrating transition conditions
   * are met and verifies the behaviour.
   */

  void testIdleToCalibrating() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, data::State::kIdle);

    // Randomise data
    randomiseInternally();

    state_machine::State *Idle = state_machine::Idle::getInstance();
    state_machine::State *new_state;

    Idle->enter();

    // Prevent Idle -> FailureStopped
    telemetry_data_.emergency_stop_command = false;

    // Enforce Idle -> Calibrating
    telemetry_data_.calibrate_command = true;
    nav_data_.module_status = data::ModuleStatus::kInitialize;
    telemetry_data_.module_status = data::ModuleStatus::kInitialize;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_calibrating_command =
        state_machine::checkCalibrateCommand(telemetry_data_);
    const bool has_modules_ready =
        state_machine::checkModulesReady(nav_data_, telemetry_data_);

    ASSERT_EQ(false, has_emergency);
    ASSERT_EQ(true, has_calibrating_command);
    ASSERT_EQ(false, has_modules_ready);

    // Let STM do its thing
    writeData();
    new_state = Idle->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered failure in Idle";
    ASSERT_EQ(stm_data_.current_state, data::State::kCalibrating)
        << "failed to transition from Idle to Calibrating";
  }

  /**
   * Modifies data such that the Idle -> FailureStopped transition conditions
   * are met and verifies the behaviour.
   */
  void testIdleEmergency() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kIdle);

    // Randomise data
    randomiseInternally();

    state_machine::State *Idle = state_machine::Idle::getInstance();
    state_machine::State *new_state;

    Idle->enter();

    // Enforce Idle -> FailureStopped
    forceEmergency();

    // Prevent FailureStopped -> Off
    telemetry_data_.shutdown_command = false;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_shutdown_command =
        state_machine::checkShutdownCommand(telemetry_data_);

    ASSERT_EQ(true, has_emergency);
    ASSERT_EQ(false, has_shutdown_command);

    // Let STM do its thing
    writeData();
    new_state = Idle->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered failure in Idle";
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kFailureStopped)
        << "failed to transition from Idle to FailureStopped";
  }

  /**
   * Modifies data such that the Calibrating -> Ready transition conditions
   * are met and verifies the behaviour.
   */
  void testCalibratingToReady() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kCalibrating);

    state_machine::State *Calibrating =
        state_machine::Calibrating::getInstance();
    state_machine::State *new_state;

    Calibrating->enter();

    // Randomise data
    randomiseInternally();

    // Prevent Calibrating -> FailureStopped
    telemetry_data_.emergency_stop_command = false;

    // Enforce Calibrating -> Ready
    nav_data_.module_status = data::ModuleStatus::kReady;
    telemetry_data_.module_status = data::ModuleStatus::kReady;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_modules_ready =
        state_machine::checkModulesReady(nav_data_, telemetry_data_);

    ASSERT_EQ(false, has_emergency);
    ASSERT_EQ(true, has_modules_ready);

    // Let STM do its thing
    writeData();
    new_state = Calibrating->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered failure in Calibrating";
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kReady)
        << "failed to transition from Calibrating to Ready";
  }

  /**
   * Modifies data such that the Calibrating -> FailureStopped transition
   * conditions are met and verifies the behaviour.
   */
  void testCalibratingEmergency() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kCalibrating);

    // Randomise data
    randomiseInternally();

    state_machine::State *Calibrating =
        state_machine::Calibrating::getInstance();
    state_machine::State *new_state;

    Calibrating->enter();

    // Enforce Calibrating -> FailureStopped
    forceEmergency();

    // Prevent FailureStopped -> Off
    telemetry_data_.shutdown_command = false;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_shutdown_command =
        state_machine::checkShutdownCommand(telemetry_data_);

    ASSERT_EQ(true, has_emergency);
    ASSERT_EQ(false, has_shutdown_command);

    // Let STM do its thing
    writeData();
    new_state = Calibrating->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered failure in Calibrating";
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kFailureStopped)
        << "failed to transition from Calibrating to FailureStopped";
  }

  /**
   * Modifies data such that the Ready -> Accelerating transition conditions are
   * met and verifies the behaviour.
   */
  void testReadyToAccelerating() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kReady);

    // Randomise data
    randomiseInternally();

    state_machine::State *Ready = state_machine::Ready::getInstance();
    state_machine::State *new_state;

    Ready->enter();

    // Prevent Ready -> FailureStopped
    nav_data_.module_status = data::ModuleStatus::kReady;
    telemetry_data_.module_status = data::ModuleStatus::kReady;
    telemetry_data_.emergency_stop_command = false;

    // Enforce Ready -> Accelerating
    telemetry_data_.launch_command = true;

    // Prevent Accelerating -> NominalBraking
    nav_data_.displacement = 0;
    nav_data_.braking_distance = 0;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_launch_command =
        state_machine::checkLaunchCommand(telemetry_data_);
    const bool has_entered_braking_zone =
        state_machine::checkEnteredBrakingZone(nav_data_);

    ASSERT_EQ(false, has_emergency);
    ASSERT_EQ(true, has_launch_command);
    ASSERT_EQ(false, has_entered_braking_zone);

    // Let STM do its thing
    writeData();
    new_state = Ready->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered failure in Ready";
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kAccelerating)
        << "failed to transition from Ready to Accelerating";
  }

  /**
   * Modifies data such that the Ready -> FailureStopped transition conditions
   * are met and verifies the behaviour.
   */
  void testReadyEmergency() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kReady);

    // Randomise data
    randomiseInternally();

    state_machine::State *Ready = state_machine::Ready::getInstance();
    state_machine::State *new_state;

    Ready->enter();

    // Enforce Ready -> FailureStopped
    forceEmergency();

    // Prevent FailureStopped -> Off
    telemetry_data_.shutdown_command = false;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_shutdown_command =
        state_machine::checkShutdownCommand(telemetry_data_);

    ASSERT_EQ(true, has_emergency);
    ASSERT_EQ(false, has_shutdown_command);

    // Let STM do its thing
    writeData();
    new_state = Ready->checkTransition();
    new_state->enter();
    readData();

    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered critical failure in Ready";
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kFailureStopped)
        << "failed to transition from Ready to FailureStopped";
  }

  /**
   * Modifies data such that the Accelerating -> NominalBraking transition
   * conditions are met and verifies the behaviour.
   */
  void testAcceleratingToNominalBraking() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kAccelerating);

    // Randomise data
    randomiseInternally();

    state_machine::State *Accelerating =
        state_machine::Accelerating::getInstance();
    state_machine::State *new_state;

    Accelerating->enter();

    // Prevent Accelerating -> FailureBraking
    nav_data_.module_status = data::ModuleStatus::kReady;
    telemetry_data_.module_status = data::ModuleStatus::kReady;
    telemetry_data_.emergency_stop_command = false;

    // Prevent Accelerating -> Finished
    nav_data_.velocity = 100;

    // Enforce PreBraking -> NominalBraking
    nav_data_.braking_distance = 1000;
    nav_data_.displacement =
        data::Navigation::kRunLength - nav_data_.braking_distance;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_entered_braking_zone =
        state_machine::checkEnteredBrakingZone(nav_data_);
    const bool has_stopped = state_machine::checkPodStopped(nav_data_);

    ASSERT_EQ(false, has_emergency);
    ASSERT_EQ(true, has_entered_braking_zone);
    ASSERT_EQ(false, has_stopped);

    // Let STM do its thing
    writeData();
    new_state = Accelerating->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered failure in Accelerating";
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kNominalBraking)
        << "failed to transition from Accelerating to NominalBraking";
  }

  /**
   * Modifies data_ such that the Accelerating -> FailurePreBraking transition
   * conditions are met and verifies the behaviour.
   */
  void testAcceleratingEmergency() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kAccelerating);

    // Randomise data
    randomiseInternally();

    state_machine::State *Accelerating =
        state_machine::Accelerating::getInstance();
    state_machine::State *new_state;

    Accelerating->enter();

    // Enforce Accelerating -> FailurePreBraking
    forceEmergency();

    // Prevent FailurePreBraking -> FailureStopped
    nav_data_.velocity = 100;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_stopped = state_machine::checkPodStopped(nav_data_);

    ASSERT_EQ(true, has_emergency);
    ASSERT_EQ(false, has_stopped);

    // Let STM do its thing
    writeData();
    new_state = Accelerating->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered failure in Accelerating";
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kFailureBraking)
        << "failed to transition from Accelerating to FailureBraking";
  }

  /**
   * Modifies data such that the NominalBraking -> Finished transition
   * conditions are met and verifies the behaviour.
   */
  void testNominalBrakingToFinished() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kNominalBraking);

    // Randomise data
    randomiseInternally();

    state_machine::State *NominalBraking =
        state_machine::NominalBraking::getInstance();
    state_machine::State *new_state;

    NominalBraking->enter();

    // Prevent NominalBraking -> FailureBraking
    nav_data_.module_status = data::ModuleStatus::kReady;
    telemetry_data_.module_status = data::ModuleStatus::kReady;
    telemetry_data_.emergency_stop_command = false;

    // Enforce NominalBraking -> Finished
    nav_data_.velocity = 0;

    // Prevent Finished -> Off
    telemetry_data_.shutdown_command = false;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_stopped = state_machine::checkPodStopped(nav_data_);
    const bool has_shutdown_command =
        state_machine::checkShutdownCommand(telemetry_data_);

    ASSERT_EQ(false, has_emergency);
    ASSERT_EQ(true, has_stopped);
    ASSERT_EQ(false, has_shutdown_command);

    // Let STM do its thing
    writeData();
    new_state = NominalBraking->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered failure in NominalBraking";
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kFinished)
        << "failed to transition from NominalBraking to Finished";
  }

  /**
   * Modifies data such that the NominalBraking -> FailureBraking transition
   * conditions are met and verifies the behaviour.
   */
  void testNominalBrakingEmergency() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kNominalBraking);

    // Randomise data
    randomiseInternally();

    // Enforce NominalBraking -> FailureBraking
    forceEmergency();

    state_machine::State *NominalBraking =
        state_machine::NominalBraking::getInstance();
    state_machine::State *new_state;

    NominalBraking->enter();

    // Prevent FailureBraking -> FailureStopped
    nav_data_.velocity = 100;

    // Verify transition conditions are as intended
    const bool has_emergency =
        state_machine::checkEmergency(nav_data_, telemetry_data_);
    const bool has_stopped = state_machine::checkPodStopped(nav_data_);

    ASSERT_EQ(true, has_emergency);
    ASSERT_EQ(false, has_stopped);

    // Let STM do its thing
    writeData();
    new_state = NominalBraking->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.critical_failure, false)
        << "encountered failure in NominalBraking";
    ASSERT_EQ(stm_data_.current_state, data::State::kFailureBraking)
        << "failed to transition from NominalBraking to EmergencyBraking";
  }

  /**
   * Modifies data such that the Finished -> Off transition conditions are met
   * and verifies the behaviour.
   */
  void testFinishedToOff() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kFinished);

    // Randomise data
    randomiseInternally();

    state_machine::State *Finished = state_machine::Finished::getInstance();
    state_machine::State *new_state;

    Finished->enter();

    // Enforce Finished -> Off
    telemetry_data_.shutdown_command = true;

    // Verify transition conditions are as intended
    const bool has_shutdown_command =
        state_machine::checkShutdownCommand(telemetry_data_);

    ASSERT_EQ(true, has_shutdown_command);

    // Let STM do its thing
    writeData();
    new_state = Finished->checkTransition();
    new_state->enter();
    readData();

    ASSERT_EQ(stm_data_.current_state, data::State::kOff)
        << "failed to transition from Finished to Off";
  }

  /**
   * Modifies data such that the FailureBraking -> FailureStopped transition
   * conditions are met and verifies the behaviour.
   */
  void testFailureBrakingToFailureStopped() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kFailureBraking);

    // Randomise data
    randomiseInternally();

    state_machine::State *FailureBraking =
        state_machine::FailureBraking::getInstance();
    state_machine::State *new_state;

    FailureBraking->enter();

    // Enforce FailureBraking -> FailureStopped
    nav_data_.velocity = 0;

    // Prevent FailureStopped -> Off
    telemetry_data_.shutdown_command = false;

    // Verify transition conditions are as intended
    const bool has_stopped = state_machine::checkPodStopped(nav_data_);
    const bool has_shutdown_command =
        state_machine::checkShutdownCommand(telemetry_data_);

    ASSERT_EQ(true, has_stopped);
    ASSERT_EQ(false, has_shutdown_command);

    // Let STM do its thing
    writeData();
    new_state = FailureBraking->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kFailureStopped)
        << "failed to transition from FailureBraking to FailureStopped";
  }

  /**
   * Modifies data such that the FailureStopped -> Off transition conditions are
   * met and verifies the behaviour.
   */
  void testFailureStoppedToOff() {
    // Check initial state
    readData();
    ASSERT_EQ(stm_data_.current_state, hyped::data::State::kFailureStopped);

    // Randomise data
    randomiseInternally();

    state_machine::State *FailureStopped =
        state_machine::FailureStopped::getInstance();
    state_machine::State *new_state;

    FailureStopped->enter();

    // Enforce FailureStopped -> Off
    telemetry_data_.shutdown_command = true;

    // Verify transition conditions are as intended
    const bool has_shutdown_command =
        state_machine::checkShutdownCommand(telemetry_data_);

    ASSERT_EQ(true, has_shutdown_command);

    // Let STM do its thing
    writeData();
    new_state = FailureStopped->checkTransition();
    new_state->enter();
    readData();

    // Check result
    ASSERT_EQ(stm_data_.current_state, data::State::kOff)
        << "failed to transition from FailureStopped to Off";
  }
}; // namespace hyped::testing

/**
 * Verifies the nominal run behaviour without any emergencies.
 */
TEST_F(RunTest, nominalRun) {
  for (std::size_t i = 0; i < kTestSize; ++i) {

    initialiseData();

    testIdleToCalibrating();
    testCalibratingToReady();
    testReadyToAccelerating();
    testAcceleratingToNominalBraking();
    testNominalBrakingToFinished();
    testFinishedToOff();
  }
}

/**
 * Verifies the state machine behaviour upon encountering an emergency in
 Idle.
 */
TEST_F(RunTest, idleEmergency) {
  for (std::size_t i = 0; i < kTestSize; ++i) {
    initialiseData();

    testIdleEmergency();
    testFailureStoppedToOff();
  }
}

/**
 * Verifies the state machine behaviour upon encountering an emergency in
 * Calibrating.
 */
TEST_F(RunTest, calibratingEmergency) {
  for (std::size_t i = 0; i < kTestSize; ++i) {

    initialiseData();

    testIdleToCalibrating();
    testCalibratingEmergency();
    testFailureStoppedToOff();
  }
}

/**
 * Verifies the state machine behaviour upon encountering an emergency in
 Ready.
 */
TEST_F(RunTest, readyEmergency) {
  for (std::size_t i = 0; i < kTestSize; ++i) {
    initialiseData();

    testIdleToCalibrating();
    testCalibratingToReady();
    testReadyEmergency();
    testFailureStoppedToOff();
  }
}

/**
 * Verifies the state machine behaviour upon encountering an emergency in
 * Accelerating.
 */
TEST_F(RunTest, acceleratingEmergency) {
  for (std::size_t i = 0; i < kTestSize; ++i) {
    initialiseData();

    testIdleToCalibrating();
    testCalibratingToReady();
    testReadyToAccelerating();
    testAcceleratingEmergency();
    testFailureBrakingToFailureStopped();
    testFailureStoppedToOff();
  }
}

/**
 * Verifies the state machine behaviour upon encountering an emergency in
 * Braking.
 */
TEST_F(RunTest, brakingEmergency) {
  for (size_t i = 0; i < kTestSize; ++i) {
    initialiseData();

    testIdleToCalibrating();
    testCalibratingToReady();
    testReadyToAccelerating();
    testAcceleratingToNominalBraking();
    testNominalBrakingEmergency();
    testFailureBrakingToFailureStopped();
    testFailureStoppedToOff();
  }
}

} // namespace hyped::testing

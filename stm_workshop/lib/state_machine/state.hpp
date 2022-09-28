#pragma once

#include "transitions.hpp"

#include <string>

#include <data/data.hpp>
#include <utils/timer.hpp>

namespace hyped::state_machine {

class State {
 public:
  State();
  static State *getInstance();

  virtual void enter() = 0;
  virtual void exit()  = 0;

  virtual State *checkTransition() = 0;

  data::Data &data_;

 protected:
  /* we usually make sure of every sub-module here*/
  data::Navigation nav_data_;
  data::Telemetry telemetry_data_;
  void updateModuleData();
};

/*
 * @brief   Generates a specific state S following the pattern of State.
 */
#define MAKE_STATE(S)                                                                              \
  class S : public State {                                                                         \
   public:                                                                                         \
    S() {}                                                                                         \
    static S *getInstance() { return &S::instance_; }                                              \
                                                                                                   \
    State *checkTransition();                                                                      \
    /* @brief   Prints log message and sets appropriate public enum value.*/                       \
    void enter()                                                                                   \
    {                                                                                              \
      /* generally a good idea to log the state we have entered*/                                  \
      data::StateMachine sm_data = data_.getStateMachineData();                                    \
      sm_data.current_state      = S::enum_value_;                                                 \
      data_.setStateMachineData(sm_data);                                                          \
    }                                                                                              \
    void exit() { }                                                                                \
                                                                                                   \
   private:                                                                                        \
    static S instance_;                                                                            \
    /* # converts an argument to a string literal*/                                                \
    static char string_representation_[];                                                          \
    static data::State enum_value_;                                                                \
  };

/*
 * Generating structs for all the states (a condensed version)
 */

MAKE_STATE(Idle)               // State on startup
MAKE_STATE(Ready)              // Entered after high power is on  


MAKE_STATE(NominalBraking)     // Second phase of the run
MAKE_STATE(Finished)           // State after the run
MAKE_STATE(FailureBraking)     // Entered upon failure during the run   

MAKE_STATE(Off)                // Entered after the pod has finished its run

#undef MAKE_STATE

}  // namespace hyped::state_machine

#include "main.hpp"

#include <cstdint>

namespace hyped::state_machine {

Main::Main()
    : utils::concurrent::Thread()
{
  current_state_ = Idle::getInstance();
}

void Main::run()
{
  utils::System &sys = utils::System::getSystem();
  data::Data &data   = data::Data::getInstance();

  current_state_->enter();

  State *new_state;
  while (sys.isRunning()) {
    // checkTransition returns a new state or nullptr
    if ((new_state = current_state_->checkTransition())) {
      current_state_->exit();
      current_state_ = new_state;
      current_state_->enter();
    }

    // Yielding because running the loop twice without any other thread being active
    // will result in identical behaviour and thus waste resources.
    yield();
  }

  data::StateMachine sm_data = data.getStateMachineData();
  const auto state_string    = ::hyped::data::stateToString(sm_data.current_state);
  /* would be nice to log which state we exited from, right? */
}

}  // namespace hyped::state_machine

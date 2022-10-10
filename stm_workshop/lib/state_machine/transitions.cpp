#include "transitions.hpp"
namespace hyped::state_machine {

//--------------------------------------------------------------------------------------
// Emergency
//--------------------------------------------------------------------------------------

/*
 * @brief   Local function that determines whether or not there is an emergency.
 */
bool checkEmergency(const data::Navigation &nav_data, \
                    const data::Telemetry &telemetry_data)
{
  /* Note: usually for each case we would add a relevant log message to know which module
     had an emergency */

  /*
     1. One of the most important things to consider for state machine is dealing with
        emergencies. These could occur in any sub-module, but for the sake of this workshop,
        you will only deal with the Navigation and Telemetry module.

        Any module can enter the kCriticalFailure module status once it experiences an emergency.
        For Telemetry specifically, it can also throw the emergency stop command to get the pod
        to stop manually. Please refer to data.hpp to get a better idea.

        Your job would be to implement the checkEmergency method which checks for any module
        throwing the kCriticalFailure flag or whether Telemetry gave the emergency stop command.
        This should return True if an emergency has occured, false otherwise.
  */

   if (nav_data.module_status == data::ModuleStatus::kCriticalFailure || 
   telemetry_data.module_status == data::ModuleStatus::kCriticalFailure || 
   telemetry_data.nominal_braking_command == true) {
      return true;
   } else {
      return false;
   }
}

//--------------------------------------------------------------------------------------
// Module Status
//--------------------------------------------------------------------------------------

/* In our actual system, we would first check if every sub-module has initilized
   before moving on */

bool checkModulesReady(const data::Navigation &nav_data, \
                    const data::Telemetry &telemetry_data)
{
  /*
    2. For this method, ensure that the sub-modules considered are ready. Again, if a module is
       ready then it would throw the kReady flag for its module status. If this is the case for all
       modules considered then return True.
   */
  
   if (nav_data.module_status == data::ModuleStatus::kReady &&
      telemetry_data.module_status == data::ModuleStatus::kReady
   ) {
      return true;
   } else {
      return false;
   }

}

//--------------------------------------------------------------------------------------
// Telemetry Commands
//--------------------------------------------------------------------------------------

/*
   3. From the Telemetry module, we get commands such as the calibrate command, launch command
      and the shutdown command.

      Your job here is to create methods that will check if these commands were received and return
      True if that is the case. Refer to data.hpp for the relevant boolean variables.
*/
bool checkCalibrateCommand(const data::Telemetry &telemetry_data) {
   if (telemetry_data.calibrate_command == true) {
      return true;
   } else {
      return false;
   }
}

bool checkLaunchCommand(const data::Telemetry &telemetry_data) {
   if (telemetry_data.launch_command == true) {
      return true;
   } else {
      return false;
   }
}

bool checkShutdownCommand(const data::Telemetry &telemetry_data) {
   if (telemetry_data.shutdown_command == true) {
      return true;
   } else {
      return false;
   }
}

/*
bool checkEmergencyStop(const data::Telemetry &telemetry_data) {
   if (telemetry_data.emergency_stop_command == true) {
      return true;
   } else {
      return false;
   }
}

bool checkNominalBraking(const data::Telemetry &telemetry_data) {
   if (telemetry_data.nominal_braking_command == true) {
      return true;
   } else {
      return false;
   }
}
*/

//--------------------------------------------------------------------------------------
// Navigation Data Events
//--------------------------------------------------------------------------------------

bool checkEnteredBrakingZone(const data::Navigation &nav_data)
{
  /*
    4. Now, we need to know when the pod has entered the braking zone for us to then engage
       our brakes.

       The way we check is to deduct the distance travelled by the pod from the total
       run length to get the remaining distance left to travel. Then, we get the required distance
       to brake by adding the braking distance to a braking buffer (Once again, refer to data.hpp).

       Lastly, if the required distance to brake exceeds the remaining distance left to travel,
       return True.
  */
   if (nav_data.kRunLength - nav_data.displacement <= nav_data.braking_distance + nav_data.kBrakingBuffer) {
      return true;
   } else {
      return false;
   }
}

bool checkPodStopped(const data::Navigation &nav_data)
{
  /*
    5. Lastly, by looking at the Navigation struct in data.hpp, determine when the pod has stopped
       and return True if that is the case.
  */
   if (nav_data.velocity > 0.0) {
      return false;
   } else {
      return true;
   }
}

}  // namespace hyped::state_machine

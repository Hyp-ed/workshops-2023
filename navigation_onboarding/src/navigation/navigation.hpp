#include <stdint.h>
#include <array>

namespace navigation{

  class Navigation
  {
  public:
  
  //class constructor
  Navigation();

  /**
   * @brief get keyence data from sensors and update data held in
   * private class member
   * 
   * note this is not how it would work in reality but illustated the sort of function
   * that may be used to process sensors data
   */
  void processKeyence();

  /**
   * @brief get wheel encoder data from sensors and update data held in
   * private class member
   * 
   * note this is not how it would work in reality but illustated the sort of function
   * that may be used to process sensors data
   */
  void processEncoders();

  /**
   * @brief compares the displacement values from keyence and encoders.
   * Sets the fail state flag to true if fail state conditions are met.
   * 
   */
  void compareKeyenceEncoders();

  /**
   * @brief detects outliers in array. Any value deemed an outlier will be set to 
   * the median value of the array
   * 
   * @param encoder_data array of current wheel encoder data
   * @return uint32_t* array of wheel encoder data with outliers set to the median
   */
  void encodersOutlierDetection();

  /**
   * @brief checks if the 2 keyence sensors agree with each other
   * 
   * @param keyence_data keyence sensor data
   */
  void doesKeyenceAgree();

  /**
   * @brief main navigation function. In reality we would have functions to 
   * get data from sensors but I just made some up for the purposes of demonstration
   * in this function
   * 
   */
  bool navigate();

  //current wheel encoder estimate for displacemnt
  uint32_t displacement_ = 0;

  //fail state flag. Would normally be written to state machine and actioned ASAP!
  bool fail_state_ = false;

  private:
    
  //keyence value for displacment. Here used as the ground truth value
  uint32_t ground_truth_displacement_ = 0;

  //number of keyence sensors
  static constexpr uint8_t kNumKeyenceSensors=2;

  //number of wheel encoders
  static constexpr uint8_t kNumEncoders=4;

  //length of track
  static constexpr uint32_t kTrackLength = 200;//meters

  //required breaking distance
  static constexpr uint32_t kBreakingDistance = 50;//meters

  static constexpr uint32_t kBreakingPoint = kTrackLength - kBreakingDistance;

  //wheel encoder data
  std::array<uint32_t, 4> encoders_data_ = {0,0,0,0};
  //uint32_t encoders_data_[4] = {0, 0, 0, 0};

  //keyence data
  std::array<uint32_t, 2> keyence_data_ = {0, 0};
  //uint32_t keyence_data_[2] = {0, 0};

  //boolean mask of reliable wheel encoders
  std::array<bool, 4> reliable_encoders_ = {true, true, true, true};
  //bool reliable_encoders_[4] = {true, true, true, true};
 };
  
}
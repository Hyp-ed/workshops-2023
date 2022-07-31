#include "navigation.hpp"
#include <algorithm>

namespace navigation{

  Navigation::Navigation(){}

  void Navigation::doesKeyenceAgree(){
    //implement a function to check if they are equal. make fail state true if so.
    //data will be found in the header file in an array called keyence_data
  }

  void Navigation::encodersOutlierDetection(){
    //this function is written badly. try to improve it (hint: look @ style guide!!)
    uint16_t encoder_copy[4];
    for(int i = 0; i < 4; i++){
      encoder_copy[i] = encoders_data_[i];
    } 

    std::sort(encoder_copy, encoder_copy+4);
    float q1 = (encoder_copy[0] + encoder_copy[1])/2;
    float median = (encoder_copy[1] + encoder_copy[2])/2;
    
    float q3 = (encoder_copy[2] + encoder_copy[3])/2;

    float iqr = q3-q1;

    float upper_limit = q3 + (1.5*iqr);
    float lower_limit = q1 - (1.5*iqr);

    for(int i = 0; i < 4; i++){
      if(encoders_data_[i] > upper_limit){
        encoders_data_[i] = median;
      }

      if(encoders_data_[i] < lower_limit){
        encoders_data_[i] = median;
      }
    }
  }

  void Navigation::processEncoders(){
    //usually some function that gets the encoders data from sensors, this is fake data!
    uint32_t new_encoders_data[4] = {2, 2, 1, 3};
    for(size_t i = 0; i < kNumEncoders; ++i){
      encoders_data_[i] = new_encoders_data[i];
    }
  }

  void Navigation::processKeyence(){
    //also usually fetched from sensors somewhere, data here is fake!
    uint32_t new_keyence_data[2] = {1, 1};
    for(size_t i = 0; i < kNumKeyenceSensors; ++i){
      keyence_data_[i] = new_keyence_data[i];
    }
  }

  void Navigation::compareKeyenceEncoders(){
    const int32_t deviance = ground_truth_displacement_ - displacement_;
    if(std::abs(deviance) > 10){
      fail_state_ = true;
    }
  }

  bool Navigation::navigate(){
    processEncoders();
    encodersOutlierDetection();

    processKeyence();
    doesKeyenceAgree();

    compareKeyenceEncoders();

    if(displacement_ >= kBreakingPoint){
      return false;
    }else if(fail_state_ == true){
      return false;
    }else{
      return true;
    }
  }

}//namespace navigation
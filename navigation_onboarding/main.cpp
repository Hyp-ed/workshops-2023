#include "main.hpp"

bool doNavigation(){
  navigation::Navigation nav;
  bool stop_yet = nav.navigate();
  return stop_yet;
}

int main(){
  //navigation getting called from central logic to estimate our position
  if(doNavigation() == true){
    braking_state = true;
  }
  return 0;
}
#include "../lib/navigation.hpp"

bool braking_state = false;

void changeBrakingState(){
  if(braking_state){braking_state = false;}
  if(!braking_state){braking_state = true;}
}

bool doNavigation(){
  navigation::Navigation nav;
  bool stop_yet = nav.navigate();
  return stop_yet;
}

// will send a signal somewhere for us to brake
void brake(){
}

int main(){
  //navigation getting called from central logic to estimate our position
  if(doNavigation()){braking_state = true;}
  return 0;
}
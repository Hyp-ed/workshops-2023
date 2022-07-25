# Navigation onboarding

Welcome to navigation! Here is a quick few tasks to help get you familiar with both c++ as well as what sort of problems you may encoounter.

- Go to the navigation.cpp file and fill in the doesKeyenceAgree function. It should read the keyence data from navigation.hpp and check if the 2 values in the array are equal. Set the fail_state flag to true if they disagree.

- Go the the encodersOutlierDetection function below the doesKeyenceAgree function. It is written very badly. Use the style guide and other code you may come across in the repository to make this fuction better.

- Extension: Once you have fixed the encodersOutlierDetection function, make it adaptable so that if one of the wheel encoders are unreliable (have a "false" value in the relaible_encoders array) then we could still run outlier detection.
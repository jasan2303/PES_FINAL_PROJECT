# PES_FINAL_PROJECT
DRONE_STABALIZER_PROJECT

The device helps balance the drone using the MMA8451Q digital accelerometer present on the MKL25z4 device. The device works on the basic principle of detecting the tilt angles of 
the accelerometer by calculating the ROLL and PITCH angle values, concerning a particular calibrated value and generating the respective signals to compensate for the tilt.
The tilt angles measured with the help of the roll and pitch axis of the accelerometer helps in controlling the strengths of the PWM signals, which regulate the speed of the 
drone's rotors which in turn helps in balancing the drone. HEre the PWM signals strength are shown using the on-board LEDs as
             
              Roll angle right             - Blue LED
              Roll angle left              - RED LED
              Pitch angle Front            - Light Green LED
              Pitch angle towards/backward - White Color(ALL the 3 LEDs are ON)
              
 The project also has the calibration functionality to calibrate the sensor before using the module, a push button is configured at **GPIO PORT D7** with interrupt enabled. The 
 module needs to be placed on still flat surface and press the push button for accurate reading of acceleration values.
 
 
 The calibrate.c module has two types of calibration methods implemented **acc_calibration()** and **accurate_callibration()**
 
      1. **acc_calibration** uses the simple offset method mentioned in AN4069. 
      2. **accurate_calibration** uses the more accurate method of calibration mentioned in AN4069, which
           takes acceleration values from all the 6 faces of the accelerometer and calibrates for both
           sensitivity and offset.
 
 The project by default has simple offset calibration active, to use the more accurate calibration option user needs to uncomment the "accurate_calibration()" function
 call in Drone_Stabilizer.c (main()) file of the project.
 
 While using the more accurate method of callibration, after the push button is pressed the must be placed in all six position so that all the accelerration of the six faces is 
 captured and the offset are calculated.
 
 The ROLL and PITCH are Logged through UART on the serial monitor. The float operations while calculating the ROLL and PITCH angles are avoided as the board does not have the 
 seperate hardware for it, therby optimizing the functionality.
 
 The module can be used to stabalize the drone flight by compensating for Roll and pitch angles by driving the rotors of the drone using the PWM signals used to drive the LED
 in the project. 
              
Calibration Demo video link: https://drive.google.com/file/d/1Bd5fQe0omt4NEiHL5SJzgTUQuCqNPjci/view?usp=drivesdk

Working Demo Link: https://drive.google.com/file/d/1Bjwcer4iBAL3y5geD6kVTXvrYbi5gCNA/view?usp=drivesdk

Project Proposal file with references is also uploaded.

Thank you


#include "calibration.h"
#include "stepper_controller.cpp"
#include "stepper_controller.h"


void setup() {


  uint16_t numMicroSteps= 1;
  bool enableFeedback = true;
  bool TC5_ISR_Enabled = true;
 {
 int32_t x,i,j;
  uint32_t angle=0;
  int32_t steps;
  bool done=false;

  int32_t mean;
  uint16_t microSteps=numMicroSteps;
  bool feedback=enableFeedback;
  bool state=TC5_ISR_Enabled;

  disableTCInterrupts();

  enableFeedback=false;
  numMicroSteps=1;
  LOG("reset motor");
//  motorReset();
  LOG("Starting calibration");
  steps=0;

  LOG("Starting calibration");
  j=0;
  while(!done)
  {
    Angle cal,desiredAngle;
    desiredAngle=(uint16_t)(getDesiredLocation() & 0x0FFFFLL);
    cal=calTable.getCal(desiredAngle);
    mean=measureMeanEncoder();

    LOG("Previous cal distance %d, %d, mean %d, cal %d",j, cal-Angle((uint16_t)mean), mean, (uint16_t)cal);

    calTable.updateTableValue(j,mean);
    updateStep(0,1);
    //steps=steps+A4954_NUM_MICROSTEPS;
    //stepperDriver.move(steps,NVM->SystemParams.currentMa);  //JUST TO COMPILE
    j++;
    if (j>=CALIBRATION_TABLE_SIZE)
    {
      done=true;
    }


  }
  calTable.saveToFlash(); //saves the calibration to flash
  calTable.printCalTable();

  numMicroSteps=microSteps;
  motorReset();
  enableFeedback=feedback;
  if (state) enableTCInterrupts();
  return done;
}

}

void loop() {
  // put your main code here, to run repeatedly:

}

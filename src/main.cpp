/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Sridaran                                         */
/*    Created:      Sat Jun 15 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "header.h"

void drive();
void helloWorld();

int main()
{
  drive();    
}

void drive()
{
  LIFT_BUTTON->pressed([] ()
  {
    liftMotor.spin(directionType::fwd, 80.0, percentUnits::pct);
  });

  LIFT_BUTTON->released([] ()
  {
    liftMotor.stop();
  });

  CLAMP_BUTTON->pressed([] ()
  {
    clampMotor.spin(directionType::fwd, 80.0, percentUnits::pct);
  });

  CLAMP_BUTTON->released([] ()
  {
    clampMotor.stop();
  });

  while (1)
  {
    rightMotorF.spin(directionType::fwd, (VERTICAL_AXIS->value() - HORIZONTAL_AXIS->value()), velocityUnits::pct);
		leftMotorF.spin(directionType::fwd, (VERTICAL_AXIS->value() + HORIZONTAL_AXIS->value()), velocityUnits::pct);
		rightMotorB.spin(directionType::fwd, (VERTICAL_AXIS->value() - HORIZONTAL_AXIS->value()), velocityUnits::pct);
		leftMotorB.spin(directionType::fwd, (VERTICAL_AXIS->value() + HORIZONTAL_AXIS->value()), velocityUnits::pct);

    this_thread::sleep_for(10);
  }
}

void helloWorld()
{
  int count = 0;
   
    while(1) {
        Brain.Screen.printAt( 10, 50, "Hello V5 %d", count++ );
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
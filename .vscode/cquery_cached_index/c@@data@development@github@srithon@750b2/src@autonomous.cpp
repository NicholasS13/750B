#include "config.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
  for (AutonAction* step : *autonActions)
  {
    float mag = step->getMagnitude();

    switch (step->getType())
    {
      // mag: 50 is half a tile
      // 50 : 1/2
      // 100 : 1
      case FORWARD_BACKWARD:
        mag /= 100; // now in terms of tiles
        mag *= TILE_LENGTH; // now in terms of inches
        driveFor(mag);
        break;
      //case TURN:

      //break;
      case STRAFE:
        mag /= 100;
        mag *= TILE_LENGTH;
        strafe(mag);
        break;
      case INTAKE_SPIN:
        
      break;
      case MOGO_IN_OUT:
      break;
      case MOGO_RELEASE:
      break;
    }
  }
}

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
  using namespace auton;
  
  for (AutonAction* step : *autonActions)
  {
    float mag = step->getMagnitude();

    switch (step->getType())
    {
      // mag: 50 is half a tile
      // 50 : 1/2
      // 100 : 1
      case AutonActionType::FORWARD_BACKWARD:
        mag /= 100; // now in terms of tiles
        mag *= TILE_LENGTH; // now in terms of inches
        driveFor(mag);
        break;
      case AutonActionType::STRAFE:
        mag /= 100;
        mag *= TILE_LENGTH;
        center_mtr->move_velocity(mag);
        break;
      case AutonActionType::INTAKE_SPIN:
    		intake_mtr->move_velocity(mag);
    		break;
      case AutonActionType::MOGO_IN_OUT:
    		mogo_mtr->move_velocity(mag);
    		break;
      case AutonActionType::MOGO_RELEASE:
    		mogo_release_mtr->move_velocity(100);
    		break;
    }
  }
}

void stopMotors()
{
	right_mtr_back->move_voltage(0);
	right_mtr_front->move_voltage(0);
	left_mtr_back->move_voltage(0);
	left_mtr_front->move_voltage(0);
}

void moveBot(double inches, int32_t velocity, bool direction)
{
  double desiredTicks = (ENCODER_TICKS_PER_ROTATION * (inches / WHEEL_CIRCUMFERENCE));

  pros::lcd::set_text(1, ("Deg = " + std::to_string(desiredTicks)));

  if (!direction)
    desiredTicks = -desiredTicks;

  double leftMotorBackEndingPosition = left_mtr_back->get_position() + desiredTicks;

  right_mtr_front->move_relative(desiredTicks, velocity);
  left_mtr_front->move_relative(desiredTicks, velocity);
  right_mtr_back->move_relative(desiredTicks, velocity);
  left_mtr_back->move_relative(desiredTicks, velocity);

  int iter = 0;

  while (left_mtr_back->get_position() < leftMotorBackEndingPosition) //replace with BLOCK function
  {
    pros::lcd::set_text(3, ("Iteration - " + std::to_string(iter)));
	iter++;
    pros::delay(100);
  }

  pros::lcd::set_text(4, "Stopping Motors");

  stopMotors();
}

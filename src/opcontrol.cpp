#include "config.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	while (true)
	{
		int strafe = controller->get_analog(STRAFE_AXIS);
		int turn;

		int forward = controller->get_analog(FORWARD_BACK_AXIS);

		if (strafe)
		{
			turn = 0;
			center_drive_mtr->move_velocity(strafe * 2);
			forward *= 1.5; // 2?
		}
		else
		{
			turn = controller->get_analog(TURN_AXIS);
		}

		right_drive_mtr->move_velocity((forward - turn));
		left_drive_mtr->move_velocity((forward + turn));

		if (controller->get_digital(INTAKE_IN))
		{
			intake_mtr_right->move_velocity(150);
			intake_mtr_left->move_velocity(150);
		}
		else if (controller->get_digital(INTAKE_OUT))
		{
			intake_mtr_right->move_velocity(-150);
			intake_mtr_left->move_velocity(-150);
		}
		else
		{
			intake_mtr_right->move_velocity(0);
			intake_mtr_left->move_velocity(0);
		}

		pros::delay(20);
	}
}

/*

*/

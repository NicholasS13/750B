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
		if (controller->get_analog(STRAFE_AXIS))
			center_drive_mtr->move_velocity(controller->get_analog(STRAFE_AXIS));
		else
		{
			int turn = controller->get_analog(TURN_AXIS);
			int forward = controller->get_analog(FORWARD_BACK_AXIS);

			right_drive_mtr->move_velocity(forward - turn);
			left_drive_mtr->move_velocity(forward + turn);
		}
		
		if (controller->get_digital_new_press(INTAKE_IN))
		{
			intake_mtr_right->move_velocity(-80);
			intake_mtr_left->move_velocity(-80);
		}
		else if (controller->get_digital_new_press(INTAKE_OUT))
		{
			intake_mtr_right->move_velocity(80);
			intake_mtr_left->move_velocity(80);
		}
			
		pros::delay(20);
	}
}

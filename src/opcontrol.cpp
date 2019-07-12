#include "main.h"
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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	
	pros::Motor left_mtr_back(LEFT_MOTOR_BACK_PORT);
	pros::Motor right_mtr_back(RIGHT_MOTOR_BACK_PORT);
	pros::Motor left_mtr_front(LEFT_MOTOR_FRONT_PORT);
	pros::Motor right_mtr_front(RIGHT_MOTOR_FRONT_PORT);

	while (true)
	{
		int turn = master.get_analog(TURN_AXIS);
		int forward = master.get_analog(FORWARD_BACK_AXIS);



		pros::delay(20);
	}
}

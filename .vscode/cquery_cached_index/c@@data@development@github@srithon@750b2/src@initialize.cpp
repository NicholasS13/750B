#include "config.h"

std::vector<AutonAction*>* auton = new std::vector<AutonAction*>();
pros::Controller* controller = new pros::Controller(pros::E_CONTROLLER_MASTER);

void on_center_button()
{
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void createAutonCheckButtons()
{
	while (true)
	{
		if (controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
			auton->push_back(new AutonAction(FORWARD_BACKWARD, 50));
		else if (controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
			auton->push_back(new AutonAction(FORWARD_BACKWARD, -50));
		else if (controller->get_digital_new_press(LIFT_UP))
			auton->push_back(new AutonAction(LIFT_VERTICAL, 50));
		else if (controller->get_digital_new_press(LIFT_DOWN))
			auton->push_back(new AutonAction(LIFT_VERTICAL, -50));
		else if (controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT))
			auton->push_back(new AutonAction(STRAFE, -50));
		else if (controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT))
			auton->push_back(new AutonAction(STRAFE, 50));
		else if (controller->get_digital_new_press)
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::Task checkButtonTask(createAutonCheckButtons);
	bool loop = true;
	while (loop)
	{

	}
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

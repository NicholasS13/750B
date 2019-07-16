#include "config.h"

std::vector<AutonAction*>* autonActions = new std::vector<AutonAction*>();

pros::Controller* controller = new pros::Controller(pros::E_CONTROLLER_MASTER);

okapi::MotorGroup* left_mtrs = new okapi::MotorGroup({LEFT_MOTOR_BACK_PORT, LEFT_MOTOR_FRONT_PORT});
okapi::MotorGroup* right_mtrs = new okapi::MotorGroup({RIGHT_MOTOR_BACK_PORT, RIGHT_MOTOR_FRONT_PORT});

pros::Motor* center_mtr = new pros::Motor(CENTER_MOTOR_PORT);

pros::Motor* intake_mtr = new pros::Motor(INTAKE_MOTOR_PORT);
pros::Motor* mogo_mtr = new pros::Motor(MOGO_MOTOR_PORT);
pros::Motor* mogo_release_mtr = new pros::Motor(MOGO_RELEASE_MOTOR_PORT);

const pros::controller_analog_e_t& FORWARD_BACK_AXIS = ANALOG_LEFT_Y;
const pros::controller_analog_e_t& TURN_AXIS = ANALOG_RIGHT_X;
const pros::controller_analog_e_t& STRAFE_AXIS = ANALOG_LEFT_X;

const pros::controller_digital_e_t& INTAKE_IN = DIGITAL_R2;
const pros::controller_digital_e_t& INTAKE_OUT = DIGITAL_R1;

const pros::controller_digital_e_t& MOGO_OUT = DIGITAL_L2;
const pros::controller_digital_e_t& MOGO_IN = DIGITAL_L1;

const pros::controller_digital_e_t& MOGO_RELEASE = DIGITAL_X;

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

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/*
Updates the auton creation display
*/
void refreshAutonDisplay()
{
	pros::lcd::set_text(autonActions->size(), autonActions->back()->to_string());
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	// pros::Task checkButtonTask(createAutonCheckButtons);
	using namespace auton;

	controller->get_digital_new_press(a_BREAK);

	unsigned int refresh = 0;

	while (!controller->get_digital_new_press(a_BREAK))
	{
		if (controller->get_digital_new_press(a_FORWARD))
			autonActions->push_back(new AutonAction(FORWARD_BACKWARD, 50));

		else if (controller->get_digital_new_press(a_BACKWARD))
			autonActions->push_back(new AutonAction(FORWARD_BACKWARD, -50));

		else if (controller->get_digital_new_press(a_INTAKE_IN))
			autonActions->push_back(new AutonAction(INTAKE_SPIN, -50));

		else if (controller->get_digital_new_press(a_STRAFE_LEFT))
			autonActions->push_back(new AutonAction(STRAFE, -50));

		else if (controller->get_digital_new_press(a_STRAFE_RIGHT))
			autonActions->push_back(new AutonAction(STRAFE, 50));

		else if (controller->get_digital_new_press(a_MOGO_OUT))
			autonActions->push_back(new AutonAction(MOGO_IN_OUT, 50));

		else if (controller->get_digital_new_press(a_MOGO_IN))
			autonActions->push_back(new AutonAction(MOGO_IN_OUT, -50));

		else if (controller->get_digital_new_press(a_MOGO_RELEASE))
			autonActions->push_back(new AutonAction(auton::MOGO_RELEASE, 50));

		else if (controller->get_digital_new_press(a_BOOST_LAST))
			autonActions->back()->change(10);

		else if (controller->get_digital_new_press(a_LESSEN_LAST))
			autonActions->back()->change(-10);

		else if (controller->get_digital_new_press(a_REMOVE_LAST))
			autonActions->pop_back();

		else
			refresh = 0;

		if (refresh)
			refreshAutonDisplay();

		pros::delay(50);
	}
}

#include "config.h"

std::vector<auton::AutonAction*>* autonActions = new std::vector<auton::AutonAction*>();

pros::Controller* controller = new pros::Controller(pros::E_CONTROLLER_MASTER);

// MOTORS

pros::Motor* left_drive_mtr = new pros::Motor(LEFT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor* right_drive_mtr = new pros::Motor(RIGHT_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor* center_drive_mtr = new pros::Motor(CENTER_MOTOR_PORT);

pros::Motor* intake_mtr_left = new pros::Motor(INTAKE_MOTOR_LEFT_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor* intake_mtr_right = new pros::Motor(INTAKE_MOTOR_RIGHT_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

// pros::Motor* platform_mtr = new pros::Motor(PLATFORM_MOTOR_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor* lift_mtr_1 = new pros::Motor(LIFT_MOTOR_1_PORT);
pros::Motor* lift_mtr_2 = new pros::Motor(LIFT_MOTOR_2_PORT);

pros::Motor* claw_mtr = new pros::Motor(CLAW_MOTOR_PORT);

// pros::Motor* push_mtr_1 = new pros::Motor(PUSHER_MOTOR_1_PORT, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
// pros::Motor* push_mtr_2 = new pros::Motor(PUSHER_MOTOR_2_PORT, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);

// CONTROLLER BINDS

const pros::controller_analog_e_t& FORWARD_BACK_AXIS = ANALOG_LEFT_Y;
const pros::controller_analog_e_t& TURN_AXIS = ANALOG_LEFT_X;
const pros::controller_analog_e_t& STRAFE_AXIS = ANALOG_RIGHT_X;

const pros::controller_digital_e_t& INTAKE_IN = DIGITAL_R1;
const pros::controller_digital_e_t& INTAKE_OUT = DIGITAL_R2;

const auto& LIFT_UP = DIGITAL_L1;
const auto& LIFT_DOWN = DIGITAL_L2;

// const pros::controller_digital_e_t& PUSHER_OUT = DIGITAL_L1;
// const pros::controller_digital_e_t& PUSHER_IN = DIGITAL_L2;

// const pros::controller_digital_e_t& PLATFORM_SHIFT_FORWARD = DIGITAL_UP;
// const pros::controller_digital_e_t& PLATFORM_SHIFT_BACKWARD = DIGITAL_DOWN;

/*

extern pros::Controller* controller;

extern pros::Motor* left_mtr;
extern pros::Motor* right_mtr;
extern pros::Motor* center_mtr;

extern okapi::MotorGroup* intake_mtrs;
extern pros::Motor* push_mtr;
extern pros::Motor* platform_mtr;
extern pros::Motor* last_mtr; // ????

 */

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
	pros::lcd::print(2, "This shit works on god");

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

		else if (controller->get_digital_new_press(a_LIFT_UP))
			autonActions->push_back(new AutonAction(LIFT_MOVE, 50));

		else if (controller->get_digital_new_press(a_LIFT_DOWN))
			autonActions->push_back(new AutonAction(LIFT_MOVE, -50));

		else if (controller->get_digital_new_press(a_TURN))
			autonActions->push_back(new AutonAction(TURN, 50));

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

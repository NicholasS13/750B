#ifndef CONFIG
#define CONFIG

#include "main.h"
#include <vector>

const uint8_t LEFT_MOTOR_BACK_PORT = 15;
const uint8_t RIGHT_MOTOR_BACK_PORT = 14;
const uint8_t LEFT_MOTOR_FRONT_PORT = 13;
const uint8_t RIGHT_MOTOR_FRONT_PORT = 12;

const pros::controller_analog_e_t& FORWARD_BACK_AXIS = ANALOG_LEFT_Y;
const pros::controller_analog_e_t& TURN_AXIS = ANALOG_RIGHT_X;
const pros::controller_analog_e_t& STRAFE_AXIS = ANALOG_LEFT_X;

const pros::controller_digital_e_t& LIFT_UP = DIGITAL_R2;
const pros::controller_digital_e_t& LIFT_DOWN = DIGITAL_R1;

enum AutonActionType
{
  FORWARD_BACKWARD, LIFT_VERTICAL, TURN, STRAFE, MOGO_IN_OUT, MOGO_RELEASE
};

class AutonAction
{
private:
  AutonActionType type;
  uint16_t mag;
public:
  AutonAction(AutonActionType type, uint16_t mag) { this->type = type; this->mag = mag; }
  AutonActionType getType() { return type; }
  void change(int change) { mag += change; }
};

extern std::vector<AutonAction*>* auton;
extern pros::Controller* controller;

#endif

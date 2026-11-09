#include "main.h"

int sign(double x) {
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    } else {
        return 0;
    }
}

double curve(double x) {
    if (abs(x) > DEADBAND / 100 * 127) {
        return a * x * (pow(b, (abs(x) - 127) / d) + c);
        // return abs(pow(abs(x), CURVE)/pow(127, CURVE - 1) + HEIGHT * sqrt(atan(abs(INITIAL * M_PI * abs(x) / 127)))) * sign(x);
        // return (0.00002 * (pow(x, 5)) + 4000 * x) * 0.00010866 * 0.6;
    } else {
        return 0;
    }
}

void teleop() {
    lift.set_brake_mode(MOTOR_BRAKE_HOLD);
    bool claw_state = true;
    int lift_static_extra_power = 0;

    while (true) {
        // get joystick values (tank)
        // int controller_left = curve(controller.get_analog(ANALOG_LEFT_Y)) * 100 / curve(127);
        // int controller_right = curve(controller.get_analog(ANALOG_RIGHT_Y)) * 100 / curve(127);
        // int controller_left = controller.get_analog(ANALOG_LEFT_Y) * 0.6;
        // int controller_right = controller.get_analog(ANALOG_RIGHT_Y) * 0.6;
        
        // chassis.tank(controller_left, controller_right);
        int controller_magnitude = curve(controller.get_analog(ANALOG_LEFT_Y) * 0.95);
        int controller_angle = curve(controller.get_analog(ANALOG_RIGHT_X));
        chassis.curvature(controller_magnitude, controller_angle, true);


        if (controller.get_digital(DIGITAL_R1)) {
            lift.move(90);
        } else if (controller.get_digital(DIGITAL_R2)) {
            lift.move(-30); // slows down power as gravity does most of the work
        } else {
            lift.move(30 + lift_static_extra_power); // counters gravity, keeps lift steady while lifted
        }

        if (controller.get_digital(DIGITAL_L1)) {
            toggle.move(80);
        } else if (controller.get_digital(DIGITAL_L2)) {
            toggle.move(-80);
        } else {
            toggle.move(0);
        }

        if (controller.get_digital_new_press(DIGITAL_A)) {
            claw_state = !claw_state;
            claw.set_value(claw_state);
            if (claw_state) {
                lift_static_extra_power = 20; // macro to move claw up when picking up objects
            }
        }

        if (lift_static_extra_power > 0) {
            lift_static_extra_power --;
        }

        // print measurements from the rotation sensor
        pros::lcd::print(1, "H Sensor: %i", horizontal_tracker.getDistanceTraveled());
        pros::lcd::print(2, "V Sensor: %i", vertical_tracker.getDistanceTraveled());
        pros::lcd::print(3, "I Sensor: %i", imu.get_heading());

        pros::delay(20); // wait 20 ms for runtime consistency
    }
}
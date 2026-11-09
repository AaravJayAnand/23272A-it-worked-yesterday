#include "main.h"

pros::MotorGroup left_motors({-3, -4});
pros::MotorGroup right_motors({1, 2});

pros::MotorGroup lift({8, -9});

pros::adi::DigitalOut claw('A');

pros::Motor toggle(11);

pros::Rotation horizontal_pod(5);
pros::Rotation vertical_pod(6);

pros::Imu imu(7);

lemlib::TrackingWheel horizontal_tracker(&horizontal_pod, lemlib::Omniwheel::NEW_2, -2.5);
lemlib::TrackingWheel vertical_tracker(&vertical_pod, lemlib::Omniwheel::NEW_2, -2.5);

lemlib::OdomSensors odometry(&horizontal_tracker, nullptr, &vertical_tracker, nullptr, &imu);
lemlib::Drivetrain drivetrain(&left_motors, &right_motors, 15, lemlib::Omniwheel::NEW_325, 450, 4);

// lateral PID controller
lemlib::ControllerSettings linear_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, linear_controller, angular_controller, odometry);

pros::Controller controller(CONTROLLER_MASTER);
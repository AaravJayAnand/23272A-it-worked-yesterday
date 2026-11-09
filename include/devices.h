#pragma once
#include "main.h"

// ports:
// 1: front left drivetrain motor
// 2: rear left drivetrain motor
// 3: front right drivetrain motor
// 4: rear right drivetrain motor
// 5: horizontal odom pod
// 6: vertical odom pod
// 7: imu
// 8: left side lift
// 9: right side lift
// 11: toggle mech
// A: claw

extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

extern pros::MotorGroup lift;

extern pros::adi::DigitalOut claw;

extern pros::Motor toggle;

extern pros::Rotation horizontal_pod;
extern pros::Rotation vertical_pod;

extern pros::Imu imu;

extern lemlib::TrackingWheel horizontal_tracker;
extern lemlib::TrackingWheel vertical_tracker;

extern lemlib::OdomSensors odometry;
extern lemlib::Drivetrain drivetrain;

extern lemlib::ControllerSettings linear_controller;

extern lemlib::ControllerSettings angular_controller;

extern lemlib::Chassis chassis;

extern pros::Controller controller;
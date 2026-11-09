#pragma once
#include "main.h"

// https://www.desmos.com/calculator/urdvesqv1f

inline const double a = 0.5; // random curve variable a
inline const double b = 2; // random curve variable b
inline const double c = 0.8; // random curve variable c
inline const double d = 6; // random curve variable d
inline const double DEADBAND = 5; // percentage

inline int sign(double x);

double curve(double x);

void teleop();
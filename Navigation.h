//  Navigation.h - Library finding distance to taget and bearing.
//  Created by Jakob Coray, March 12, 2015.
//  Released into the public domain.

#ifndef Cube_h
#define Cube_h

#include "Arduino.h"

double calculateDistance(double robotLat,double endLat, double robotLong, double endLong);
double calculateBearing(double robotLat, double endLat, double robotLong, double endLong);

#endif

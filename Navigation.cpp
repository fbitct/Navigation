//  Navigation.cpp - Library finding distance to taget and bearing.
//  Created by Jakob Coray, March 12, 2015.
//  Released into the public domain.

#include "Arduino.h"
#include "Navigation.h"
#include <math.h>

double _toRadians(double deg)  {
  double rad = deg * (PI/180);
  return rad;
}

double _toDegrees(double rad)  {
  double deg = rad * (180 / PI);
  return deg;
}

double calculateDistance(double robotLat,double endLat, double robotLong, double endLong)  {
  //  This function calculates the great circle distance (the earth is a sphere after all)
  //  by using the haversine formula. It assumes that the earth is a sphere.
  //  It was adapted from and tested at: http://www.movable-type.co.uk/scripts/latlong.html
  //  acording the the website, it has an accuracy of a few meters (using 64 bit doubles,
  //  these are only 32 bits). If it is very slow in may be better to use Pythagoras’ theorem,
  //  use the Spherical Law of Cosines or use an ellipsoidal model of the earth (Vincenty)
  //  found here: http://www.movable-type.co.uk/scripts/latlong-vincenty.html
  //  returns the distance in meters
  double R = 6371000; //  radius of the earth in metres
  double phi1 = _toRadians(robotLat); // the trig functions require radians
  double phi2 = _toRadians(endLat); //  phi = Laditude
  double deltaPhi = _toRadians(endLat-robotLat);
  double deltaLambda = _toRadians(endLong-robotLong); //  lambda = Longitude
  //  Behold, the line of math. Bathe in its glory.
  double a = sin(deltaPhi/2) * sin(deltaPhi/2) + cos(phi1) * cos(phi2) * sin(deltaLambda/2) * sin(deltaLambda/2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a)); // angular distance in radians (comment taken from website)
  double d = R * c; // a is the square of half the chord length between the points (comment taken from website)
  return d;
}

double calculateBearing(double robotLat, double endLat, double robotLong, double endLong)  {
  //  This function finds the angle from north that the object is. This is useful so that
  //  the robot can turn to that angle. It was also tested and adapted from the same website
  //  as calculateDistance(), (see for more notes). It may be both easier and less computationally
  //  expensive to assume that the object will remain at the same bearing for the whole trip.
  //  returns the bearing in degrees North (0 - 360)
  double phi1 = _toRadians(robotLat);
  double phi2 = _toRadians(endLat);
  double deltaLambda = _toRadians(endLong-robotLong);
  double y = sin(deltaLambda) * cos(phi2);
  double x = cos(phi1) * sin(phi2) - sin(phi1) * cos(phi2) * cos(deltaLambda);
  double bearing = _toDegrees(atan2(y,x)); // returns the bearing in (-180, 180)
  double compassNormalized = fmod(bearing + 360, 360); // doubleing point modulo used to convert to (0, 360)
  return compassNormalized;
}

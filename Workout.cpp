#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include "Workout.h"


/* Constructor for Workout class.
    Takes a radius in inches or meters, and Imperial is true if in inches and false if in meters.
      radius:  float > 0 in either inches or meters.
      Imperial:  Boolean true for Imperial and false for Metric.
*/

Workout::Workout(float radius, bool Imperial, int magnets) {
      if (radius <= 0) {         // Make sure radius is real and if not replace it with 1 meter.
        radius = 1;
        Imperial = false;
      }
      if (Imperial) {
        radiusI = radius / 12;      // Store radius in feet
        radiusM = radius / 39.37;   // Inches to meters
      }
      else {
        radiusM = radius;
        radiusI = radius / 1.09;   // meters to yards
      }
      magNum = magnets;
      timerOn = false;
      pauseOn = false;
}  

/* WORKOUT::RPM returns the revolutions per minute.
    No intake function  
    Returns a float with revolutions / minute, needs conversion to integer if want rounding
*/

float Workout::RPM() {
        float revolution;
        revolution = (lastPass - previousPass) * magNum;   // Gives the amount of microseconds to complete a single revolution
        return (60 / revolution);           // Not robust if doing less than 1 revolution per minute will return 0
}

/* Workout::MPH   Returns and produces MPH
    No intake and no modifiers
    Uses radiusI to calculate MPH
*/
float Workout::MPH() {
        float exactRPM, exactMPH, temp;
        exactRPM = this->RPM();          // Revolutions / minute
        exactMPH = exactRPM * 60;            // Revolutions / hour
        temp = 2 * 3.141 * (radiusI / 0.00018939);       // Convert to circumference in miles
        exactMPH = temp * exactMPH;          // miles / hour
        return exactMPH;
}

/* Workout::KPH   Returns and produces KPH
    No intake and no modifiers
    Uses radiusM to calculate KPH
*/
float Workout::KPH() {
        float exactRPM, exactKPH, temp;
        exactRPM = this->RPM();         // Revolutions / minute
        exactKPH = exactRPM * 60;            // Revolutions / hour
        temp = 2 * 3.141 * (radiusM / 1000);    // convert to circumference in kilometers
        exactKPH = temp * exactKPH;          // Kilometers / hour
        return exactKPH;
}

/* Workout::time() Function to return to total time since the start, minutes and seconds
    No intake and no modifiers
    Output microseconds since starting
    This takes into account pause time
*/
unsigned long Workout::time() {
    unsigned long curTime = micros();
    return curTime - startTime - pauseTime;
}

/* Workout::startTimer  Function to start the timer and to end the timer
    No intake and no modifiers
    No output
*/
void Workout::startTimer() {
  if ((timerOn == true) || (pauseOn == true)) {                    // Timer is already running or the workout is paused.  End the workout
    timerOn = false;
    unsigned long endTime = micros();
    pauseOn = false;
  }
  else if (timerOn == false) {                                   // Timer is off, start the workout
    unsigned long startTime = micros();
    timerOn = true;
  }
}

/* Workout::hallPass  Function to record magnet passing, main workhorse of the class
    Alters previousPass, lastPass, and distance
    No input and no modifiers
    No output
*/
void Workout::hallPass() {
	previousPass = lastPass;						// Store time of last pass in
	lastPass = micros();							// Store time of current pass
	distance += (2 * radiusM * 3.141) / magNum;	// Add distance (circumference / number of magnets)
}
               /*     
		void hallPass(); // Records magnet pass
		float averageI(); // returns average MPH
		float averageM(); // returns average KPH
                void pauseTimer(bool pause ); //  pauses the workout and starts filling the pause time variable

	
		unsigned long lastPass; // holds time of last magnet pass
                unsigned long previousPass;  // holds the time of the previous last pass
		float radiusI; // radius in miles
		float radiusM; // radius in meters
		unsigned long startTime  ; // holds start time
		unsigned long endTime; // holds end time
		float distance; // holds distance in meters
		bool timerOn; // is the timer running?  0 for no 1 for yes
*/

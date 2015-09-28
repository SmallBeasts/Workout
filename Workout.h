/* Workout Class */
#ifndef _WORKOUT_
#define _WORKOUT_

class Workout {

	public: 
		Workout(float radius, bool Imperial, int magnets);  // radius in meters, 1 for Imperial
		void hallPass(); // Records magnet pass
		float RPM(); // Returns RPM
		float MPH(); // returns MPH
		float KPH(); // returns KPH
		unsigned long time(); // returns total time
		float averageI(); // returns average MPH
		float averageM(); // returns average KPH
		void startTimer(); // sets start time or end time if timerOn active
                void pauseTimer(bool pause); //  pauses the workout and starts filling the pause time variable
                
	private:
		unsigned long lastPass; // holds time of last magnet pass
                unsigned long previousPass;  // holds the time of the previous last pass
                unsigned long pauseTime;     // holds the number of microseconds that the program has been paused.  This is additive.
		float radiusI; // radius in miles
		float radiusM; // radius in meters
		unsigned long startTime  ; // holds start time
		unsigned long endTime; // holds end time
		float distance; // holds distance in meters
		bool timerOn; // is the timer running?  0 for no 1 for yes
                int magNum;   // How many magnets are there on the wheel ( for one magnet one pass = 1 revolution, 2 magnets 2 passes = 1 revolution)
                bool pauseOn;    // is the timer paused?  0 for no 1 for yes.
};
#endif

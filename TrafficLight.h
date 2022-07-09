// This Header file contains the class TrafficLight with attributes, getters and setters
// It has functions to make the program wait and print the state of traffic lights
// Created by: Sushil Bohara

#pragma once
#include <iomanip>  
using namespace std;
class TrafficLight {
private:
	// Declaring private attributes
	int ID;
	int state;
	double GreenTiming;
	static int NoOfTrafficlights; // static variable
public:
	// Default Constructor
	TrafficLight() {
		state = 1;
		GreenTiming = 0;   // (in seconds)
		NoOfTrafficlights++;
		ID = NoOfTrafficlights;
	}
	// Non Default Constructor
	TrafficLight(int newstate, double newGreenTiming) {
		state = newstate;
		GreenTiming = newGreenTiming;
	}
	// Getters and Setters
	int getID() {
		return ID;
	}
	int getstate() {
		return state;
	}
	double getGreenTiming() {
		return GreenTiming;
	}
	static int getNoOfTrafficlights() {
		return NoOfTrafficlights;
	}
	void setstate(int newstate) {
		state = newstate;
	}
	void setGreenTiming(double newGreenTiming) {
		GreenTiming = newGreenTiming;
	}
	// Function to make the program wait for specific seconds
	void wait(double seconds) {
		// Declare local variable for duration to wait
		double waitduration;
		// find the initial system time
		auto starttime = chrono::steady_clock::now();
		// Loop to make the program wait..
		do
		{   // calculate instantaneous system time
			auto endtime = chrono::steady_clock::now();
			// Calculate the difference between instantaneous time and initial time
			waitduration = double(chrono::duration_cast<chrono::nanoseconds>(endtime - starttime).count());

		} while (waitduration < (seconds * 1e9)); // Repeat the loop until the specific seconds(converted to nanoseconds) are passed


	}
	// Function to print the state of the traffic lights
	void printLightInfo(int state, int ID) {
		// Print Off if state is 0
		if (state == 0) {
			cout << "L" << ID << setw(15) << "Off" << endl;
		}
		// Print Red if state is 1
		if (state == 1) {
			cout << "L" << ID << setw(15) << "Red" << endl;
		}
		// Print Yellow if state is 2
		if (state == 2) {
			cout << "L" << ID << setw(15) << "Yellow" << endl;
		}
		// Print Green if state is 3
		if (state == 3) {
			cout << "L" << ID << setw(15) << "Green" << endl;
		}
	}
	// destructor
	~TrafficLight() {

	}

};
// initialize the static variable
int TrafficLight::NoOfTrafficlights = 0;

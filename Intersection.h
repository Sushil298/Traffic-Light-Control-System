// This Header file contains the class Intersection with attributes, getters and setters
// It has functions to add/drop traffic lights, run the traffic light simulation,  read data from the file and update the Green Timing
// Created by: Sushil Bohara


#pragma once
#include <fstream>
// Declare constants
# define YellowTime 3        // Duration of Yellow Light
# define Max_Objects 8        // Maximum no. of traffic lights
# define updateinterval 24    // Green Timing update interval
class Intersection {
	// attributes
private:
	double cyclelength;
	int NoOfTrafficlights;
	//Array of TrafficLight Objects
	TrafficLight TrafficLight_Objects[Max_Objects];
	// Array of traffic flow rates
	int TrafficFlowRate[Max_Objects];
public:
	// Default Constructor
	Intersection() {

		NoOfTrafficlights = 0;
		// Initialize cyclelength and trafficflow rates to safe values
		cyclelength = 400; // in seconds
		for (int i = 0; i < Max_Objects; i++)
		{
			TrafficFlowRate[i] = 100;
		}

	}
	// Getters and Setters
	int getNoOfTrafficlights() {
		return NoOfTrafficlights;
	}
	double getcyclelength() {
		return cyclelength;
	}
	int* getTrafficFlowRate() {
		return TrafficFlowRate;
	}
	void setcyclelength(double newcyclelength) {
		cyclelength = newcyclelength;
	}
	void setTrafficFlowRate(int newrate[]) {
		for (int i = 0; i < Max_Objects; i++)
			TrafficFlowRate[i] = newrate[i];
	}

	// Function to add a new traffic light object

	void AddLight(TrafficLight alight) {
		//add new object only if the maximum number has not been reached
		if (NoOfTrafficlights < Max_Objects) {
			TrafficLight_Objects[NoOfTrafficlights] = alight;
			NoOfTrafficlights++;
		}
		else
			cout << "Can't add more traffic lights, maximum value reached" << endl;
	}
	// Function to drop a traffic Light Object searching by ID
	void dropLight(int droplightid) {

		bool isfound = false;
		// Loop to search the ID of the traffic light to be dropped 
		for (int i = 0; i < NoOfTrafficlights; i++) {
			// if ID is found,replace that traffic light object by next in the array and so on..
			if (droplightid == TrafficLight_Objects[i].getID())
			{
				cout << "The light to be removed is found." << " Light L" << droplightid << " is removed." << endl;
				for (int j = i; j < NoOfTrafficlights; j++) {
					TrafficLight_Objects[j] = TrafficLight_Objects[j + 1];
				}



				NoOfTrafficlights--;
				isfound = true; // Assign true to isfound
			}
		}
		// if ID is not found, inform the user via a message.
		if (!isfound)
			cout << "Can't find the traffic light to be dropped" << endl;
	}

	// Function to run the simulation

	void run() {

		// Declare a variable to store the time duration
		double elapsed_time;
		// if any traffic lights are turned off, display "OFF" message in the screen
		for (int countoff = 0; countoff < NoOfTrafficlights; countoff++) {
			if (TrafficLight_Objects[countoff].getstate() == 0) {
				TrafficLight_Objects[countoff].printLightInfo(TrafficLight_Objects[countoff].getstate(), TrafficLight_Objects[countoff].getID());

			}

		}
		cout << endl;
		
		// infite loop to run the simulation....

		while (1) {
			// find the initial system time
			auto starttime = chrono::steady_clock::now();
			// Read the data from the file calling another function
			readTrafficData();
			// Loop which runs continuously for 24 hours.
			do {
				// Loop that goes through all the TrafficLight objects

				for (int i = 0; i < NoOfTrafficlights; i++)
				{   // Loop to assign the state of the 'on' traffic light object to green(3) and yellow(2)
					if (TrafficLight_Objects[i].getstate() != 0) {
						for (int k = 3; k > 1; k--)
						{

							// assign the state of ith traffic Light state to k
							TrafficLight_Objects[i].setstate(k);
							// print the color of ith traffic light object
							TrafficLight_Objects[i].printLightInfo(TrafficLight_Objects[i].getstate(), TrafficLight_Objects[i].getID());

							// Loop to assign the state of all other 'on' Traffic Light objects to Red(1) 
							for (int j = 0; j < NoOfTrafficlights; j++)
							{
								if (j != i && TrafficLight_Objects[j].getstate() != 0) {
									// Assign the state of jth Traffic Light Object to red(1)
									TrafficLight_Objects[j].setstate(1);
									// Print the color of the jth traffic light object
									TrafficLight_Objects[j].printLightInfo(TrafficLight_Objects[j].getstate(), TrafficLight_Objects[j].getID());
								}
							}
							// Print a newline to make clear visibility of change of state in the traffic light.
							cout << endl;
							// wait for the duration equal to green timing if green light is on in ith object.
							if (k == 3)
								TrafficLight_Objects[i].wait(TrafficLight_Objects[i].getGreenTiming());
							// wait for the duration equal to yellow timing if yellow light is on in ith object.
							if (k == 2)
								TrafficLight_Objects[i].wait(YellowTime);


						}
					}
				}
				// Find the instantaneous system time
				auto endtime = chrono::steady_clock::now();
				// Calculate the elapsed time in nanoseconds
				elapsed_time = double(chrono::duration_cast<chrono::nanoseconds>(endtime - starttime).count());
			} while (elapsed_time < (updateinterval * 86400 * 1e9));  // Exit the loop in 24 hours to read new data from the file

		}







	}
	// Function to read New Data from the file
	void readTrafficData() {
		// Create a variable to store the total traffic flow rate and initialize to 0
		double Qt(0);
		// create the file stream to read data from the file
		ifstream inputfile;
		inputfile.open("TrafficData.txt");
		// Dispaly the error message if the file is not opened
		if (inputfile.fail()) {
			cerr << "Error in opening the file" << endl;
		}
		// If file is opened, read the data..
		else

		{ // Read the cyclelength from the first line
			inputfile >> cyclelength;
			// read the traffic flow rates of all the traffic light objects (This will not give errors if any objects were dropped)
			for (int i = 0; i < Max_Objects; i++)
			{
				inputfile >> TrafficFlowRate[i];
			}

			// calculate the total traffic flow rate

			for (int k = 0; k < NoOfTrafficlights; k++)
			{
				// Since the ID of the object is 1 more than the index of the corresponding traffic flow rate,
				//we can write traffic flow rate of jth object = TrafficFlowRate[TrafficLight_Objects[j].getID()-1]
				// Doing this will not give errors if any objects were dropped
				Qt += TrafficFlowRate[TrafficLight_Objects[k].getID() - 1];

			}
			// Call the function to update the green timings of all the traffic lights
			for (int j = 0; j < NoOfTrafficlights; j++) {

				updateGreenTiming(TrafficFlowRate[TrafficLight_Objects[j].getID() - 1], cyclelength, Qt, j);

			}


		}




	}
	// Function to update the green timings of all the traffic light objects
	void updateGreenTiming(int Qi, double C, double Qt, int i) {

		TrafficLight_Objects[i].setGreenTiming((Qi * C) / Qt); // Calculte the green timing and update.
	}

	// destructor
	~Intersection() {

	}

};

// This Program controls the traffic lights at the intersection of roads
// Created by : Sushil Bohara 
// If any light is dropped, it means that it is completely removed but the sensor still reads the data for corresponding roads and updates in the file



#include <iostream>
#include <chrono>
#include "TrafficLight.h"
#include "Intersection.h"
using namespace std;


int main()
{   // creating the objects of the class TrafficLight
	TrafficLight L1, L2, L3, L4, L5, L6;
	// Turn off two(arbitrary number) lights
	L2.setstate(0);
	L4.setstate(0);
	// create the object of the class "Intersection"
	Intersection I;
	// Adding 'TrafficLight' Objects
	I.AddLight(L1);
	I.AddLight(L2);
	I.AddLight(L3);
	I.AddLight(L4);
	I.AddLight(L5);
	I.AddLight(L6);
	// Print the total number of traffic lights
	cout << "Total No. of Traffic lights = " << I.getNoOfTrafficlights() << endl;
	// Drop Two(arbitrary number) Traffic lights
	I.dropLight(L1.getID());
	I.dropLight(L6.getID());
	// Print the number of traffic lights after dropping
	cout << "Total lights after dropping = " << I.getNoOfTrafficlights() << endl;
	// Run the simulation
	I.run();
	return (0);
}




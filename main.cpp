/**
 * File:    main.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 1
 * Notes:  
 *
 *
 *
 * Hunter College 2012
 */

#include <iostream>
#include "System.h"
#include <sstream>

using namespace std;


int main ()
{
     
    // Create a new system
    System simulator;
    
    // Start the simulation
    simulator.runSysGen();
    simulator.initializeDevices();
    simulator.runSimulator();
    //simulator.displayReadyQueue();
  
    return 0;
}


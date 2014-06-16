/**
 * File:    Process.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 1
 * Notes:  
 *
 *
 *
 * Hunter College 2012
 */

#include "Process.h"

Process::Process(int p)
{
    processState = NEW;
    PID = p;
    memLocation = 0;
    lengthOfFile = 0;
    filename = "";
    action ="";
    read = false;
    write = false;
}

void Process::changeState(STATE newSTATE)
{
    processState = newSTATE;
    
}

int Process::getPID()
{
    return PID;
}

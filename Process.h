/**
 * File:    Process.h
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 1
 * Notes:  
 *
 *
 *
 * Hunter College 2012
*/

#ifndef PROCESS_H
#define PROCESS_H

#include <string>
using namespace std;

enum STATE {NEW, READY, RUNNING, WAITING, TERMINATED};

class Process 
{
public:
    friend class PrinterQueue;
    friend class DiskQueue;
    friend class CDRWQueue;
    friend class ReadyQueue;
    friend class System;
    friend class CPU;
    
    Process(int p);
    void changeState(STATE newState);
    int getPID();
    
    
private:
    STATE processState;
    int PID;
    // For print processes
    string filename;
    int memLocation;
    string action;
    int lengthOfFile;
    bool read;
    bool write;
};

#endif

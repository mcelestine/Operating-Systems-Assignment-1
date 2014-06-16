/**
 * File:    QueueADT.h
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 1
 * Notes:   
 *          BASE CLASS FOR THE DEVICE QUEUES.
 *          USES STL QUEUE CLASS.
 *          EACH DERIVED CLASS OF THIS BASE CLASS WILL HAVE
 *          A PROCESS QUEUE
 *
 * Hunter College 2012
 */

#ifndef QUEUEADT_H
#define QUEUEADT_H
#include "Process.h"
#include <queue>
#include <iostream>


class QueueADT 
{
public:
    friend class PrinterQueue;
    friend class DiskQueue;
    friend class CDRWQueue;
    friend class ReadyQueue;
    friend class System;
    friend class CPU;
    
    bool isEmpty()const;
    void enqueue(Process *);
    Process* dequeue();
    //virtual void sendInterrupt() = 0;
    //void displayStats();
    
private:
    bool busy;
    queue<Process*> processQueue; 
};



#endif

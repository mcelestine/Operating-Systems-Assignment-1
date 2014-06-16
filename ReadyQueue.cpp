/**
 * File:    ReadyQueue.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 1
 * Notes:  
 *
 *
 *
 * Hunter College 2012
 */

#include "ReadyQueue.h"

ReadyQueue::ReadyQueue()
{
    
}

void ReadyQueue::displayStats()
{
    queue<Process *> tempQueue;
    tempQueue = processQueue; //point to queue it's going to copy
    cout << "Processes that are in the ready queue\n";
    
    while (!tempQueue.empty())
    {
        cout <<"PID: " << tempQueue.front()->PID << "||";
        tempQueue.pop();
    }
}
 

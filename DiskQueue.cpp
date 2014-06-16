/**
 * File:      DiskQueue.cpp
 * Author:    Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project:   CSCI340 Assignment 1
 * Notes:  
 *
 *
 * Hunter College 2012
 */

#include "DiskQueue.h"

DiskQueue::DiskQueue(int i)
{
    name = 'D';
    diskNum = i;

}

void DiskQueue::displayDiskStats()
{
    
    queue<Process *> tempQueue;
    tempQueue = processQueue; //point to queue it's going to copy
    cout << "Processes that were in the Disk queue\n";
    
    while (!tempQueue.empty())
    {        
        //cout <<"---------------------------------------\n";
        cout <<"PID: " << tempQueue.front()->PID << "||" 
             << "File name: " << tempQueue.front()->filename << "||" 
             << "Length of file: " << tempQueue.front()->lengthOfFile << "||" 
             <<"Starting location in memory: " << tempQueue.front()->memLocation;
        tempQueue.pop();
    }
    
}

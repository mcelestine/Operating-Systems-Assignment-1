/**
 * File:    PrinterQueue.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 1
 * Notes:  
 *
 *
 *
 * Hunter College 2012
 */
#include "PrinterQueue.h"


PrinterQueue::PrinterQueue()
{
    
}
void PrinterQueue::printerStats()
{
    
    queue<Process *> tempQueue;
    tempQueue = processQueue; //point to queue it's going to copy
    cout << "Process info that were in the printer queue\n";
    
    while (!tempQueue.empty())
    {
        //cout <<"---------------------------------------\n";
        cout <<"PID: " << tempQueue.front()->PID << "--|--" 
            << "File name: " << tempQueue.front()->filename << "--|--" 
            << "Length of file: " << tempQueue.front()->lengthOfFile << "--|--" 
        <<"Starting location in memory: " << tempQueue.front()->memLocation << endl;
        tempQueue.pop();
    }
}

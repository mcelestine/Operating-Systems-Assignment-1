/**
 * File:      DiskQueue.h
 * Author:    Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project:   CSCI340 Assignment 1
 * Notes:  
 *
 *
 *
 * Hunter College 2012
 */

#ifndef DISKQUEUE_H
#define DISKQUEUE_H

#include "QueueADT.h"

class DiskQueue: public QueueADT
{
public:
    DiskQueue(int i);
    void displayDiskStats();
private:
    char name;
    int diskNum;
};


#endif

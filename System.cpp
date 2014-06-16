/**
 * File:    System.cpp
 * Author:  Makina Celestine <mcelesti@hunter.cuny.edu>
 * Project: CSCI340 Assignment 1
 * Notes:  
 * Revisions:
              10/14/2012
             -To input a system call, user can now type "p1"<enter>.
             - When a process requests a device it "leaves the CPU". 
               Once a device request is made, the CPU becomes available and
               the system sends the next process to the CPU. (i.e. the CPU points to the 
               newly allocated process.)
             - Altered the terminate function for the CPU:
               Fixed the segmentation fault issue when the terminate function attempted
               to free the same memory twice.
             - Fixed interrupt functions that caused a segmentation fault when trying
               to dequeue an empty device queue.
             - When user tries to enter a system call with an empty CPU, the prompt 
               would just be returned to you.
 *
 * Hunter College 2012
 */

#include "System.h"


void System::runSysGen()
{
    cout << "----------------------------------------\n";
    cout << "SYSTEM GENERATION - SYSTEM SET UP" << endl;
    
    cout << "In this part of the installation, you will specify the number of devices in the system.\n";        
}

 // initializeDevices()
 // Function to set up the system.
 // Initializes/Creates the respective devices and their queues.
 // Vectors initially contain empty device queues.
void System::initializeDevices()
{
    cout << "----------------------------------------\n";
    while ((cout << "How many printers are there? ") 
           && !(cin >> numOfPrinters))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    for (int i = 0; i < numOfPrinters; i++)
    {
        Printers.push_back(PrinterQueue());
    }
    
    cout << "----------------------------------------\n";
    while ((cout << "How many disks? ") 
           && !(cin >> numOfDisks))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    for (int i = 0; i < numOfDisks; i++)
    {
        Disks.push_back(DiskQueue(i+1));
    }
    
    cout << "----------------------------------------\n";
    while ((cout << "How many CD/RW drives? ")
           && !(cin >> numOfCDRW))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    for (int i = 0; i < numOfCDRW; i++)
    {
        CDRWs.push_back(CDRWQueue());
    }
    
    cout << "THANK YOU. SYSTEM SET UP IS COMPLETE!" << endl;
    cout << "----------------------------------------\n";
}


void System::runSimulator()
{
    int i = 0; //used to generate PID
    string command;
    int processCommand;
    char snapshotCommand;
    int c;
    cout << endl;
    cout << "System is Now Running" << endl;
    
    do 
    {
        cout << "Enter a command: ";
        getline(cin,command);
        
        if (command == "A")
        {
            i++;
            Process *temp = new Process(i);
            cout << endl;
            cout << "Process was created " << endl;
            sendToReadyQueue(temp);
            cout << "Process "<< i <<" was sent to Ready Queue" << endl;
            CPUHandler();
        }
        else if (command == "t")
        {
            if (systemCPU.current->processState != TERMINATED)
            {
                cout << "Process " << systemCPU.current->PID << " is terminated.\n";
                systemCPU.terminateProcess();
                CPUHandler();
            }
            else
                CPUHandler();
        }
        else if (command == "S")
        {
            cout << "Waiting for next input..." << endl;
            cin >> snapshotCommand;
            if (snapshotCommand == 'r')
            {
                cout << endl;
                systemReadyQueue.displayStats();
            }
            else if (snapshotCommand == 'p')
            {
                for (int i = 0; i < Printers.size(); i++)
                {
                    cout << "Stats for Printer " << i+1 << " : ";
                    Printers[i].printerStats();
                    cout << endl;
                }
            }
            else if (snapshotCommand == 'd')
            {
                for (int i = 0; i < Disks.size(); i++)
                {
                    cout << "Stats for Disk " << i+1 << " : ";
                    Disks[i].displayDiskStats();
                    cout << endl;
                }
            }
            else if (snapshotCommand == 'c')
            {
                for (int i = 0; i < CDRWs.size(); i++)
                {
                    cout << "Stats for CDRW " << i+1 << " : ";
                    CDRWs[i].displayCDRWStats();
                    cout << endl;
                }
            }
        }
        else 
        {
            if (systemCPU.isOccupied == true)
            {
                c = command.find("p");
                if (c != command.npos)
                {
                    printerHandler(command);
                    if (systemReadyQueue.isEmpty() == false)
                        CPUHandler(); //send next process to CPU
                }
            
                c = command.find("d");
                if (c != command.npos)
                {
                    diskHandler(command);
                    if (systemReadyQueue.isEmpty() == false)
                        CPUHandler();
                }
            
                c = command.find("c");
                if (c != command.npos)
                {
                    CDRWHandler(command);
                    if (systemReadyQueue.isEmpty() == false)
                        CPUHandler();
                }
            }
        
            //cout << "NOTE: System calls cannot be completed without a process."<< endl;
            
            c = command.find("P");
            if (c != command.npos)
            {
                printerInterrupt(command);
                CPUHandler();
            }
            
            c = command.find("D");
            if (c != command.npos)
            {
                diskInterrupt(command);
                if (systemReadyQueue.isEmpty() == false)
                    CPUHandler();
            }
            
            c = command.find("C");
            if (c != command.npos)
            {
                CDRWInterrupt(command);
                if (systemReadyQueue.isEmpty() == false)
                    CPUHandler();
            }
            
        }
    }
    while (command != "Q");
}

/***********************DEVICE HANDLERS********************************/

void System::CPUHandler()
{
    if (systemCPU.isOccupied == false)
    {
        cout << "CPU is ready to accept a process." << endl;
        if (systemReadyQueue.isEmpty() == false)
        {
            systemCPU.receiveProcess(systemReadyQueue.dequeue());
        }
        else
            cout << "No jobs in Ready Queue." << endl;
    }
    else
        cout << "CPU is currently busy." << endl;
        cout << endl;
}

void System::printerHandler(string p)
{
    char holder = p[1];
    int num = holder - '0';
    if (num > numOfPrinters || num <= 0)
    {
        cout << "Cannot issue request. Printer doesn't exist\n";
    }
    else
    {
        sendPrinterRequest(num-1);
    }
}

void System::diskHandler(string d)
{
    char holder = d[1];
    int num = holder - '0';
    if (num > numOfDisks || num <= 0)
    {
        cout << "Cannot issue request. Disk doesn't exist\n";
    }
    else
    {
        sendDiskRequest(num-1);
    }
    
}

void System::CDRWHandler(string c)
{
    char holder = c[1];
    int num = holder - '0';
    if (num > numOfCDRW || num <= 0)
    {
        cout << "Cannot issue request. CDRW device doesn't exist\n";
    }
    else
    {
        sendCDRWRequest(num-1);
    }
}

/********************************************************************/
void System::sendToReadyQueue(Process *send)
{
    systemReadyQueue.enqueue(send);
    send->processState = READY;
}

void System::sendPrinterRequest(int num)
{
    
    string file;
    int location;
    int fileLength;
    
    Process *temp = systemCPU.current;
    temp->processState = WAITING;
    systemCPU.isOccupied = false;
    
    temp->write = true;
    cout << "Enter file name: ";
    cin >> file;
    temp->filename = file;
    
    while ((cout << "Enter starting location in memory: ") 
           && !(cin >> location))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    temp->memLocation = location;    
        
    while ((cout << "How long is the file? ")
            && !(cin >> fileLength))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    temp->lengthOfFile = fileLength;
    cout << "Process out of CPU. Now in Printer Queue. " << endl;
    Printers[num].enqueue(temp);
}

void System::sendDiskRequest(int num)
{
    string file;
    int location;
    int fileLength;
    string readWrite;
    
    Process *temp = systemCPU.current;
    temp->processState = WAITING;
    
    systemCPU.isOccupied = false;
    
    cout << "Enter file name: ";
    cin >> file;
    temp->filename = file;
    
    while ((cout << "Enter starting location in memory: ") 
           && !(cin >> location))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    temp->memLocation = location;
    
    cout << "Is the requested action a read (type 'r') or write (type 'w')? ";
    cin >> readWrite;
    if (readWrite == "r")
    {
        temp->read = true;
    }
    else if (readWrite == "w")
    {
        temp->write = true;
        while ((cout << "How long is the file? ")
               && !(cin >> fileLength))
        {
            cout << "Invalid input. Enter an integer: " << endl;
            cin.clear();
            cin.ignore(20, '\n');
        }
        temp->lengthOfFile = fileLength;
    }
    else
    {
        cout << "Input invalid. Default: Performing a read.";
        temp->read = true;
    }
    Disks[num].enqueue(temp); //Enqueue process to disk queue
}

void System::sendCDRWRequest(int num)
{
    string file;
    int location;
    int fileLength;
    string readWrite;
    
    Process *temp = systemCPU.current;
    temp->processState = WAITING;
    
    systemCPU.isOccupied = false;
    cout << "Enter file name: ";
    cin >> file;
    temp->filename = file;
   
    while ((cout << "Enter starting location in memory: ") 
           && !(cin >> location))
    {
        cout << "Invalid input. Enter an integer: " << endl;
        cin.clear();
        cin.ignore(20, '\n');
    }
    
    temp->memLocation = location;
    
    cout << "Is the requested action a read (type 'r') or write (type 'w')? ";
    cin >> readWrite;
    if (readWrite == "r")
    {
        temp->read = true;
    }
    else if (readWrite == "w")
    {
        temp->write = true;
        while ((cout << "How long is the file? ")
               && !(cin >> fileLength))
        {
            cout << "Invalid input. Enter an integer: " << endl;
            cin.clear();
            cin.ignore(20, '\n');
        }
        temp->lengthOfFile = fileLength;
    }
    else
    {
        cout << "Input invalid. Default: Performing a read.";
        temp->read = true;
    }
    CDRWs[num].enqueue(temp); //Enqueue process to CDRW queue
}

/********************************************************************/

// Signals that the printer has completed its process task
void System::printerInterrupt(string pI)
{
    char holder = pI[1];
    int num = holder - '0'; //Convert ascii value to the right integer
    if (Printers[num-1].isEmpty() == false)
    {
        cout << endl;
        cout << "Printer request completed." << endl;
        cout << "Now sending process to Ready Queue." << endl;
        sendToReadyQueue(Printers[num-1].dequeue());
    }
    else
        cout << "Device queue is empty. Cannot complete request." << endl;
}

void System::diskInterrupt(string dI)
{
    char holder = dI[1];
    int num = holder - '0';
    if (Disks[num-1].isEmpty() == false)
    {
        cout << endl;
        cout << "Disk request completed." << endl;
        cout << "Now sending process to Ready Queue." << endl;
        sendToReadyQueue(Disks[num-1].dequeue());
    }
    else
        cout << "Device queue is empty. Cannot complete request." << endl;
    
}

void System::CDRWInterrupt(string cI)
{
    char holder = cI[1];
    int num = holder - '0';  
    //Dequeue from queue
    //Enqueue to Ready Queue
    if (CDRWs[num-1].isEmpty() == false)
    {
        cout << endl;
        cout << "CDRW request completed." << endl;
        cout << "Now sending process to Ready Queue." << endl;
        sendToReadyQueue(CDRWs[num-1].dequeue());
    }
    else
        cout << "Device queue is empty. Cannot complete request." << endl;
}

/********************************************************************/
void System::displayReadyQueue()
{
    systemReadyQueue.displayStats();
}

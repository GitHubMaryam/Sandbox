#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H
// UMSATS - CDH Scheduler 
//
// File Description:
//   Implements the interface for the main CAN traffic manager.
//
// History
// 2018-05-12 by Tamkin Rahman
// - Created.

#include "PeriodicTaskRunner.h"

// -----------------------------------------------------------------------------------------------
// ----------------------- STRUCTURES AND STRUCTURE TYPEDEFS -------------------------------------
// -----------------------------------------------------------------------------------------------
typedef union
{
    unsigned char bytes[8];
} BytesData;

typedef struct 
{
    unsigned int id;
    int extended;
    unsigned char length;
    BytesData data;
} CAN_Message;

extern SemaphoreHandle_t canRxQueueLock;
extern SemaphoreHandle_t canTxQueueLock;

// -----------------------------------------------------------------------------------------------
// ----------------------- FUNCTION PROTOTYPES ---------------------------------------------------
// -----------------------------------------------------------------------------------------------

//------------
// Function Description: The task that initializes and runs the CAN manager.
void CANManager(void *pvParameters);

// Function Description: The task that monitors the CAN bus for received messages, transmits messages in the TX queue,
//                       and passes messages to/from the CAN manager.
void CANMonitor(void *pvParameters);

//------------
// Function Description: Add the given message to the internal RX queue. If a failure occurs, return 0.
int AddToRXQueue(CAN_Message * message);

// Function Description: Add the given message to the internal TX queue. If a failure occurs, return 0.
int AddToTXQueue(CAN_Message * message);

// Function Description: Get the next message to transmit. If there is no message to transmit, return 0.
int GetNextCANTXMessage(CAN_Message * message);

#endif // CAN_MANAGER_H
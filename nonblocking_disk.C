/*
     File        : nonblocking_disk.c

     Author      : 
     Modified    : 

     Description : 

*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "assert.H"
#include "utils.H"
#include "console.H"
#include "nonblocking_disk.H"
/* Added this to have access to the system scheduler*/
#include "system.H"

/*--------------------------------------------------------------------------*/
/* CONSTRUCTOR */
/*--------------------------------------------------------------------------*/

NonBlockingDisk::NonBlockingDisk(unsigned int _size) 
  : SimpleDisk(_size) {
}

void NonBlockingDisk::wait_while_busy() {
  /*While the disk is busy*/
  while(is_busy()){
    /*Put the current thread in the scheduler’s ready queue*/
    System::SCHEDULER->resume(Thread::CurrentThread());
    /*Give up the CPU*/
    Console::puts("[disk debug] Disk busy; thread yielding.\n");
    System::SCHEDULER->yield();
    Console::puts("[disk debug] Disk thread resumed.\n");
  }
  Console::puts("[disk debug] Disk ready; continuing.\n");
}


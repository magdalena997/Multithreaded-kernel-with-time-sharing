#include"Thread.h"

#include "PCB.h"
#include"SCHEDULE.h"
#include <iostream.h>
extern volatile int zahtevana_promena_konteksta=0;




Thread::Thread(StackSize stackSize, Time timeSlice){
#ifndef BCC_BLOCK_IGNORE
	lock
	myPCB=new PCB(stackSize, timeSlice, this);
	unlock
#endif

}

Thread::~Thread(){
#ifndef BCC_BLOCK_IGNORE
	asm pushf
	asm cli

	delete myPCB;

	asm popf
#endif

}

void Thread::sleep(Time timetoSleep){
#ifndef BCC_BLOCK_IGNORE
	lock
	if(timetoSleep>0){
			PCB::running->timetoSleep=timetoSleep;
			PCB::running->status=blokirane;
			PCB::uspavane->dodaj(PCB::running);
			zahtevana_promena_konteksta=1;
			asm int 8h
	}
	unlock
#endif
}

void Thread::start(){
#ifndef BCC_BLOCK_IGNORE
	lock
	if(myPCB!=0){
		myPCB->startovan=1;
		myPCB->status=spreman; //ready
		Scheduler::put(myPCB);
	}


	unlock
#endif
}

void dispatch(){
#ifndef BCC_BLOCK_IGNORE
	asm pushf
	asm cli
	zahtevana_promena_konteksta=1;
	asm int 08h
	asm popf
#endif
}

void Thread::waitToComplete() {
#ifndef BCC_BLOCK_IGNORE
	lock
	if(myPCB){
		if(!(myPCB->status==zavrsen) && myPCB->startovan){
			PCB::running->status=blokirane;
			myPCB->cekajuce->dodaj(PCB::running);
			zahtevana_promena_konteksta=1;
			asm int 8h
		}
	}
unlock

#endif

}








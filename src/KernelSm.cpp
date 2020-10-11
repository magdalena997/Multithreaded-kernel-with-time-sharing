#include"Thread.h"
#include"semaphor.h"
#include "queue.h"
#include "SCHEDULE.H"
#include "stdio.h"
#include "iostream.h"

#include "KernelSm.h"

#include "PCB.h"
extern volatile int zahtevana_promena_konteksta;

#ifndef BCC_BLOCK_IGNORE

KernelSem::KernelSem(int init){
	lock
	vrednost=init;
	lista=new Queue();
	unlock
}




void KernelSem::signal(){
	lock
	if((vrednost++<0)){
		PCB* pom=lista->uzmi();
		pom->status=spreman;
		Scheduler::put(pom);

	}
	unlock
}

int KernelSem::wait(int toBlock){

	if(toBlock != 0){
		vrednost --;
		if(vrednost<0){
			lista->dodaj(PCB::running);
			PCB::running->status=blokirane;
			zahtevana_promena_konteksta=1;
			asm int 8h
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if(vrednost<=0)
			return -1;
		else{
			vrednost--;
			return 0;
		}
	}
}
#endif

KernelSem::~KernelSem(){
	delete lista;
}

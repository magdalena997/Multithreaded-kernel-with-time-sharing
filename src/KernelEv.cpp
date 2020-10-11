#include "event.h"
#include "KernelEv.h"

#include "PCB.h"
#include "IVTEntry.h"
#include"SCHEDULE.h"

extern volatile int zahtevana_promena_konteksta;

KernelEv::KernelEv(IVTNo en){
	vrednost=0;
	pcb=PCB::running;
	entry=IVTEntry::getIVTentry(en);
	entry->event=this;
}

KernelEv::~KernelEv(){
	entry->event=0;
	if(vrednost){
		pcb->status=spreman;
		Scheduler::put(pcb);
		vrednost=0; //menjano
	}
}

void KernelEv::signal(){
	if(vrednost){
		pcb->status=spreman;
		Scheduler::put(pcb);
		vrednost=0;

	}
}

void KernelEv::wait(){
	if(PCB::running==pcb){
		PCB::running->status=blokirane;
		vrednost=1;
		zahtevana_promena_konteksta=1;
	    asm int 8h
	}
}

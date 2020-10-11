
#include<stdio.h>
#include<dos.h>
#include"PCB.h"
#include"Thread.h"
#include"Queue.h"
#include"SCHEDULE.h"
#include"Idle.h"
#include <iostream.h>

#include <stdlib.h>


#include<conio.h>



PCB* PCB::running=0;
Queue* PCB::uspavane=new Queue();


volatile unsigned tsp,tss,tbp;
volatile int brojac=0;

Thread* idle=new Idle();
extern void tick();

ID PCB::IDcnt=0;

extern volatile int zahtevana_promena_konteksta;

PCB::PCB(StackSize stackSizee, Time timeSlicee, Thread* thread){
#ifndef BCC_BLOCK_IGNORE
	lock
	myThread=thread;

	cekajuce=new Queue();

	PID=IDcnt++;
	startovan=0;



	this->kvant=timeSlicee;
	status=kreiran;
	timetoSleep=0;

	if(stackSizee>=defaultStackSize){this->size=stackSizee;}     // minimalna vrednost je defaultStackSize tj 4096
		else{this->size=defaultStackSize; }
	stackSizee /=2;

	stek=new unsigned[stackSizee];
	stek[stackSizee-1]=0x200;

	stek[stackSizee-2]=FP_SEG(&(wrapper));
	stek[stackSizee-3]=FP_OFF(&(wrapper));
	sp=FP_OFF(stek+stackSizee-12);
	ss=FP_SEG(stek+stackSizee-12);
	bp=FP_OFF(stek+stackSizee-12);

	unlock
#endif
}

ID PCB::dohvID(){
	return PID;
}

PCB::PCB(){
	PCB::running->status=kreiran;
	kvant=0;
}
#ifndef BCC_BLOCK_IGNORE
PCB::~PCB(){

	lock
	delete stek;
	delete cekajuce;
	unlock

}



void PCB::exitThread(){

	lock
	cekajuce->pozovi();
	status=zavrsen;
	zahtevana_promena_konteksta=1;
	asm int 8h
	unlock
#endif
}
void PCB::sleep(Time time){
#ifndef BCC_BLOCK_IGNORE
	lock
	if(time>0){
		PCB::running->timetoSleep=time;
		PCB::running->status=blokirane;
		PCB::uspavane->dodaj(PCB::running);
		zahtevana_promena_konteksta=1;
		asm int 8h

	}
	unlock
#endif
}





void PCB::wrapper(){
	PCB::running->myThread->run();
	PCB::running->exitThread();
}

void interrupt timer(){
	if (!zahtevana_promena_konteksta) {
		tick();
		brojac--;
		if(PCB::uspavane) PCB::uspavane->probudi();
		}
	if (brojac == 0 || zahtevana_promena_konteksta) {

	asm {
		mov tsp, sp
		mov tss, ss
		mov tbp, bp
	}
	PCB::running->bp=tbp;
	PCB::running->sp = tsp;
	PCB::running->ss = tss;
	if(!(PCB::running->status==zavrsen ||PCB::running->status==blokirane)){
		Scheduler::put(PCB::running);
	}

	PCB::running= Scheduler::get();

	if(PCB::running==0){

		idle->start();
		PCB::running=Scheduler::get();


	}


	tbp=PCB::running->bp;
	tsp = PCB::running->sp;
	tss = PCB::running->ss;
	brojac =PCB::running->kvant;

#ifndef BCC_BLOCK_IGNORE
	asm {
		mov bp, tbp
		mov sp, tsp
		mov ss, tss
	}
	}
	if(!zahtevana_promena_konteksta) asm int 60h;
#endif
	if(brojac<0) brojac=0;
	zahtevana_promena_konteksta = 0;



}

#include "SCHEDULE.H"

#include "Queue.h"

#include "PCB.h"

void Queue::dodaj(PCB* p){
	Elem* novi=new Elem(p);
	if(!prvi) prvi=novi;
	else{
		Elem* pom=prvi;
		while(pom->next) pom=pom->next;
		pom->next=novi;
	}
	br++;
}

int Queue::duz() const{
	return br;
}

PCB* Queue::uzmi(){
	if(!prvi) return 0;
	PCB* p=prvi->pcb;
	Elem* pom=prvi;
	prvi=prvi->next;
	delete pom;
	br--;
	if(br==0)
		prvi=0;
	return p;
}

void Queue::prazni(){
	while(prvi) {Elem* pom=prvi; prvi=prvi->next; delete pom; }
	prvi=0;
	br=0;
}

Queue::~Queue(){
	prazni();
}

void Queue::pozovi(){
	PCB* pom=uzmi();
	while(pom!=0){
		pom->status=spreman;
		Scheduler::put(pom);
		pom=uzmi();
	}
}

void Queue::probudi(){
	int n=duz();
	PCB* pom=0;
	for(int i=0;i<n;i++){
		pom=uzmi();
		if((--pom->timetoSleep)==0){
			pom->status=spreman;
			Scheduler::put(pom);
		}
		else{
			dodaj(pom);
		}
	}
}

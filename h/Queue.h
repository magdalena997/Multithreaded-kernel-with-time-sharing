#ifndef QUEUE_H_

#define QUEUE_H_

#include "PCB.h"

class Queue{
private:
	struct Elem{
		PCB*  pcb;
		Elem* next;
		Elem(PCB* p){
			pcb=p;
			next=0;
		}
		~Elem(){
			pcb=0;
			next=0;
		}

	};
	Elem* prvi;
	int br;
public:
	friend class Semaphore;
	friend class KernelSem;
	Queue(){prvi=0; br=0;}
	~Queue();
	void dodaj(PCB* pcb);
	PCB* uzmi();
	void prazni();
	int duz() const;
	void pozovi();
	void probudi();
};

#endif

#ifndef PCB_H_

#define PCB_H_

#include"sys.h"
#include"Queue.h"
#include"Thread.h"
#include"SCHEDULE.h"
#include<dos.h>
#include<conio.h>



class Queue;

class PCB{
public:
	PCB(StackSize stackSizee, Time timeSlicee, Thread* thread);
	PCB();
	Status status;
	static PCB* running;
	void exitThread();
	void sleep(Time time);
	static void wrapper();
	~PCB();
	ID dohvID();
	ID PID;
	int startovan;


private:
	friend void interrupt timer();
	friend class Queue;
	friend class Thread;
	static ID IDcnt;

	Thread* myThread;
	unsigned* stek;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	Time kvant;
	Time timetoSleep;
	StackSize size;
	Queue* cekajuce;
	static Queue* uspavane;




};

#endif

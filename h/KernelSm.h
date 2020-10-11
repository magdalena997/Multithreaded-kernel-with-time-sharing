#ifndef _KernelSem_h_
#define _KernelSem_h_


#include"Queue.h"


class KernelSem{
private:
	Queue* lista;
	int vrednost;
public:
	KernelSem (int init=1);
	~KernelSem ();
	friend class Semaphore;
	int wait (int toBlock);
	void signal();

	int val () const {return vrednost;}
};

#endif

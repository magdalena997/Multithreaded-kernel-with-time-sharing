#ifndef _KernelEv_h_
#define _KernelEv_h_

#include "PCB.h"
#include"IVTEntry.h"
#include"sys.h"

typedef unsigned char IVTNo;
class IVTEntry;

class KernelEv{
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();

	void wait();
	void signal();
private:
	friend class IVTEntry;
	IVTEntry* entry;
	PCB* pcb;
	int vrednost;

};

#endif

#ifndef _ivtentry_h_
#define _ivtentry_h_

#include"KernelEv.h"
#include"sys.h"


class KernelEv;

class IVTEntry{
private:
	PtrToIntr oldInterrupt;
	IVTNo entry;
	int callOld;
public:
	KernelEv* event;
	IVTEntry(IVTNo num, PtrToIntr newInterrupt, int old);
	~IVTEntry();
	void callOldRoutine();
	void signal();
	static IVTEntry* getIVTentry(IVTNo n);
	static IVTEntry* IVT[256];
};








#endif

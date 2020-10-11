#include"event.h"
#include"KernelEv.h"



Event::Event(IVTNo ivtNo){
#ifndef BCC_BLOCK_IGNORE
	lock
	myImpl=new KernelEv(ivtNo);
	unlock
#endif

}

Event::~Event(){
#ifndef BCC_BLOCK_IGNORE
	lock
	delete myImpl;
	unlock
#endif
}

void Event::signal(){
#ifndef BCC_BLOCK_IGNORE
	lock
	if(myImpl!=0) myImpl->signal();
	unlock
#endif
}

void Event::wait(){
#ifndef BCC_BLOCK_IGNORE
	lock
	if (myImpl!=0) myImpl->wait();
	unlock
#endif
}


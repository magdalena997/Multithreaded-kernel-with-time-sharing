#include "Thread.h"
#include "sys.h"
#include "Idle.h"
#include "SCHEDULE.h"
#include "Queue.h"
#include<conio.h>
#include"semaphor.h"
#include"event.h"
#include <iostream.h>
#include <stdio.h>

#include "user.h"
#include "PCB.h"





extern int userMain (int argc, char* argv[]);


int vred;





int main(int argc, char* argv[]){
	inic();
	PCB * p=new PCB();
	PCB::running=p;

	vred= userMain(argc, argv);


	cout<<"USPEH";
	restore();
	return vred;
}

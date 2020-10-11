#include"sys.h"
#include"SCHEDULE.H"
#include<stdio.h>
#include<iostream.h>
#include "PCB.h"

unsigned oldTimerOFF, oldTimerSEG;

void inic(){
	asm {cli

		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax,word ptr es:0022h
		mov word ptr oldTimerSEG,ax

		mov ax,word ptr es:0020h
	    mov word ptr oldTimerOFF,ax



		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer



		mov ax,oldTimerSEG
		mov word ptr es:0182h, ax
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax



		pop ax
		pop es



		sti;

		}

}

void restore(){



	asm {cli

	     push es

		 push ax



		 mov ax,0

		 mov es,ax



		 mov ax,word ptr oldTimerSEG

		 mov word ptr es:0022h,ax

		 mov ax, word ptr oldTimerOFF

		 mov word ptr es:0020h, ax



		 pop ax

		 pop es

		 sti

	}



}



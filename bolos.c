#include <unistd.h>
#include <signal.h> 
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#define CADENA 80


void nonada(){}

void arbol( int retornoB, int retornoC, int estadoE, int estadoI, int estadoH) {

			
	char arbol[500],A,B,C,D,E,F,G,H,I,J;

	A = '-'; B = 'B'; C = 'C'; D='D'; E='E'; F='F';G='G';H='H';I='I';J='J';	

	if(retornoB == 0){
		B = '-';
	} else if (retornoB == 1){
		B = '-'; D = '-';
	} else if (retornoB == 2){
		B = '-'; D = '-'; G=' ';
	} else {
		B = 'B'; D='D';G='G';
	}
	
	if(retornoC == 0){
		C = '-';
	}
	else if (retornoC == 1){
		C = '-'; F = '-';
	}
	else if (retornoC == 2){
		C = '-'; F = '-'; J='-';
	} else {
		C = 'C'; F='F'; J='J';
	}
	
	if(estadoE == 0){ 
		E = 'E'; 
	} 
	if(estadoE == 1){ 
		E = '-';
	} 
	if(estadoH == 0){ 
		H = 'H';
	}  
	if(estadoH == 1){ 
		H = '-';
	} 
	if(estadoI == 0){ 
		I = 'I';
	} 
	if(estadoI == 1){ 
		I = '-';
	} 
	
	sprintf(arbol, "\n\t\t\t\t%c\n\t\t\t%c\t\t%c\n\t\t%c\t\t%c\t\t%c\n\t%c\t\t%c\t\t%c\t\t%c\n",A, B, C, D, E, F, G, H, I, J);
	 
	write(1, arbol, strlen(arbol));

	return;
}

int main (int argc, char *argv[]){
	

int pidA, pidB, pidC, pidD, pidE, pidF, pidG, pidH, pidI, pidJ;
char pidAux1[5], pidAux2[5]; 
char matar[CADENA];
int estadoH, estadoI,  estadoE;
int retorno, status, retornoB, retornoC, valor;
int decision;
long int micro;
struct timeval tiempo;

sigset_t c_vacio, c_SIGTERM, c_viejo, c_sinSIGTERM;
struct sigaction act, oldact;
    
		
	
		if(strcmp(argv[0],"./bolos")==0){
		pidA = fork();
		if(pidA>0){
			//printf("Soy P al crear a A\n");
			sprintf(matar, "Para lanzar la bola escribe en la terminal 'kill %d'\n ", getpid() + 1);
			write(1, matar, strlen(matar));
			
		}else{
			//printf("Soy A\n");
			execl(argv[0],"A",argv[0],NULL);
			return 0;
		}
		
		
	}

	//Creamos hijos de A
	if (strcmp(argv[0],"A")==0){
		
		pidI = fork();
		if(pidI>0){
			//printf("Soy A al crear I\n");
		}else{
			//printf("Soy I\n");
			execl(argv[1],"I",argv[1],NULL);
		}
	
		
		pidH = fork();
		if(pidH>0){
			//printf("Soy A al crear H\n");
		}else{
			//printf("Soy H\n");
			execl(argv[1],"H",argv[1],NULL);
		}
		
		
		pidE = fork();
		if(pidE>0){
			
			//printf("Soy A al crear E\n");
		}else{
			//printf("Soy E\n");
			sprintf(pidAux1, "%d", pidH);
			sprintf(pidAux2, "%d", pidI);
			execl(argv[1],"E",argv[1],pidAux1,pidAux2,NULL);
		}

			pidC = fork();
		if(pidC>0){
			//printf("Soy A al crear C\n");
		}else{
			
			//printf("Soy C\n");
			sprintf(pidAux1, "%d", pidE);
			sprintf(pidAux2, "%d", pidI);
			execl(argv[1],"C",argv[1],pidAux1,pidAux2,NULL);
		}
	
		
		pidB = fork();
		if(pidB>0){
			//printf("Soy A al crear B\n");
			sigemptyset(&c_SIGTERM);
			sigaddset(&c_SIGTERM,SIGTERM);
			sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);
		}else{
			
			//printf("Soy B\n");
			sprintf(pidAux1, "%d", pidE);
			sprintf(pidAux2, "%d", pidH);
			execl(argv[1],"B",argv[1],pidAux1,pidAux2,NULL);
		}
		
		c_sinSIGTERM = c_viejo;
		sigdelset(&c_sinSIGTERM,SIGTERM);
		sigemptyset(&c_vacio);

		act.sa_handler = nonada;
		act.sa_mask = c_vacio;
		act.sa_flags=0;
		sigaction(SIGTERM,&act,&oldact);

		sigsuspend(&c_sinSIGTERM);

		gettimeofday(&tiempo,NULL);
		micro = tiempo.tv_usec;
   		decision = micro%4;

   		if(decision == 0){
   				return 0;
   		}
   		if(decision == 1){
   			kill(pidB,SIGTERM);

   			retorno = waitpid(pidB,&retornoB,0);
   		}

   		if(decision == 2){
   			kill(pidC,SIGTERM);

   			retorno = waitpid(pidC,&retornoC,0);
   		}
   		if(decision == 3){
   			kill(pidC,SIGTERM);
   			kill(pidB,SIGTERM);

   			retorno = waitpid(pidC,&retornoC,0);
   			retorno = waitpid(pidB,&retornoB,0);
   		}

   		//printf("Decision A: %d\n",decision);

   		sleep(4);

   		if(waitpid(pidH,&valor,WNOHANG) == pidH){ //Lo coge si no ocupa CPU
					 	   estadoH = 1; 
					 } else {
					 	estadoH = 0; 
					 	
					 }
		if(waitpid(pidE,&valor,WNOHANG) == pidE){
					 	   estadoE = 1; 
					 } else {
					 	estadoE = 0; 
					 	
					 }
		if(waitpid(pidI,&valor,WNOHANG) == pidI){
					 	   estadoI = 1; 
					 } else {
					 	estadoI = 0; 
					 	
					 }
		
		arbol(WEXITSTATUS(retornoB),WEXITSTATUS(retornoC),estadoE,estadoI,estadoH);

		
		
		
		execl("/bin/ps","ps","-f",NULL);
		

		//Para matar todos los procesos usamos kill(0,SIGINT);
		//No sabemos como mandar la señal kill(0,SIGINT) despues de sacar el ps -f por pantalla.		
				
		
		
		return 0;
	}
	
	if (strcmp(argv[0],"B")==0){


			pidD = fork();
			if(pidD>0){
				//printf("Soy B al crear D\n");
				sigemptyset(&c_SIGTERM);
				sigaddset(&c_SIGTERM,SIGTERM);
				sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);

			
			}else{
				//printf("Soy D");
				execl("./bolos","D",argv[1],argv[3],NULL);
			}

			c_sinSIGTERM = c_viejo;
			sigdelset(&c_sinSIGTERM,SIGTERM);
			sigemptyset(&c_vacio);

			act.sa_handler = nonada;
			act.sa_mask = c_vacio;
			act.sa_flags=0;
			sigaction(SIGTERM,&act,&oldact);

			sigsuspend(&c_sinSIGTERM);

			pidE = atoi(argv[2]);

			//printf("Decision B: %d\n",decision);
			gettimeofday(&tiempo,NULL);
			micro = tiempo.tv_usec;
   			decision = micro%4;
   			if(decision == 0){
   				return 0;
   			}
   			if(decision == 1){
   				kill(pidD,SIGTERM);

   				retorno = waitpid(pidD,&status,0);
   				return WEXITSTATUS(status) + 1;
   			}

   			if(decision == 2){
   				kill(pidE,SIGTERM);

   				return 0;
   			}
   			if(decision == 3){
   				kill(pidD,SIGTERM);
   				kill(pidE,SIGTERM);

   				retorno = waitpid(pidD,&status,0);
   				return WEXITSTATUS(status) + 1;
   			}
   			
	}
	
	if (strcmp(argv[0],"C")==0){

		pidF = fork();
		if(pidF>0){
			//printf("Soy C al crear a F\n");	
			sigemptyset(&c_SIGTERM);
			sigaddset(&c_SIGTERM,SIGTERM);
			sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);
		}else{
			//printf("Soy F");
			execl("./bolos","F",argv[1],argv[3],NULL);

		}

		c_sinSIGTERM = c_viejo;
		sigdelset(&c_sinSIGTERM,SIGTERM);
		sigemptyset(&c_vacio);

		act.sa_handler = nonada;
		act.sa_mask = c_vacio;
		act.sa_flags=0;
		sigaction(SIGTERM,&act,&oldact);

		sigsuspend(&c_sinSIGTERM);

		pidE = atoi(argv[2]);

			gettimeofday(&tiempo,NULL);
			micro = tiempo.tv_usec;
   			decision = micro%4;
   			if(decision == 0){
   				return 0;
   			}
   			if(decision == 1){

   				kill(pidE,SIGTERM);

   				return 0;
   			}
   			if(decision == 2){
   				kill(pidF,SIGTERM);

   				retorno = waitpid(pidD,&status,0);
   				return WEXITSTATUS(status) + 1;
   			}
   			if(decision == 3){
   				kill(pidE,SIGTERM);
   				kill(pidF,SIGTERM);

   				retorno = waitpid(pidF,&status,0);
   				return WEXITSTATUS(status) + 1;
   			}
   			//printf("Decision C: %d\n",decision);

	}

	if (strcmp(argv[0],"D")==0){

		pidG = fork();
		if(pidG>0){
			//printf("Soy D al crear a G\n");	
			sigemptyset(&c_SIGTERM);
			sigaddset(&c_SIGTERM,SIGTERM);
			sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);
		}else{
			//printf("Soy G");
			execl("./bolos","G",argv[1],NULL);

		}

		c_sinSIGTERM = c_viejo;
		sigdelset(&c_sinSIGTERM,SIGTERM);
		sigemptyset(&c_vacio);

		act.sa_handler = nonada;
		act.sa_mask = c_vacio;
		act.sa_flags=0;
		sigaction(SIGTERM,&act,&oldact);

		sigsuspend(&c_sinSIGTERM);

		pidH = atoi(argv[2]);

		gettimeofday(&tiempo,NULL);
			micro = tiempo.tv_usec;
   			decision = micro%4;
   			if(decision == 0){
   				return 0;
   			}
   			if(decision == 1){

   				kill(pidH,SIGTERM);

   				return 0;
   			}
   			if(decision == 2){
   				kill(pidG,SIGTERM);

   				retorno = waitpid(pidD,&status,0);
   				return WEXITSTATUS(status) + 1;
   			}
   			if(decision == 3){
   				kill(pidG,SIGTERM);
   				kill(pidH,SIGTERM);

   				retorno = waitpid(pidG,&status,0);
   				return WEXITSTATUS(status) + 1;
   			}


	}

	if (strcmp(argv[0],"E")==0){

		sigemptyset(&c_SIGTERM);
		sigaddset(&c_SIGTERM,SIGTERM);
		sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);

		c_sinSIGTERM = c_viejo;
		sigdelset(&c_sinSIGTERM,SIGTERM);
		sigemptyset(&c_vacio);

		act.sa_handler = nonada;
		act.sa_mask = c_vacio;
		act.sa_flags=0;
		sigaction(SIGTERM,&act,&oldact);

		sigsuspend(&c_sinSIGTERM);

		pidH = atoi(argv[2]);
		pidI = atoi(argv[3]);
		gettimeofday(&tiempo,NULL);
			micro = tiempo.tv_usec;
   			decision = micro%4;
   			if(decision == 0){
   				return 0;
   			}
   			if(decision == 1){

   				kill(pidH,SIGTERM);

   				return 1;
   			}
   			if(decision == 2){
   				kill(pidI,SIGTERM);

   				return 1;
   			}
   			if(decision == 3){
   				kill(pidI,SIGTERM);
   				kill(pidH,SIGTERM);

   				return 2;
   			}
   			printf("Decision E: %d\n",decision);

	}

	if (strcmp(argv[0],"F")==0){

		pidJ = fork();
		if(pidJ>0){
			//printf("Soy F al crear a J\n");	
			sigemptyset(&c_SIGTERM);
			sigaddset(&c_SIGTERM,SIGTERM);
			sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);
		}else{
			//printf("Soy J");
			execl("./bolos","J",argv[1],NULL);

		}

		c_sinSIGTERM = c_viejo;
		sigdelset(&c_sinSIGTERM,SIGTERM);
		sigemptyset(&c_vacio);

		act.sa_handler = nonada;
		act.sa_mask = c_vacio;
		act.sa_flags=0;
		sigaction(SIGTERM,&act,&oldact);

		sigsuspend(&c_sinSIGTERM);

		pidI = atoi(argv[2]);

			gettimeofday(&tiempo,NULL);
			micro = tiempo.tv_usec;
   			decision = micro%4;
   			if(decision == 0){
   				return 0;
   			}
   			if(decision == 1){

   				kill(pidJ,SIGTERM);

   				retorno = waitpid(pidJ,&status,0);

   				return WEXITSTATUS(status)+1;
   			}
   			if(decision == 2){
   				kill(pidI,SIGTERM);
   				return 0;
   			}
   			if(decision == 3){
   				kill(pidJ,SIGTERM);
   				kill(pidI,SIGTERM);

   				retorno = waitpid(pidJ,&status,0);
   				return WEXITSTATUS(status) + 1;
   			}
   			printf("Decision F: %d\n",decision);

	}

	if (strcmp(argv[0],"G")==0){

		sigemptyset(&c_SIGTERM);
		sigaddset(&c_SIGTERM,SIGTERM);
		sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);

		c_sinSIGTERM = c_viejo;
		sigdelset(&c_sinSIGTERM,SIGTERM);
		sigemptyset(&c_vacio);

		act.sa_handler = nonada;
		act.sa_mask = c_vacio;
		act.sa_flags=0;
		sigaction(SIGTERM,&act,&oldact);

		sigsuspend(&c_sinSIGTERM);
	}
	if (strcmp(argv[0],"H")==0){

		sigemptyset(&c_SIGTERM);
		sigaddset(&c_SIGTERM,SIGTERM);
		sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);

		c_sinSIGTERM = c_viejo;
		sigdelset(&c_sinSIGTERM,SIGTERM);
		sigemptyset(&c_vacio);

		act.sa_handler = nonada;
		act.sa_mask = c_vacio;
		act.sa_flags=0;
		sigaction(SIGTERM,&act,&oldact);

		sigsuspend(&c_sinSIGTERM);
	}
	if (strcmp(argv[0],"I")==0){

		sigemptyset(&c_SIGTERM);
		sigaddset(&c_SIGTERM,SIGTERM);
		sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);

		c_sinSIGTERM = c_viejo;
		sigdelset(&c_sinSIGTERM,SIGTERM);
		sigemptyset(&c_vacio);

		act.sa_handler = nonada;
		act.sa_mask = c_vacio;
		act.sa_flags=0;
		sigaction(SIGTERM,&act,&oldact);

		sigsuspend(&c_sinSIGTERM);
	}
	if (strcmp(argv[0],"J")==0){

		sigemptyset(&c_SIGTERM);
		sigaddset(&c_SIGTERM,SIGTERM);
		sigprocmask(SIG_BLOCK,&c_SIGTERM,&c_viejo);

		c_sinSIGTERM = c_viejo;
		sigdelset(&c_sinSIGTERM,SIGTERM);
		sigemptyset(&c_vacio);

		act.sa_handler = nonada;
		act.sa_mask = c_vacio;
		act.sa_flags=0;
		sigaction(SIGTERM,&act,&oldact);

		sigsuspend(&c_sinSIGTERM);
	}	
	

	return 0;
	
	
}

#include <stdio.h>      // libreria estandar
#include <stdlib.h>     // para usar exit y funciones de la libreria standard
#include <string.h>
#include <pthread.h>    // para usar threads
#include <semaphore.h>  // para usar semaforos
#include <unistd.h>


#define LIMITE 50

//creo estructura de semaforos 
struct semaforos {
	sem_t sem_mezclar;
	sem_t sem_salar;
	sem_t sem_hornear;
	sem_t sem_armarmedallon;
	sem_t sem_cortarmore;
	sem_t sem_cocinar;
	sem_t sem_armarhamburguesa;
	sem_t sem_ganador;   
	//poner demas semaforos aqui
};

//creo los pasos con los ingredientes
struct paso {
   char accion [LIMITE];
   char ingredientes[4][LIMITE];

   
};

//creo los parametros de los hilos 
struct parametro {
 int equipo_param;
 struct semaforos semaforos_param;
 struct paso pasos_param[8];
};

//funcion para imprimir las acciones y los ingredientes de la accion
void* imprimirAccion(void *data, char *accionIn) {
	struct parametro *mydata = data;
	FILE *log;
	log=fopen("logreceta.txt","a");
	//calculo la longitud del array de pasos 
	int sizeArray = (int)( sizeof(mydata->pasos_param) / sizeof(mydata->pasos_param[0]));
	//indice para recorrer array de pasos 
	int i;
	for(i = 0; i < sizeArray; i ++){
		//pregunto si la accion del array es igual a la pasada por parametro (si es igual la funcion strcmp devuelve cero)
		if(strcmp(mydata->pasos_param[i].accion, accionIn) == 0){
		printf("\n\tEquipo %d - accion %s \n " , mydata->equipo_param, mydata->pasos_param[i].accion);
		fprintf(log,"\n\tEquipo %d - accion %s \n " , mydata->equipo_param, mydata->pasos_param[i].accion);
		//calculo la longitud del array de ingredientes
		int sizeArrayIngredientes = (int)( sizeof(mydata->pasos_param[i].ingredientes) / sizeof(mydata->pasos_param[i].ingredientes[0]) );
		//indice para recorrer array de ingredientes
		int h;
		printf("\tEquipo %d -----------ingredientes : ----------\n",mydata->equipo_param);
		fprintf(log,"\tEquipo %d -----------ingredientes : ----------\n",mydata->equipo_param); 
			for(h = 0; h < sizeArrayIngredientes; h++) {
				//consulto si la posicion tiene valor porque no se cuantos ingredientes tengo por accion 
				if(strlen(mydata->pasos_param[i].ingredientes[h]) != 0) {
							printf("\tEquipo %d ingrediente  %d : %s \n",mydata->equipo_param,h,mydata->pasos_param[i].ingredientes[h]);
							fprintf(log,"\tEquipo %d ingrediente  %d : %s \n",mydata->equipo_param,h,mydata->pasos_param[i].ingredientes[h]);
				}
			}
		}
	}fclose(log);
}

//funcion para tomar de ejemplo
void* cortar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "cortar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 20000 );
	//doy la señal a la siguiente accion (cortar me habilita mezclar y cortarmore)
    sem_post(&mydata->semaforos_param.sem_mezclar);
    sem_post(&mydata->semaforos_param.sem_cortarmore);
	
    pthread_exit(NULL);
}


void* mezclar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "mezclar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	
	//espero tener cortado antes de mezclar	
	sem_wait(&mydata->semaforos_param.sem_mezclar);
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 30000 );
	//libero mezclar
	sem_post(&mydata->semaforos_param.sem_mezclar);

	//doy la señal a la siguiente accion 
    sem_post(&mydata->semaforos_param.sem_salar);
	
    pthread_exit(NULL);
}




void* salar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "salar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//espero poder usar el salero	
	sem_wait(&mydata->semaforos_param.sem_salar);
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 50000 );
	//libero salero
	sem_post(&mydata->semaforos_param.sem_salar);
	//doy la señal a la siguiente accion 
    	sem_post(&mydata->semaforos_param.sem_armarmedallon);

    pthread_exit(NULL);
}


void* armarmedallon(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "armarmedallon";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;

	//espero ppara poder armar medallon	
	sem_wait(&mydata->semaforos_param.sem_armarmedallon);
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep(30000 );
	//libero medallon
	sem_post(&mydata->semaforos_param.sem_armarmedallon);
	

	//doy la señal a la siguiente accion 
    sem_post(&mydata->semaforos_param.sem_cocinar);
	
    pthread_exit(NULL);
}


void* cocinar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "cocinar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;

	//espero poder usar la plancha, ademas tener el medallon	
	sem_wait(&mydata->semaforos_param.sem_cocinar);	

	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 50000 );
	//libero cocinar
	sem_post(&mydata->semaforos_param.sem_cocinar);


	//doy la señal a la siguiente accion 
    sem_post(&mydata->semaforos_param.sem_armarhamburguesa);
	
    pthread_exit(NULL);
}

void* cortarmore(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "cortarmore";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;

	//espero se haya liberado cortar
	sem_wait(&mydata->semaforos_param.sem_cortarmore);	

	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 40000 );
	//libero cortarmore
	sem_post(&mydata->semaforos_param.sem_cortarmore);

	//doy la señal a la siguiente accion 
    sem_post(&mydata->semaforos_param.sem_armarhamburguesa);
	
    pthread_exit(NULL);
}


void* hornear(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "hornear";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;

	//espero poder usar el horno	
	sem_wait(&mydata->semaforos_param.sem_hornear);

	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 100000 );
	//libero hornear
	sem_post(&mydata->semaforos_param.sem_hornear);

	//doy la señal a la siguiente accion 
   	 sem_post(&mydata->semaforos_param.sem_armarhamburguesa);
	
    pthread_exit(NULL);
}



void* armar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "armar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;


	//espero tener la hamburguesa y por otro la lechuga y tomate	
	sem_wait(&mydata->semaforos_param.sem_cortarmore);
	sem_wait(&mydata->semaforos_param.sem_cocinar);	
	sem_wait(&mydata->semaforos_param.sem_hornear);
	sem_wait(&mydata->semaforos_param.sem_armarhamburguesa);

	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep(30000 );
	//libero
	sem_post(&mydata->semaforos_param.sem_cortarmore);
	sem_post(&mydata->semaforos_param.sem_cocinar);
	sem_post(&mydata->semaforos_param.sem_hornear);
	sem_post(&mydata->semaforos_param.sem_armarhamburguesa);
	sem_post(&mydata->semaforos_param.sem_ganador);

	
    pthread_exit(NULL);
}

void* ganador(void *data) {
	
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
        FILE *log;
	log=fopen("logreceta.txt","a");
	//espero la accion que termine de armar hamburguesa	
	
	sem_wait(&mydata->semaforos_param.sem_ganador);

	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	printf("El ganador es:\tEquipo%d \n", mydata->equipo_param);
	
	fprintf(log,"El ganador es:\tEquipo%d \n", mydata->equipo_param);
	exit(-1);
	
	pthread_exit(NULL);
	fclose(log);
}


void* ejecutarReceta(void *i) {
	

	//variables semaforos
	sem_t sem_mezclar;
        sem_t sem_salar;
        sem_t sem_hornear;
        sem_t sem_armarmedallon;
        sem_t sem_cortarmore;
        sem_t sem_cocinar;
        sem_t sem_armarhamburguesa;
	sem_t sem_ganador;
	//crear variables semaforos aqui
	
	//variables hilos
	pthread_t p1;
        pthread_t p2; 
	pthread_t p3;  
	pthread_t p4;
 	pthread_t p5; 	
	pthread_t p6; 	
	pthread_t p7; 
	pthread_t p8; 
	pthread_t p9; 
	//crear variables hilos aqui
	
	//numero del equipo (casteo el puntero a un int)
	int p = *((int *) i);
	
	printf("Ejecutando equipo %d \n", p);

	//reservo memoria para el struct
	struct parametro *pthread_data = malloc(sizeof(struct parametro));

	//seteo los valores al struct
	
	//seteo numero de grupo
	pthread_data->equipo_param = p;

	//seteo semaforos
	pthread_data->semaforos_param.sem_mezclar = sem_mezclar;
        pthread_data->semaforos_param.sem_salar = sem_salar;
        pthread_data->semaforos_param.sem_hornear = sem_hornear;
        pthread_data->semaforos_param.sem_armarmedallon = sem_armarmedallon;
        pthread_data->semaforos_param.sem_cortarmore = sem_cortarmore;
        pthread_data->semaforos_param.sem_cocinar = sem_cocinar;
        pthread_data->semaforos_param.sem_armarhamburguesa = sem_armarhamburguesa;
	pthread_data->semaforos_param.sem_ganador = sem_ganador;
           
	//setear demas semaforos al struct aqui
	

	//seteo las acciones y los ingredientes (Faltan acciones e ingredientes) ¿Se ve hardcodeado no? ¿Les parece bien?


	FILE *fp;
	char buffer[LIMITE] = "";
		
	fp = fopen ("receta.txt","r");
	
	if (fp == NULL) 
		exit(1);
	else
	{
		
		//printf("\n %s \n",buffer);
		int j=0;
		while ((feof(fp) == 0) && (j<8))
			{
				fgets(buffer,LIMITE,fp);	

				//printf("\n %s \n",buffer);	
				int i = 0;
				char *accion = strtok(buffer," ");
				char *ingre = strtok(NULL,"-");
				strcpy(pthread_data->pasos_param[j].accion, accion);
				
				//printf("\n%d-%s\n",j,accion);
				while (ingre != NULL)
					{
						//printf("\n%s\n",ingre);
						strcpy(pthread_data->pasos_param[j].ingredientes[i],ingre);
						ingre = strtok(NULL,"-");

						i++;
					}
				j++;
			}
	}
	fclose(fp);

		
	
	//inicializo los semaforos

	sem_init(&(pthread_data->semaforos_param.sem_mezclar),0,0);
        sem_init(&(pthread_data->semaforos_param.sem_salar),0,0);
        sem_init(&(pthread_data->semaforos_param.sem_hornear),0,1);
        sem_init(&(pthread_data->semaforos_param.sem_armarmedallon),0,0);
        sem_init(&(pthread_data->semaforos_param.sem_cortarmore),0,0);
        sem_init(&(pthread_data->semaforos_param.sem_cocinar),0,0);
        sem_init(&(pthread_data->semaforos_param.sem_armarhamburguesa),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_ganador),0,0);

	//inicializar demas semaforos aqui


	//creo los hilos a todos les paso el struct creado (el mismo a todos los hilos) ya que todos comparten los semaforos 
	int rc;
	rc = pthread_create(&p1,                           //identificador unico
                            NULL,                          //atributos del thread
                                cortar,            //funcion a ejecutar
                                pthread_data); 

	rc = pthread_create(&p2,                           //identificador unico
                            NULL,                          //atributos del thread
                                mezclar,             //funcion a ejecutar
                                pthread_data);
	rc = pthread_create(&p3,                           //identificador unico
                            NULL,                          //atributos del thread
                                salar,             //funcion a ejecutar
                                pthread_data);
	rc = pthread_create(&p4,                           //identificador unico
                            NULL,                          //atributos del thread
                                armarmedallon,             //funcion a ejecutar
                                pthread_data);
	rc = pthread_create(&p5,                           //identificador unico
                            NULL,                          //atributos del thread
                                hornear,             //funcion a ejecutar
                                pthread_data);
	rc = pthread_create(&p6,                           //identificador unico
                            NULL,                          //atributos del thread
                                cortarmore,             //funcion a ejecutar
                                pthread_data);
	rc = pthread_create(&p7,                           //identificador unico
                            NULL,                          //atributos del thread
                                cocinar,             //funcion a ejecutar
                                pthread_data);
	rc = pthread_create(&p8,                           //identificador unico
                            NULL,                          //atributos del thread
                                armar,             //funcion a ejecutar
                                pthread_data);

	rc = pthread_create(&p9,                           //identificador unico
                            NULL,                          //atributos del thread
                                ganador,             //funcion a ejecutar
                                pthread_data);

        
	//doy la señal a la siguiente accion 

            
	//crear demas hilos aqui
	
	
	//join de todos los hilos
	pthread_join (p1,NULL);
	pthread_join (p2,NULL);
	pthread_join (p3,NULL);
	pthread_join (p4,NULL);
	pthread_join (p5,NULL);
	pthread_join (p6,NULL);
	pthread_join (p7,NULL);
	pthread_join (p8,NULL);
	pthread_join (p9,NULL);
	
	//crear join de demas hilos


	//valido que el hilo se alla creado bien 
    if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     }


 
	//destruccion de los semaforos 
	sem_destroy(&sem_mezclar);
        sem_destroy(&sem_salar);
        sem_destroy(&sem_hornear);
        sem_destroy(&sem_armarmedallon);
        sem_destroy(&sem_cortarmore);
        sem_destroy(&sem_cocinar);
        sem_destroy(&sem_armarhamburguesa);
 	sem_destroy(&sem_ganador);
	//destruir demas semaforos 
	
	//salida del hilo
	 pthread_exit(NULL);
}


int main ()
	
{
      

	//creo los nombres de los equipos 
	int rc;
	int *equipoNombre1 =malloc(sizeof(*equipoNombre1));
	int *equipoNombre2 =malloc(sizeof(*equipoNombre2));
	int *equipoNombre3 =malloc(sizeof(*equipoNombre3));
	*equipoNombre1 = 1;
	*equipoNombre2 = 2;
	*equipoNombre3 = 3;


	//creo las variables los hilos de los equipos
	pthread_t equipo1; 
	pthread_t equipo2;
	pthread_t equipo3;
 
	//inicializo los hilos de los equipos
    	rc = pthread_create(&equipo1,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre1); 
	


    	rc = pthread_create(&equipo2,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre2);


    	rc = pthread_create(&equipo3,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre3);



   	if (rc)
	{
       		printf("Error:unable to create thread, %d \n", rc);
       		exit(-1);
     	} 

	//join de todos los hilos
	pthread_join (equipo1,NULL);
	pthread_join (equipo2,NULL);
	pthread_join (equipo3,NULL);
	

    	pthread_exit(NULL);
}


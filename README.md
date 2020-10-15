Trabajo Práctico de Semáforos e Hilos

Sistemas Operativos y Redes




Profesores: Sosa, Noelia y  Vargas, Mariano. 



Alumno: Bálsamo, Cristian.



Comisión: Com1.



Año Lectivo: Segundo Semestre 2020.
Introducción:
El objetivo de este trabajo es poner en práctica algunos de los conceptos adquiridos en clases, a través de investigación sobre semáforos e hilos.


Pseudocódigo
Invocar las librerías que utilizaran en el resto del código.

Creamos el limite del buffer.
#define LIMITE 50

struct semáforos {
	Creo estructura de semáforos con los semáforos necesarios.
}

struct paso {
Creo la estructura paso con acciones e ingredientes
   }

struct parámetro {
creo los parámetros de los hilos
}



void* imprimirAccion() { En esta función imprimimos las lista de las acciones e ingredientes de cada uno además de generar un archivo log donde guarda los datos generados en pantalla.
Hago una llamada a struct parámetro y asignamos nuestros datos
FILE Uso FILE para declarar el puntero con el fin de apuntar al archivo desde el que queremos leer o escribir.
fopen (“Nombre de archivo.txt”,” parámetro”) Creamos archivo donde se guardará la información generada.
Calculo el largo del array de paso	
Agrego un  índice para recorrer array de pasos 
for(Recorremos el array  hasta que el valor sea menor a la longitud del array)
pregunto si la acción del array es igual a la pasada por parámetro (si es igual la función strcmp devuelve cero);
printf(Imprimo cada acción de cada equipo);
fprintf(nombre del puntero del archivo donde guardaremos nuestros datos, datos a guardar de acción);
Se calcula la longitud del array de ingredientes
Coloco un índice para recorrer array de ingredientes
printf(Imprime nombre de equipo y -----------ingredientes : ----------);
fprintf(nombre del puntero del archivo donde guardaremos nuestros datos, datos a guardar nombre de equipo y -----------ingredientes : ----------); 
Consulto si la posición tiene valor porque no sé cuántos ingredientes tengo por acción 
if(verificamos si el largo de los atributos del puntero son) != 0) 
printf(Imprimo nombre  de equipo e ingredientes);
fprintf(nombre del puntero del archivo donde guardaremos nuestros datos, datos a guardar nombre de equipo e ingredientes);
				
void* cortar(void *data) {Esta se encargada de habilitar la función mezclar y cortarmore.
Creo el nombre de la acción de la función y defino el tipo de atributo.
char *acción = "cortar";
Creamos el puntero para pasarle la referencia de memoria (data) del struct pasado por parámetro (la cual es un puntero). 
imprimirAccion(llamo a la función imprimir le paso el struct y la acción de la función);
usamos usleep para simular que pasa tiempo
Doy la señal a la siguiente acción (cortar me habilita mezclar y cortarmore)


void* mezclar(void *data) {Esta función permite mezclar los ingredientes cortados y habilita  salar.
Creamos  el nombre de la acción de la función 
char *acción = "mezclar";
Creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parámetro (la cual es un puntero). 
	
Llamo a la función imprimir le paso el struct y la acción de la función
Espero tener cortado antes de mezclar usando un sem_wait	
sem_wait(&mydata->semaforos_param.sem_mezclar);
llamo a la función imprimir, le paso el struct y la acción de la función
imprimirAccion(mydata,accion);
Uso usleep para simular que pasa tiempo
Libero mezclar
sem_post(&mydata->semaforos_param.sem_mezclar);

Doy la señal a la siguiente acción salar
sem_post(&mydata->semaforos_param.sem_salar);
Termino el hilo para que esté disponible nuevamente.
pthread_exit(NULL);

void* salar(void *data) {Esta función permite salar la mezcla, por lo que antes tuvo que cortar y mezclar, también habilita la función armarmedallon.
creamos el nombre de la acción de la función salar.
char *acción = "salar";
//creamos el puntero para pasarle la referencia de memoria (data) del struct pasado por parámetro (la cual es un puntero).
Espero poder usar el salero usando un sem_wait.	
sem_wait(&mydata->semaforos_param.sem_salar);
llamo a la función imprimir le paso el struct y la acción de la función
Uso sleep para simular que pasa tiempo
Libero salero con un sem_post
Doy la señal a la siguiente acción armarmedallon
Termino el hilo para que esté disponible nuevamente.
pthread_exit(NULL);
}


void* armarmedallon(void *data) {Esta función permite armar el medallón de carne después de haber mezclado y salado.
Creo el nombre de la acción de la función armarmedallon
char *acción = "armarmedallon";
Creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parámetro (la cual es un puntero). 
Espero para poder armar medallon	usando un sem_wait
Llamo a la función imprimir le paso el struct y la acción de la función
Uso usleep para simular que pasa tiempo
Libero medallón con un sem_post
Doy la señal a la siguiente acción cocinar con un sem_post. 
    
Termino el hilo para que esté disponible nuevamente.
pthread_exit(NULL);
}



void* cocinar(void *data) { Esta función permite cocinar el medallón después de armarlo.
Creo el nombre de la acción de la función cocinar. 
char *acción = "cocinar";
Creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parámetro (la cual es un puntero). 
Espero poder usar la plancha, ademas tener el medallón con un sem_wait	
Llamo a la función imprimir le paso el struct y la acción de la función
Uso usleep para simular que pasa tiempo
Libero cocinar  con un sem_post
sem_post(&mydata->semaforos_param.sem_cocinar);

Doy la señal a la siguiente acción con un sem_post a armarhamburguesa


Termino el hilo para que esté disponible nuevamente.
	
    pthread_exit(NULL);
}



void* cortarmore(void *data) {Esta función es diferente a la de cortar ya que corta otros ingredientes los cuales los usamos para armar la hamburguesa. Esta función habilita armarhamburguesa
Creo el nombre de la acción de la función 
char *acción = "cortarmore";
Creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parámetro (la cual es un puntero). 
struct parámetro *mydata = data;

Espero se haya liberado cortar con un sem_wait
sem_wait(&mydata->semaforos_param.sem_cortarmore);	
Llamo a la función imprimir le paso el struct y la acción de la función
Uso sleep para simular que que pasa tiempo
Libero cortar con un sem_post
Doy la señal a la siguiente acción armarHamburguesa

Termino el hilo para que esté disponible nuevamente.
    pthread_exit(NULL);
}

void* hornear(void *data) {
Creo el nombre de la acción de la función 
char *acción = "hornear";
Creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parámetro (la cual es un puntero). 
Espero poder usar el horno con sem_wait	
Llamo a la función imprimir le paso el struct y la acción de la función
Uso sleep para simular que que pasa tiempo
Libero horno con un sem_post
	
Doy la señal a la siguiente acción armarhamburguesa
Termino el hilo para que esté disponible nuevamente.
  pthread_exit(NULL);
}



void* armar(void *data) {Esta función permite armar la hamburguesa con todos los ingredientes manipulados en las funciones anteriores. También habilita a la función ganador.
Creo el nombre de la acción de la función armar
char *acción = "armar";
Creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parámetro (la cual es un puntero). 
Espero con un sem_wait tener la hamburguesa, por otro la lechuga, tomate y el pan.	
Llamo a la función imprimir le paso el struct y la acción de la función
	
Uso sleep para simular que pasa tiempo
Libero con un sem_post las funciones utilizadas para armar la hamburguesa.
	sem_post(&mydata->semaforos_param.sem_cortarmore);
	sem_post(&mydata->semaforos_param.sem_cocinar);
	sem_post(&mydata->semaforos_param.sem_hornear);
	sem_post(&mydata->semaforos_param.sem_armarhamburguesa);
	sem_post(&mydata->semaforos_param.sem_ganador);

Termino el hilo para que esté disponible nuevamente.
    pthread_exit(NULL);
}

void* ganador(void *data) {Esta función permite mostrar al ganador de los tres equipos. ósea al primero que arma la hamburguesa.
	
Creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parámetro (la cual es un puntero). 
struct parámetro *mydata = data;
        
Espero la acción que termine de armar hamburguesacon un sem_wait	
Llamo a la función imprimir le paso el struct y la acción de la función
printf(Imprimo la frase “El ganador es: y el nombre del equipo);
Termino la función con exit(parámetro)	
exit(-1);
	

Termino el hilo para que esté disponible nuevamente.
pthread_exit(NULL);
}


void* ejecutarReceta(void *i) {
Creo las variables semáforos
Creo la variable de los hilos
crear variables hilos aqui
Número del equipo (casteo el puntero a un int)
nt p = *((int *) i);
	
printf(Imprime el equipo que esta ejecutando el proceso);
Reservo memoria para el struct
struct parámetro *pthread_data = malloc(sizeof(struct parámetro));

Seteo numero de grupo
	pthread_data->equipo_param = p;

Seteo semáforos
	
Seteo las acciones y los ingredientes con la apertura de un archivo llamado receta.txt


	FILE *puntero;
	char buffer[LIMITE] = "";
		
	fp = fopen ("nombre de archivo.txt","parámetro de lectura");
	
	if (puntero == NULL) 
		exit(1);
	else
	{
		
		int j=0; inicializo contador en cero
while ((recorro hasta el final del archivo hasta que sea)== 0) && (j<8))
			{
				fgets(buffer,LIMITE,fp);	

				int i = 0; inicializo contador en cero
                                   	char *acción = strtok(buffer," "); 
 				Separo las acciones por espacios.
				char *ingre = strtok(NULL,"-");
Separo los ingredientes por guiones.
				strcpy(pthread_data->pasos_param[iteración de j].acción, acción);
				
			while (ingre diferente de = NULL) 
					{
						strcpy(pthread_data->pasos_param[iteración de j].ingredientes[iteración de i],ingre);
						ingre = strtok(NULL,"-");

						i++; incrementa valor de i en 1
					}
				j++;incrementa valor de j en 1
			}
	}
	fclose(fp); cierra el archivo abierto(puntero del archivo)

Inicializo todos los semáforos.
Creo los hilos a todos les paso el struct creado (el mismo a todos los hilos) ya que todos comparten los semáforos
Se crean los hilos de los procesos 
Hago un join de los hilos de cada proceso creado	
Valido que el hilo se halla creado bien 
    if (rc){
       printf("Muestro mensaje de error al crear el proceso”);
       exit(-1);Salgo de la función
Destruyo los semáforos una vez utilizados.
Salida del hilo
	 pthread_exit(NULL);
}






int main ()
	
{
      
Creo los nombres de los equipos los cuales son tres y le hago una asignación dinámica de memoria con malloc.
Creo las variables los hilos de los equipos
Inicializo los hilos de cada equipo 
Valido la creación de cada hilo.
   	if (rc)
	{
       		printf("Imprime error y el hilo, si el hilo no fue creado correctamente);
       		exit(-1); finaliza el programa
     	} 

	Hago un join de los hilos de cada equipo.
	
	Termino el hilo para que esté disponible nuevamente
    	pthread_exit(NULL);




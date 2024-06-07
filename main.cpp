#include <iostream>
#include <omp.h>
#include <ctime>

void parallel_sin_seccion_critica();
void parallel_con_seccion_critica();
void parallel_for();
void parallel_section();
void parallel_critical();
void parallel_atomic();


int main() {

    /*  Se busca comparar el funcionamiento entre parallel con y sin sección crítica*/
    //parallel_sin_seccion_critica();
    //parallel_con_seccion_critica();
    /*  Los resultados indican que sin sección crítica, se produce incoherencia en el resultado*/

    /*  Se presenta el funcionamiento del bucle for trabajando el paralelo*/
    //parallel_for();
    /**/

    /*  Se busca mostrar el funcionamiento de dos secciones paralelas en paralelo*/
    //parallel_section();
    /**/

    /*  Comparar critical con atomic*/
    parallel_critical();
    parallel_atomic();
    /*  Los resultados indican claramente que es más rápido utilizar atomic en vez de critical*/

}

void parallel_sin_seccion_critica(){
    int j = 0;
    /*
    * En este caso tenemos en parallel, en donde hace que el bloque entre corchetes que se encuentra debajo de el
    * trabaje en paralelo utilizando todos los hilos del procesador.
    * Es importante que los corchetes se encuentren debajo del #pragma
    * En este caso, al ejecutar se observará incoherencia en el resultado de j, ya que no estamos considerando
    * la sección crítica.
    */
#pragma omp parallel
    {
        for(int i=0; i<10; i++){
            j++;
        }
    }
    std::cout << "valor j = " << j << std::endl;
}

void parallel_con_seccion_critica(){
    int j = 0;
    /*
     * A diferencia del caso anterior, sí se considera sección crítica, por lo que no habrá incoherencia, sin embargo,
     * se observa que, cómo el parallel ejecuta la sentencia con cada uno de sus hilos, en mi caso 8 hilos, el resultado es 80.
    */
#pragma omp parallel
    {
        for(int i=0; i<10; i++){
#pragma omp critical
            {
                j++;
            }
        }
    }
    std::cout << "valor j = " << j << std::endl;
}

void parallel_for(){
    int j = 0;
    /*
     * Cuando tenemos un for, para evitar problemas como el anterior, debemos utilizar un "parallel for", en donde
     * tenemos que escribir "#pragma parallel for" encima del for correspondiente, y debemos quitar los corchetes.
    */
#pragma omp parallel for
        for(int i=0; i<10; i++) {
#pragma omp critical
            {
                j++;
            }
        }
    std::cout << "valor j = " << j << std::endl;
}

void parallel_section(){
    long j = 0;
#pragma omp parallel sections   //Se utiliza sections para cerrar el bloque de código que trabajará con varias secciones en paralelo
    {
#pragma omp section             //Primera sección en paralelo
        {
#pragma omp parallel for        //Bucle for que trabaja desde el inicio hasta la mitad
            for(int i=0; i<5; i++){
#pragma omp critical
                {
                    //std::cout << "section 1" << std::endl;
                    j++;
                }
            }
        }
#pragma omp section
        {
#pragma omp parallel for        //Bucle for que trabaja desde el fin hasta la mitad
            for(long t=10; t>5; t--){
#pragma omp critical
                {
                    //std::cout << "section 2" << std::endl;
                    j++;
                }
            }
        }
    }
    std::cout << "j = " << j << std::endl;
}

/*
 * Función paralela que contiene un for y que busca comparar critical con atomic
 */
void parallel_critical(){
    clock_t t;      //Declaramos el reloj r
    t = clock();    //Inicializamos el reloj
    long j = 0;

#pragma omp parallel for
    for(long i=0; i<100000000; i++){
#pragma omp critical
        {
            j++;
        }
    }
    t = clock() - t;
    std:: cout << "j = " << j << " time = " << t << std::endl;
}
void parallel_atomic(){
    clock_t r;      //Declaramos el reloj r
    r = clock();    //Lo inicializamos
    long j = 0;
#pragma omp parallel for
    for(long i=0; i<100000000; i++){
#pragma omp atomic
            j++;
    }
    r = clock() - r;    //Calculamos el tiempo
    std:: cout << "j = " << j << " time = " << r << std::endl;
}
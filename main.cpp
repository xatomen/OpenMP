#include <iostream>
#include <omp.h>

void parallel_sin_seccion_critica();
void parallel_con_seccion_critica();
void parallel_for();

int main() {

    parallel_sin_seccion_critica();

    parallel_con_seccion_critica();

    parallel_for();

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
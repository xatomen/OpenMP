#include <iostream>
#include <omp.h>

void parallel_sin_seccion_critica();

int main() {

    parallel_sin_seccion_critica();

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
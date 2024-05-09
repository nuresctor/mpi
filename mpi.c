#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char* argv[]) {

    double valor_real_pi = 3.14159265358979323846;
    int samples = 30000000; /* Valor por defecto */
    
    int rank;
    int count = 0;
    int mycount = 0; 
    double pi;
    int size;
    double x, y;
    int i;
    
    double inicio = MPI_Wtime();
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(rank);
    
    MPI_Bcast(&samples, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    for (i = 0; i < samples; ++i) {
        x = ((double)rand()) / ((double)RAND_MAX); // 0≤x≤1
        y = ((double)rand()) / ((double)RAND_MAX);
        if (x * x + y * y <= 1.0) {
            ++mycount;
        }
    }
    
    printf("Proceso %d tiene un conteo total de = %d\n", rank, mycount);
    
    MPI_Reduce(&mycount, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 
    
    double fin = MPI_Wtime();
    
    if (rank == 0) {
        pi = 4.0 * count / (samples * size); 
        printf("Cantidad de Iteraciones = %d, Pi estimado: %g \n", samples * size, pi);
        printf("TIEMPO DE EJECUCION = %lf s\n", fin-inicio);
    }
    
    MPI_Finalize();
    
    return 0;
}
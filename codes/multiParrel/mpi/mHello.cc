/* /home/juzhou/bin/mpirun -np 4 
*/


#include "mpi.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int main(int argc,char *argv[])
{
    int myid, numprocs;  
	

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);//get how many processes
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);//get current process index    

    cout << "total process is " << numprocs << endl;
	cout << "my index is " << myid << endl;
	pid_t pid = getpid();
	cout << "hello from " << pid << endl << endl;

    
    MPI_Finalize();
    return 0;
}


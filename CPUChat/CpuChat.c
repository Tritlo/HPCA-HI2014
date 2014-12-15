#include <mpi.h> 
#include <stdio.h> 
#include <string.h>
int main(argc,argv) int argc; char *argv[]; { 
	int numtasks, rank, dest, source, rc, count, tag=1; char inmsg, outmsg='x'; 
	char msg[140];
    int length = 140; //Same for all.
    char chatlog[4*140];
    int i;

	MPI_Status Stat; 
	MPI_Init(&argc,&argv); 
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    sprintf(msg,"Hello, I am rank %d\n",rank);

    sprintf(chatlog,"Chat Log:\n");

    int root = 0;
    dest = root;
    for(i = 1; i < numtasks; i++){
        source = i;
        if (rank == 0){
            // Rank 0 recieves the messages from all,
            // And broadcasts the entire thing to everybody.
            rc = MPI_Recv(&msg, length, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat); 
            strcat(chatlog,msg);
        } else {
            rc = MPI_Send(&msg, length, MPI_CHAR, dest, tag, MPI_COMM_WORLD); 

        }
        MPI_Bcast(&chatlog,4*length,MPI_CHAR,root,MPI_COMM_WORLD);
    }

    printf("I am rank %d, and the chat log was:\n", rank);
    printf("%s",chatlog);

    MPI_Finalize(); 

} 


/*
 * Description:
 * This is a simple example showing how processes can utilize BCast
 * to get the current state of some global object after each operation.
 * Here we see that on every iteration of the for loop, the root process
 * waits on one of the sub processes to send him a message, and then it 
 * concatenates that message to a chat log. It then broadcasts the new
 * chatlog.
 *
 * All the subprocesses send the root process a message, and then they
 * recieve an updated chatlog of all the messages that have been sent.
 * In this way, the processes can share a global state. 
 */

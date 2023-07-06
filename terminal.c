#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() 
{ 
    system ("/bin/stty raw");
    // ftok to generate unique key 

    key_t key1;
    
    if (-1 != open("/tmp/data", O_CREAT, 0777)) {
        key1 = ftok("/tmp/data", 0);
     } else {
        perror("open");
        exit(1);
    }
  
    int id1 = shmget(key1, 0x1000, IPC_CREAT | SHM_R | SHM_W);

    char *str = (char*) shmat(id1,0,0);

    char c;
    while((c=getchar())!= '.') {	
    	*str=c;
    }
      
    //detach from shared memory  
    shmdt(str); 
    
    // destroy the shared memory 
    shmctl(id1,IPC_RMID,NULL); 
    system ("/bin/stty cooked");
     
    return 0;
}
#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
# include <stdio.h>
# include <pthread.h>

    
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];

                   ///// write(client_sock , "127.168.1.1" , 10));
void * writethread()
{
    while(1)
    { 
        printf("writing .......   \n");
        char message[1000];
        ///scanf("%s" , message); 
      gets(message);
       write(client_sock , message , strlen(message));
    }
}        

void * readthread()
{
     printf("reading.......   \n");
       while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
                {

                    //Send the message back to client
                    puts(client_message);
                    /////////client_message=NULL;
                    printf("Enter message : ");
                    
                }
}
int main(int argc , char *argv[])
{
    

    int con1,con2;
    pthread_t r,w;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
   
    //Receive a message from client
				

                con1 = pthread_create(&r, NULL,readthread,NULL);
                if (con1 != 0)
                {
                    perror("read Thread creation failed");
                    
                }


                con2 = pthread_create(&w, NULL,writethread,NULL);
                if (con2 != 0)
                {
                    perror("read Thread creation failed");
                    
                }

        




				    			    		
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     
    return 0;
}

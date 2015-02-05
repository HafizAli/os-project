/*
    C ECHO client example using sockets
*/
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
 
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
 
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8880 );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    puts("Connected\n");
    char optionArray[1000]={NULL};
    if( recv(sock , optionArray , 1000 , 0) < 0)
    {
            puts("recv failed");
            ////break;
    }
     puts(optionArray);

/////////////user will input////////////
char option_take[10];
//printf("Enter option --1--for login or --2--- for sign up: \n");

        ///scanf("%s" , message);
        gets(option_take);
        ///printf("your input is %d\n",option_take );
       if( send(sock , option_take , strlen(option_take) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
////////////////////////////

/////////keep communicating with server
   while(1)
    { 
    char message[1000]={NULL};
    char server_reply[2000]={NULL};
        printf("Enter message : ");
        ///scanf("%s" , message);
         gets(message);
        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        ///// message=NULL;
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
         
        puts("Server reply :");
        puts(server_reply);
    //////server_reply=NULL;
    }
     
    close(sock);
    return 0;
}

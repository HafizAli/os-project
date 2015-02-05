/*t
    C socket server example
*/
 
#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
 
int main(int argc , char *argv[])
{



       char sign_up[100][100];
       int iterator=0;
       

        int socket_desc , client_sock , c , read_size;
        struct sockaddr_in server , client;
        char client_message[2000]={NULL};
        struct sockaddr_in server_addr,client_addr;




        //////database login////



         //////////////
        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
            printf("Could not create socket");
        }
        puts("Socket created");
         
        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr =inet_addr("127.0.0.1");
        server.sin_port = htons( 8880 );
        printf("server ip %d \n",server.sin_addr.s_addr);
         
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
        printf("\n I got a connection from (%s , %d)",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
        

        if (client_sock < 0)
        {
            perror("accept failed");
            return 1;
        }
        puts("Connection accepted");
    /////////////i giving options////
        char option[1000]={"for sign up press 1 & login for press 1"};
        ////write(client_sock , option , strlen(option));
        send(client_sock , option , strlen(option) , 0);
    /////////////////////////////////show what user select form option
        recv(client_sock , client_message , 2000 , 0);
        puts(client_message);


        ////////////deciding login or sign uo//////
        ///char user_name[1000]={"enter user name"};
     if (strcmp( client_message,"0")==0)
     {
        char user_name[1000]={"enter user name"};
         send(client_sock , user_name , strlen(option) , 0);
         char Receive_option[100]={NULL};
         recv(client_sock,Receive_option,100,0);
         puts("user_name is: ");
         puts(Receive_option);
         ////////aking password
        char user_password[1000]={"enter your password"};
         send(client_sock , user_password , strlen(user_password) , 0);
         char Receive_password[100]={NULL};
         recv(client_sock,Receive_password,100,0);

         puts("user passwors is: ");
         puts(Receive_password); 
       /////////index of database

         strcpy(sign_up[iterator++],Receive_option);
         strcpy(sign_up[iterator++],Receive_password);
         strcpy(sign_up[iterator++]=inet_ntoa(client.sin_addr));

         
        printf("you have created your account succefully ......\n");
         //   printf("user name form database is: %s\n",sign_up[0]);
         //   puts("checkin  put is ");
       //puts(sign_up[0]);
     }
     else if (strcmp( client_message,"1")==0)
     {
        printf(" client choose q");
         
     }
    ////////////////

       
        //Receive a message from client


    				while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    				{
    				    //Send the message back to client
    				    puts(client_message);
    				    /////////client_message=NULL;
    				    printf("Enter message : ");
    				    char message[1000]={NULL};
    				    ///scanf("%s" , message);
    				    gets(message);
    				    
    				    write(client_sock , message , strlen(message));
                         
                         client_message[2000]=NULL;
    				   ///// write(client_sock , "127.168.1.1" , 10));
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

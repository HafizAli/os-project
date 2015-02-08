#include <stdio.h> //printf
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //write
#include <pthread.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/types.h>


	void *thread_read_function(int sock)
{
	int read_size;
	char client_message[200]={NULL};
	while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
	{
		printf("Message from server :\n");
		//Send the message back to client
		puts(client_message);
		/////////client_message=NULL;
	}
	pthread_exit("closing read thread");
}
void *thread_write_function(int sock)
{
	int read_size;
	while(1)
	{
		//Receive a message from server
		printf("Enter message : ");
		char message[1000]={NULL};
		///scanf("%s" , message);
		gets(message);
		send(sock , message , strlen(message) , 0);
	}
	pthread_exit("closing write thread");
}


int main(int argc , char *argv[])
{

				




			printf("check handler n chat %s\n",argv[1]);

			int read,write;
			pthread_t read_thread,write_thread;
			read = pthread_create(&read_thread, NULL,thread_read_function,argv[1]);
			if (read != 0)
			{
				perror("read Thread creation failed");
				exit(EXIT_FAILURE);
			}
			//write thread genrate
			write = pthread_create(&write_thread, NULL,thread_write_function,argv[1]);
			if (write != 0)
			{
				perror("write Thread creation failed");
				exit(EXIT_FAILURE);
			}

		while(1);
}
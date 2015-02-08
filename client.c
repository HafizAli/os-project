#include <stdio.h> //printf
#include <string.h> //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //write
#include <pthread.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/types.h>

	




	int sock;
	int client_sock;
	int clint_to_client_socket;
	struct sockaddr_in server,client,client2,clint_client_socket;


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





void * client_listen_thread(int clint_sock)
{
	while(1)
	{
		printf("i am a cline but listning \n");
		//create another socket for clint to clint comeunecate
		client.sin_family = AF_INET;
		client.sin_addr.s_addr =inet_addr("127.0.0.1");
		client.sin_port = htons( 8881 );
		//client clint binding
		if( bind(clint_sock,(struct sockaddr *)&client , sizeof(client)) < 0)
		{
		//print the error message
		perror("bind failed. Error");
		return 1;
		}
		listen(clint_sock , 3);
		//Accept and incoming connection
		puts("Waiting for incoming connections...");
		int c = sizeof(struct sockaddr_in);
		//accept connection from an incoming client
		client_sock = accept(clint_sock, (struct sockaddr *)&client2, (socklen_t*)&c);
		printf("\n I got a connection from (%s , %d)",inet_ntoa(client2.sin_addr),ntohs(client2.sin_port));
		if (client_sock < 0)
		{
			perror("accept failed");
			return 1;
		}
			int read,write;
			pthread_t read_thread,write_thread;
			read = pthread_create(&read_thread, NULL,thread_read_function,client_sock);
			if (read != 0)
			{
				perror("read Thread creation failed");
				exit(EXIT_FAILURE);
			}
			//write thread genrate
			write = pthread_create(&write_thread, NULL,thread_write_function, client_sock);
			if (write != 0)
			{
				perror("write Thread creation failed");
				exit(EXIT_FAILURE);
			}


	}
	/*
	
	*/
}




int main(int argc , char *argv[])
{
	int clint_sock;
	int lis;
	//create another socket for clint to clint comeunecate
	clint_sock = socket(AF_INET , SOCK_STREAM , 0);
	if (clint_sock == -1)
	{
	printf("Could not create socket for clint ");
	}
	pthread_t client_com;
	lis = pthread_create(&client_com, NULL,client_listen_thread, clint_sock);
	if (lis != 0)
	{
		perror("write Thread creation failed");
		exit(EXIT_FAILURE);
	}


	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	//
		puts("Socket created");
		server.sin_addr.s_addr =inet_addr("127.0.0.1");
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

		clint_to_client_socket = socket(AF_INET , SOCK_STREAM , 0);

		clint_client_socket.sin_addr.s_addr =inet_addr(optionArray);
		clint_client_socket.sin_family = AF_INET;
		clint_client_socket.sin_port = htons( 8881 );
		//Connect to remote server
		if (connect(clint_to_client_socket , (struct sockaddr *)&clint_client_socket , sizeof(clint_client_socket)) < 0)
		{
			perror("connect failed. Error");
			return 1;
		}
	
	int read,write;
	pthread_t read_thread,write_thread;
	read = pthread_create(&read_thread, NULL,thread_read_function,clint_to_client_socket);
	if (read != 0)
	{
		perror("read Thread creation failed");
		exit(EXIT_FAILURE);
	}
	//write thread genrate
	write = pthread_create(&write_thread, NULL,thread_write_function, clint_to_client_socket);
	if (write != 0)
	{
		perror("write Thread creation failed");
		exit(EXIT_FAILURE);
	}

	while(1);
	/////////////user will input////////////
	char option_take[50]={NULL};
	printf("Enter option n");
	gets(option_take);
	///printf("your input is %d\n",option_take );
	if( send(sock , option_take ,strlen(option_take), 0) < 0)
	{
	puts("Send failed");
	return 1;
	}
	char option_take2[50]={NULL};
	if( recv(sock , option_take2 , 2000 , 0) < 0)
	{
	puts("recv failed");
	}
	puts(option_take2);/////// asking question
	char user_name[100]={NULL};
	gets(user_name);
	//////////sending user_name
	if( send(sock , user_name ,strlen(user_name), 0) < 0)
	{
	puts("Send failed");
	return 1;
	}
	//////////////password///
	char Receive_password[100]={NULL};
	if( recv(sock , Receive_password , 2000 , 0) < 0)
	{
	puts("recv failed");
	}
	puts(Receive_password);
	char user_password[100]={NULL};
	gets(user_password);
	//////////sending user_name
	if( send(sock , user_password ,strlen(user_password), 0) < 0)
	{
	puts("Send failed");
	return 1;
	}
	/*
	 char Receive_pass[100]={NULL};
	if( recv(sock , Receive_pass , 100 , 0) < 0)
	{
	puts("recv failed");
	}
	puts(Receive_pass);
	printf("Now sign_IN:\n");
	char user_pass[100]={NULL};
	printf("Enter your user name:\n");
	gets(user_pass);
	send(sock , user_pass ,strlen(user_pass), 0);
	printf("Enter your Password:\n");
	char user_p[100]={NULL};
	gets(user_p);
	send(sock , user_p ,strlen(user_p), 0);
	*/
	///////////////////////////
	/////////keep communicating with server	
	close(sock);
	return 0;
}

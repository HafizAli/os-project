#include <stdio.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //write
#include <pthread.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/types.h>

#include <string.h>
/*
struct node

    {
        int num;
        char ip;

        struct node *ptr;

    };

    typedef struct node NODE;


    NODE *head, *first, *temp = 0;
    int count = 0;
    first = 0;

 */


/*
struct Node
{
	char user_name_save[100];
	char user_pass_save[100];
	char user_ip_save[100];

};
*/

//list <Node> LinkList;
enum { MAXLINES = 30 };

char sign_up[100][100];
char sign_in[100][100];
char ipss[100][100];
int l=0;
int sign_up_updater=0;
int login_updater=0;


void *thread_read_function(int client_sock)
	{
		int read_size;
		char client_message[200]={NULL};
		while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
			{
				printf("Message from client :\n");
				//Send the message back to client
				puts(client_message);
				/////////client_message=NULL;
			}
		pthread_exit("closing read thread");
	}



void *thread_write_function(int client_sock)
	{
		int read_size;
		while(1)
			{
				//Receive a message from client
				printf("Enter message : ");
				char message[1000]={NULL};
				///scanf("%s" , message);
				gets(message);
				send(client_sock , message , strlen(message) , 0);
			}
		pthread_exit("closing write thread");
	}



void * sign_in_up_func(int client_sock)
{
int read_size;
char client_message[2000]={NULL};
struct sockaddr_in server , client;
///////////i giving options////
////char option[1000]={"for sign up press 1 & login for press 1"};
/////write(client_sock , option , strlen(option));
/////send(client_sock , option , strlen(option) , 0);
/////////////////////////////////show what user select form option
//recv(client_sock , client_message , 2000 , 0);
//puts(client_message);
////////////deciding login or sign uo//////
///char user_name[1000]={"enter user name"};
/*if (strcmp( client_message,"0")==0)
{
	char user_name[1000]={"enter user name"};
	send(client_sock , user_name , strlen(option) , 0);
	char Receive_option[100]={NULL};
	recv(client_sock,Receive_option,100,0);
	printf("user name is:");
	puts(Receive_option);
	////////aking password
	char user_password[1000]={"enter your password"};
	send(client_sock , user_password , strlen(user_password) , 0);
	char Receive_password[100]={NULL};
	recv(client_sock,Receive_password,100,0);
	printf("user passwors is:");
	puts(Receive_password);*/

	/////////index of database
/*
	Node obj;
	strcpy(obj.user_name_save,Receive_option);
	strcpy(obj.user_pass_save,Receive_password);
	strcpy(obj.user_ip_save,inet_ntoa(client.sin_addr));
	LinkList.insert(obj);
*/
	/*int itr;
	for(itr=LinkList.begin(); itr!=LinkList.end(); itr++){ 
                    cout<<(*itr)->(); 
                    */

	//strcpy(sign_up[sign_up_updater++],Receive_option);
	//strcpy(sign_up[sign_up_updater++],Receive_password);
	//strcpy(sign_up[sign_up_updater++],inet_ntoa(client.sin_addr));
	
	//char msg[100]={"You have created your account successfully"};
	//
	
//}
	///after sign up know sign in section
	//recev usernama
	/*char Receive_user[100]={NULL};
	recv(client_sock,Receive_user,100,0);
	//recev pass
	char Receive_pass[100]={NULL};
	recv(client_sock,Receive_pass,100,0);
	//verifecation....
	int i;
	for(i=0;i<sign_up_updater;i++)
	{
	int check=0;
	if( strcmp(Receive_user,sign_up[sign_up_updater++])==0)
	{
	check++;
	}
	if( strcmp(Receive_pass,sign_up[sign_up_updater++])==0)
	{
	check++;
	}
	if(check==2)
	{
	printf("successfully loged in ...\n");
	strcpy(sign_in[login_updater++],Receive_user);
	strcpy(sign_in[login_updater++],Receive_pass);
	//print loged in listt
	printf("Log in people list :\n");
	for(i=0;i<login_updater;i=i++)
	{
	printf("user name : %s\n",sign_in[login_updater]);
	}
	}
	}
	}
	else if (strcmp( client_message,"1")==0)
	{
	printf(" client choose q");
	}
	*/

	int read,write;
	pthread_t read_thread,write_thread;
	//read thread genrate
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
	if(read_size == 0)
		{
			puts("Client disconnected");
			fflush(stdout);
		}
	else if(read_size == -1)
		{
			perror("recv failed");
		}
}



int main(int argc , char *argv[])
{
pthread_t sign_in_sign_up_thread;
int sign_in_Up;
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
	while (1)
	{
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
	
	strcpy(sign_up[sign_up_updater++],inet_ntoa(client.sin_addr));
	/////send(client_sock , sign_up[sign_up_updater-2] , strlen(sign_up[sign_up_updater-2]) , 0);
		





	puts("Connection accepted");
	char option[1000]={"For sign up press  -- s  ---& login for press -- l --"};
	write(client_sock , option , strlen(option));
	char client_user_name[10]={NULL};
	recv(client_sock , client_user_name , 10, 0);


/////////////////


	struct info{
        char name[10];
        char sur[10];
     char *ip;
    };
    struct info rec;

    FILE *f1;

 FILE *passl; 
 FILE *ipl;
 ///////////////////////
	if (strcmp(client_user_name,"s")==0)
		{

			//////////name
		 printf("client choose s \n");
		char option[100]={"Enter user name"};
		write(client_sock , option , strlen(option));
    	char client_name[10]={NULL};
	    recv(client_sock , rec.name , 10, 0);
         puts(client_name);

              
         ////////////////password
         char password[100]={"Enter password"};
		  write(client_sock , password , strlen(password));
    	char client_password[10]={NULL};
	    recv(client_sock , rec.sur , 10, 0);
         puts(client_password);
                    
           rec.ip=inet_ntoa(client.sin_addr);




               
                f1=fopen("database.txt","a+"); //<- open file for writing
                fputs(rec.name,f1);
                fprintf(f1,"\n");
                fclose(f1);

              	passl=fopen("password.txt","a+"); //<- open file for writing
                fputs(rec.sur,passl);
                fprintf(passl,"\n");
                fclose(passl);

               ipl=fopen("ipl.txt","a+"); //<- open file for writing
                fputs(rec.ip,ipl);
                fprintf(ipl,"\n");
                fclose(ipl); 
                // close the file. this will flush the buffer.*/
                printf("congrats you added!\n");
                ////////////////////////////link list pani for ip
               


		      }
		else if (strcmp(client_user_name,"l")==0)
		{
			printf("client choose l \n");



			   char usernmae[100]={"Write usernmae to login:"};
		       write(client_sock , usernmae , strlen(usernmae)); 
				
               char cmp[40];
               char dummy;

               char client_name_login[10]={NULL};
	           recv(client_sock , client_name_login , 10, 0);
      

            char user_password[100]={"Write password login:"};
		       write(client_sock , user_password , strlen(user_password)); 
				
               

               char client_pass_login[10]={NULL};
	           recv(client_sock , client_pass_login , 10, 0);


    

                printf("Search account\n");
                ///printf("Write surname to search: ");
                ///////fgets(cmp, sizeof(cmp), stdin);
                ///////////f1=fopen("txt.txt","r"); //<- open the file for reading
                      

                      
    char lines[MAXLINES][BUFSIZ];
    char lines2[MAXLINES][BUFSIZ];
    char lines3[MAXLINES][BUFSIZ];
    FILE *fp = fopen("database.txt", "r");
    

    if (fp == 0)
    {
        fprintf(stderr, "failed to open input.txt\n");
        exit(1);
    }
    int i = 0;
    while (i < MAXLINES && fgets(lines[i], sizeof(lines[0]), fp))
    {
        lines[i][strlen(lines[i])-1] = '\0';
        i = i + 1;
    }
    fclose(fp);
    int j;
    for(j=0;j<i;j++)
   	if (strcmp(lines[j],client_name_login)==0)
   	{
   
   	
    printf("findddddd  %s\n", lines[j]);
	     FILE *p = fopen("password.txt", "r");
	     if (p == 0)
			    {
			        fprintf(stderr, "failed to open input.txt\n");
			        exit(1);
			    } 
	               
	    		int k = 0;

			    while (k < MAXLINES && fgets(lines2[k], sizeof(lines2[0]), p))
				    {
				    	 
				        lines2[k][strlen(lines2[k])-1] = '\0';
				        k = k + 1;
				       
				    }



			    		if(strcmp(lines2[j],client_pass_login)==0)
			    		{	
			    			printf("ooooooooooooooooooooooo\n");

///////////////////////////////////storing onine ip/////
						FILE *ipi = fopen("ipl.txt", "r");
							     if (ipi == 0)
									    {
									        fprintf(stderr, "failed to open input.txt\n");
									        exit(1);
									    } 
								int q = 0;

								while (q < MAXLINES && fgets(lines3[q], sizeof(lines3[0]), ipi))
								{

									lines3[q][strlen(lines3[q])-1] = '\0';
											q = q + 1;

								}
							strcpy(	ipss[l++],lines3[j]);
								
								char ch[10]={NULL};
								ch[0]=l;
								ch[0] =ch[0]+48;
								printf("%s\n",ch );
								 write(client_sock , ch , strlen(ch)); 
								int z;

								for(z=0;z<l;z++)
								{
									write(client_sock , ipss[z] , strlen(ipss[z]));
									write(client_sock ,lines[j] , strlen(lines[j])) ;

								}
									 
							
							
								
/*								//////////////////////////////////////

                        head  = (NODE *)malloc(sizeof(NODE)); 
								strcpy(head->ip,lines3[j]);		

                               
								if (first != 0)

								{

								temp->ptr = head;

								temp = head;

								}

								else

								{

								first = temp = head;

								}

								fflush(stdin);

								temp->ptr = 0;
								temp = first;

								printf("\n status of the linked list is\n");

								while (temp != 0)

								{

								printf("%d=>", temp->num);



								temp = temp -> ptr;

								}

								printf("NULL\n");

    


			    		



							

*/

			    		}
			    		else{
			    			printf("no here\n");
			    		}

/////////////////


	}

	    

    }

		}

	//////sign_in_Up = pthread_create(&sign_in_sign_up_thread, NULL,sign_in_up_func,client_sock);

}

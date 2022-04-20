#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void *send_message(char *IP);
void *recieve_message();
void *connection_handler(void *);

int main(int argc , char *argv[])
{
	int socket_desc , new_socket , c, *new_sock;;
	struct sockaddr_in server , client;
	char *message, server_reply[2000];;

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
		
	server.sin_addr.s_addr = inet_addr("192.168.56.101");
	server.sin_family = AF_INET;
	server.sin_port = htons( 5010 );

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	//Get Reciepient IP
	message = "LNS";
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	
	//Receive a reply from the server
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
		puts("recv failed");
	}
	puts(server_reply);
	close(socket_desc);

	//Recieve message from client
	recieve_message();
	return 0;

}

void *send_message(char *IP)
{

	int socket_desc , new_socket , c, *new_sock;;
        struct sockaddr_in server , client;
        char *message, server_reply[2000];;

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }

        server.sin_addr.s_addr = inet_addr(IP);
        server.sin_family = AF_INET;
        server.sin_port = htons( 5011 );

        //Connect to remote server
        if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                puts("connect error");
                //return 1;
        }

        //Get Reciepient IP
        message = "Hello client";
        if( send(socket_desc , message , strlen(message) , 0) < 0)
        {
                puts("Send failed");
                //return 1;
        }

        close(socket_desc);

}

void *recieve_message()
{

	int socket_desc , new_socket , c, *new_sock;;
        struct sockaddr_in server , client;
        char *message;

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 5011 );


        //Bind
        if( bind(socket_desc,(struct sockaddr *) & server , sizeof(server)) < 0)
        {
                puts("bind failed");
        }
        puts("bind done");

        //Listen
         listen(socket_desc , 3);

        //Accept and incoming connection
         puts("Waiting for incoming connections...");
        c = sizeof(struct sockaddr_in);
        while( (new_socket = accept(socket_desc, (struct sockaddr *) & client, (socklen_t*) & c)) )
        {
                puts("Connection accepted");

                pthread_t sniffer_thread;
                new_sock = malloc(1);
                *new_sock = new_socket;

                if( pthread_create( & sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
                {
                        perror("could not create thread");
                        //return 1;
                }

                puts("Handler assigned");
        }
        if (new_socket < 0)
        {
                perror("accept failed");
                //return 1;
        }


        //return 0;
}

/*
 *  *  * This will handle connection for each client
 *   *   * */

void *connection_handler(void *socket_desc)
{

	//Get the socket descriptor
	int sock = *(int*)socket_desc;
        int read_size;
        char client_message[2000];

        //Receive a message from client
        read_size = (recv(sock , client_message , 2000 , 0) > 0);
	puts(client_message);
        //Handle with GTK
       
        if(read_size == 0)
        {
                puts("Client disconnected");
                fflush(stdout);
        }
        else if(read_size == -1)
        {
                perror("recv failed");
        }

        //Free the socket pointer
        free(socket_desc);

        return 0;

}

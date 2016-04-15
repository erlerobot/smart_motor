/*
    C socket server example, handles multiple clients using threads
    Compile
    gcc server.c -lpthread -o server
*/

#include <stdio.h>
#include <string.h>    //strlen
#include <stdlib.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> //for threading , link with lpthread
#include "server.h"
#include "service.h"
#include "../../config.h"

char *server_intro ="*********************************************************\n"
    			"*        SmartServo controlling system                  *\n"
    			"*********************************************************\n"
    			"* Send CMD:                                             *\n"
    			"*   - CMD_GET_ID         - CMD_SET_ID                   *\n"
    			"*   - CMD_GET_POSITION   - CMD_SET_GOAL                 *\n"
    			"*   - CMD_GET_TEMP       - CMD_SET_CW_LIMIT             *\n"
    			"*   - CMD_GET_BATTERY    - CMD_SET_CCW_LIMIT            *\n"
    			"*   - CMD_GET_CURRENT    - CMD_SET_PID_CONF             *\n"
    			"*   - CMD_GET_ERROR      - CMD_SET_PID_IGAIN            *\n"
    			"*   - CMD_GET_VELOCITY   - CMD_SET_PID_DGAIN            *\n"
    			"*   - CMD_GET_PID_CONF                                  *\n"
    			"*   - CMD_GET_CW_LIMIT                                  *\n"
    			"*   - CMD_GET_CCW_LIMIT                                 *\n"
    			"*   - CMD_GET_ALL                                       *\n"
    			"*                                                       *\n"
    			"***********************************************************";

int comenzarPeticionServidor();
int esperarConexion(int socketEspera);
//the thread function
void *connection_handler(void *);

/**
*
*   Initialize the Server. Create a socket and wait for conection.
*
*   @return	0.
*
*   @note		None.
*
*/
int SERVER_init(){

    int socket_desc;

    socket_desc = comenzarPeticionServidor();
    esperarConexion(socket_desc);

    return 0;
}
/**
*
*   Create socket and bind it.
*
*   @return	socket descriptor.
*
*   @note		None.
*
*/
int comenzarPeticionServidor()
{
	int socket_desc;
	struct sockaddr_in server;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
#ifdef CONFIG_DEBUGGER
    puts("Socket created");
#endif
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
#ifdef CONFIG_DEBUGGER
    puts("bind done");
#endif

    return socket_desc;
}

/**
*
*   Wait for connections from the server to the client. A thread is created
*   for each client.
*
*   @param socket_desc socket descriptor to achive communication.
*
*   @return	0.
*
*   @note		None.
*
*/
int esperarConexion(int socket_desc)
{
	int client_sock , c;
	struct sockaddr_in  client;

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
#ifdef CONFIG_DEBUGGER
    puts("Waiting for incoming connections...");
#endif
    c = sizeof(struct sockaddr_in);

	pthread_t thread_id; //Pero solo se creará un thread_id no??

    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
	  #ifdef CONFIG_DEBUGGER
        puts("Connection accepted");
      #endif
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        //puts("Handler assigned");
    }

    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    return 0;
}

/**
*
*   This will handle connection for each client.
*
*   @param socket_desc pointer to send and recive MSG.
*
*   @note		None.
*
*/
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
//    char client_message[2000];
    MSG msg;

    unsigned char end = 0;


    //Send intro messages to the client
    write(sock , server_intro , strlen(server_intro));
//    memset(client_message, 0, 2000);

    //Receive a message from client
    while( ((read_size = recv(sock , (void*)&msg , sizeof(MSG) , 0)) > 0 ) && end!=-1)
    {
      #ifdef CONFIG_DEBUGGER
	    printf("comando:%i\n",msg.cmd);
      #endif
        //end of string marker
    	end = SERVICE_execute(&msg);
		//Send the message back to client
    	write(sock ,(void*) &msg , sizeof(MSG) );
		//clear the message buffer
    	memset(&msg, 0,sizeof(MSG));
    }

    if(read_size == 0)
    {
      #ifdef CONFIG_DEBUGGER
        puts("Client disconnected");
      #endif
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
    /**
     * @ todo See how to close the sockets!!
     */
    //close(socket_desc);

    return 0;
}




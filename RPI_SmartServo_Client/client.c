/*
 C ECHO client example using sockets
 */
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include "service.h"

int initClient();
void reciveServerIntro(int sock);
int enterCommand(MSG *msg, char *message);
void serverReply(MSG *msg);
void setID(MSG *msg);
void setGoal(MSG *msg);
void setCWLimit(MSG *msg);
void setCCWLimit(MSG *msg);
void setPIDconf(MSG *msg);

int main(int argc, char *argv[]) {
	int sock;
	char message[1000];
	MSG msg;

	//Initialize the Client
	sock = initClient();
	//Recive some intro from the Server first
	reciveServerIntro(sock);

	//keep communicating with server
	while (1) {
		int server_reply;
		server_reply = enterCommand(&msg, message);

		//Send some data
		if (send(sock, (void*) &msg, sizeof(MSG), 0) < 0) {
			puts("Send failed");
			return 1;
		}

		//Receive a reply from the server
		if (recv(sock, (void*) &msg, sizeof(MSG), 0) < 0) {
			puts("recv failed");
			break;
		}

		if (server_reply) {
			puts("Server reply :");
			serverReply(&msg);
		}

	}

	return 0;
}

int initClient() {
	int sock;
	struct sockaddr_in server;

	//Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	//Connect to remote server
	if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}

	puts("Connected\n");

	return sock;
}

void reciveServerIntro(int sock) {
	char server_intro[2000];

	//Receive intro from the server
	if (recv(sock, server_intro, 2000, 0) < 0) {
		puts("recv failed");
	}
	//Server intro
	puts(server_intro);
	//clear the message buffer
	memset(server_intro, 0, 2000);

}

int enterCommand(MSG *msg, char *message) {
	//Put a return value to do not evaluate when is a bad command.
	int ret = 1;

	printf("Enter command: ");
	scanf("%s", message);
	if (strcmp(message, "CMD_GET_ID") == 0) {
		msg->cmd = CMD_GET_ID;

	} else if (strcmp(message, "CMD_GET_POSITION") == 0) {
		msg->cmd = CMD_GET_POSITION;

	} else if (strcmp(message, "CMD_GET_TEMP") == 0) {
		msg->cmd = CMD_GET_TEMP;

	} else if (strcmp(message, "CMD_GET_BATTERY") == 0) {
		msg->cmd = CMD_GET_BATTERY;

	} else if (strcmp(message, "CMD_GET_CURRENT") == 0) {
		msg->cmd = CMD_GET_CURRENT;

	} else if (strcmp(message, "CMD_GET_ERROR") == 0) {
		msg->cmd = CMD_GET_ERROR;

	} else if (strcmp(message, "CMD_GET_VELOCITY") == 0) {
		msg->cmd = CMD_GET_VELOCITY;

	} else if (strcmp(message, "CMD_GET_PID_CONF") == 0) {
		msg->cmd = CMD_GET_PID_CONF;

	} else if (strcmp(message, "CMD_GET_CW_LIMIT") == 0) {
		msg->cmd = CMD_GET_CW_LIMIT;

	} else if (strcmp(message, "CMD_GET_CCW_LIMIT") == 0) {
		msg->cmd = CMD_GET_CCW_LIMIT;

	} else if (strcmp(message, "CMD_GET_ALL") == 0) {
		msg->cmd = CMD_GET_ALL;
	} else if (strcmp(message, "CMD_SET_ID") == 0) {
		msg->cmd = CMD_SET_ID;
		setID(msg);

	} else if (strcmp(message, "CMD_SET_GOAL") == 0) {
		msg->cmd = CMD_SET_GOAL;
		setGoal(msg);

	} else if (strcmp(message, "CMD_SET_CW_LIMIT") == 0) {
		msg->cmd = CMD_SET_CW_LIMIT;
		setCWLimit(msg);

	} else if (strcmp(message, "CMD_SET_CCW_LIMIT") == 0) {
		msg->cmd = CMD_SET_CCW_LIMIT;
		setCCWLimit(msg);

	} else if (strcmp(message, "CMD_SET_PID_CONF") == 0) {
		msg->cmd = CMD_SET_PID_CONF;
		setPIDconf(msg);

	} else {
		printf("Not a valid command\n");
		ret = 0;
	}

	return ret;
}

void serverReply(MSG *msg) {
	switch (msg->cmd) {
	case CMD_GET_ID:
		printf("cmd: %i, id: %i \n", msg->cmd, msg->id);
		break;
	case CMD_GET_POSITION:
		printf("cmd: %i, position: %f \n", msg->cmd, msg->position);
		break;
	case CMD_GET_TEMP:
		printf("cmd: %i, temp: %f \n", msg->cmd, msg->temp);
		break;
	case CMD_GET_BATTERY:
		printf("cmd: %i, battery: %f \n", msg->cmd, msg->battery);
		break;
	case CMD_GET_CURRENT:
		printf("cmd: %i, current: %f \n", msg->cmd, msg->current);
		break;
	case CMD_GET_ERROR:
		printf("cmd: %i, error: %f \n", msg->cmd, msg->error);
		break;
	case CMD_GET_VELOCITY:
		printf("cmd: %i, velocity: %f \n", msg->cmd, msg->velocity);
		break;
	case CMD_GET_PID_CONF:
		printf("cmd: %i, p_gain: %i, d_gain: %i \n", msg->cmd, msg->p_gain,
				msg->d_gain);
		break;
	case CMD_GET_CW_LIMIT:
		printf("cmd: %i, cw_limit: %i \n", msg->cmd, msg->cw_limit);
		break;
	case CMD_GET_CCW_LIMIT:
		printf("cmd: %i, ccw_limit: %i \n", msg->cmd, msg->ccw_limit);
		break;
	case CMD_GET_ALL:
		printf("cmd: %i, cw_limit: %i \n", msg->cmd, msg->cw_limit);
		break;
	default:
		printf("cmd: %i\n", msg->cmd);
		break;
	}
}

void setID(MSG *msg) {
	int id;
	printf("Enter id to set:");
	scanf("%i", &id);
	msg->id = id;
}
void setGoal(MSG *msg) {
	int goal;
	printf("Enter goal to set:");
	scanf("%i", &goal);
	msg->goal = goal;

}
void setCWLimit(MSG *msg) {
	int cw_limit;
	printf("Enter CW limit to set:");
	scanf("%i", &cw_limit);
	msg->cw_limit = cw_limit;

}
void setCCWLimit(MSG *msg) {
	int ccw_limit;
	printf("Enter CCW limit to set:");
	scanf("%i", &ccw_limit);
	msg->ccw_limit = ccw_limit;
}
void setPIDconf(MSG *msg) {
	int p_gain, d_gain;
	printf("Enter p gain:");
	scanf("%i", &p_gain);
	msg->p_gain = p_gain;
	printf("Enter d gain:");
	scanf("%i", &d_gain);
	msg->d_gain = d_gain;
}

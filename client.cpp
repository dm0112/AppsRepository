#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <errno.h>
#include <cstdio>
using namespace std;
#define PORT 6666

int main(int argc, char *argv[]){
       

	int clientSocket, ret; // PORT;
	sockaddr_in serverAddr;
	char buffer[1024];


	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		cerr<<"err in connection";
		return errno;
	}
	cout<<"connection socket created"<<endl;
	/*if(!argv[1])
	{
		cout<<"You forgot the port!"<<endl;
		cout<<"I'll give you one more chance, enter the port: ";
		int secChance;
		cin>>secChance;
		if(!secChance)
			{cerr<<"No more chances"<<endl;
		exit(1);}
		else PORT=secChance;
	}
	if(argv[1])*/
	//PORT=atoi(argv[1]);
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);

	//serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // deprecated

	inet_pton(AF_INET,"0.0.0.0",&serverAddr.sin_addr);

	ret = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		cerr<<"Error in connection"<<endl;
		return errno;}
	cout<<"Connected to server"<<endl;
	cout<<"To disconnect, type 'exit'"<<endl;

	while(1){
		bzero(buffer,sizeof(buffer));
		fgets(buffer,sizeof(buffer),stdin);
		size_t len = strlen(buffer); /// ------ eliminare enter input
		if (len > 1 && buffer[len-1] == '\n') {  //// daca bufferul nu contine doar \n, eliminam \n
  		buffer[--len] = '\0';
		} /// -----
		send(clientSocket, buffer, strlen(buffer), 0); // fara \n
		if(strcmp(buffer, "exit")==0){ //deconectare la gasirea unui exit
			close(clientSocket);
			cout<<"disconnected from server"<<endl;
			return errno;
		}
		/// recv client de la server
		if(recv(clientSocket, buffer, 1024, 0) < 0){
			cerr<<"error in receiving data";
		}else{
			//cout<<strlen(buffer)<<endl;
			//cout<<endl<<buffer<<endl;
			fflush(stdout);
			bzero(buffer, sizeof(buffer));
		}
	}

	return 0;
}

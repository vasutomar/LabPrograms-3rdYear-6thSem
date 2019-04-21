#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#define PORT 8080

using namespace std;

// variable declaration
int serverSocket , clientSocket[2];
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;

int players = 0;
int sender = 0;
int receiver = 1;

void AcceptPlayer() {
    // Acceptor
    clilen = sizeof(cli_addr);
    clientSocket[players] = accept(serverSocket, (struct sockaddr *) &clientSocket[players], &clilen);
    if(clientSocket[players] < 0) {
        cout<<"Error socket accept... return code : "<<clientSocket[0]<<endl;
        exit(-1);
    }
    players++;
}

string read(int playerid) {
    // Reader
    bzero(buffer,256);
    int received = read(clientSocket[playerid],buffer,255);
    if(received < 0) {
        cout<<"Error socket reading... return code : "<<received<<endl;
        exit(-1); 
    }
    size_t len;
    cout<<buffer<<endl;
    string s = string(buffer);
    return s;
}

void send(int playerid, string symbol) {
    // Sender
    char cstr[symbol.size()+1];
    strcpy(cstr, symbol.c_str());

    send(clientSocket[playerid] ,cstr , strlen(cstr) , 0 );     
}

int main() {

    // Creator
    serverSocket = socket(AF_INET , SOCK_STREAM, 0);
    if(serverSocket < 0) {
        cout<<"Error socket creation... return code : "<<serverSocket<<endl;
        exit(-1);
    }

    // Binidor
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    int bind_code = bind(serverSocket, (struct sockaddr *) &serv_addr,sizeof(serv_addr));
    if (bind_code < 0) {
        cout<<"Error socket binding... return code : "<<bind_code<<endl;
        exit(-1);
    }

    // Listener
    int listen_code = listen(serverSocket, 5);
    if(listen_code < 0) {
        cout<<"Error socket listening... return code : "<<listen_code<<endl;
        exit(-1);
    }

    AcceptPlayer();
    AcceptPlayer();

    cout<<"The game begins."<<endl;
    
    while(true) {
        string symbol = read(sender); // step 2 and 3
        cout<<symbol<<endl;
        send(receiver, symbol);       // step 4
        string word = read(receiver); // step 8

        sender = (sender+1)%2;
        receiver = (receiver+1)%2;
    }

    return 0;
}
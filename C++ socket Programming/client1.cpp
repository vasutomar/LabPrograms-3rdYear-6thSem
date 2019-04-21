#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <arpa/inet.h>

#define PORT 8080

using namespace std;

int sock, n;
struct sockaddr_in serv_addr;
struct hostnet *server;
char buffer[256];

void send_symbol() {
    string str;

    cout<<"Enter a symbol : ";
    cin>>str;
    char message[str.size()+1];
    strcpy(message,str.c_str());
    
    send(sock , message , strlen(message) , 0);
}

char read_symbol() {
    // Reader
    int valread = read(sock, buffer, 256);
    return buffer[0];
}

/*void read_from_server() {
    // Reader
    valread = read(sock, buffer, 256);
    size_t len;
    cout<<buffer<<endl;
    string s(reinterpret_cast<char const*>(buffer), len);
    return s;

}*/

void send_word(string word) {

    char message[word.size()+1];
    strcpy(message,word.c_str());
    
    send(sock , message , strlen(message) , 0);
}

string produceWord(char symbol) {
    string s;
    cout<<"Enter a string from "<<symbol<<" : ";
    cin>>s;
    return s;
}

int main() {

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        cout<<"Error socket creation... return code : "<<sock<<endl;
        exit(-1);
    }
    
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 

    if(inet_pton(AF_INET,"127.0.0.1", &serv_addr.sin_addr)<=0) {
        cout<<"invaid addr."<<endl;
        exit(-1);
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }  

    // He sends first
    while(true) {
        send_symbol(); //step 2
        char symbol = read_symbol();        // step 5 
        string word = produceWord(symbol);  // step 6
        send_word(word);
    }
    return 0;
}


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string.h>


int status;
struct addrinfo hints;
struct addrinfo *servinfo;  // will point to the results


int main(){
    memset(&hints, 0, sizeof hints); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

    // get ready to connect
    status = getaddrinfo("www.example.net", "3490", &hints, &servinfo);

    // servinfo now points to a linked list of 1 or more struct addrinfos

    // etc.
    std::cout << "Client" << '\n';
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <string>
#include <sha256.h>


#define MAX_SIZE 256
class Server
{
public:
	Server(std::string port);
private:
    int sockfd, new_fd, yes=1,rv,numbytes;
    int socket_descriptor,status,backlog=10;
	char s[INET6_ADDRSTRLEN];
	char port_array[5];
	char buf[MAX_SIZE];
	std::string port;
	socklen_t sin_size;
	struct addrinfo hints;
	struct addrinfo *servinfo, *p;
    struct sockaddr_storage their_addr;
    struct sigaction sa;
	
	void close_main_socket();
	void start_server();
	void *get_in_addr(struct sockaddr *sa);
	int recive_controller();
};
/*
 * author: Nadeem Elahi
 * nadeem.elahi@gmail.com
 * nad@3deem.com
 * license: gpl v3
 */
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h> /* close( fd ) */

int connect2socket( struct addrinfo *addr ){

	printf("connect2socket()\n");

	// socket()
	int sockfd = socket (
			addr->ai_family ,
			addr->ai_socktype ,
			addr->ai_protocol 
			);

	if ( sockfd == -1 ) {
		fprintf(stderr, "connect2socket(): socket(): error\n");
		return -1;
	}

	printf("connect2socket(): socket() ok\n");

	// connect()
	int ret = connect (
			sockfd ,
			addr->ai_addr ,
			addr->ai_addrlen
			);

	if ( ret == -1 ) {
		fprintf(stderr, "connect2socket(): connect(): error\n");
		close( sockfd );
		return -2;
	}

	printf("connect2socket(): connect() ok, returning sockfd\n");



	return sockfd ;

}

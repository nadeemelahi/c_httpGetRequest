/*
 * author: Nadeem Elahi
 * nadeem.elahi@gmail.com
 * nad@3deem.com
 * license: gpl v3
 */
#include <stdio.h>
#include <netdb.h> /* getaddrinfo() */
#include <arpa/inet.h> /* inet_ntop() */
#include <unistd.h> /* close( fd ) */

#include "a03_structs.h"

int connect2socket( struct addrinfo *addr );
int httpGetRequest( int sockfd , struct uri *uri01 );

int loopAvailableAddresses ( struct uri *uri01 ) {
	
	/* gai */
	/* basic addrinfo configuration */

	printf("loopAvailableAddresses(): configuring 'struct addrinfo hints' for a tcp/ip v4 socket\n");

	int ret;
	struct addrinfo hints = {0}; //memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // ip version 4
	hints.ai_socktype = SOCK_STREAM;

	printf("loopAvailableAddresses(): getting address info for given hostname: %s\n", uri01->host );
	printf("loopAvailableAddresses(): getaddrinfo() returns a linked list\n");

	struct addrinfo *addr_ll; // list of addresses for given hostname - linked list
	ret = getaddrinfo ( uri01->host , uri01->port , &hints, &addr_ll ) ;

	if ( ret ) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror( ret ) );
		return 2;
	}
	

	struct addrinfo *each_addr;
	struct sockaddr_in *ip_field ;
	char ipstr[INET_ADDRSTRLEN] ;

	printf("loopAvailableAddresses(): loop through ip addresses linked list - struct addrinfo *addr_ll:\n");
	// loop over linked list res 
	for ( 
			each_addr = addr_ll; 
			each_addr != NULL; 
			each_addr = each_addr->ai_next 
	    ) {

		if ( each_addr->ai_family == AF_INET ) { 
			// if ip version 4 

			// cast to internet socket address from regular socket address
			ip_field = (struct sockaddr_in *)each_addr->ai_addr;

			// convert the IP from binary to a string and print it:
			inet_ntop(
					AF_INET ,
					&(ip_field->sin_addr) , 
					ipstr , sizeof ipstr
				 );

			printf("loopAvailableAddresses(): ipstr: %s\n", ipstr);

			break; // just grab the first one

		} 	
	}

	int sockfd;
	sockfd = connect2socket( each_addr );
	if( sockfd < 0 ) { 
		fprintf(stderr, "loopAvailableAddresses(): connect2socket() error \n" );
		return 3;
	}

	freeaddrinfo( addr_ll ); // free the linked list

	printf("loopAvailableAddresses(): socket fd: %d\n", sockfd);

	ret = httpGetRequest( sockfd , uri01 );

	if ( ret ) {
		fprintf(stderr, "loopAvailableAddresses(): readFromSocket() error\n" );
		return 4;
	}


	close(sockfd);


	return 0;
}


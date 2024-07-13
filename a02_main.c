/*
 * author: Nadeem Elahi
 * nadeem.elahi@gmail.com
 * nad@3deem.com
 * license: gpl v3
 */
#include <stdio.h>
#include <netdb.h> /* struct sockaddr_in */

#include "a03_structs.h"

int processCMDargs ( int argc , char *argv[] , 
		struct uri *uri01
		);

int loopAvailableAddresses ( struct uri *uri01 ) ;

int main ( int argc, char *argv[] ) {

	int ret;
	/* 1. processing command line arguments */
	struct uri uri01 = {0};

	/* 2. */
	ret = processCMDargs( argc , argv , &uri01 );

	if ( ret ) { fprintf(stderr , "main(): processCMDargs() call returned error\n"); return 1; }


	/* 3. */
	ret = loopAvailableAddresses ( &uri01 ) ;

	if ( ret ) { fprintf(stderr , "main(): loopAvailableAddresses() call returned error\n"); return 2; }
;



	return 0;
}

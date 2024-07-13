/*
 * author: Nadeem Elahi
 * nadeem.elahi@gmail.com
 * nad@3deem.com
 * license: gpl v3
 */
#include <stdio.h>
#include "a03_structs.h"

void printUsage(){
	printf ( "main(): usage: $a.out host_name.com port_number path\n" ) ; 
	printf ( "main():    ex: $a.out 3deem.com 80 /\n" ) ;
	printf ( "main():    ex: $a.out 3deem.com 80 /about\n" ) ;

}
int processCMDargs( 
		int argc , char *argv[] , 
		struct uri *uri01
		){

	printUsage();

	if ( argc != 4 ){
		fprintf(stderr, "usage error: argc != 4\n");
		printUsage();
		return 1;
	}	

	sprintf( uri01->host , "%s", argv[1] ) ;
	sprintf( uri01->port , "%s", argv[2] ) ;
	sprintf( uri01->path , "%s", argv[3] ) ;

	printf("processCMDargs(): set hostname:port:path: %s:%s:%s\n", 
			uri01->host , 
			uri01->port, 
			uri01->path
			);

	return 0;

}

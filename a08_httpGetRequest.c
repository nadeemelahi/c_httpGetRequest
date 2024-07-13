#include<stdio.h>
#include<string.h> /* strlen() */
#include<unistd.h>/* close ( fd ) */
#include<sys/socket.h>/* recv( sockfd , buffer , len) */

#include "a03_structs.h"

int httpGetRequest( int sockfd , struct uri *uri01 ){

	printf("httpGetRequest():\n");
	/* in the previous plain tcp client
	 * we just call recv()
	 * but with an http get request
	 * we must first make an http get request
	 * that is, we must send( "get request string" )
	 * then recv( "http response string - ie html" )
	 * https://gist.github.com/nolim1t/126991/ae3a7d36470d2a81190339fbc78821076a4059f7
	 *
	 * https://aticleworld.com/http-get-and-post-methods-example-in-c/
	 * char pszRequest[100]= {0};
    char pszResourcePath[]="2016/04/create-xml-request-in-c-for-server.html";
    char pszHostAddress[]="www.aticleworld.com";
	 * sprintf(pszRequest, "GET /%s HTTP/1.1\r\nHost: %s\r\nContent-Type: text/plain\r\n\r\n", pszResourcePath, pszHostAddress);
	 */

	/* 3 parts 
	 * GET / HTTP/1.1\r\n
	 * Host: example.com\r\n
	 * Content-Type: text/plain\r\n\r\n
	 */
	
	// full get request
	char getReqStrBuf[300] = {0};
	char *getReqStr = getReqStrBuf;
	sprintf ( getReqStr , 
			"GET %s HTTP/1.1\r\nHost: %s\r\n\r\n" , 
			uri01->path , 
			uri01->host 
			);

	int getStrLen = strlen ( getReqStr );

	printf("len: %d\n" , getStrLen );

	printf("Get Req: \n%s\n" , getReqStr );


	int ret;

	// send() the get request
	// test
	//char *testGetStr = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
	//getStrLen = strlen ( testGetStr ) ; printf("len: %d\n" , getStrLen );
	//ret = send ( sockfd , testGetStr , getStrLen , 0 );
	
	ret = send ( sockfd , getReqStr , getStrLen , 0 );

	if ( ret == -1 ) {
		fprintf ( stderr , "ERROR: httpGetRequest(): send(): \n" );
		return 1;
	}
	
	// http Response - from web server

	int numbytes , max = 2048;
	char readbuf[max];
	char *buf = readbuf;


	numbytes = recv (
			sockfd ,
			buf ,
			(max - 1) ,
			0
			);

	if ( numbytes == -1 ) {
		fprintf(stderr, "readFromSocket(): recv(): error\n");
		close( sockfd );
		return 1;
	}

	buf[numbytes] = '\0'; // null terminate

	printf("httpGetRequest(): recv() ok\n");

	// print out the text received from on the socket
	printf("httpGetRequest(): recieved: %s\n", buf);
	

	return 0;
}

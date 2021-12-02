
#include <bits/stdc++.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <string.h>
#include <stdio.h>


using namespace std;



#define _WIN32_WINNT 0X501


int main(int argc, char *argv[])
{
int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;

char buffer[256];

/*
if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
}
*/
portno = 8080;
/* Create a socket point */
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) 
{
    perror("ERROR opening socket");
    exit(1);
}
server = gethostbyname("localhost");
if (server == NULL) {
     printf("Plf ");
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
}

bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
bcopy((char *)server->h_addr, 
       (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);
serv_addr.sin_port = htons(portno);
printf("connecting...\n");
/* Now connect to the server */
if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
{
     perror("ERROR connecting");
     printf("Pl ");
     exit(1);
}   
/* Now ask for a message from the user, this message
* will be read by server
*/
printf("Please enter the message: ");

//explicit_bzero(buffer,256);
//memset(buffer,'\0',256);
//fgets(buffer,255,stdin);
//cout<<'f';
/* Send message to the server */
cout<<sockfd;
cout.flush();
string s;
getline(cin,s);
s+="\n";
n = write(sockfd,s.c_str(),s.length());

cout<<sockfd;
cout.flush();
if (n < 0) 
{
     perror("ERROR writing to socket");
     exit(1);
}
/* Now read server response */
bzero(buffer,256);

n = read(sockfd,buffer,255);
if (n < 0) 
{
     perror("ERROR reading from socket");
     exit(1);
}
printf("%s\n",buffer);
return 0;
}
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
using namespace std;

#define MAXLINE 100
int main(int argc, char** argv)
{
   int listenfd,connfd;
   struct sockaddr_in servaddr;
   char buff[MAXLINE+1] = " I am junius";
   
   unsigned short port;
   int flag=1,len=sizeof(int);
   port=19782;
   if( (listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
   {
     cout << "create socket failed" << endl;     
   }
   
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(port);

   //if there is a connection just release, server restart will be failed.
   //because there is a 2MSL timer for port re-binding
   if( setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, len) == -1)
   {
      cout << "set option failed" << endl;
      
   }
   
   if( bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
   {
      cout << "binding failed" << endl;
      
   }
   else
     cout << "binding successful" << endl;
      
   if( listen(listenfd,5) == -1)
   {
     cout << "listening failed" << endl;
     
   }
   for(;;)
   {
      if( (connfd = accept(listenfd,(struct sockaddr*)NULL,NULL)) == -1)
      {
         cout << "accept failed" << endl;         
      }
      send(connfd,(void*)buff,100,0);
      
     close(connfd);
     
  }
} 
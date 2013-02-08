#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <iostream>
using namespace std;
int main()
{
	struct sockaddr_in serverAddr;
	int sockfd;
	char recvLine[100];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
  if (sockfd < 0)
     cout << "error" << endl;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(19782);

  connect(sockfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));

  memset(recvLine,0,100);
  int n = read(sockfd,recvLine,100);
  cout << recvLine << endl;

struct sockaddr_in tmpAddr;
socklen_t len = (socklen_t)sizeof(tmpAddr);
  getsockname(sockfd,(sockaddr*)&tmpAddr,&len);
  cout << tmpAddr.sin_addr.s_addr << endl;
  getpeername(sockfd,(sockaddr*)&tmpAddr,&len);
  cout << ntohs(tmpAddr.sin_port) << endl;

return 1;
}

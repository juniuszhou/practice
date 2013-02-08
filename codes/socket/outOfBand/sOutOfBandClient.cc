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

  send(sockfd,"123",3,0);
  send(sockfd,"abc",3,0);
  sleep(1);

  send(sockfd,"456",3,MSG_OOB);
  sleep(1);

  send(sockfd,"123",3,0);
  sleep(1);

  send(sockfd,"789",3,MSG_OOB);
  sleep(1);

  send(sockfd,"123",3,0);
  sleep(1);

return 1;
}

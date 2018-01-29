#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"


#define PORT 4444
#define BUF_SIZE 2000

int main(int argc, char**argv) {
 struct sockaddr_in addr, cl_addr;
 int sockfd, ret;
 char buffer[BUF_SIZE];
 struct hostent * server;
 char * serverAddr;

 if (argc < 2) {
  printf("Kullanılan: client < ip address >\n");
  exit(1);
 }

 serverAddr = argv[1];

 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {
  printf("Soket oluşturulurken hata oluştu\n");
  exit(1);
 }
 printf("Soket oluşturuldu\n");

 memset(&addr, 0, sizeof(addr));
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = inet_addr(serverAddr);
 addr.sin_port = PORT;

 ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 if (ret < 0) {
  printf("Server'a bağlanırken hata oluştu\n");
  exit(1);
 }
 printf("Server'a bağlanıldı\n");

 memset(buffer, 0, BUF_SIZE);
 printf("Mesajızını giriniz: ");

 while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
  ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
  if (ret < 0) {
   printf("Veri gönderilirken hata oluştu\n\t-%s", buffer);
  }
  ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
  if (ret < 0) {
   printf("Veri alınırken hata oluştu\n");
  } else {
   printf("Alınan: ");
   fputs(buffer, stdout);
   printf("\n");
	
  }
 }

 return 0;
}

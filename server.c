#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"

#define PORT 4444

#define CLADDR_LEN 100

void main() {

 struct sockaddr_in adres, client_addr;
 int soket, len, ret, yenisocket;
 char buffer[1000];
 pid_t cocukkontrol;
 char clientAddr[CLADDR_LEN];

 soket = socket(AF_INET, SOCK_STREAM, 0);

 printf("Soket oluşturuldu\n");

 memset(&adres, 0, sizeof(adres));
 adres.sin_family = AF_INET;
 adres.sin_addr.s_addr = INADDR_ANY;
 adres.sin_port = PORT;


//socket iletisim kurulan yol

 ret = bind(soket, (struct sockaddr *) &adres, sizeof(adres));

 printf("Bağlantı gerçekleitirildi.\n");

 printf("Client bekleniyor\n");

 listen(soket, 10);

 for (;;) { 
  len = sizeof(client_addr); 
  //client adres bilgilerinin tutulduğu alana ait gösterici ile soketi bagladık
  yenisocket = accept(soket, (struct sockaddr *) &client_addr, &len);
  if (yenisocket < 0) {
   printf("Client bağlanmadı\n");
   exit(1);
  }
  printf("Client ile bağlantı gerçekleştirildi\n");

  inet_ntop(AF_INET, &(client_addr.sin_addr), clientAddr, CLADDR_LEN);
  if ((cocukkontrol = fork()) == 0) {

   close(soket);


   for (;;) {
    memset(buffer, 0, 1000);
    ret = recvfrom(yenisocket, buffer, 1000, 0, (struct sockaddr *) &client_addr, &len);
   
    printf("Alınan mesaj: %s\n", buffer);


    memset(buffer, 0, 1000);
    printf("Mesajınızı girin: ");
    while (fgets(buffer, 1000, stdin) != NULL) {
    ret = sendto(yenisocket, buffer, 1000, 0, (struct sockaddr *) &client_addr, sizeof(client_addr));
    break;

     }

    printf("Gönderilen mesaj: %s\n",  buffer);
   }
  }

  close(yenisocket);
 }
}

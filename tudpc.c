#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
    char buf[100];
    pid_t pid;
    socklen_t len;
    int sock_desc;
    struct sockaddr_in server;

    sock_desc=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8084);



    do{
        printf("Enter the message to be sent: ");
        scanf("%s",buf);
        sendto(sock_desc,buf,100,0,(struct sockaddr*)&server,sizeof(server));
        if(strcmp(buf,"stop")==0){
            break;
        }

        len=sizeof(server);
        recvfrom(sock_desc,buf,100,0,(struct sockaddr*)&server,&len);
        printf("%s",buf);
    }while(strcmp(buf,"stop")!=0);
    close(sock_desc);
}

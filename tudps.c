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
    struct sockaddr_in server,client;

    sock_desc=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8084);

    bind(sock_desc, (struct sockaddr*)&server, sizeof(server));


    do{
        len=sizeof(client);
        recvfrom(sock_desc,buf,100,0,(struct sockaddr*)&client,&len);
        printf("Message received from client is: %s\n",buf);
        pid=fork();
        if(pid==0){
            time_t rawtime;
            struct tm *timeinfo;

            time(&rawtime);
            timeinfo=localtime(&rawtime);

            sprintf(buf,"Time is %2d:%2d:%2d\n",timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
            sendto(sock_desc,buf,100,0,(struct sockaddr*)&client,len);
        }
    }while(strcmp(buf,"stop")!=0);


    close(sock_desc);

}

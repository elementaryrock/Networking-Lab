#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
    char buf[100];
    socklen_t len;
    int sock_desc,temp_sock_desc;
    struct sockaddr_in server,client;

    sock_desc= socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    bind(sock_desc,(struct sockaddr*)&server,sizeof(server));

    listen(sock_desc,1);

    len=sizeof(client);
    temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);

    recv(temp_sock_desc,buf,100,0);
    printf("Message received from client: %s\n",buf);

    printf("Enter message to be sent to client: ");
    fgets(buf,100,stdin);
    send(temp_sock_desc,buf,100,0);

    close(temp_sock_desc);
    close(sock_desc);
}

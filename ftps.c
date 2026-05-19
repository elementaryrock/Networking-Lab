#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    char buf[100],fileContent[1024];
    int sock_desc,client_desc;
    socklen_t len;
    struct sockaddr_in server,client;

    sock_desc=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8085);

    bind(sock_desc,(struct sockaddr*)&server,sizeof(server));

    listen(sock_desc,1);

    len=sizeof(client);
    client_desc=accept(sock_desc,(struct sockaddr*)&client,&len);

    recv(client_desc,buf,100,0);
    buf[strcspn(buf,"\n")]='\0';
    printf("\nMessage received from client: %s\n",buf);

    FILE *fp;
    fp=fopen(buf,"r");
    if (fp==NULL){
        printf("File not Found");
        strcpy(fileContent,"ERROR");
        send(client_desc,fileContent,sizeof(fileContent),0);
    }
    else{
        int readc=fread(fileContent,1,sizeof(fileContent),fp);
        fileContent[readc]='\0';
        send(client_desc,fileContent,sizeof(fileContent),0);
        fclose(fp);
        }

    close(client_desc);
    close(sock_desc);
    }


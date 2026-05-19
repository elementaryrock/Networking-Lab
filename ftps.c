#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


int main(){
    char buf[100];
    char fileContent[1024];
    int sock_desc,client_desc;
    socklen_t len;
    struct sockaddr_in server,client;

    sock_desc=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8090);

    bind(sock_desc,(struct sockaddr*)&server,sizeof(server));

    listen(sock_desc,1);

    len=sizeof(client);
    client_desc=accept(sock_desc,(struct sockaddr*)&client,&len);

    recv(client_desc,buf,sizeof(buf),0);
    buf[strcspn(buf,"\n")] = '\0';
    printf("%s",buf);

    FILE *fp=fopen(buf,"r");
    if (fp==NULL){
        strcpy(fileContent,"ERROR");
        printf("File not found");
    }
    else{
        int readCount = fread(fileContent,1,sizeof(fileContent)+1,fp);
        fileContent[readCount]='\0';
    }
    send(client_desc,fileContent,sizeof(fileContent)+1,0);
    fclose(fp);
    close(client_desc);
    close(sock_desc);
}

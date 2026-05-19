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
    struct sockaddr_in server;

    sock_desc=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8090);

    connect(sock_desc,(struct sockaddr*)&server,sizeof(server));

    printf("Enter the filename: ");
    fgets(buf,sizeof(buf),stdin);
    send(sock_desc,buf,sizeof(buf),0);

    recv(sock_desc,fileContent,sizeof(buf)+1,0);

    printf("%s",fileContent);

    if(strcmp(fileContent,"ERROR")!=0){
        FILE *fp=fopen("re.txt","w");
        if(fp!=NULL){
            fprintf(fp,"%s",fileContent);
        }
        else{
            printf("File not found");
        }
        fclose(fp);
    }

    send(client_desc,fileContent,sizeof(fileContent)+1,0);

    close(sock_desc);
}

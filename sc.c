#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

void Stop(int FrameSize);
void Go(int FrameSize,int WindowSize);
void Sel(int FrameSize,int WindowSize);

int main(){
    int FrameSize=5,WindowSize=3,c;
    srand(time(NULL));
    printf("\nMenu:\n1.Stop-and-Wait\n2.Go-Back-N\n3.Selective-Repeat\n");
    printf("\nEnter Choice: \n");
    scanf("%d",&c);

    switch(c){
        case 1:
            Stop(FrameSize);
            break;
        case 2:
            Go(FrameSize,WindowSize);
            break;
        case 3:
            Sel(FrameSize,WindowSize);
            break;
    }
}

void Stop(int FrameSize){
    int i=1;
    while(i<FrameSize){
        printf("\n[[Sending] Frame %d]\n",i);
        if(rand() %5==0){
            printf("\n[[ERROR]Dropped Frame%d]\n",i);
            continue;
        }
        printf("\n[[RECEIVED]Frame %d]\n",i);
        i++;
    }
}

void Go(int FrameSize,int WindowSize){
    int ack=0,send=0;
    while(ack<FrameSize){

        for(int i=send;i<ack+WindowSize && i<FrameSize;i++){
            printf("\n[Send] Frame %d",i+1);
            send++;
        }
        if(rand()%4==0){
            printf("\n[[ERROR]Dropped Frame %d]\n",ack+1);
        }
        else{
            printf("\n[[RECEIVED]Frame %d]\n",ack+1);
            ack++;
        }

    }
}


void Sel(int FrameSize,int WindowSize){
    bool ack[10]={false};
    int ackc=0,pass=1;
    while(ackc<FrameSize){
        printf("\nPass %d",pass);
        pass++;
        int send=0;
        for(int i=0;i<FrameSize && send<WindowSize;i++){
            if(ack[i]){
                continue;
            }

            send++;
            printf("\n[Send] Frame %d",i+1);

            if(rand()%3!=0){
                printf("\n[[RECEIVED]Frame %d]\n",i+1);
                ack[i]=true;
                ackc++;
            }
            else{
                printf("\n[[ERROR]Dropped Frame %d]\n",i+1);
            }
        }
    }
}

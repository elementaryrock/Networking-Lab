#include <stdio.h>

int main(){
    int b,op,i,bs=0,n;

    printf("\nEnter bucket capacity,output rate and no of packets :\n");
    scanf("%d%d%d",&b,&op,&n);

    int a[n];

    for(i=0;i<n;i++){
        printf("\nEnter size of packet %d :\n",i+1);
        scanf("%d",&a[i]);
    }

    for(i=0;i<n;i++){
        printf("\n======Time is %d\n======",i+1);
        printf("\nIncoming packet %d\n",i+1);
        printf("\nOutput rate: %d\n",op);
        if(a[i]+bs<=b){
            bs=bs+a[i];
            printf("\nAccepted\n");
        }
        else{
            printf("\nRejected\n");
        }

        if(bs!=0){
            if(bs>op){
                bs=bs-op;
                printf("\nLeaked size : %d\n",op);
            }
            else{
                printf("\nLeaked size : %d\n",bs);
                bs=0;
            }
        }
        else{
            printf("\nNo packets to remove\n");
        }
    }
    int extra_time=n+1;
    while(bs>0){
        printf("\n======Time is %d\n======",extra_time++);
        printf("\nIncoming packet 0\n");
        printf("\nOutput rate: %d\n",op);
        if(bs>op){
            bs=bs-op;
            printf("\nLeaked size : %d\n",op);
        }
        else{
            printf("\nLeaked size : %d\n",bs);
            bs=0;
        }
    }
}

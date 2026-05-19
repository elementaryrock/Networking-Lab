#include <stdio.h>

int main(){
    int b,op,i,bs=0,n;

    printf("Enter bucket capacity,output rate and no of incoming packets: ");
    scanf("%d%d%d",&b,&op,&n);

    int a[n];

    for (i=0;i<n;i++){
        printf("Enter packet size of packet %d: ",i+1);
        scanf("%d",&a[i]);
    }

    for (i=0;i<n;i++){
        printf("Time is %d\n",i+1);
        printf("incoming packet: %d\n",a[i]);
        printf("output rate: %d\n",op);

        if(a[i]+bs<=b){
            bs=bs+a[i];
            printf("Accepted\n");
        }
        else{
            printf("Rejected\n");
        }
        if(bs!=0){
            if(bs>op){
                bs=bs-op;
                printf("Leaked data is %d\n",op);
            }
            else{
                printf("Leaked data is %d\n",bs);
                bs=0;
            }
        }
        else{
            printf("No packets to remove\n");
        }
    }

    int extra_tick=n+1;

    while(bs>0){
        printf("Time is %d\n",extra_tick++);
        printf("output rate: %d\n",op);
        if(bs>op){
            bs=bs-op;
            printf("Leaked data is %d\n",op);
        }
        else{
            printf("Leaked data is %d\n",bs);
            bs=0;
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

void stopAndWait(int totalFrames);
void goBackN(int totalFrames, int windowSize);
void selectiveRepeat(int totalFrames, int windowSize);

int main() {
    int choice, totalFrames = 5, windowSize = 3;
    srand(time(NULL));
    printf("--- Network Flow Control Simulation ---\n");
    printf("1. Stop and Wait ARQ\n");
    printf("2. Go-Back-N ARQ\n");
    printf("3. Selective Repeat ARQ\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: stopAndWait(totalFrames); break;
        case 2: goBackN(totalFrames, windowSize); break;
        case 3: selectiveRepeat(totalFrames, windowSize); break;
        default: printf("Invalid choice!\n");
    }

    return 0;
}

void stopAndWait(int totalFrames) {
    int i = 1;
    while (i <= totalFrames) {
        printf("\n[Sender]: Sending Frame %d...", i);
        if (rand() % 5 == 0) {
            printf("\n[Error]: Frame %d lost! Retransmitting...", i);
            continue;
        }
        printf("\n[Receiver]: Frame %d received. Sending ACK %d...", i, i + 1);
        i++;
    }
    printf("\n\nAll frames sent successfully.\n");
}

void goBackN(int totalFrames, int windowSize) {
    int sent = 0, acked = 0;
    while (acked < totalFrames) {
        for (int i = sent; i < acked + windowSize && i < totalFrames; i++) {
            printf("\n[Sender]: Sending Frame %d", i);
            sent++;
        }
        int randomBit = rand() % 4;
        if (randomBit == 0) {
            printf("\n[Error]: Frame %d lost! Window resets.", acked);
            sent = acked;
        } else {
            printf("\n[Receiver]: Received Frame %d. Sending ACK.", acked);
            acked++;
        }
    }
    printf("\n\nAll frames sent successfully.\n");
}

void selectiveRepeat(int totalFrames, int windowSize) {
    printf("\n========== Selective Repeat ARQ ==========\n");

    bool acked[64] = {false};
    int ackedCount = 0;
    int pass = 1;

    while (ackedCount < totalFrames) {
        printf("--- Pass %d ---\n", pass);
        pass++;

        int sent = 0;
        for (int i = 0; i < totalFrames && sent < windowSize; i++) {
            if (acked[i]==true)
                continue;

            sent++;
            printf("  [Sender] : Sending Frame %d", i);

            if (rand() % 3!= 0){
                printf(" -> ACKed\n");
                acked[i] = true;
                ackedCount++;
            } else {
                printf(" -> Dropped!\n");
            }
        }
        printf("\n");
    }

    printf(">> All %d frames delivered successfully.\n", totalFrames);
}

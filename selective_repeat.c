#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int sent;
    int ack;
    int received;
} Frame;

void selectiveRepeat(int totalFrames, int windowSize) {
    Frame *frames = (Frame *)malloc(sizeof(Frame) * totalFrames);
    for (int i = 0; i < totalFrames; i++) {
        frames[i].sent = 0;
        frames[i].ack = 0;
        frames[i].received = 0;
    }

    int base = 0;
    srand(time(NULL));

    printf("\n=== Correct Selective Repeat ARQ Simulation ===\n");

    while (base < totalFrames) {
        printf("\nSender Window: ");
        for (int i = base; i < base + windowSize && i < totalFrames; i++) {
            printf("[%d] ", i);
        }
        printf("\n");

        for (int i = base; i < base + windowSize && i < totalFrames; i++) {
            if (!frames[i].sent) {
                printf("Sending Frame %d...\n", i);
                frames[i].sent = 1;
            }
        }

        for (int i = base; i < base + windowSize && i < totalFrames; i++) {
            if (frames[i].ack) continue;

            int ackReceived = rand() % 2;

            if (ackReceived) {
                printf("Frame %d received. ACK sent.\n", i);
                frames[i].ack = 1;
                frames[i].received = 1;
            } else {
                printf("Frame %d lost! No ACK.\n", i);
            }
        }

        for (int i = base; i < base + windowSize && i < totalFrames; i++) {
            if (!frames[i].ack) {
                printf("Retransmitting Frame %d...\n", i);
                printf("Frame %d received after retransmission. ACK sent.\n", i);
                frames[i].ack = 1;
                frames[i].received = 1;
            }
        }

        while (base < totalFrames && frames[base].ack) {
            base++;
        }
    }

    printf("\nAll frames sent and acknowledged successfully using Selective Repeat ARQ.\n");

    free(frames);
}

int main() {
    int totalFrames, windowSize;

    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);

    printf("Enter window size: ");
    scanf("%d", &windowSize);

    selectiveRepeat(totalFrames, windowSize);

    return 0;
}

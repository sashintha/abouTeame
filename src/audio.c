#include "address_map_arm.h"

#define BUF_SIZE 80000 // about 10 seconds of buffer (@ 8K samples/sec)
#define BUF_THRESHOLD 96 // 75% of 128 word buffer

volatile int * LED_ptr = (int *)LED_BASE;
volatile int * audio_ptr = (int *) AUDIO_BASE;

// audio playback
int fifospace;
int play = 0, bufferIndex = 0;
int leftBuffer[BUF_SIZE];
int rightBuffer[BUF_SIZE];

// if timer = 0 play sound

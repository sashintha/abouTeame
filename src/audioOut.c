#include "address_map_arm.h"

// define pointers
volatile int * SW_ptr = (int *)SW_BASE; //pointer for switches
volatile int * LED_ptr = (int *)LED_BASE; //pointer for LEDs
volatile int * SSD_ptr1 = (int *)HEX3_HEX0_BASE; //pointer for SSD
volatile int * SSD_ptr2 = (int *)HEX5_HEX4_BASE; //pointer for SSD
volatile int * audio_ptr = (int *)AUDIO_BASE; //pointer for audio base

// hardcode for testing
// volatile int * SW_ptr = (int *)0xFF200040; //pointer for switches
// volatile int * LED_ptr = (int *)0xFF200000; //pointer for LEDs
// volatile int * SSD_ptr1 = (int *)0xFF200020; //pointer for SSD
// volatile int * SSD_ptr2 = (int *)0xFF200030; //pointer for SSD
// volatile int * audio_ptr = (int *)0xFF203040;

// ------ TO-DO------ //
//
// Wait for signal from timer file when timer has finished
// output audio by writing FIFO to left and right channels (FIFO max depth: 128 32-bit words)
//
// ------------------ //


typedef struct ctrlStruct{
	int control;
	int fifospace;
    int leftData;
    int rightData;
}ctrlStruct;

void main(){

}
#include "address_map_arm.h"

// define pointers
volatile int * SW_ptr = (int *)SW_BASE; //pointer for switches
volatile int * LED_ptr = (int *)LED_BASE; //pointer for LEDs
volatile int * SSD_ptr1 = (int *)HEX3_HEX0_BASE; //pointer for SSD
volatile int * SSD_ptr2 = (int *)HEX5_HEX4_BASE; //pointer for SSD

// hardcode for testing
// volatile int * SW_ptr = (int *)0xFF200040; //pointer for switches
// volatile int * LED_ptr = (int *)0xFF200000; //pointer for LEDs
// volatile int * SSD_ptr1 = (int *)0xFF200020; //pointer for SSD
// volatile int * SSD_ptr2 = (int *)0xFF200030; //pointer for SSD

// ------ TO-DO------ //
//
// might want to include functionality for moving arm ?
//
// also create some sort of table to store different tea types and their corresponding steep times and temperatures
//
// figure out how to connect to i/o ports for audio
//
// ------------------ //

typedef struct ctrlStruct{
	int type;
	int currentTemp;
}ctrlStruct;

void Start(ctrlStruct* ctrlStruct);
void Stop(ctrlStruct* ctrlStruct);
void Pause(ctrlStruct* ctrlStruct);
void DisplayTimer(ctrlStruct* ctrlStruct);
void TeaSelect(ctrlStruct* ctrlStruct);
void ArmMovement(ctrlStruct* ctrlStruct);
void PlayAudio();
int ReadSwitches();

int ReadSwitches() {
    // return switch
	return *SW_ptr;
}

void Start(ctrlStruct* ctrlStruct){
    // start timer
    // lower arm

}

void Stop(ctrlStruct* ctrlStruct){
    // stop timer
    // raise arm

}

void Pause(ctrlStruct* ctrlStruct){
    // pause timer
    // raise arm

}

void DisplayTimer(ctrlStruct* ctrlStruct){
    // display timer on SSD

}

void TeaSelect(ctrlStruct* ctrlStruct){
    // return tea values

}

void ArmMovement(ctrlStruct* ctrlStruct){
    // control arm movement (up and down)

}

void PlayAudio(){
    // play audio
}

void main(){
//printf("%d \n");

    while(1){
    // ------ STAND-BY MODE ------ //
    // wait for input from on button -> tea selection -> start button
    // --------------------------- //


    // ------ STEEPING MODE ------ //
    // using tea type select pre-defined time -> heat up water to desired temp,
    // lower arm -> start timer -> display timer
    // --------------------------- //


    // ------ FINISHED MODE ------ //
    // timer reaches 0 -> raise arm -> display visual feedback
    // --------------------------- //


    }

}


#include "address_map_arm.h"
#include "timer.c"

// define pointers
volatile int * SW_ptr = (int *)SW_BASE; //pointer for switches
volatile int * LED_ptr = (int *)LED_BASE; //pointer for LEDs
volatile int * SSD_ptr1 = (int *)HEX3_HEX0_BASE; //pointer for SSD
volatile int * SSD_ptr2 = (int *)HEX5_HEX4_BASE; //pointer for SSD

void Start();
void Stop();
void Pause();
void DisplayTimer();
void TeaSelect();
void ArmMovement();
int ReadSwitches();

// might want to include functionality for moving arm ?

// also create some sort of table to store different tea types and their corresponding steep times and temperatures

typedef struct ctrlStruct{
	int type;
	int currentTemp;
}ctrlStruct;

int ReadSwitches() {
    // return switch
	return *SW_ptr;
}

void Start(){
    // start timer
    // lower arm

}

void Stop(){
    // stop timer
    // raise arm

}

void Pause(){
    // pause timer
    // raise arm

}

void DisplayTimer(){
    // display timer on SSD

}

void TeaSelect(){
    // return tea values

}

void ArmMovement(){
    // control arm movement (up and down)

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


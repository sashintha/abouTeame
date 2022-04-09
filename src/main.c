#include "address_map_arm.h"
#include "audio.c"

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


//time in sec
int teaTimeTable[] = {240,90, 150,150, 300, 180, 240, 450, 450};


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
void SetTimer(int time){
    // set timer based on tea type
}
void DisplayTimer(ctrlStruct* ctrlStruct){
    // display timer on SSD

}

void TeaSelect(ctrlStruct* ctrlStruct){
    // return tea values
    // use switches 0-8
    // switch values 2^(switch#)

    int value = ReadSwitches();
     switch(value) {
        case 0: 
            //black, 4 min
            SetTimer(teaTimeTable[0]);
            break; 
        case 1:
            //green, 90 sec
            SetTimer(teaTimeTable[1]);
            break; 
        case 2:
            //white, 2.5 min
            SetTimer(teaTimeTable[2]);
            break; 
        case 4:
            //oolong, 2.5 min
            SetTimer(teaTimeTable[3]);
            break; 
        case 8:
            //Pu-erh, 5 min
            SetTimer(teaTimeTable[4]);
            break; 
        case 16:
            //Purple, 3 min
            SetTimer(teaTimeTable[5]);
            break; 
        case 32:
            //Mate, 4 min
            SetTimer(teaTimeTable[6]);
            break; 
        case 64:
            //Herbal, 5-10 min
            SetTimer(teaTimeTable[7]);
            break; 
        case 128:
            //Rooibos, 5-10 min
            SetTimer(teaTimeTable[8]);
            break; 

    }

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


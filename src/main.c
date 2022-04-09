#include "address_map_arm.h"
#include "audio.c"

// define pointers
volatile int * SW_ptr = (int *)SW_BASE; //pointer for switches
volatile int * LED_ptr = (int *)LED_BASE; //pointer for LEDs
volatile int * SSD_ptr1 = (int *)HEX3_HEX0_BASE; //pointer for SSD
volatile int * SSD_ptr2 = (int *)HEX5_HEX4_BASE; //pointer for SSD
volatile GPIO *gpio_ptr = (GPIO *)0xff200060;
volatile ADC *adc_ptr = (ADC *)0xff204000;


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

// each value increment by 5 deg, start at 0C, end at 105C, total 22 temp values
int voltageTable[] = {1192,1387,1585,1802,2012,2226,2431,2627,2813,2986,3143,3286,3419,3535,3640,3731,3816,3888,3946,4007,4057,4096};


typedef struct ctrlStruct{
	int type;
	int currentTemp;

}ctrlStruct;
typedef struct _GPIO{
    int data;
    int direction;
    int mask;
    int edge;
} GPIO;

typedef struct _ADC{
    int ch0;
    int ch1;
} ADC;



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

void readTemp() {
    int channel0;
    int adc_data0;
	gpio_ptr->direction = 0xffff; //make GPIO all output
    adc_ptr->ch1 = 1; //write 1 to second channel to start auto-update
    while (1){
        
        //masking with 15th bit to check if channel is ready
		channel0 = adc_ptr -> ch0 & 1<<15; 

		//select which channel to use
		if(*(SW_ptr) & 0x1){
			if(channel0 == 0){
                //range = 0 - 4096
				adc_data0 = adc_ptr->ch0;
				display(adc_data0);
				
			}
		}
    }

}

//potentiometer changes in voltage
void display(temp) {
    if(temp < voltageTable[0] ) {
        printf("temp = 0");
    } else if (temp == voltageTable[1]) {
        printf("temp = 5");
    }else if (temp == voltageTable[2]) {
        printf("temp = 10");

    }else if (temp == voltageTable[3]) {
        printf("temp = 15");
        
    }else if (temp == voltageTable[4]) {
        printf("temp = 20");
        
    }else if (temp == voltageTable[5]) {
        printf("temp = 25");
        
    }else if (temp == voltageTable[6]) {
        printf("temp = 30");
        
    }else if (temp == voltageTable[7]) {
        printf("temp = 35");
        
    }else if (temp == voltageTable[8]) {
        printf("temp = 40");
        
    }else if (temp == voltageTable[9]) {
        printf("temp = 45");
        
    }else if (temp == voltageTable[10]) {
        printf("temp = 50");
        
    }else if (temp == voltageTable[11]) {
        printf("temp = 55");
        
    }else if (temp == voltageTable[12]) {
        printf("temp = 60");
        
    }else if (temp == voltageTable[13]) {
        printf("temp = 65");
        
    }else if (temp == voltageTable[14]) {
        printf("temp = 70");
        
    }else if (temp == voltageTable[15]) {
        printf("temp = 75");
        
    }else if (temp == voltageTable[16]) {
        printf("temp = 80");
        
    }else if (temp == voltageTable[17]) {
        printf("temp = 85");
        
    }else if (temp == voltageTable[18]) {
        printf("temp = 90");
        
    }else if (temp == voltageTable[19]) {
        printf("temp = 95");

    }else if (temp == voltageTable[20]) {
        printf("temp = 100");

    }else if (temp == voltageTable[21]) {
        printf("temp = 105");

    }
    
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


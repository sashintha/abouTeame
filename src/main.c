// #include "address_map_arm.h"
// #include "audio.c"

// define pointers

volatile int * SW_ptr = (int *)0xFF200040; //pointer for switches
volatile int * LED_ptr = (int *)0xFF200000; //pointer for LEDs
volatile int * SSD_ptr1 = (int *)0xFF200020; //pointer for SSD
volatile int * SSD_ptr2 = (int *)0xFF200030; //pointer for SSD

//time in sec
int teaTimeTable[] = {240,90, 150,150, 300, 180, 240, 450, 450};

//tea temperatures
int teaTempTable[] = {100, 80, 80, 90, 100, 80, 68, 100, 100};

// each value increment by 5 deg, start at 0C, end at 105C, total 22 temp values
int voltageTable[] = {1192,1387,1585,1802,2012,2226,2431,2627,2813,2986,3143,3286,3419,3535,3640,3731,3816,3888,3946,4007,4057,4096};

typedef struct ctrlStruct{
	int type;
	int currentTemp;
    int teaTemp;
    int time;
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

volatile GPIO *gpio_ptr = (GPIO *)0xff200060;
volatile ADC *adc_ptr = (ADC *)0xff204000;

void Start(ctrlStruct* ctrlStruct);
void TeaSelect(int T);
void ArmMovement(ctrlStruct* ctrlStruct);
int ReadSwitches(ctrlStruct ctrlStruct);
void reset(ctrlStruct* ctrlStruct);

//

// This does not work...
void reset(ctrlStruct* ctrlStruct){
    ctrlStruct->currentTemp = 0;
    ctrlStruct->teaTemp = 0;
    ctrlStruct->time = 0;
    ctrlStruct->type = 0;
}

int ReadSwitches(ctrlStruct ctrlStruct) {
    int tempCheck = 0; 
    while(tempCheck == 0){
        if(*SW_ptr != 0){
            ctrlStruct.type = *SW_ptr; 
            tempCheck = 1;
        }
    }
    return ctrlStruct.type;
}

void TeaSelect(int T){
    int value = T;    
    printf("%d \n", value);
     switch(value) {
        case 1: 
            //black, 4 min
            *(LED_ptr) = 0x1;
            //ctrlStruct->time = teaTimeTable[0];
            //ctrlStruct->teaTemp = teaTempTable[0];
            break; 
        case 2:
            //green, 90 sec
            *(LED_ptr) = 0x2;
            //ctrlStruct->time = teaTimeTable[1];
            //ctrlStruct->teaTemp = teaTempTable[1];
            break; 
        case 4:
            //white, 2.5 min
            *(LED_ptr) = 0x3;
           // ctrlStruct->time = teaTimeTable[2];
           // ctrlStruct->teaTemp = teaTempTable[2];
            break; 
        case 8:
            *(LED_ptr) = 0x8;
            //oolong, 2.5 min
            //ctrlStruct->time = teaTimeTable[3];   
           // ctrlStruct->teaTemp = teaTempTable[3];        
            break; 
        case 16:
            *(LED_ptr) = 0xF;
            //Pu-erh, 5 min
           // ctrlStruct->time = teaTimeTable[4];
           // ctrlStruct->teaTemp = teaTempTable[4];
            break; 
        case 32:
            *(LED_ptr) = 0x20;
            //Purple, 3 min
           // ctrlStruct->time = teaTimeTable[5];
           // ctrlStruct->teaTemp = teaTempTable[5];
            break; 
        case 64:
         *(LED_ptr) = 0x40;
            //Mate, 4 min
            //ctrlStruct->time = teaTimeTable[6];
           // ctrlStruct->teaTemp = teaTempTable[6];
            break; 
        case 128:
         *(LED_ptr) = 0x80;
            //Herbal, 5-10 min
            //ctrlStruct->time = teaTimeTable[7];
            //ctrlStruct->teaTemp = teaTempTable[7];
            break;
        case 256:
            *(LED_ptr) = 0x100;
            //Rooibos, 5-10 min
            //ctrlStruct->time = teaTimeTable[8];
            //ctrlStruct->teaTemp = teaTempTable[8];
            break; 
        case 512:
             *(LED_ptr) = 0x200;
            //Rooibos, 5-10 min
            //ctrlStruct->time = teaTimeTable[8];
            //ctrlStruct->teaTemp = teaTempTable[8];
            break; 
   }
}

int readTemp(ctrlStruct ctrlStruct) {
    int readChannel;
    int adc_data;
	gpio_ptr->direction = 0xffff; //make GPIO all output
    adc_ptr->ch1 = 1; //write 1 to second channel to start auto-update
    while (1){
        //masking with 15th bit to check if channel is ready
		readChannel = adc_ptr -> ch0 & 1<<15; 
		// read from first channel
        if(readChannel == 0){
            adc_data = adc_ptr->ch0;
            //changeVoltage(adc_data);
            return adc_data;
        }
    }
}

//potentiometer changes in voltage
// void changeVoltage(temp) {
//     if(temp < voltageTable[0] ) {
//         printf("temp = 0");
//     } else if (temp == voltageTable[1]) {
//         printf("temp = 5");
//     }else if (temp == voltageTable[2]) {
//         printf("temp = 10");
//     }else if (temp == voltageTable[3]) {
//         printf("temp = 15");
//     }else if (temp == voltageTable[4]) {
//         printf("temp = 20");
//     }else if (temp == voltageTable[5]) {
//         printf("temp = 25");
//     }else if (temp == voltageTable[6]) {
//         printf("temp = 30");
//     }else if (temp == voltageTable[7]) {
//         printf("temp = 35");
//     }else if (temp == voltageTable[8]) {
//         printf("temp = 40");
//     }else if (temp == voltageTable[9]) {
//         printf("temp = 45");
//     }else if (temp == voltageTable[10]) {
//         printf("temp = 50");
//     }else if (temp == voltageTable[11]) {
//         printf("temp = 55");
//     }else if (temp == voltageTable[12]) {
//         printf("temp = 60");
//     }else if (temp == voltageTable[13]) {
//         printf("temp = 65");
//     }else if (temp == voltageTable[14]) {
//         printf("temp = 70");
//     }else if (temp == voltageTable[15]) {
//         printf("temp = 75");
//     }else if (temp == voltageTable[16]) {
//         printf("temp = 80");
//     }else if (temp == voltageTable[17]) {
//         printf("temp = 85");
//     }else if (temp == voltageTable[18]) {
//         printf("temp = 90");  
//     }else if (temp == voltageTable[19]) {
//         printf("temp = 95");
//     }else if (temp == voltageTable[20]) {
//         printf("temp = 100");
//     }else if (temp == voltageTable[21]) {
//         printf("temp = 105");
//     }
// }

/// FINAL MAIN

void main(){
    ctrlStruct ctrlStruct;
    int selectedTea;

    // READ SWITCH (to get what tea to steep)
    selectedTea = ReadSwitches(ctrlStruct); 
   
    while(1){
    // GET TEMP FROM GPIO
    //ctrlStruct.currentTemp = readTemp(ctrlStruct);

    // SET TEA
    TeaSelect(selectedTea);

    }

}

// --------------------------- //
//  THIS SECTION IS FOR TIMER
// --------------------------- //




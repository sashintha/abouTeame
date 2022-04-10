// #include "address_map_arm.h"

// volatile int * SW_ptr = (int *)SW_BASE; //pointer for switches
// volatile int * LED_ptr = (int *)LED_BASE; //pointer for LEDs
// volatile int * SSD_ptr1 = (int *)HEX3_HEX0_BASE; //pointer for SSD
// volatile int * SSD_ptr2 = (int *)HEX5_HEX4_BASE; //pointer for SSD
// volatile int * BTN_ptr = (int *)KEY_BASE; //pointer for push buttons

// hardcode for testing
volatile int * SW_ptr = (int *)0xFF200040; //pointer for switches
volatile int * LED_ptr = (int *)0xFF200000; //pointer for LEDs
volatile int * SSD_ptr1 = (int *)0xFF200020; //pointer for SSD
volatile int * SSD_ptr2 = (int *)0xFF200030; //pointer for SSD
volatile int * BTN_ptr = (int *)0xFF200050; //pointer for push buttons

int lookUpTable[] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F};

typedef struct a9_timer{
	int loadValue;
	int currentValue;
	int control;
	int status;
}a9_timer;

typedef struct clock_{
	int ms;
	int s;
	int m;
}clock;

typedef struct mainStruct {
	a9_timer* timer;
	clock time;
	int lastButtonState;
	int done;
} mainStruct;

void start_timer(mainStruct* ctrlStruct);
void stop_timer(mainStruct* ctrlStruct);
void update_timer(mainStruct* ctrlStruct);
void check_timer(mainStruct* ctrlStruct);
void lap_timer(mainStruct* ctrlStruct);
void display_hex(mainStruct* ctrlStruct);
void clear_timer(mainStruct* ctrlStruct);
void checkBtn(mainStruct* ctrlStruct);

void start_timer(mainStruct* ctrlStruct){ //starts the timer counting, clears previous timeout flag
	ctrlStruct->timer->control = 0b0011;
	ctrlStruct->time.m = 0b0;
	ctrlStruct->time.s = 0b01100;
	ctrlStruct->time.ms = 0b0;
}

void stop_timer(mainStruct* ctrlStruct){ //stops timer
	ctrlStruct->timer->control = 0;
}

void update_timer(mainStruct* ctrlStruct){	

	ctrlStruct->time.ms -= 1;

	if(ctrlStruct->time.ms <= 0){
		ctrlStruct->time.s -= 1;
		ctrlStruct->time.ms = 100;
	}
	if(ctrlStruct->time.s <= 0){
		if(ctrlStruct->time.m > 0){
			ctrlStruct->time.m -= 1;
			ctrlStruct->time.s = 60;
		}else{
			ctrlStruct->time.m = 0;
			ctrlStruct->time.s = 0;
	 		ctrlStruct->done = 1;
		}
	}
	
}

void check_timer(mainStruct* ctrlStruct){ //returns 0 if timer is still counting, 1 if timer is done
	if(ctrlStruct->timer->status == 0){
		return;
	}
	else{
		//reset status flag by writing 1 to it
		ctrlStruct->timer->status = 1;
		update_timer(ctrlStruct);
	}
}

void display_hex(mainStruct* ctrlStruct){ //display timer values on display
 	//int a = 0;
    int b = 0;
	int c = 0;
	int currDigit = 0;
	//int tempMS = 0;
	int tempS = 0;	
	int tempM = 0;

	int switchState = (*(int *)0xff200040);

		// load main time
		//tempMS = ctrlStruct->time.ms;
		tempS = ctrlStruct->time.s;	
		tempM = ctrlStruct->time.m;
		
		printf("%d %d \n",tempM, tempS);
		//printf("%d \n",tempM);

		if(ctrlStruct->done == 0){
			for(int i = 0; i < 2 ; i++)
			{

				currDigit = tempS % 10; 
				tempS -= currDigit;
				tempS = tempS / 10;

				b += lookUpTable[currDigit] << (8*i); //bitshift left for second digit

				currDigit = tempM % 10; 
				tempM -= currDigit;
				tempM = tempM / 10;

				c += lookUpTable[currDigit] << (8*i); //bitshift left for second digit

			}
		}else{
			for(int i = 0; i < 2 ; i++){
			//ctrlStruct->time.ms;
			ctrlStruct->time.s;
			ctrlStruct->time.m;
			//
			b += lookUpTable[0] << (8*i); //bitshift left for second digit
			c += lookUpTable[0] << (8*i); //bitshift left for second digit
			//
			}
		}

	b += c <<16; 
	*SSD_ptr1 = b; //display number

}

void clear_timer(mainStruct* ctrlStruct){ //clears timer
	//ctrlStruct->time.ms = 0;
	ctrlStruct->time.m = 0;
	ctrlStruct->time.s = 0;
	ctrlStruct->timer->control = 0;
	ctrlStruct->timer->status = 1;
	ctrlStruct->lastButtonState = 0;
	ctrlStruct->done = 0;
	display_hex(ctrlStruct);
}

void checkBtn(mainStruct* ctrlStruct){
	int temp = *BTN_ptr;

	//debouncing btns
	if(temp == ctrlStruct->lastButtonState){
		return;
	}
	else{
		ctrlStruct->lastButtonState = temp;
	}

	if(temp == 1){
		start_timer(ctrlStruct);
	}
	else if(temp == 2){
		stop_timer(ctrlStruct);
	}
	else if(temp == 4){
		clear_timer(ctrlStruct);
	}
}

int main(){
	mainStruct ctrlStruct;
	ctrlStruct.timer = (a9_timer*)0xfffec600;
	ctrlStruct.timer->loadValue = 2000000; // timeout = 1/(200 MHz) x 200x10^6 = 1 sec
	//clear_timer(&ctrlStruct);

	while(1){
		checkBtn(&ctrlStruct);
		check_timer(&ctrlStruct);
		display_hex(&ctrlStruct);
	}
}

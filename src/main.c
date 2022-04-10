#define BUF_SIZE 40000   // about 10 seconds of buffer (@ 8K samples/sec)
#define BUF_THRESHOLD 96 // 75% of 128 word buffer

// define pointers
volatile int *SW_ptr = (int *)0xFF200040;   // pointer for switches
volatile int *LED_ptr = (int *)0xFF200000;  // pointer for LEDs
volatile int *SSD_ptr1 = (int *)0xFF200020; // pointer for SSD
volatile int *SSD_ptr2 = (int *)0xFF200030; // pointer for SSD
volatile int *BTN_ptr = (int *)0xFF200050;  // pointer for push buttons

// audio pointers
volatile int *red_LED_ptr = (int *)0xFF200000;
volatile int *audio_ptr = (int *)0xFF203040;
volatile int *KEY_ptr = (int *)0xFF200050;
//

// time in sec
int teaTimeTable[] = {240, 90, 150, 150, 300, 180, 240, 450, 450};

// tea temperatures
int teaTempTable[] = {100, 80, 80, 90, 100, 80, 68, 100, 100};

// each value increment by 5 deg, start at 0C, end at 105C, total 22 temp values
int voltageTable[] = {1192, 1387, 1585, 1802, 2012, 2226, 2431, 2627, 2813, 2986, 3143, 3286, 3419, 3535, 3640, 3731, 3816, 3888, 3946, 4007, 4057, 4096};

// values for seven segement display
int lookUpTable[] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F};

typedef struct ctrlStruct
{
    int type;
    int currentTemp;
    int teaTemp;
    int time;
    int timerStarted;
} ctrlStruct;

typedef struct _GPIO
{
    int data;
    int direction;
    int mask;
    int edge;
} GPIO;

typedef struct _ADC
{
    int ch0;
    int ch1;
} ADC;

typedef struct a9_timer
{
    int loadValue;
    int currentValue;
    int control;
    int status;
} a9_timer;

typedef struct clock_
{
    int ms;
    int s;
    int m;
} clock;

typedef struct timerStruct
{
    a9_timer *timer;
    clock time;
    int lastButtonState;
    int done;
    int timerStartedDone;
    int playAudio;
} timerStruct;

volatile GPIO *gpio_ptr = (GPIO *)0xff200060;
volatile ADC *adc_ptr = (ADC *)0xff204000;

void Start(ctrlStruct *ctrlStruct);
void TeaSelect(ctrlStruct *ctrlStruct, timerStruct *timeStruct, int T);
int ReadSwitches(ctrlStruct *ctrlStruct);

int ReadSwitches(ctrlStruct *ctrlStruct)
{
    int tempCheck = 0;
    while (tempCheck == 0)
    {
        if (*SW_ptr != 0)
        {
            ctrlStruct->type = *SW_ptr;
            tempCheck = 1;
            ctrlStruct->timerStarted = 1;
        }
    }
    return ctrlStruct->type;
}

void TeaSelect(ctrlStruct *ctrlStruct, timerStruct *timeStruct, int T)
{
    int value = T;
    switch (value)
    {
    case 1:
        // black, 4 min
        *(LED_ptr) = 0x1;
        timeStruct->time.m = 0b0100;
        timeStruct->time.s = 0b0;
        break;
    case 2:
        // green, 90 sec
        *(LED_ptr) = 0x2;
        timeStruct->time.m = 0b01;
        timeStruct->time.s = 0b011110;
        break;
    case 4:
        // white, 2.5 min
        *(LED_ptr) = 0x4;
        timeStruct->time.m = 0b010;
        timeStruct->time.s = 0b011110;
        break;
    case 8:
        *(LED_ptr) = 0x8;
        // oolong, 2.5 min
        timeStruct->time.m = 0b010;
        timeStruct->time.s = 0b011110;
        break;
    case 16:
        *(LED_ptr) = 0xF;
        // Pu-erh, 5 min
        timeStruct->time.m = 0b0101;
        timeStruct->time.s = 0b0;
        break;
    case 32:
        *(LED_ptr) = 0x20;
        // Purple, 3 min
        timeStruct->time.m = 0b011;
        timeStruct->time.s = 0b0;
        break;
    case 64:
        *(LED_ptr) = 0x40;
        // Mate, 4 min
        timeStruct->time.m = 0b0100;
        timeStruct->time.s = 0b0;
        break;
    case 128:
        *(LED_ptr) = 0x80;
        // Herbal, 5-10 min
        timeStruct->time.m = 0b0101;
        timeStruct->time.s = 0b0;
        break;
    case 256:
        *(LED_ptr) = 0x100;
        // Rooibos, 5-10 min
        timeStruct->time.m = 0b0101;
        timeStruct->time.s = 0b0;
        break;
    case 512:
        *(LED_ptr) = 0x200;
        // Rooibos, 5-10 min
        timeStruct->time.m = 0b0101;
        timeStruct->time.s = 0b0;
        break;
    }
}

int readTemp(ctrlStruct ctrlStruct)
{
    int readChannel;
    int adc_data;
    gpio_ptr->direction = 0xffff; // make GPIO all output
    adc_ptr->ch1 = 1;             // write 1 to second channel to start auto-update
    while (1)
    {
        // masking with 15th bit to check if channel is ready
        readChannel = adc_ptr->ch0 & 1 << 15;
        // read from first channel
        if (readChannel == 0)
        {
            adc_data = adc_ptr->ch0;
            changeVoltage(adc_data);
            return adc_data;
        }
    }
}

// potentiometer changes in voltage
 void changeVoltage(temp) {
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

// --------------------------- //
//            TIMER            //
// --------------------------- //

void start_timer(timerStruct *timeStruct);
void update_timer(timerStruct *timeStruct);
void check_timer(timerStruct *timeStruct);
void display_hex(timerStruct *timeStruct);
void clear_timer(timerStruct *timeStruct);
void checkBtn(timerStruct *timeStruct);
void check_KEYs(int *, int *, int *);

void start_timer(timerStruct *timeStruct)
{ // starts the timer counting, clears previous timeout flag
    timeStruct->timer->control = 0b0011;
    timeStruct->done = 0;

    // test values //
    timeStruct->time.m = 0b0;
    timeStruct->time.s = 0b101;
    // test values //

    timeStruct->time.ms = 0b0;
    timeStruct->timerStartedDone = 1;
}

void update_timer(timerStruct *timeStruct)
{
    timeStruct->time.ms -= 1;

    if (timeStruct->time.ms <= 0)
    {
        timeStruct->time.s -= 1;
        timeStruct->time.ms = 100;
    }
    if (timeStruct->time.s <= 0)
    {
        if (timeStruct->time.m > 0)
        {
            timeStruct->time.m -= 1;
            timeStruct->time.s = 60;
        }
        else
        {
            timeStruct->time.m = 0;
            timeStruct->time.s = 0;
            timeStruct->playAudio = 1;
        }
    }
}

void check_timer(timerStruct *timeStruct)
{ // returns 0 if timer is still counting, 1 if timer is done
    if (timeStruct->timer->status == 0)
    {
        return;
    }
    else
    {
        // reset status flag by writing 1 to it
        timeStruct->timer->status = 1;
        update_timer(timeStruct);
    }
}

void display_hex(timerStruct *timeStruct)
{ // display timer values on display
    int b = 0;
    int c = 0;
    int currDigit = 0;
    int tempS = 0;
    int tempM = 0;

    int switchState = (*(int *)0xff200040);

    // load main time
    tempS = timeStruct->time.s;
    tempM = timeStruct->time.m;

    if (timeStruct->done == 0)
    {
    for (int i = 0; i < 2; i++)
    {
        currDigit = tempS % 10;
        tempS -= currDigit;
        tempS = tempS / 10;

        b += lookUpTable[currDigit] << (8 * i); // bitshift left for second digit

        currDigit = tempM % 10;
        tempM -= currDigit;
        tempM = tempM / 10;

        c += lookUpTable[currDigit] << (8 * i); // bitshift left for second digit
    }
    }
    else
    {
        timeStruct->done = 1;
        for (int i = 0; i < 2; i++)
        {
            timeStruct->time.s;
            timeStruct->time.m;
            b += lookUpTable[0] << (8 * i); // bitshift left for second digit
            c += lookUpTable[0] << (8 * i); // bitshift left for second digit
        }
    }

    b += c << 16;
    *SSD_ptr1 = b; // display number
}

void clear_timer(timerStruct *timeStruct)
{ // clears timer
    timeStruct->time.ms = 0;
    timeStruct->time.m = 0;
    timeStruct->time.s = 0;
    timeStruct->timer->control = 0;
    // timeStruct->timer->status = 1;
    timeStruct->lastButtonState = 0;
    timeStruct->done = 0;
    display_hex(timeStruct);
}

// --------------------------- //
//            MAIN             //
// --------------------------- //
void main()
{
    ctrlStruct ctrlStruct;
    timerStruct timeStruct;
    timeStruct.timer = (a9_timer *)0xfffec600;
    timeStruct.timer->loadValue = 2000000; // timeout = 1/(200 MHz) x 200x10^6 = 1 sec

    clear_timer(&ctrlStruct);

    // FOR AUDIO
    timeStruct.playAudio = 0;
    int fifospace;
    int record = 0, play = 0, buffer_index = 0;
    int left_buffer[BUF_SIZE];
    int right_buffer[BUF_SIZE];
    // FOR AUDIO

    ctrlStruct.timerStarted = 0;
    timeStruct.timerStartedDone = 0;
    int selectedTea;

    // READ SWITCH (to get what tea to steep)
    selectedTea = ReadSwitches(&ctrlStruct);

    // SET TEA BASED OFF SELECTED SWITCH
    TeaSelect(&ctrlStruct, &timeStruct, selectedTea);

    while (1)
    {
        // GET TEMP FROM GPIO (currently useless)
        // constantly reading from GPIO to get changing temperature (simulating temperture change)
        // ctrlStruct.currentTemp = readTemp(ctrlStruct);

        if (timeStruct.playAudio == 1)
        {
            fifospace = *(audio_ptr + 1); // read the audio port fifospace register
            if ((fifospace & 0x00FF0000) > BUF_THRESHOLD)
            { // check WSRC
                // output data until the buffer is empty or the audio-out FIFO if full
                while ((fifospace & 0x00FF0000) && (buffer_index < BUF_SIZE))
                {
                    *(audio_ptr + 2) = left_buffer[buffer_index];
                    *(audio_ptr + 3) = right_buffer[buffer_index];

                    ++buffer_index;
                    fifospace = *(audio_ptr + 1); // read the audio port fifospace register
                }
            }
            timeStruct.playAudio = 0;
        }

        if (ctrlStruct.timerStarted == 1)
        {
            if (timeStruct.timerStartedDone == 0)
            {
                start_timer(&timeStruct);
            }
            if(timeStruct.done == 0){
                check_timer(&timeStruct);
                display_hex(&timeStruct);
            }
        }
    }
}

//#include "address_map_arm.h"
/* globals */
#define BUF_SIZE 40000   // about 10 seconds of buffer (@ 8K samples/sec)
#define BUF_THRESHOLD 96 // 75% of 128 word buffer
/* function prototypes */
void check_KEYs(int *, int *, int *);
/*******************************************************************************
 * This program performs the following:
 * 1. records audio for 10 seconds when KEY[0] is pressed. LEDR[0] is lit
 * while recording.
 * 2. plays the recorded audio when KEY[1] is pressed. LEDR[1] is lit while
 * playing.
 ******************************************************************************/

typedef struct audioStruct
{
    int control;
    int fifo_space;
    int leftData;
    int rightData;
} audioStruct;


    volatile int *red_LED_ptr = (int *)0xFF200000;
    volatile int *audio_ptr = (int *)0xFF203040;

int main(void)
{

    /* used for audio record/playback */
    int fifospace;
    int record = 0, play = 0, buffer_index = 0;
    int left_buffer[BUF_SIZE];
    int right_buffer[BUF_SIZE];
    /* read and echo audio data */
    record = 0;
    play = 0;

    *(red_LED_ptr) = 0x1; // turn on LEDR[0]
    fifospace = *(audio_ptr + 1); // read the audio port fifospace register
   
    if ((fifospace & 0x000000FF) > BUF_THRESHOLD)
    {   // check RARC
        // store data until the the audio-in FIFO is empty or the buffer
        // is full
        while ((fifospace & 0x000000FF) && (buffer_index < BUF_SIZE))
        {
            left_buffer[buffer_index] = *(audio_ptr + 2);
            right_buffer[buffer_index] = *(audio_ptr + 3);

            ++buffer_index;
            // if (buffer_index == BUF_SIZE)
            // {
            //     // done recording
            //     record = 0;
            //     *(red_LED_ptr) = 0x0; // turn off LEDR
            // }
            // fifospace = *(audio_ptr + 1); // read the audio port fifospace register
            
        }
    }

    while (1)
    {
        check_KEYs(&record, &play, &buffer_index);
        if (play)
        {
            *(red_LED_ptr) = 0x2; // turn on LEDR_1
            fifospace = *(audio_ptr + 1); // read the audio port fifospace register
            
            if ((fifospace & 0x00FF0000) > BUF_THRESHOLD)
            { // check WSRC
                // output data until the buffer is empty or the audio-out FIFO
                // is full
                while ((fifospace & 0x00FF0000) && (buffer_index < BUF_SIZE))
                {
                    *(audio_ptr + 2) = left_buffer[buffer_index];
                    *(audio_ptr + 3) = right_buffer[buffer_index];

                
                    ++buffer_index;
                    if (buffer_index == BUF_SIZE)
                    {
                        // done playback
                        play = 0;
                        *(red_LED_ptr) = 0x0; // turn off LEDR
                    }
                   fifospace = *(audio_ptr + 1); // read the audio port fifospace register
                   
                }
            }
        }
    }
}

/****************************************************************************************
 * Subroutine to read KEYs
 ****************************************************************************************/
void check_KEYs(int *KEY0, int *KEY1, int *counter)
{
    volatile int *KEY_ptr = (int *)0xFF200050;
    volatile int *audio_ptr = (int *)0xFF203040;
    //audioStruct ctrlStruct;

    int KEY_value;
    KEY_value = *(KEY_ptr); // read the pushbutton KEY values
    while (*KEY_ptr)
        ; // wait for pushbutton KEY release

    if (KEY_value == 0x1)
    { // check KEY0
        // reset counter to start recording
        *counter = 0;
        // clear audio-in FIFO
        *(audio_ptr) = 0x4;
        *(audio_ptr) = 0x0;

        *KEY0 = 1;
    }
    else if (KEY_value == 0x2) // check KEY1
    {
        // reset counter to start playback
        *counter = 0;
        // clear audio-out FIFO
        *(audio_ptr) = 0x8;
        *(audio_ptr) = 0x0;

        *KEY1 = 1;
    }
}
//
//	------------     MiniOS entry point     -------------
//

#include "stdio.h"
#include "minios/system.h"
#include "minios/hal/hal.h"

#define APP_MAX_SIZE	20480			//20 KB max size (the buffer occupies space!)
//It is not difficult to remove this limitation. The app loader can be written
//to load "on-the-fly" i.e. read one byte, load it, and discard it.
//The most difficult change is to extend HAL NVMem to enable this behavior


void error_sequence(uint8_t* msg );
void println( uint8_t* );
void load_app( uint8_t*, uint8_t*, uint32_t );
void execute_ram( uint8_t* );


// count down function reduce the satiety, energy, and happiness for 1
void count_down();
//the three attribute value of the pet 
uint8_t satiety= 100;
uint8_t energy= 100;
uint8_t happiness= 100;


uint8_t* app_name = "App.bin";	//App.bin by default
uint8_t app_buffer[APP_MAX_SIZE];
tMemRegion app_memreg;

int main(void)
{
	//Initializes the system
	system_init();
	
	hal_systimer_start(500, count_down());
	
	while(1); //if main returns we want to stop here...
	//else garbage gets executed.
	//Q: why? (Hint: Picture machine code in memory)
}
// s= satiety, e= energy, h= happiness
void count_down(void){
	if (satiety>0)
	{
		satiety-=satiety;
	}else{println("the satiety is 0.")}
		
	if (energy>0)
	{
		energy-=energy;
	}else{println("the energy is 0.")}
	
	if (happiness>0)
	{
		happiness-=happiness;
	}else{println("the happiness is 0.")}
	
	
}
void load_app( uint8_t* mem, uint8_t* binary, uint32_t size ){
	
	for(uint32_t i = 0; i<size; i++)
	mem[i] = binary[i];

}

void error_sequence( uint8_t* msg ){
	uint8_t error_msg[20];
	sprintf( error_msg, "%s not fnd", msg );
	
	while(true){
		println( error_msg );
		hal_led_write( Led0, !hal_led_read(Led0) );
		hal_led_write( Led1, !hal_led_read(Led1) );
		hal_led_write( Led2, !hal_led_read(Led2) );
		hal_led_write( Led3, !hal_led_read(Led3) );
		hal_led_write( Led4, !hal_led_read(Led4) );
		
		hal_delay(1500);
	}
}

uint32_t line_num = 0;
void println( uint8_t* string ){
	uint8_t c;
	
	while( c = *string++ )
	hal_display_putc( c );

	//newline + carriage return
	line_num = (line_num + 1) % hal_display_numlines();
	hal_display_gotoxy( 0, line_num );
}

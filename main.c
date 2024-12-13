#define osObjectsPublic                     // define objects in main module
//#include "osObjects.h"                      // RTOS object definitions
#include "LPC17xx.h" 
#include "GLCD.h"
#include "photo_viewer.h"
#include "KBD.h"
#include "game_logic.h"
#include "usbdmain.h"

uint32_t joystick_val = 0;
unsigned int option = 0;
uint32_t led_num = 0; 


void update_screen(unsigned int option){
	switch(option){
		case 1:

			GLCD_SetBackColor(Green);
			GLCD_SetTextColor(Blue);
			GLCD_DisplayString (1, 0, __FI, "   Use the joystick      ");
			GLCD_DisplayString (2, 0, __FI, "      to select     ");
		
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Black);
			GLCD_DisplayString (5, 0, __FI, "1.   Audio player     ");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (6, 0, __FI, "2.   Photo Gallery      ");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (7, 0, __FI, "3.   Game               ");
			
			break;
		case 2:
				
			GLCD_SetBackColor(Green);
			GLCD_SetTextColor(Blue);
			GLCD_DisplayString (1, 0, __FI, "   Use the joystick      ");
			GLCD_DisplayString (2, 0, __FI, "      to select     ");
		
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (5, 0, __FI, "1.   Audio player     ");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Black);
			GLCD_DisplayString (6, 0, __FI, "2.   Photo Gallery      ");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (7, 0, __FI, "3.   Game               ");

			break;
		case 3:
			GLCD_SetBackColor(Green);
			GLCD_SetTextColor(Blue);
			GLCD_DisplayString (1, 0, __FI, "   Use the joystick      ");
			GLCD_DisplayString (2, 0, __FI, "      to select     ");
		
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (5, 0, __FI, "1.   Audio player     ");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (6, 0, __FI, "2.   Photo Gallery      ");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Black);
			GLCD_DisplayString (7, 0, __FI, "3.   Game               ");
			break;
		
		default:
			GLCD_SetBackColor(Green);
			GLCD_SetTextColor(Blue);
			GLCD_DisplayString (1, 0, __FI, "   Use the joystick      ");
			GLCD_DisplayString (2, 0, __FI, "      to select     ");
		
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (5, 0, __FI, "1.   Audio player    ");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (6, 0, __FI, "2.   Photo Gallery      ");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (7, 0, __FI, "3.   Game               ");
			break;
			
	}
}

int get_joystick(){
		while(1){
			joystick_val = get_button();
			switch(joystick_val){
				case KBD_DOWN: 
					led_num = 0x01;
					if(option < 3){ 
						option++;
					}else {
						option = 0;
					}
					break;
				case KBD_UP:
					led_num = 0x02;
					if(option > 0){
						option--;
					}
					break;
				case KBD_SELECT:
					return joystick_val;
				
		}
	}
}

void update_lcd(unsigned int option){
	unsigned int selected_option = option;
	switch(option){
		case 1:
			GLCD_Clear(White);
			audio_main();
			selected_option = 0;
			break;
		case 2:
			GLCD_Clear(White);
			photo_viewer();
			selected_option = 0;
			break;
		case 3: 
			GLCD_Clear(White);
			game_main();
			selected_option = 0;
			break;
		default:
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (5, 0, __FI, "1. Audio player");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (6, 0, __FI, "2. Photo Gallery");
			
			GLCD_SetBackColor(Blue);
			GLCD_SetTextColor(Red);
			GLCD_DisplayString (7, 0, __FI, "3. Game");
			
			GLCD_SetBackColor(White);
			GLCD_SetTextColor(Blue);
			GLCD_DisplayString (1, 0, __FI, "Use the joystick");
			GLCD_DisplayString (2, 3, __FI, "to select");
			get_joystick();
			break;
	}
}



int main (void) {
	//LED_Init ();
  GLCD_Init();
  GLCD_Clear(White);
	//SysTick_Config(SystemCoreClock/100); 

	
  while(1){
		joystick_val = get_button();
		switch(joystick_val){
			case KBD_DOWN: 
				led_num = 0x01;
				if(option < 3){ 
					option++;
				}else {
					option = 0;
				}
				break;
			case KBD_UP:
				led_num = 0x02;
				if(option > 0){
					option--;
				}
				break;
			case KBD_SELECT:
				led_num = 0x03;
				update_lcd(option);
				break;
		}
		update_screen(option);
	}
}
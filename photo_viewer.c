
#include "LPC17xx.h" 
#include "photo_viewer.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "string.h"


extern unsigned char ClockLEDOn;
extern unsigned char ClockLEDOff;
extern unsigned char ClockANI;


extern unsigned char Bg_16bpp_t[];
extern unsigned char CAT_pixel_data[];
extern unsigned char KYOGRE_pixel_data[];



void render_picture(int image_id)  // Function to render the selected image
{
    //int delay_counter = 0;
    if (image_id == 0)
    {
        GLCD_Clear(Black);
        GLCD_Bitmap(0, 0, 240, 240, CAT_pixel_data);
				
    }
   
		else if (image_id == 1)
    {
        GLCD_Clear(Black);
				GLCD_Bitmap(0,0,240,240,Bg_16bpp_t);
			
		}

    else if (image_id == 2)
    {
       GLCD_Clear(Black);
        GLCD_Bitmap(0, 0, 240, 240, KYOGRE_pixel_data);

			
    }
		
}

void photo_viewer(){
		GLCD_Clear(Black);
	GLCD_DisplayString(0, 0, 1, (unsigned char *)":LEFT right to scroll. Down to exit");
    int current_image = 0, slide_delay = 0;
    int view_timer = 0;
    unsigned char *img_pointer = 0;
    int prev_joystick_state = get_button();
    int curr_joystick_state = get_button();
    int refresh_counter = 0;
    render_picture(current_image);

    while (1)
    {
        curr_joystick_state = get_button();
			
            if (curr_joystick_state == KBD_RIGHT)
            {
                current_image = (current_image + 1) % 3;
                render_picture(current_image);
            }
            else if (curr_joystick_state == KBD_LEFT)
            {
                current_image = (current_image - 1) % 3;
                render_picture(current_image);
            }
						else if(curr_joystick_state == KBD_DOWN){
							break;
						}

        if (refresh_counter >= 50)
        {
            current_image = (current_image + 1) % 3;
            render_picture(current_image);
            refresh_counter = 0;
        }
    }

    view_timer = 0;
    GLCD_Clear(White);
    GLCD_DisplayString(0, 0, 1, "Ahmad's Media Center");
    GLCD_DisplayString(1, 6, 1, "MAIN MENU");
		
}

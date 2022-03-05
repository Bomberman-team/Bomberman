#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Function.h"
#define UPSCALE 4

 //Funções
void map_create();
void sair();
void tempo();
void dtt_colid ();
void colide ();
void control ();
void draw();

 //Variaveis Globais
 int width = 208 * UPSCALE;;
 int height = 176 * UPSCALE;

int main(void)
{
    srand(time(0));
    map_create();
	bool done = false;
	int pos_x = 70;
	int pos_y = 30;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					pos_y -= 10;
					break;
				case ALLEGRO_KEY_DOWN:
					pos_y += 10;
					break;
				case ALLEGRO_KEY_RIGHT:
					pos_x += 10;
					break;
				case ALLEGRO_KEY_LEFT:
					pos_x -= 10;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;
		}

        ALLEGRO_BITMAP *player;
        player = al_load_bitmap("imagem.png");
        al_convert_mask_to_alpha(player,al_map_rgb(255,233,127));
        al_draw_scaled_bitmap(player,p1.wx,p1.wy,p1.w,p1.h,pos_x,pos_y,p1.w*UPSCALE,p1.h*UPSCALE,0);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        draw();
	}
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}


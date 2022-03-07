#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Function.h"
#define UPSCALE 4
#include <stdio.h>

enum KEYS{ UP, DOWN, LEFT, RIGHT};

 //Funções
void map_create();
void sair();
void tempo();
void dtt_colid ();
void colide ();
void control ();
void draw();

 //Variaveis Globais

int width = 208 * UPSCALE;
int height = 176 * UPSCALE;
int pos_x = 70;
int pos_y = 30;
bool done = false;
bool keys[4] = {false, false, false, false};
int sai = 0;
int drc = 1;
ALLEGRO_BITMAP *player;

int main(void)
{

    ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    map_create();

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
	al_register_event_source(event_queue, al_get_display_event_source(display));

	while(!done)
	{
		int face = p1.wx + (p1.frame/3) * p1.w + drc*96;

		draw();
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
        al_rest(0.02);
		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
					drc = 0;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					drc = 1;
					p1.frame++;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					drc = 2;
					p1.frame++;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					drc = 3;
					p1.frame++;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		if (keys[UP] == true || keys[DOWN] == true || keys[LEFT] == true || keys[RIGHT] == true) p1.frame++;
		if(p1.frame > 5) p1.frame = 0;


		printf("%d",p1.frame);

		pos_y -= keys[UP] * 4;
		pos_y += keys[DOWN] * 4;
		pos_x -= keys[LEFT] * 4;
		pos_x += keys[RIGHT] * 4;

        player = al_load_bitmap("move_sprite.png");
        al_convert_mask_to_alpha(player,al_map_rgb(255,233,127));
        al_draw_scaled_bitmap(player,face,p1.wy,p1.w,p1.h,pos_x,pos_y,p1.w*UPSCALE,p1.h*UPSCALE,0);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

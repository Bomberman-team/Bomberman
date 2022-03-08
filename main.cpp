#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "Function.h"
#define UPSCALE 4
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#define FPS 60

enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE};

//Funções
void map_create();
void sair();
void tempo();
void dtt_colid ();
void colide ();
void control ();
void draw();
void b_bomb();
void tempo_bomba();

//Variaveis Globais
bool redraw = false;
int width = 208 * UPSCALE;
int height = 176 * UPSCALE;
int pos_x = 70;
int pos_y = 30;
bool done = false;
bool keys[5] = {false, false, false, false, false};
int sai = 0;
extern int drc=0;
static bool k = false;
const int maxFrame = 3;
int curFrame = 0;
int frameCount = 0;
int frameDelay = 5;

int main(void)
{

    ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bomba[maxFrame];
    ALLEGRO_BITMAP *player;

	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object
    timer = al_create_timer(1.0/FPS);

	if(!display)										//test display object
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    map_create();
    al_start_timer (timer);

	while(!done)
	{

        int face = p1.wx + (p1.frame/20) * p1.w + (drc*96);
        tempo_bomba();
        printf("%d %d %d %d %d\n", bomb.timer, bomb.x, bomb.y, p1.x/64, p1.y/54);

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

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
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					drc = 2;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					drc = 3;
					break;
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = true;
                    if(bomb.timer==0){
                    b_bomb();
                    bomb.timer = 90;
                    }
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
                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = false;
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
		else if(ev.type == ALLEGRO_EVENT_TIMER){

            redraw=true;
    }

		if (keys[UP] == true || keys[DOWN] == true || keys[LEFT] == true || keys[RIGHT] == true) p1.frame++;
		if(p1.frame > 100) p1.frame = 0;

        if(redraw && al_event_queue_is_empty(event_queue)){

            draw();
            int face = p1.wx + (p1.frame/20) * p1.w + (drc*96);
            p1.y -= keys[UP] * 4;
            p1.y += keys[DOWN] * 4;
            p1.x -= keys[LEFT] * 4;
            p1.x += keys[RIGHT] * 4;

           // colide();
            player = al_load_bitmap("move_sprite.png");
            al_convert_mask_to_alpha(player,al_map_rgb(255,233,127));
            al_draw_scaled_bitmap(player,face,p1.wy,p1.w,p1.h,p1.x,p1.y,p1.w*UPSCALE,p1.h*UPSCALE,0);
            al_flip_display();



        }
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

//Funcao

void colide (){
    for(int x=0; x < 13; x++){
            for(int y=0 ; y < 11; y++){
            if(dtt_colid(p1.x+4, p1.y+40, p1.w*UPSCALE, p1.h*UPSCALE, x*16*UPSCALE, y*16*UPSCALE, 16*UPSCALE, 16*UPSCALE)){
                if( map[y][x] == 1 || map[y][x]==2 ){
                    switch (drc){
                    case 0: p1.y += 4; break;
                    case 1: p1.y -= 4; break;
                    case 2: p1.x -= 4; break;
                    case 3: p1.x += 4; break;
                    }
                }
            }
        }
    }
}

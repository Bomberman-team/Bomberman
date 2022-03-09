#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Function.h"
#define UPSCALE 4
#define FPS 60

enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE};

 //Fun��es
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
int inside_bomb= -1;
bool redraw = false;
int width = 208 * UPSCALE;
int height = 176 * UPSCALE;
int pos_x = 70;
int pos_y = 30;
bool done = false;
bool keys[5] = {false, false, false, false, false};
int sai = 0;
extern int drc = 1;
static bool k = false;


int main(void)
{
    srand(time(0));                                  //Randomiza��o do Mapa

    //Ponteiros

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *player;
    ALLEGRO_SAMPLE *song;
    //ALLEGRO_SAMPLE_INSTANCE *inst_song = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_TIMER *timer = NULL;
	/*song = al_load_sample("Bomberman-Theme.wav");
	inst_song = al_create_sample_instance(song);
	al_attach_sample_instance_to_mixer(inst_song, al_get_default_mixer());
	al_set_sample_instance_playmode(inst_song, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(inst_song, 0.8);*/

    map_create();

	if(!al_init())
		return -1;

    //Cria��o de Display e Timer

	display = al_create_display(width, height);
    timer = al_create_timer(1.0/FPS);

	if(!display)										//Teste de Display
		return -1;

    //Add-ons e Instala��es

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_install_audio ();
	al_init_acodec_addon ();

	al_reserve_samples(1);

	event_queue = al_create_event_queue();

    //Registro de Sources

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    font18 = al_load_font("c:/windows/fonts/arial.ttf", 18, 0);

    al_start_timer (timer);

    if(!font18)    {
        return -1;
    }
	while(!done)
	{
		int face = p1.wx + (p1.frame/8) * p1.w + drc*96;
		tempo_bomba();

		//al_draw_textf(font18, al_map_rgb(255,255,255),20,20,0,"%d",p1.x/16)*UPSCALE);

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
                    int x = (p1.x+8*UPSCALE)/(16*UPSCALE), y= (p1.y+21*UPSCALE)/(16*UPSCALE);
                    inside_bomb = x+y*13;
                    break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					p1.frame = 0;
					break;
				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					p1.frame = 0;
					break;
				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					p1.frame = 0;
					break;
				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					p1.frame = 40;
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
		if(ev.type== ALLEGRO_EVENT_TIMER){
            redraw=true;
		}

		if (keys[UP] == true || keys[DOWN] == true || keys[LEFT] == true || keys[RIGHT] == true) p1.frame++;
		if(p1.frame > 40) p1.frame = 0;

        if(redraw && al_event_queue_is_empty(event_queue)){
            al_play_sample(song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,0);
            draw();
            colide();
            player = al_load_bitmap("move_sprite.png");
            al_convert_mask_to_alpha(player,al_map_rgb(255,233,127));
            al_draw_scaled_bitmap(player,face,p1.wy,p1.w,p1.h,p1.x,p1.y,p1.w*UPSCALE,p1.h*UPSCALE,0);
            //al_draw_rectangle(p1.x+12, p1.y+48, p1.x+12+ hb_p1.w*4, p1.y+48+ hb_p1.h*4, al_map_rgb(255,255,255),4);
            al_flip_display();
        }
	}

	//Finalizador

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_sample(song);
    //al_destroy_sample_instance(inst_song);


	return 0;
}

//Funcao

void control (){
    p1.y -= keys[UP] * 4;
    p1.y += keys[DOWN] * 4;
    p1.x -= keys[LEFT] * 4;
    p1.x += keys[RIGHT] * 4;
}

void colide (){
    control ();
    for(int x=0; x < 13; x++){
        for(int y=0; y < 11; y++){
            if(map[y][x] == 1 || map[y][x] == 2 || map[y][x] == 3){
                if(dtt_colid(p1.x+12, p1.y+48, 10*UPSCALE, 10*UPSCALE, x*16*UPSCALE, y*16*UPSCALE, 16*UPSCALE, 16*UPSCALE)){
                    if (map[y][x] == 3 && x+y*13 == inside_bomb){
                        continue;
                    }
                    p1.y += keys[UP] * 4;
                    p1.y -= keys[DOWN] * 4;
                    p1.x += keys[LEFT] * 4;
                    p1.x -= keys[RIGHT] * 4;
                }
                else if (map[y][x] == 3 && x+y*13 == inside_bomb){
                    inside_bomb = -1;
                }
            }
        }
    }
}


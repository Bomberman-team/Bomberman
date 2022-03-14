#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
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
void tempo_fire();

//Estruturas

// wx = posi��o em X(sprite), wy = posi��o em Y(sprite), w = largura, h = altura, id = identifica��o

struct obj {int wx, wy ,w, h, x, y, frame, timer, id, life;};
struct obj p1 = {0,0,16,24,64,40,0,0,0,0},
hb_p1 = {0,0,10,10,(p1.x+4),(p1.y+40),0,0,0,0}, //teste
p2 = {},
hard_wall = {0,0,16,16,0,0,0,0,0,0},
soft_wall = {34,0,16,16,0,0,0,0,0,0},
floor = {17,0,16,16,0,0,0,0,0,0},
bomb = {0,0,16,16,-1,-1,0,90,0,0},
fire = {0,0,16,16,-1,-1,0,0,0,0},
end_wall {};

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
int drc = 1;
static bool k = false;
char map [11][13];

ALLEGRO_BITMAP *player;
ALLEGRO_SAMPLE *song;
ALLEGRO_BITMAP *tiles;
ALLEGRO_BITMAP *bomb_a;
ALLEGRO_BITMAP *fire_a;


int main(void)
{
    srand(time(0));                                  //Randomiza��o do Mapa

    //Ponteiros

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_SAMPLE_INSTANCE *inst_song = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_TIMER *timer = NULL;


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

    //Carregamento

    font18 = al_load_font("c:/windows/fonts/arial.ttf", 18, 0);
    player = al_load_bitmap("move_sprite.png");
    tiles = al_load_bitmap("image_tiles.png");
    bomb_a = al_load_bitmap("sprite_bomb.png");
    song = al_load_sample("Bomberman-Theme.wav");
    fire_a = al_load_bitmap("sprite_fire.png");
	inst_song = al_create_sample_instance(song);
	al_attach_sample_instance_to_mixer(inst_song, al_get_default_mixer());
	al_set_sample_instance_playmode(inst_song, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(inst_song, 0.8);

	//Teste

    if(!player){
        printf("teste");
    }

    if(!tiles){
        printf("teste");
    }
    if(!bomb_a){
        printf("teste");
    }

    al_start_timer (timer);

    if(!font18)    {
            printf("Sem fonte");
        return -1;
    }


	while(!done)
	{

		printf("%d %d \n ", fire.timer, bomb.timer);
		int face = p1.wx + (p1.frame/8) * p1.w + drc*96;
		tempo_bomba();
        tempo_fire();

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
    al_destroy_sample_instance(inst_song);


	return 0;
}

//Funcoes

void control (){
    p1.y -= keys[UP] * 4;
    p1.y += keys[DOWN] * 4;
    p1.x -= keys[LEFT] * 4;
    p1.x += keys[RIGHT] * 4;
}

bool dtt_colid (int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh) {
    if(Ax + Aw >= Bx && Ax <= Bx + Bw && Ay + Ah >= By && Ay <= By + Bh || (Ax + Aw >= Bx && Ax <= Bx + Bw && !Ay && !Ah && !By && !Bh)){
        return 1;
    }
	return 0;
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

void draw(){
        for(int x=0; x < 13; x++){
            for(int y=0; y < 11; y++){
                switch(map[y][x]){
                    case 0:al_draw_scaled_bitmap(tiles,floor.wx,floor.wy,floor.w,floor.h,floor.w*x*UPSCALE,floor.h*y*UPSCALE,floor.w*UPSCALE,floor.h*UPSCALE,0); break;
                    case 1:al_draw_scaled_bitmap(tiles,hard_wall.wx,hard_wall.wy,hard_wall.w,hard_wall.h,hard_wall.w*x*UPSCALE,hard_wall.h*y*UPSCALE,hard_wall.w*UPSCALE,hard_wall.h*UPSCALE,0); break;
                    case 2:al_draw_scaled_bitmap(tiles,soft_wall.wx,soft_wall.wy,soft_wall.w,soft_wall.h,soft_wall.w*x*UPSCALE,soft_wall.h*y*UPSCALE,soft_wall.w*UPSCALE,soft_wall.h*UPSCALE,0); break;
                    case 3:al_draw_scaled_bitmap(bomb_a,bomb.wx,bomb.wy,bomb.w,bomb.h,bomb.w*x*UPSCALE,bomb.h*y*UPSCALE,bomb.w*UPSCALE,bomb.h*UPSCALE,0); break;
                    case 4:al_draw_scaled_bitmap(fire_a,fire.wx,fire.wy,fire.w,fire.h,fire.w*x*UPSCALE,fire.h*y*UPSCALE,fire.w*UPSCALE,fire.h*UPSCALE,0); break;

                        //al_draw_scaled_bitmap(fire_a,fire.wx,fire.wy,fire.w,fire.h,fire.w*x*UPSCALE,fire.h*y*UPSCALE,fire.w*UPSCALE,fire.h*UPSCALE,0); break;
                }
            }
        }
}

void b_bomb(){
    for(int x=0; x < 13; x++){
            for(int y=0; y < 11; y++){
                    bomb.x = ((p1.x+(8*UPSCALE))/(16*UPSCALE));
                    bomb.y = ((p1.y+(21*UPSCALE))/(16*UPSCALE));
                    map [((p1.y+(21*UPSCALE)) /(16*UPSCALE))][((p1.x+(8*UPSCALE))/(16*UPSCALE))] = 3;
            }
    }
}


//Fun��es

/* Cria��o do Mapa por meio de uma matriz 13x11 que pode assumir os valores 0,1,2 e 3.
0 = Ch�o
1 = Blocos quebr�veis
2 = Blocos Indestrut�veis
3= Bomba */

void map_create(){
    for(int x=0; x < 13; x++){
        for(int y=0; y < 11; y++){
            if(x==0 || x==12 || y==0 || y==10 || (x>1 && x<11 && !(x % 2) && (y>1 && y<9 && !(y % 2)))) {
                map[y][x]=1;
            }
        else map [y][x] = (rand() % 2) * 2 ;
        }
    }
map[1][1]=0;
map[1][2]=0;
map[2][1]=0;
map[8][11]=0;
map[9][10]=0;
map[9][11]=0;
}

void tempo_bomba(){

    if(bomb.timer > 0){

        bomb.wx = (bomb.timer/30) * bomb.w + bomb.frame;
        bomb.timer--;

    }
    if(bomb.timer==0){

        fire.timer  = 20;

        map[bomb.y][bomb.x]= 4;
        if (map[bomb.y+1][bomb.x] != 1) map[bomb.y+1][bomb.x] = 4;
        if (map[bomb.y-1][bomb.x] != 1) map[bomb.y-1][bomb.x] = 4;
        if (map[bomb.y][bomb.x+1] != 1) map[bomb.y][bomb.x+1] = 4;
        if (map[bomb.y][bomb.x-1] != 1) map[bomb.y][bomb.x-1] = 4;



    }
}

void tempo_fire(){

    if(fire.timer > 0){

        fire.wx = (fire.timer/5)*fire.w + fire.frame;

        fire.timer--;

    }
    if(fire.timer==0){

    map[bomb.y][bomb.x]= 0;
        if (map[bomb.y+1][bomb.x] != 1) map[bomb.y+1][bomb.x] = 0;
        if (map[bomb.y-1][bomb.x] != 1) map[bomb.y-1][bomb.x] = 0;
        if (map[bomb.y][bomb.x+1] != 1) map[bomb.y][bomb.x+1] = 0;
        if (map[bomb.y][bomb.x-1] != 1) map[bomb.y][bomb.x-1] = 0;
    }

}

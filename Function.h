#define UPSCALE 4
char map [11][13];

//Funções

void map_create () {
    for(int x=0; x < 13; x++){
        for(int y=0; y < 11; y++){
        if(x==0 || x==12 || y==0 || y==10 || (x>1 && x<11 && !(x % 2) && (y>1 && y<9 && !(y % 2)))) map[y][x]=1;
        else map [y][x]= (rand() % 2) * 2;
        }
    }
map[1][1]=0;
map[1][2]=0;
map[2][1]=0;
}


void draw_map(){
        ALLEGRO_BITMAP *imagem;
        imagem = al_load_bitmap("imagem2.png");
        for(int x=0; x < 13; x++){
            for(int y=0; y < 11; y++){
                    switch(map[y][x]){

                    case 0:al_draw_scaled_bitmap(imagem,24,16,16,16,x*16*UPSCALE,y*16*UPSCALE,16*UPSCALE,16*UPSCALE,0); break;
                    case 1:al_draw_scaled_bitmap(imagem,40,32,16,16,x*16*UPSCALE,y*16*UPSCALE,16*UPSCALE,16*UPSCALE,0); break;
                    case 2:al_draw_scaled_bitmap(imagem,55,111,16,16,x*16*UPSCALE,y*16*UPSCALE,16*UPSCALE,16*UPSCALE,0); break;
            }
        }
}
}

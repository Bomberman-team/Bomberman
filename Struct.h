//Estruturas

// wx = posi��o em X, wy = posi��o em Y, w = largura, h = altura, id = identifica��o

struct obj {int wx, wy ,w, h, x, y, frame, timer, id, life;};
struct obj p1 = {0,0,16,24,0,0,0,0,0,0},
p2 = {},
hard_wall= {0,0,16,16,0,0,0,0,0,0},
soft_wall = {34,0,16,16,0,0,0,0,0,0},
floor = {17,0,16,16,0,0,0,0,0,0},
bomb = {0,17,16,16,0,0,0,0,0,0},
fire = {};


#include <allegro.h>
#include <cstdlib>
#define MAXFILAS  20    //para el eje y
                        
#define MAXCOLS   31    //para el eje x
BITMAP *buffer;
BITMAP *roca;
BITMAP *pacbmp;
BITMAP *pacman;
BITMAP *Comida;
BITMAP *enemigobmp; //estos son mapa de enemigos 
BITMAP *enemigo;



int dir = 4;
int px=30*14, py=30*17;// con 14 , 17 y 4 se cambio su posicion inicialmente era con 10 10 0

int fdir = 0;
int _x=30*14, _y=30*15;

char mapa[MAXFILAS][MAXCOLS] = {
 "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
 "X O O|O O O XXXXX  O O | O OX",
 "XOXXX XXXXX XXXXX XXXXX XXXOX",
 "XOXXX XXXXX XXXXX XXXXX XXXOX",
 "X O O O|O O O O O O | O O OOX",
 "X XXX XX XXXXXXXXXXX XX XXX X",
 "X O O|XX O O XXX O O XX O O X",
 "X XXX XXXXXX XXX XXXXXX XXX X",
 "X XXX XX O O|O O|O O XX XXX X",
 "  O O|XX XXXXXXXXXXX XX|O O  ",
 "X XXX XX XXXXXXXXXXX XX XXX X",
 "X XXX XX O0O|OOO|O O XX XXX X",
 "X XXX XXXXXX XXX XXXXXX XXX X",
 "X O O XX O O XXX O O XX O O X",
 "X XXX XX XXXXXXXXXXX XX XXX X",
 "X XXX|O | O O O O O |  |XXX X",
 "X XXX XXXX XXXXXXXX XXX XXX X",
 "X XXX XXXX O O O O  XXX XXX X",
 "X O O|O O  XXXXXXXX O O|O O X",
 "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};
void dibujar_mapa()
    {
       int row, col;
        for(row = 0 ; row< MAXFILAS ;  row++ ){
             for(col = 0; col < MAXCOLS; col++){
                if(mapa[row][col] == 'X'){
                   draw_sprite(buffer, roca , col*30 ,row*30);
                   }
                   else if(mapa[row][col] == 'O')
                   draw_sprite(buffer, Comida , col*30 ,row*30);
                   if(py/30 == row && px/30 == col){
                     mapa[row][col] = ' ';
                     }
            }
       }
  }
void pantalla(){
	blit(buffer, screen , 0, 0, 0, 0, 880, 600);
}
void dibujar_personaje(){
     blit(pacbmp,pacman, dir*33, 0, 0, 0, 33, 33);
     draw_sprite(buffer,pacman,px,py);
     }
     //funcion booleano  
bool game_over(){
     int row, col;
     for(row = 0 ; row< MAXFILAS ;  row++ ){
             for(col = 0; col < MAXCOLS; col++){
                if(mapa[row][col] == 'O') return true;
                }
             }
        return false;
        
     }
     
void dibujar_fantasma(){
     blit(enemigobmp,enemigo, 0, 0, 0, 0, 30, 30);
     draw_sprite(buffer,enemigo,_x,_y);
     
     }
void fantasma(){//esta funcio es para mover fantasma
     dibujar_fantasma();
     if(mapa[_y/30][_x/30] == '|'){
          fdir = rand()%4;     
     }
     
     if(fdir == 0){
             if(mapa[_y/30][(_x-30)/30] != 'X' ) _x-=30;
             else fdir = rand()%3;// este desde rand nos genera un numero al azar
             
             }
     if(fdir == 1){
          if(mapa[_y/30][(_x+30)/30] != 'X' ) _x+=30;
             else fdir = rand()%3;
             }
     if(fdir == 2){
          if(mapa[(_y-30)/30][_x/30] != 'X' ) _y-=30;
             else fdir = rand()%3;
             }
     if(fdir == 3){
          if(mapa[(_y+30)/30][_x/30] != 'X' ) _y+=30;
             else fdir = rand()%3;
             }
     //rutina de atajos 
     if(_x <= -30) _x = 870;
       else if(_x >= 870) _x = -30;
     
     }

int main()
{
   allegro_init();
   install_keyboard();

   set_color_depth(32);
   set_gfx_mode(GFX_AUTODETECT_WINDOWED, 880, 600, 0, 0);
   
   buffer = create_bitmap(880, 600);
   roca = load_bitmap("roca.bmp", NULL);
   pacbmp = load_bitmap("pacman.bmp", NULL);
   pacman = create_bitmap(33,33);
   Comida = load_bitmap("Comida.bmp", NULL);
   enemigo = create_bitmap(30,30);
   enemigobmp = load_bitmap("enemigo.bmp", NULL);
   

   while(!key[KEY_ESC] && game_over()){ // con este while es donde se pregunta si presionas esc o terminas de comer
       if(key[KEY_RIGHT]) dir = 1;  // rutina mover pacman
       else if(key[KEY_LEFT]) dir = 0;
       else if(key[KEY_UP]) dir = 2;
       else if(key[KEY_DOWN]) dir = 3;
       
       if (dir == 0){
             if(mapa[py/30][(px-30)/30] !='X') 
               px -= 30;
             else dir = 4;
       }  
       if (dir == 1){ 
             if(mapa[py/30][(px+30)/30] !='X')   
               px += 30;
              else dir = 4;  
       }
       if (dir == 2){
            if(mapa[(py-30)/30][(px)/30] !='X')   
                py -= 30;
            else dir = 4;    
       }
       if (dir == 3){
          if(mapa[(py+30)/30][(px)/30] !='X')    
                py += 30;
          else dir = 4;
       }
       // rutina para atajo sesaparese y aparese en otro lado
       if(px <= -30) px = 870;
       else if(px >= 870) px = -30;
       
       clear(buffer);
       dibujar_mapa();
       dibujar_personaje();
       fantasma();
       pantalla();
       rest(70);
       
       clear(pacman);
       blit(pacbmp,pacman, 4*33, 0, 0, 0, 33, 33);
       draw_sprite(buffer,pacman,px,py);
       pantalla();
       rest(90);
   }
}

END_OF_MAIN();

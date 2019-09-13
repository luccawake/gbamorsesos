/*

  Universidade Federal de Sergipe · UFS
  Departamento de Computação  · DComp
  COMP0418 · Interface Hardware/Software
  Alunos: Henrique Gomes Santana e Lucas Almeida Francisco

*/

#include <gb/gb.h>
#include <stdio.h>
#include "keyboarddata.c"
#include "sprites.c"
#include "keyboardmap.c"
#include "cursor.c"
#include "inicial.c"

unsigned char texto[34];
unsigned char contador[2];
struct Cursor cursor;
const UINT8 minCursorX = 12;
const UINT8 minCursorY = 80;
const UINT8 maxCursorX = 156;
const UINT8 maxCursorY = 128;

UINT8 textoCaractereIndex;
UBYTE keyDown, enviarTexto;
UINT8 cont;

//Função que define a unidade de "pausa" para o espaço entre letras e palavras, definido,
//respectivamente, por três e sete pausas.
void espaco(){
  UINT8 i = 0;
  //_io_out é a variável que armazena os dados a serem enviados pelo Game Boy através da porta serial.
  _io_out = 0x00;
  for(i = 0; i != 20; i++){
      send_byte();
      while (_io_status == IO_SENDING);
      delay(10);
  }
}

//O ponto, em morse, é definido como a unidade "mínima": pode ser um bip, um piscar de LED, etc.
void ponto(){
  UINT8 i = 0;
  _io_out = 0xff;
  for(i = 0; i != 20; i++){
      send_byte();
      while (_io_status == IO_SENDING);
      delay(10);
  }
}

//Um traço, em morse, é definido por uma sequência de três pontos.
void traco(){
  ponto();
  ponto();
  ponto();
}

//O espaço entre letras é definido, em morse, como três "pausas".
void espacoLetras(){
  espaco();
  espaco();
  espaco();
}

//O espaço entre palavras é definido, em morse, como sete "pausas".
void espacoPalavras(){
  espaco();
  espaco();
  espaco();
  espaco();
}

//mapeia caracteres alfanuméricos para o padrão morse.
void enviarChar(UINT8 letra){
  
  switch (letra)
  {
  case 1:   //A
    ponto();
    espaco();
    traco();
    break;
  
  case 2:   //B
    traco();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    break;

  case 3:   //C
    traco();
    espaco();
    ponto();
    espaco();
    traco();
    espaco();
    ponto();
    break;

  case 4:   //D
    traco();
    espaco();
    ponto();
    espaco();
    ponto();
    break;

  case 5:   //E
    ponto();
    break;

  case 6:   //F
    ponto();
    espaco();
    ponto();
    espaco();
    traco();
    espaco();
    ponto();
    break;

  case 7:   //G
    traco();
    espaco();
    traco();
    espaco();
    ponto();
    break;

  case 8:   //H
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    break;

  case 9:   //I
    ponto();
    espaco();
    ponto();
    break;

  case 10:   //J
    ponto();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    traco();
    break;

  case 11:   //K
    traco();
    espaco();
    traco();
    break;

  case 12:   //L
    ponto();
    espaco();
    traco();
    espaco();
    ponto();
    espaco();
    ponto();
    break;
    
  case 13:   //M
    traco();
    espaco();
    traco();
    break;

  case 14:   //N
    traco();
    espaco();
    ponto();
    break;

  case 15:   //O
    traco();
    espaco();
    traco();
    espaco();
    traco();
    break;
    
  case 16:   //P
    ponto();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    ponto();
    break;

  case 17:   //Q
    traco();
    espaco();
    espaco();
    espaco();
    espaco();
    traco();
    espaco();
    ponto();
    espaco();
    traco();
    break;

  case 18:   //R
    ponto();
    espaco();
    traco();
    espaco();
    ponto();
    break;

  case 19:   //S
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    break;

  case 20:   //T
    traco();
    break;

  case 21:   //U
    ponto();
    espaco();
    ponto();
    espaco();
    traco();
    break;

  case 22:   //V
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    traco();
    break;

  case 23:   //W
    ponto();
    espaco();
    traco();
    espaco();
    traco();
    break;

  case 24:   //X
    traco();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    traco();
    break;

  case 25:   //Y
    traco();
    espaco();
    ponto();
    espaco();
    traco();
    espaco();
    traco();
    break;

  case 26:   //Z
    traco();
    espaco();
    traco();
    espaco();
    ponto();
    espaco();
    ponto();
    break;

  case 29:   // space
    espacoPalavras();
    break;

  case 31:   //0
    traco();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    traco();
    break;

  case 32:   //1
    ponto();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    traco();
    break;

  case 33:   //2
    ponto();
    espaco();
    ponto();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    traco();
    break;

  case 34:   //3
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    traco();
    espaco();
    traco();
    break;

  case 35:   //4
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    traco();
    break;

  case 36:   //5
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    break;

  case 37:   //6
    traco();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    break;
    
  case 38:   //7
    traco();
    espaco();
    traco();
    espaco();
    ponto();
    espaco();
    ponto();
    espaco();
    ponto();
    break;

  case 39:   //8
    traco();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    ponto();
    espaco();
    ponto();
    break;

  case 40:   //9
    traco();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    traco();
    espaco();
    ponto();
    break;

  default:
    break;
  }
  espacoLetras();
}

//As funções que seguem estão relacionadas à interface gráfica da ROM.
void performantdelay(UINT8 numLoops){
    UINT8 ii;
    for(ii = 0; ii < numLoops; ii++){
        wait_vbl_done();
    }     
}

UBYTE estaNaRegiaoDoTeclado(UINT8 x, UINT8 y){
    //controla a região do seletor, permitindo que ele "navegue" apenas na região do teclado -- isto é, na região
    //em que as tiles dos caracteres foram desenhadas.
    if(x==140 && y==144 || x==156 && y==144){
        return 1;
    }
    return x >= minCursorX && x <= maxCursorX && y >= minCursorY && y <= maxCursorY;
}

void adicionarCaractere(struct Cursor* cursor){

    UINT8 caractereIndex = cursor->row * 10 + cursor->col + 1; 
    if(cursor->row == 2 && (cursor->col == 6 || cursor->col == 7 || cursor->col == 8)) return;
    if(caractereIndex == 30)
        caractereIndex = 29;
    if(textoCaractereIndex == 34) return; // comprimento máximo da mensagem atingida
    texto[textoCaractereIndex] = caractereIndex;
    textoCaractereIndex++;
}

void removerCaractere(){
    if(textoCaractereIndex>0){
        textoCaractereIndex--;
        texto[textoCaractereIndex] = 0;
    }
}

void mapearContador(UINT8 numero){
    UINT8 dezena = numero/10;
    UINT8 unidade = numero%10;
    contador[0] = 31 + dezena;
    contador[1] = 31 + unidade;
}

void escreverTexto(){
    set_bkg_tiles(1, 3, 17, 2, texto);
    mapearContador(34 - textoCaractereIndex);
    set_bkg_tiles(16, 1, 2, 1, contador);
}

void atualizarTexto(struct Cursor* cursor){

    if(cursor->col==8 && cursor->row == 4){

        removerCaractere();
        escreverTexto();
    }
    else if (cursor->col==9 && cursor->row == 4){
        UINT8 i;
        for(i = 0; i != textoCaractereIndex; i++){
            enviarChar((UINT8) texto[i]);
        }
        while (textoCaractereIndex != 0){
          removerCaractere();
          escreverTexto();
        }
    }
    else{
        adicionarCaractere(cursor);
        escreverTexto();
    }
}


void main(){

    set_sprite_data(0, 1, sprites);
    set_sprite_tile(0, 0);

    set_bkg_data(0, 45, keyboarddata);
    set_bkg_tiles(0, 0, 20, 18, inicial);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;    
    
    while(1) {
            waitpad(J_START);
            if(joypad() == J_START){
                waitpadup();
                cursor.x = 12;
                cursor.y = 80;
                cursor.col = 0;
                cursor.row = 0;
                move_sprite(0, cursor.x, cursor.y);
        
                set_bkg_data(0, 45, keyboarddata);
                set_bkg_tiles(0, 0, 20, 18, keyboardmap);
                scroll_bkg(-4,0);

                escreverTexto();
      
                while(!enviarTexto){
                    if(keyDown){
                        waitpadup();
                        keyDown = 0;
                    }

                    switch(joypad()){
                        case J_UP:
                            if(estaNaRegiaoDoTeclado(cursor.x, cursor.y - 16)){
                                cursor.y -= 16;
                                scroll_sprite(0,0,-16);
                                keyDown = 1;
                                cursor.row--;
                            }
                            break;
                        case J_DOWN: 
                            if(estaNaRegiaoDoTeclado(cursor.x, cursor.y + 16)){            
                                cursor.y += 16;
                                scroll_sprite(0,0,16);
                                keyDown = 1;
                                cursor.row++;
                            }
                            break;  
                        case J_LEFT: 
                            if(estaNaRegiaoDoTeclado(cursor.x - 16, cursor.y)){
                                cursor.x -= 16;
                                scroll_sprite(0,-16,0);
                                keyDown = 1;
                                cursor.col--;
                            }
                            break; 
                        case J_RIGHT: 
                            if(estaNaRegiaoDoTeclado(cursor.x + 16, cursor.y)){            
                                cursor.x += 16;
                                scroll_sprite(0,16,0);
                                keyDown = 1;
                                cursor.col++;
                            }
                            break;
                        case J_A:
                            atualizarTexto(&cursor);
                            keyDown = 1;                
                            break;
                    }
                    performantdelay(2);
                }
            }
        
    }    
}

/*


Para o desenho do teclado, utilizamos "sprites", que funcionam como pequenas imagens no Gameboy.

Cada tile é mapeada com o seu respectivo caractere dentro dos casos da função enviaChar().





*/
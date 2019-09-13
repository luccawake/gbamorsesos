/*

  Universidade Federal de Sergipe · UFS
  Departamento de Computação  · DComp
  COMP0418 · Interface Hardware/Software
  Alunos: Henrique Gomes Santana e Lucas Almeida Francisco

*/

#include <gb/gb.h>
#include <stdio.h>
#include "leddata.c"
#include "blackmap.c"
#include "whitemap.c"


void ativaSom(UINT8 trigger){
  switch (trigger)
  {
  case 0x00U: //sinal 0000 0000 (baixo)
    set_bkg_tiles(0, 0, 20, 18, blackmap);  //background preto
    break;
  case 0xFFU: //sinal 1111 1111 (alto)
    set_bkg_tiles(0, 0, 20, 18, whitemap);  //background branco


    //Os registradores a seguir reproduzem o som do beep. Para este projeto, utilizamos
    //apenas o Canal 1 de som do Gameboy, que reproduz ondas quadradas.

    //Créditos ao Gaming Monsters por documentarem de maneira bastante simplificada o funcionamento dos bits
    //de cada registrador dos canais de aúdio -- descritos a seguir:

    //Canal 1 · Registrador 0
    // Frequency sweep settings
    // 7	Unused
    // 6-4	Sweep time(update rate) (if 0, sweeping is off)
    // 3	Sweep Direction (1: decrease, 0: increase)
    // 2-0	Sweep RtShift amount (if 0, sweeping is off)
    NR10_REG = 0x70U;   // 0111 0000, sweep time 111 (7 decimal), sweep direction increase

    //Canal 1 · Registrador 1
    //Wave pattern duty and sound length
    // Channels 1 2 and 4
    // 7-6	Wave pattern duty cycle 0-3 (12.5%, 25%, 50%, 75%), duty cycle is how long a quadrangular  wave is "on" vs "of" so 50% (2) is both equal.
    // 5-0 sound length (higher the number shorter the sound)
    NR11_REG = 0x81U;   // 1000 0001 duty cycle 0 (12,5%), wave length 1

    //Canal 1 · Registrador 2
    //Volume Envelope (Makes the volume get louder or quieter each "tick")
    // On Channels 1 2 and 4
    // 7-4	(Initial) Channel Volume
    // 3	Volume sweep direction (0: down; 1: up)
    // 2-0	Length of each step in sweep (if 0, sweeping is off)
    // NOTE: each step is n/64 seconds long, where n is 1-7
    NR12_REG = 0x33U; //0011 0011 Volume 2, sweep down, step length 3

    //Canal 1 · Registrador 3
    //Frequency LSBs (Least Significant bits) and noise options
    // for Channels 1 2 and 3
    // 7-0	8 Least Significant bits of frequency (3 Most Significant Bits are set in register 4)
    NR13_REG = 0xD6U; //1101 0110

    //Canal 1 · Registrador 4
    // Playback and frequency MSBs
    // Channels 1 2 3 and 4
    // 7	Initialize (trigger channel start, AKA channel INIT) (Write only)
    // 6	Consecutive select/length counter enable (Read/Write). When "0", regardless of the length of data on the NR11 register, sound can be produced consecutively.  When "1", sound is generated during the time period set by the length data contained in register NR11.  After the sound is ouput, the Sound 1 ON flag, at bit 0 of register NR52 is reset.
    // 5-3	Unused
    // 2-0	3 Most Significant bits of frequency
    // 1100 0011 is 0xC3, initialize, no consecutive, frequency = MSB + LSB = 011 0000 0000 = 0x300
    NR14_REG = 0x86U; //1000 0110
  default:
    break;
  }  
}

void main(){
    // Esta ordem específica é um requisito.
    NR52_REG = 0x80;  //equivale a 1000 0000 em binário e diz ao Gameboy que teremos som na ROM.
    NR50_REG = 0x77;  //configura o volume para ambos os canais esquerdo e direito da saída de áudio.
                      //  Aqui, o volume está configurado no máximo (0x77)
    NR51_REG = 0x11;  // 0001 0001 - ativa os canais do Game Boy e os canais de saída de áudio (L e R)
                      //que serão utilizados. Neste caso, indicamos que queremos os canais L e R do Canal 1.

    //Ativa background, sprites e liga a tela
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON; 

    set_bkg_data(0, 2, leddata);
    set_bkg_tiles(0, 0, 20, 18, blackmap);
    
    while(1) {
      //recebe os dados
      receive_byte();
      while(_io_status == IO_RECEIVING) {
        //reproduz o som em morse
        ativaSom(_io_in);
        //_io_in é a variável que armazena os dados recebidos pelo Game Boy através da porta serial.
      }
    }
}



#include <FastLED.h>

// 定義LED燈带的数據腳位、LED数量和顏色類型
#define DATA_PIN 3
#define BUTTON1 10
#define BUTTON2 9
#define BUTTON3 11
#define BUTTON4 10
#define LED_COUNT 100
#define LED_TYPE WS2812B

//define music 
#define NOTE_A0 0
#define NOTE_D1  37
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831

int melody1[] = {
  NOTE_D4, NOTE_A0
};

int noteDurations1[] = {
  2,2
};

int melody2[] = {
  NOTE_E5, NOTE_A0
};

int noteDurations2[] = {
  2,2
};

int melody3[] = {
  NOTE_B3, NOTE_A0
};
int noteDurations3[] = {
  2,2
};

int melody4[] = {
  NOTE_G5, NOTE_A0
};
int noteDurations4[] = {
  2,2
};

int melody5[] = {
  NOTE_B4, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D1
};
int noteDurations5[] = {
  2,2,2,2,2,2,2
};



void play(int *melody, int *noteDurations, int num){
  for(int note = 0; note < num; note++){
    int noteDuration = 300 / noteDurations[note];
    tone(8, melody[note], noteDuration);
    delay(50);
  }
}
// 定義FastLED對象
CRGB leds[LED_COUNT];

void setup() {
  // 初始化FastLED庫
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, LED_COUNT);
  Serial.begin(9600);  // 初始化串口通信
  pinMode(6, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
}


void loop() {
    int Three[10][10] = 
    {{0,0,0,0,0,0,0,0,0,0}
    ,{0,0,1,1,1,1,1,0,0,0}
    ,{0,0,0,0,0,0,1,0,0,0}
    ,{0,0,0,0,0,0,1,0,0,0}
    ,{0,0,1,1,1,1,1,0,0,0}
    ,{0,0,0,0,0,0,1,0,0,0}
    ,{0,0,0,0,0,0,1,0,0,0}
    ,{0,0,1,1,1,1,1,0,0,0}
    ,{0,0,0,0,0,0,0,0,0,0}
    ,{0,0,0,0,0,0,0,0,0,0}
    };
    
    
    int Two[10][10] = 
    {{0,0,0,0,0,0,0,0,0,0}
    ,{0,0,1,1,1,1,1,0,0,0}
    ,{0,0,0,0,0,0,1,0,0,0}
    ,{0,0,0,0,0,0,1,0,0,0}
    ,{0,0,1,1,1,1,1,0,0,0}
    ,{0,0,1,0,0,0,0,0,0,0}
    ,{0,0,1,0,0,0,0,0,0,0}
    ,{0,0,1,1,1,1,1,0,0,0}
    ,{0,0,0,0,0,0,0,0,0,0}
    ,{0,0,0,0,0,0,0,0,0,0}
    };
    
    
    int One[10][10] = 
    {{0,0,0,0,0,0,0,0,0,0}
    ,{0,0,0,1,1,0,0,0,0,0}
    ,{0,0,0,0,1,0,0,0,0,0}
    ,{0,0,0,0,1,0,0,0,0,0}
    ,{0,0,0,0,1,0,0,0,0,0}
    ,{0,0,0,0,1,0,0,0,0,0}
    ,{0,0,0,0,1,0,0,0,0,0}
    ,{0,0,0,0,1,0,0,0,0,0}
    ,{0,0,0,0,0,0,0,0,0,0}
    ,{0,0,0,0,0,0,0,0,0,0}
    };
    
    
    int Zero[10][10] = 
    {{0,0,0,0,0,0,0,0,0,0}
    ,{0,0,1,1,1,1,1,0,0,0}
    ,{0,0,1,0,0,0,1,0,0,0}
    ,{0,0,1,0,0,0,1,0,0,0}
    ,{0,0,1,0,0,0,1,0,0,0}
    ,{0,0,1,0,0,0,1,0,0,0}
    ,{0,0,1,0,0,0,1,0,0,0}
    ,{0,0,1,1,1,1,1,0,0,0}
    ,{0,0,0,0,0,0,0,0,0,0}
    ,{0,0,0,0,0,0,0,0,0,0}
    };

    int t = 0, score = 0, player = 5, cd = 0;
    int Screen[10][10] = {0}, button1, button2, button3;  
    int i, j;
    for(i=0; i<10; i++) for(j=0; j<10; j++) Screen[i][j] = 1;
  
      
    printled(Screen);
    if(digitalRead(BUTTON1)) button1 = 0;
    if(digitalRead(BUTTON2)) button2 = 0;
    if(digitalRead(BUTTON3)) button3 = 0;
    
    if(!digitalRead(BUTTON1)) button1++;
    if(!digitalRead(BUTTON2)) button2++;
    if(!digitalRead(BUTTON3)) button3++;
    if(button1==1 || button2==1 || button3==1){ 
      for(i=0; i<10; i++) for(j=0; j<10; j++) Screen[i][j] = 0;
      delay(200);
      printled(Three);
      play(melody3, noteDurations3, 1);
      delay(1000);
      printled(Two);
      play(melody3, noteDurations3, 1);
      delay(1000);
      printled(One);
      play(melody3, noteDurations3, 1);
      delay(1000);
      printled(Zero);
      play(melody4, noteDurations4, 1);
      delay(1000);
      Screen[9][player] = Screen[9][player-1] = Screen[9][player+1] = Screen[8][player] = 1;
      while(1){
        delay(20);
        t=(t+1)%10000;
        if(cd>=0) cd--;
        
        if(Screen[8][player]==3 || Screen[8][player+1]==3 || Screen[8][player-1]==3 || Screen[7][player]==3) break;

        if(cd<0) Screen[9][player] = 7;
        printled(Screen);
        if(cd<0) Screen[9][player] = 1;
        
        if(digitalRead(BUTTON1)) button1 = 0;
        if(digitalRead(BUTTON2)) button2 = 0;
        if(digitalRead(BUTTON3)) button3 = 0;
        
        if(!digitalRead(BUTTON1)) button1++;
        if(!digitalRead(BUTTON2)) button2++;
        if(!digitalRead(BUTTON3)) button3++;
        
         if(button1==1 || button2==1 || button3==1){
          if(button1==1 && player>1){
            Screen[8][player] = 0;
            Screen[8][player-1] = 1;
            Screen[9][player+1] = 0;
            Screen[9][player-2] = 1;
            player--;
          }else if(button3==1 && player<8){
            Screen[8][player] = 0;
            Screen[8][player+1] = 1;
            Screen[9][player-1] = 0;
            Screen[9][player+2] = 1;
            player++;
          }else if(button2>=1 && cd<0){
            Screen[7][player] = 2;
            Screen[7][player+1] = 2;
            Screen[7][player-1] = 2;
            cd=100;
            play(melody2, noteDurations2, 1);
          }
        }
        
        if(t%10 == 0){
          for(int i=8; i>=1; i--){
            for(int j=0; j<10; j++){
              if(Screen[i][j]+Screen[i-1][j] == 6){
                if(Screen[i+1][j]==2){
                  Screen[i-1][j] = 0;
                  Screen[i][j] = 0;
                  Screen[i+1][j] = 0;
                }else{
                  Screen[i-1][j] = 0;
                  Screen[i+1][j] = 3;
                }
              }
            }
          }
          for(int j=0; j<10; j++) if(Screen[0][j] == 3) Screen[1][j] = 3;
          for(int j=0; j<10; j++) if(Screen[8][j]+Screen[9][j] == 6) Screen[8][j] = 0;
          for(int j=0; j<10; j++) if(Screen[8][j]+Screen[9][j] == 3) Screen[9][j] = 0;       
        }
        if(t%3 == 0){
          for(int i=0; i<10; i++){
            for(int j=0; j<10; j++){
              if(Screen[i][j] == 2){
                if(i == 0){
                  Screen[i][j] = 0;
                }else if(Screen[i-1][j] == 3){
                  Screen[i][j] = 0;
                  Screen[i-1][j] = 0;
                  Screen[i-2][j] = 0;
                }else{
                  Screen[i][j] = 0;
                  Screen[i-1][j] = 2;
                }
              }
            }
          }
        }
        if(t%12 == 0){
            Screen[7][player] = 2;
            play(melody1, noteDurations1, 1);
        }
        if(t%30 == 0){
          Screen[0][random()%8+1] = 3;
        
         }
      }
      printled(Screen);
      play(melody5, noteDurations5, 5);
      delay(2000);
    }
}



void printled(int Screen[10][10]) //螢幕顯示(arduino要改成控制LED) 
{  
  int i, j;
  for(i=0; i<10; i++){
    for(j=0; j<10; j++){
      switch(Screen[i][j]){
        case 0:
          leds[10*i+j] = CRGB::Black;
          break;
        case 1:
          leds[10*i+j] = CRGB::Purple;
          break;
        case 2:
          leds[10*i+j] = CRGB::Red;
          break;
        case 3:
          leds[10*i+j] = CRGB::Yellow;
          break;
        case 4:
          leds[10*i+j] = CRGB::Orange;
          break;
        case 5:
          leds[10*i+j] = CRGB::Pink;
          break;
        case 6:
          leds[10*i+j] = CRGB::Gray;
          break;
        case 7:
          leds[10*i+j] = CRGB::Blue;
          break;
        case 8:
          leds[10*i+j] = CRGB::Purple;
          break;
        case 9:
          leds[10*i+j] = CRGB::White;
          break;
        case 10:
          leds[10*i+j] = CRGB::Brown;
          break;
      }
    }
  }
  FastLED.show();
}

#include <FastLED.h>

// 定義LED燈带的数據腳位、LED数量和顏色類型
#define DATA_PIN 3
#define BUTTON1 10
#define BUTTON2 9
#define BUTTON3 11
#define BUTTON4 10
#define LED_COUNT 100
#define LED_TYPE WS2812B



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

int c1;

void loop() {
  
  int Three[10][10] = 
  {{0,0,0,0,0,0,0,0,0,0}
  ,{0,0,10,10,10,10,10,0,0,0}
  ,{0,0,0,0,0,0,10,0,0,0}
  ,{0,0,0,0,0,0,10,0,0,0}
  ,{0,0,10,10,10,10,10,0,0,0}
  ,{0,0,0,0,0,0,10,0,0,0}
  ,{0,0,0,0,0,0,10,0,0,0}
  ,{0,0,10,10,10,10,10,0,0,0}
  ,{0,0,0,0,0,0,0,0,0,0}
  ,{0,0,0,0,0,0,0,0,0,0}
  };
  
  
  int Two[10][10] = 
  {{0,0,0,0,0,0,0,0,0,0}
  ,{0,0,10,10,10,10,10,0,0,0}
  ,{0,0,0,0,0,0,10,0,0,0}
  ,{0,0,0,0,0,0,10,0,0,0}
  ,{0,0,10,10,10,10,10,0,0,0}
  ,{0,0,10,0,0,0,0,0,0,0}
  ,{0,0,10,0,0,0,0,0,0,0}
  ,{0,0,10,10,10,10,10,0,0,0}
  ,{0,0,0,0,0,0,0,0,0,0}
  ,{0,0,0,0,0,0,0,0,0,0}
  };
  
  
  int One[10][10] = 
  {{0,0,0,0,0,0,0,0,0,0}
  ,{0,0,0,10,10,0,0,0,0,0}
  ,{0,0,0,0,10,0,0,0,0,0}
  ,{0,0,0,0,10,0,0,0,0,0}
  ,{0,0,0,0,10,0,0,0,0,0}
  ,{0,0,0,0,10,0,0,0,0,0}
  ,{0,0,0,0,10,0,0,0,0,0}
  ,{0,0,0,0,10,0,0,0,0,0}
  ,{0,0,0,0,0,0,0,0,0,0}
  ,{0,0,0,0,0,0,0,0,0,0}
  };
  
  
  int Zero[10][10] = 
  {{0,0,0,0,0,0,0,0,0,0}
  ,{0,0,10,10,10,10,10,0,0,0}
  ,{0,0,10,0,0,0,10,0,0,0}
  ,{0,0,10,0,0,0,10,0,0,0}
  ,{0,0,10,0,0,0,10,0,0,0}
  ,{0,0,10,0,0,0,10,0,0,0}
  ,{0,0,10,0,0,0,10,0,0,0}
  ,{0,0,10,10,10,10,10,0,0,0}
  ,{0,0,0,0,0,0,0,0,0,0}
  ,{0,0,0,0,0,0,0,0,0,0}
  };
  
  int i, j, button1, button2 ,button3;
  int Screen[10][10] = {0};  
  for(i=0; i<10; i++) for(j=0; j<10; j++) Screen[i][j] = 10;

    
  printled(Screen);
  if(digitalRead(BUTTON1)) button1 = 0;
  if(digitalRead(BUTTON2)) button2 = 0;
  if(digitalRead(BUTTON3)) button3 = 0;
  
  if(!digitalRead(BUTTON1)) button1++;
  if(!digitalRead(BUTTON2)) button2++;
  if(!digitalRead(BUTTON3)) button3++;
  if(button1==1 || button2==1 || button3==1){ 
    delay(200);
    printled(Three);
    delay(1000);
    printled(Two);
    delay(1000);
    printled(One);
    delay(1000);
    printled(Zero);
    delay(1000);
    int t = 0, score = 0;
    c1 = 4;
    for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
        Screen[i][j] = 0;
      }
    }
    for(int i=7; i<10; i++){
      for(int j=1; j<10; j++){
        Screen[i][j] = 10;
      }
    }
    Screen[8][2] = 0;
    Screen[8][5] = 0;
    Screen[8][8] = 0;
    Screen[2][(rand()%3)*3+2] = 1;
    Screen[5][(rand()%3)*3+2] = 1;
    Screen[8][(rand()%3)*3+2] = 1;

    
    while(1){
      if(digitalRead(BUTTON1)) button1 = 0;
      if(digitalRead(BUTTON2)) button2 = 0;
      if(digitalRead(BUTTON3)) button3 = 0;
      
      if(!digitalRead(BUTTON1)) button1++;
      if(!digitalRead(BUTTON2)) button2++;
      if(!digitalRead(BUTTON3)) button3++;
      delay(10);
      t++;Serial.println(t);
      if(t == 1800) break;
      //Screen[0][t/180] = 4;
      Screen[10-score/15][0] = 2;
      if(score%15 == 0){
        c1 = random()%9+1;
        score++;
      }
      printled(Screen);
      
      if(button1==1 || button2==1 || button3==1){
        if(button1==1 && Screen[8][2]==1){
          G(Screen);
          score++;
        }
        else if(button2==1 && Screen[8][5]==1){
          G(Screen);
          score++;
        }
        else if(button3==1 && Screen[8][8]==1){
          G(Screen);
          score++;
        }else{
          for(int i=0; i<3; i++){
            if(Screen[8][i*3+2] == 1){
              Screen[8][i*3+2] = 0;
              Screen[7][i*3+2] = 1;
              printled(Screen);
              delay(200);
              Screen[7][i*3+2] = 10;
              Screen[8][i*3+2] = 1;
              printled(Screen);
            }
          }      
        }
      }
    }
    
    
    int i, j;
    for(i=0; i<3; i++){
      for(j=0; j<3; j++){
        Screen[i*3+2][j*3+2] = 1;
      }
    }
    printled(Screen);
    delay(2000);
  }
}


void G(int Screen[10][10]){
  int i, j;
  for(i=2; i>=1; i--){
    for(j=0; j<3; j++){
      if(Screen[i*3+2-3][j*3+2] == 1){
        Screen[i*3+2][j*3+2] = 1; 
      }else{
        Screen[i*3+2][j*3+2] = 0; 
      }
    }
  }
  for(j=0; j<3; j++) Screen[2][j*3+2] = 0;
  Screen[2][rand()%3*3+2] = 1;  
}

void printled(int Screen[10][10]) //螢幕顯示(arduino要改成控制LED) 
{  
  int i, j;
  for(i=0; i<10; i++){
    for(j=0; j<10; j++){
      int a = Screen[i][j];
      if(a == 1){
        a = c1;
      }
      switch(a){
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

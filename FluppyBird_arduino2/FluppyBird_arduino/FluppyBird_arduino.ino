#include <FastLED.h>

// 定義LED燈带的数據腳位、LED数量和顏色類型
#define DATA_PIN 3
#define BUTTON1 9
#define BUTTON2 10
#define BUTTON3 11
#define BUTTON4 12
#define LED_COUNT 100
#define LED_TYPE WS2812B
#define micPin A0  // 小麥克風連接到模擬輸入A0引腳

// 定義FastLED對象
CRGB leds[LED_COUNT];

void setup(){
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
  int Screen[10][10] = {0},button1 = 0, button2 = 0, button3 = 0, button4 = 0;   //紀錄 10*10 LED矩陣亮暗
  
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

  double x = -1, y = 5, v = 0, t = -1, cd = 0; // 紀錄flapppy bird高度, 下落速度, 時間
  
  int i, j;
  for(i=0; i<10; i++) for(j=0; j<10; j++) Screen[i][j] = 1;

    
  printled(Screen);
  if(digitalRead(BUTTON1)) button1 = 0;
  if(digitalRead(BUTTON2)) button2 = 0;
  if(digitalRead(BUTTON3)) button3 = 0;
  
  if(!digitalRead(BUTTON1)) button1++;
  if(!digitalRead(BUTTON2)) button2++;
  if(!digitalRead(BUTTON3)) button3++;
  if(button1==1 || button2==1 || button3==1 || button4==1){ 
    delay(200);
    printled(Three);
    delay(1000);
    printled(Two);
    delay(1000);
    printled(One);
    delay(1000);
    printled(Zero);
    delay(1000);
    for(i=0; i<10; i++) for(j=0; j<10; j++) Screen[i][j] = 0;

    while(1){
      if(digitalRead(BUTTON1)) button1 = 0;
      if(digitalRead(BUTTON2)) button2 = 0;
      if(digitalRead(BUTTON3)) button3 = 0;
      
      if(!digitalRead(BUTTON1)) button1++;
      if(!digitalRead(BUTTON2)) button2++;
      if(!digitalRead(BUTTON3)) button3++;
      
      delay(50);    // 畫面每50ms更新一次  
      t += 1;
      
      printled(Screen);
      
      
      if(Screen[(int)y][3]==1 || y<0 || y>=10){    // 判斷是否出界
        delay(1000); 
        break; 
      } 
      
      Screen[(int)y][3] = 0;
      y += v;
      v += 0.02;
      Screen[(int)y][3] = 2;
      
      if(Screen[(int)y][3]==1 || y<0 || y>=10){    // 判斷是否出界
        delay(1000); 
        break; 
      } 
      
      //點擊按鍵
      if(button1==1 || button2==1 || button3==1 || button4==1){
        v = -0.3;
      }
      
      //每250ms 
      if(((int)t)%5 == 0){
        int i, j, temp[10][10] = {0};
        
        //牆往右移動
        for(i=0; i<10; i++) for(j=0; j<9; j++) Screen[i][j] = (Screen[i][j+1] == 1)?1:0;
  
        for(i=0; i<10; i++) Screen[i][9] = 0;
        
        //每20000ms在最右側生成新的牆
        if(((int)t)%30 == 0){
          int i, j, hole_y = random()%6+2;
          for(i=0; i<10; i++) Screen[i][9] = (abs(i-hole_y)>2)?1:0;  
        } 
      } 
      printled(Screen);
      if(Screen[(int)y][3]==1 || y<0 || y>=10){    // 判斷是否出界
        delay(1000); 
        break; 
      } 
    }
    
  }
}


void printled(int Screen[10][10]) //螢幕顯示(arduino要改成控制LED) 
{  
  int i, j;
  for(i=0; i<10; i++){
    for(j=0; j<10; j++){
      switch(Screen[i][j]){
        case 0:
          leds[10*i+j] = 0;
          break;
        case 1:
          leds[10*i+j] = CRGB::Green;
          break;
        case 2:
          leds[10*i+j] = CRGB::Yellow;
          break;
        case 3:
          break;
        case 4:
          break;
        case 5:
          break;
        case 6:
          break;
        case 7:
          break;
        case 8:
          break;
      }
    }
  }
  FastLED.show();
}

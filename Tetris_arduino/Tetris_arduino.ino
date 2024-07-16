#include <FastLED.h>

// 定義LED燈带的数據腳位、LED数量和顏色類型
#define DATA_PIN 3
#define BUTTON1 10
#define BUTTON2 11
#define BUTTON3 9
#define BUTTON4 10
#define LED_COUNT 100
#define LED_TYPE WS2812B
#define micPin A0  // 小麥克風連接到模擬輸入A0引腳
#define NOTE_D4  294
#define NOTE_E5  659
#define NOTE_A0  0

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


int Sc[14][14]={0},Now[3],c1,button1 = 0, button2 = 0, button3 = 0// y,x,shape
,point=0,Shape[5][5]={0},Shape2[5][5]={0},
Table[7][5][5]{
  { // I--0
       {0,0,0,0,0}
      ,{0,0,0,0,0}
      ,{0,1,1,1,1}
      ,{0,0,0,0,0}
      ,{0,0,0,0,0}
  },{// J--1
       {0,0,0,0,0}
      ,{0,1,0,0,0}
      ,{0,1,1,1,0}
      ,{0,0,0,0,0}
      ,{0,0,0,0,0}
  },{// L--2
       {0,0,0,0,0}
      ,{0,0,0,1,0}
      ,{0,1,1,1,0}
      ,{0,0,0,0,0}
      ,{0,0,0,0,0}
  },{// O--3
       {0,0,0,0,0}
      ,{0,0,1,1,0}
      ,{0,0,1,1,0}
      ,{0,0,0,0,0}
      ,{0,0,0,0,0}
  },{// S--4
       {0,0,0,0,0}
      ,{0,0,1,1,0}
      ,{0,1,1,0,0}
      ,{0,0,0,0,0}
      ,{0,0,0,0,0}
  },{// T--5
       {0,0,0,0,0}
      ,{0,0,1,0,0}
      ,{0,1,1,1,0}
      ,{0,0,0,0,0}
      ,{0,0,0,0,0}
  },{// Z--6
       {0,0,0,0,0}
      ,{0,1,1,0,0}
      ,{0,0,1,1,0}
      ,{0,0,0,0,0}
      ,{0,0,0,0,0}
  }
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
  c1 = 4+random()%7;
  for(int i=0;i<14;i++) Sc[i][1]=2;
  for(int i=0;i<14;i++) Sc[i][12]=2;
  for(int i=0;i<14;i++) Sc[13][i]=2;

  char ch;
  int times = 0;
  bool gameend = false;
  Setnew();
  int t = 0;
  while(1){
      if(digitalRead(BUTTON1)) button1 = 0;
      if(digitalRead(BUTTON2)) button2 = 0;
      if(digitalRead(BUTTON3)) button3 = 0;
      
      if(!digitalRead(BUTTON1)) button1++;
      if(!digitalRead(BUTTON2)) button2++;
      if(!digitalRead(BUTTON3)) button3++;
      Delete();
      for(int i=2;i<12;i++) if(Sc[2][i]==2) gameend = true;
      
      if(gameend) break;
      if(times++==20){
          if(!G()){
              //方塊落下
              if(!Setnew()) gameend=true;
              play(melody1, noteDurations1, 1);
          }
          times=0;
      }
      delay(20);
      t = (t+1)%1000;

      //
      int i, j, Screen[10][10];
      for(i=0; i<10; i++){
        for(j=0; j<10; j++){
              Screen[i][j] = Sc[i+3][j+2];
          }
      }
      printled(Screen);
      if(button1 == 1){
        if(Check(0,-1)){
            Draw(Now[0],Now[1],0,-1);
            Now[1]--;
            Draw2();
        }
      }

      
      if(button2 == 1){
        if(Check(0,1)){
            Draw(Now[0],Now[1],0,+1);
            Now[1]++;
            Draw2();
        }
      }
      if(button3 == 1){
          play(melody2, noteDurations2, 1);
          for(int i=0;i<5;i++){
              for(int j=0;j<5;j++){
                  Shape2[i][j]=Shape[4-j][i];
                
              }
         
          }
          swaps();
          if(!Check(0,0)){
              swaps();
              for(int i=0;i<5;i++){
                  for(int j=0;j<5;j++){
                      Shape2[i][j]=Shape[i][j];
                  }
              }
          }
          Draw(Now[0],Now[1],0,0);
          for(int i=0;i<5;i++){
              for(int j=0;j<5;j++){
                  Shape2[i][j]=Shape[i][j];
              }
          }
          Draw2();
     }/*
     if(digitalRead(BOTTON4)){
        while(G()){}
        if(!Setnew()) gameend=true;
        break;
     }*/
  }
  int i, j;
  for(i=0; i<14; i++){
    for(j=0; j<12; j++){
      Sc[i][j] = 0;
    }
  }
}


void swaps(){
    int Shape3[5][5];
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) Shape3[i][j] = Shape[i][j];
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) Shape[i][j]  = Shape2[i][j];
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) Shape2[i][j] = Shape3[i][j];
}

bool Check(int x,int y){
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) 
    if(Shape[i][j]==1 && Sc[Now[0]+i+x][Now[1]+j+y]==2) return false;
    return true;
}

void Draw(int x,int y,int ax,int ay){ //位移方塊 
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) if(Shape2[i][j] == 1) Sc[Now[0]+i][Now[1]+j]=0;
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) if(Shape[i][j] == 1)  Sc[Now[0]+i+ax][Now[1]+j+ay]=1;
}
  
void Draw2(){ //畫預測位置 
    for(int i=2;i<13;i++) for(int j=2;j<13;j++) if(Sc[i][j]==3) Sc[i][j]=0;
    int c=1;
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) while(Check(c,0)) c++;
    for(int i=0;i<5;i++) for(int j=0;j<5;j++)
    if((Shape[i][j]==1)&&(Sc[Now[0]+i+c-1][Now[1]+j]==0)) Sc[Now[0]+i+c-1][Now[1]+j]=3;         
}

bool Setnew(){
    int n=random()%7;
    if(n==0){
        Now[0]=0;
    Now[1]=random()%5+1;
    }else{
        Now[0]=1;
    Now[1]=random()%6+1;
    }
    Now[2]=n;
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) Shape[i][j]=Shape2[i][j]=Table[n][i][j];
    if(Check(0,0)){
        Draw(Now[0],Now[1],0,0);
        Draw2();
    }else{
        Draw(Now[0],Now[1],0,0);
        return false;
    }
    return true;
}


void Delete(){
    bool ok;
    int down=0;
    for(int i=12;i>=2;i--){
        ok=true;
        for(int j=2;j<12;j++) if(Sc[i][j]!=2){ok=false;break;}
        if(down){
            for(int j=2;j<12;j++){Sc[i+down][j]=Sc[i][j];Sc[i][j]=0;}
        }
        if(ok) down++;
    }
    point+=down*10000;
}

bool G(){
    if(Check(1,0)){
        Draw(Now[0],Now[1],1,0);
        Now[0]++;
        return true;
    }
    int t=0;
    while(1){
        if(t++ == 10) break;
        delay(10);
        if(button1 == 1){
            if(Check(0,-1)){
                Draw(Now[0],Now[1],0,-1);
                Now[1]--;
            }
        }
        if(button2 == 1){
             if(Check(0,1)){
                Draw(Now[0],Now[1],0,+1);
                Now[1]++;
            }
        }
    }

    if(Check(1,0)){
        Draw(Now[0],Now[1],1,0);
        Now[0]++;
        return true;
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(Shape[i][j]==1){
                Sc[Now[0]+i][Now[1]+j]=2;
            }
        }
    }
    return false;
}


void printled(int Screen[10][10]) //螢幕顯示(arduino要改成控制LED) 
{  
  int i, j;
  for(i=0; i<10; i++){
    for(j=0; j<10; j++){
      int a;
      a = Screen[i][j];
      if(a == 2) a=c1;
      switch(a){
        case 0:
          leds[10*i+j] = CRGB::Black;
          break;
        case 1:
          leds[10*i+j] = CRGB::Green;
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

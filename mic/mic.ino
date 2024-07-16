const int micPin = A0;  // 小麥克風連接到模擬輸入A0引腳

void setup() {
  Serial.begin(9600);  // 初始化串口通信
}


int Screen[10][10] = {0};   //紀錄 10*10 LED矩陣亮暗
double x = -1, y = 5, v = 0; //紀錄flapppy bird高度, 下落速度 

void print(int Screen[10][10], double x) //螢幕顯示(arduino要改成控制LED) 
{  
}
void loop() {
  while(1){  
    delay(10);        //畫面每10ms更新一次
    print(Screen, x);
    
    Screen[(int)y][3] = 0;
    y += v;
    x += 1;
    v += 0.02;
    if(Screen[(int)y][3] == 1  || y<0 || y>=10){
      delay(2000); 
      break; //判斷是否出界
    } 
    Screen[(int)y][3] = 2;
    
    //點擊按鍵(arduino要改成由麥克風控制) 
    if(true){
      //
      v = -0.3;
    }
    
    //每50ms 
    if(((int)x)%5 == 0){
      int i, j, temp[10][10] = {0};
      
      //牆往右移動 
      for(i=0; i<10; i++) for(j=0; j<9; j++)
        if(Screen[i][j+1] == 1) Screen[i][j] = 1;
        else Screen[i][j] = 0;
      for(i=0; i<10; i++) Screen[i][9] = 0;
      
      //每400ms
      if(((int)x)%40 == 0){
        //在最右側生成新的牆
        int i, j, hole_y = rand()%6+2;
        for(i=0; i<10; i++) if(abs(i-hole_y) > 2) Screen[i][9] = 1;  
      } 
    } 
  }
}

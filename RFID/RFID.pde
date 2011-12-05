int val = 0;
char code[10];
int bytesread = 0;
 
void setup() {
 
Serial.begin(2400); // 將Serial RX pin(digital 0) 設為2400bps
pinMode(2,OUTPUT); // 將digital pin 2設為輸出，以便傳送訊號給RFID reader
}
 
 void loop() {
 digitalWrite(0, LOW);                  // 啟動RFID reader
 if(Serial.available() > 0) {          // 假如reader有資料讀入
    if((val = Serial.read()) == 10) {   // 檢查標頭是否為10
      bytesread = 0;
      while(bytesread<10) {             
        if( Serial.available() > 0) {
          val = Serial.read();
          if((val == 10)||(val == 13)) { //假如讀到表示標頭的10或結束的13           
            break;                       // 停止讀取
          }
          code[bytesread] = val;         //紀錄讀入的值          
          bytesread++;                   //準備讀取下一個位元 
        }
      }
      if(bytesread == 10) {              // 如果十個號碼皆讀取成功
        //Serial.print("TAG code is: ");  
        Serial.print(code);            // 顯示TAG號碼
      }
      bytesread = 0;
      digitalWrite(0, HIGH);             // 關閉RFID reader
      delay(500);                     
    }
 }
}

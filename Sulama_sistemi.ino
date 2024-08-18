#include <LiquidCrystal_I2C.h> // lcd ekan için kütüphane
int sensor = A0; // nem sensörü bağlantısı
int buzzer = 13; // buzzer bağlantısı
int motor = 8; // su pompasın bağlantısı
int Nem ; // sensör Nemini okumak için değişken
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(sensor, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); //kullanılan baud
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  
}

void loop() {
  Nem = analogRead(sensor); // Sensör değerini Nem değişkenine yazıyor 
  lcd.clear(); //okunan eski değeri silinmesini sağlıyor
  lcd.print("Nem orani=");
  lcd.print(Nem);
  lcd.setCursor(2,1);
  if(Nem > 700)
  lcd.print("Cok Kuru!!!");
  if(Nem > 230 && Nem < 700)
  lcd.print("Normal Durumda");
  if(Nem < 230 )
  lcd.print("Fazla Islak");
  // lcd ekrana nem miktarını yazdırıyor 
  Serial.println(Nem); // Serial monitöre nem değerini yazıyor
  if (Nem > 550) { // nem 450 üstündeyse sulama işlemini yapıyor
    digitalWrite(motor, LOW);
    delay(2000);
    digitalWrite(motor, HIGH);
    delay(4000);
    if(Nem > 550){// nemi tekrar kontrol ediyor 450 üstüyse sulamaya devam ediyor
      digitalWrite(motor, LOW);
      delay(2300);
      digitalWrite(motor, HIGH);
      delay(2000);
    }
  }
  else{
    digitalWrite(motor, HIGH);
  }

  if (Nem > 750 || Nem < 200) { // Toprak çok kuru olduğu zaman alarm çalılıyor
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(1000);
  }
delay(10000); // nem oranını tekrar ölçmeden önce istendiği kadar beklemesini sağlıyor burda 10 saniye
}

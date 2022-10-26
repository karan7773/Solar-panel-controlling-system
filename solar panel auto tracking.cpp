#include <Servo.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
double intensity(int anval,int resistor){
  double vout=anval*0.0048828125;
  int lux=((2500/vout-500)/resistor);
  return lux;
} 
const int voltageSensor = A0;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 160; 
int servovLimitLow = 20; 
int ldrtopr = 1;  //top right LDR yellow 
int ldrbotl = 3;  // bottom left LDR blue 

void setup () 
{
  lcd.init();
  lcd.backlight();
  servoverti.attach(9); 
  servoverti.write(0); 
  delay(50); 
  Serial.begin(9600);
}
void loop()
{ 
  int anvv=analogRead(A1);
  int anvss=analogRead(A3);
  int ress=10;
  servov = servoverti.read(); 
  //capturing analog values of each LDR  
  int topr = analogRead(ldrtopr); 
  int botl = analogRead(ldrbotl);  
  // calculating average 
  int avgtop = topr ;   //average of top LDR
  int avgbot = botl;    //average of bottom ldr 
  if (avgtop < avgbot) 
  {
    servoverti.write(servov +1); 
    if(servov > servovLimitHigh) 
    {
      servov = servovLimitHigh; 
    }
    delay(100);
  }
  else if (avgbot < avgtop) 
  {
    servoverti.write(servov -1);
}
 if (servov < servovLimitLow) 
    {
      servov = servovLimitLow; 
}
    delay(100); 
  }
  else
 {
    servoverti.write(servov); 
  }
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0 ) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  delay(50); 
  lcd.setCursor(0,0);          
  lcd.print("intensity:");
  lcd.print(int(intensity(anvv,ress)));
  Serial.print("Light intensity : ");
  Serial.print(int(intensity(anvv,ress)));
  Serial.print(" lux \n");
  lcd.setCursor(0,1);
  lcd.print("voltage : ");
  lcd.print(vIN);
  delay(100);
  Serial.print("voltage : ");
  Serial.print(vIN);
  Serial.print("\n");

}

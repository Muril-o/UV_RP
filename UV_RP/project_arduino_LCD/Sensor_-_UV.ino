#include <LiquidCrystal.h> //Inclusão da biblioteca do Display LCD 16x2


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//Definições dos pinos
int UVOUT = A0; //Sinal de saída do sensor
int REF_3V3 = A1; 

 
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
 
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
 
  Serial.println("ML8511 example");
  
}
 
void loop()
{
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Use o pino de alimentação de 3.3V como referência para obter um valor de saída muito preciso do sensor
  float outputVoltage = 3.3/ refLevel * uvLevel ;
  
  float uvIntensity = mapfloat(outputVoltage, 0.97, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
  uvIntensity = uvIntensity/21.46;

  if (uvIntensity<0)
  {
    uvIntensity=0;
  }
  
 int mostrar_UV;
  
  Serial.println();
 //Ifs referentes aos índices UV, de acordo com a OMS 
  if(0>= uvIntensity<0.025)
    {
       mostrar_UV=1;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Baixo");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
    
  if(0.025>= uvIntensity<0.05)
    {
        mostrar_UV=2;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Baixo");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
     if(0.05>= uvIntensity<0.075)
    {
        mostrar_UV=3;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Moderado");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
     if(0.075>= uvIntensity<0.1)
    {
       mostrar_UV=4;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Moderado");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
     if(0.1>= uvIntensity<0.125)
    {
       mostrar_UV=5;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Moderado");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
     if(0.125>= uvIntensity<0.15)
    {
        mostrar_UV=6;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Alto");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
      if(0.15>= uvIntensity<0.175)
    {
      mostrar_UV=7;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Alto");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
      if(0.175>= uvIntensity<0.2)
    {
       mostrar_UV=8;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Muito Alto");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
     if(0.2>= uvIntensity<0.225)
    {
       mostrar_UV=9;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Muito Alto");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
    if(0.225>= uvIntensity<0.25)
    {       
       mostrar_UV=10;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Muito Alto");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }
     if(uvIntensity>0.25)
    {
       mostrar_UV=11;
       lcd.clear();
       lcd.print("Intensidade UV");
       lcd.setCursor(0, 1);
       lcd.print(uvIntensity);
       lcd.print(" W/m^2");
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      
       lcd.clear();
       lcd.print("Indice UV:");
       lcd.setCursor(0, 1);
       lcd.print(mostrar_UV);
       delay(1000);
        for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      lcd.clear();
       lcd.print("Risco:");
       lcd.setCursor(0, 1);
       lcd.print("Extremo");
       lcd.setCursor(1, 1);
        delay(1000);
       for (int posicao = 0; posicao < 15; posicao++)
       {
        lcd.scrollDisplayRight();
        delay(300);
      }
      delay(1000);
    }

  delay(200);

  /* Serial.print("output: ");
  Serial.print(refLevel);
 
  Serial.print("ML8511 output: ");
  Serial.print(uvLevel);*/
  
  Serial.print(" ML8511 voltage: ");
  Serial.print(outputVoltage);
  Serial.print( "  ");
 
  Serial.print(" / Intensidade UV (W/m^2): ");
  Serial.print(uvIntensity);
  Serial.print( "  ");

  Serial.print(" / Índice UV): ");
  Serial.print(mostrar_UV);
  Serial.print( "  ");
}
 
//Leva uma média de leituras em um determinado pino
//Retorna a média
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
 
  return(runningValue);
}
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

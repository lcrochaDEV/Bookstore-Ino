/**************************LUCAS ROCHA****************************/
/*
 * Portas Alalogicas A = 1,2,3,4,5,6,7.
 * Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12.
 * 
*/
#define btn 6
#define pin_ 9 //LOOP MODE
#define led1 A1
#define led2 A2
#define tmpLongo 2000
#define tmpCurto 500
long tmpInicio;
/*****************************************************************/

void setup() {
  //put your setup code here, to run once:
  pinMode(btn, INPUT_PULLUP);
  //pinMode(btn, INPUT); //PIN_6
  pinMode(led1, OUTPUT); //A1
  pinMode(pin_, OUTPUT); //PIN_7
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW); 
}

void loop() {
  //put your main code here, to run repeatedly:
  tmpInicio = digitalRead(btn); //le o estado do botão - HIGH OU LOW
  if(digitalRead(btn) == LOW){
    tmpInicio = millis();  
    while((millis() - tmpInicio < tmpLongo) && (digitalRead(btn) == LOW));
    
    if(millis() - tmpInicio < tmpCurto){            //CLICK E ACIOMA O LED1 E APAGA
      digitalWrite(led1, !digitalRead(led1));
      digitalWrite(led2, LOW);      
    
    }else if(millis() - tmpInicio >= tmpLongo){     //CLICK E ACIOMA O LED2 E APAGA
      digitalWrite(led2, !digitalRead(led2));
      digitalWrite(led1, LOW);
      while(digitalRead(btn) == LOW);
      
    }
  }
}//fim loop
//C:\Users\LuKInhas\AppData\Local\Temp\arduino_build_570449\Bot_o_dupla_fun__o.ino.hex

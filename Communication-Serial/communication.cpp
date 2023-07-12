#define btn_13 13 //PIN_D13

String pinArr [] = {"A1", "D13"};

int pin_On = HIGH; //PIN STATE AUTO = 1
int pin_Off = LOW; //PIN STATE BAIXO = 0
String promptCLI = "ESP-NOW> ";

//regexp = /\w[A-z]{2}\s(\w\d{2})\s(\w+)/gm

void setup() {
    Serial.begin(9600);
    pinMode(btn_13, OUTPUT); //PIN_D13
    boasVindas();
}
void boasVindas() {
  Serial.print("O Modulo Iniciou com Sucesso! ");
  Serial.println();
  Serial.print(promptCLI);
  Serial.println();
}

//SERIAL COMMAND
void console() {
  if(Serial.available() > 0){
    String consoleText = Serial.readString();
    consoleText.trim();
    Serial.print(promptCLI);
    Serial.println(consoleText);
    //comandos(consoleText);
    pinSelection(consoleText);
  }
}

int cont = 0;
void pinSelection(String pin) {
while(cont > -1){
    if(pinArr[cont].indexOf(pin)){ //imprimindo texto em branco*
        Serial.print("ESP-NOW-" + pin + "> ");
        Serial.println();
      break;
    } else {
      comnandError();
      break;
  }
    cont++;
  }
}
void pinOnOff(String pin){
  if(pin == String("On")){
    Serial.print("ESP-NOW-" + pin + "> ");
    Serial.println();
  } else {
      comnandError();
  }
}


void comandos(String status){
  if(status == String("pin_On")){
    Serial.print(promptCLI + "PIN_ON");
    Serial.println();
  } else if(status == String("pin_Off")){
    Serial.print(promptCLI + "PIN_OFF");
    Serial.println();
  } else {
    comnandError();
    Serial.print(promptCLI);
    Serial.println();
  }
}

void comnandError() {
    Serial.print("error, comando null!");
    Serial.println();
}

void loop(){
 /* 
  digitalWrite(btn_13, HIGH);
  delay(1000);
  digitalWrite(btn_13, LOW);
  delay(1000);
  */
  console();
}

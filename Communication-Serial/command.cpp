/**************************LUCAS ROCHA****************************/
/*
 * Portas Alalogicas A = 1,2,3,4,5,6,7.
 * Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.
 * Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.
 *
 * Data 12/07/2023
*/
/*****************************************************************/
String promptCLI = "ESP-NOW> ";

String pinType[] = {"A1", "D2", "D13"};
String bufferArray[3]; // =>  activePin, estado}

int pin_On = HIGH; //PIN STATE ALTO = 1
int pin_Off = LOW; //PIN STATE BAIXO = 0

int contagem = 0; //CONTADOR
//CONTA O TAMANHO DO ARRAY pinNumber
int pinMode_lenght(){
  return sizeof(pinType)/ sizeof(int);
}
template< typename T, size_t N > size_t ArraySize (T (&) [N]){
  return N; 
}
class Message {
  public:
    Message(String msg);
    void MessageView();
  private:
    String text;
};
Message::Message(String msg){
  text = msg;
}
void Message::MessageView(){
  Serial.print(text);
  Serial.println();
}

//MENSAGENS E RETORNOS DE ERROS
Message boasVindas("O Modulo Iniciou com Sucesso...");
Message promptInicial("ESP-NOW> ");

void setup() {
  Serial.begin(9600);
  boasVindas.MessageView();
  promptInicial.MessageView();
}
// VERIFICAR FILTRA ELEMENTOS DE UM ARRAY (filter)
//SERIAL COMMAND
void console() {
  if (Serial.available() > 0) {
    String consoleText = Serial.readString();
    consoleText.trim();
    if (consoleText.length() > 1) {
      consoleText.toUpperCase();
      pinTypeExiste(consoleText);
    } else {
      pinLost(consoleText); //ERRO
    }
  }
}
//FUNÇÃO QUE VERIFICA SE ELEMENTO EXISTE NO ARRAY pinType
int pinTypeExiste(String consoleText){ //imprimindo texto em branco*
  while(contagem < pinMode_lenght()) {
    if(consoleText == pinType[contagem]){ //VERIFICA SE EXISTE NO ARRAY
      if (consoleText.indexOf("A") == 0 && consoleText.length() == 2 || consoleText.indexOf("D") == 0 && consoleText.length() <= 3) {
        bufferArray[0] = consoleText; //OBRIGATÓRIO
        printTxt(consoleText);
      break;
      }
    }else if(consoleText == "INPUT" || consoleText == "OUTPUT" || consoleText == "OUTPUT"){
      pin_mode(consoleText);
    break;
    }else if(consoleText == "ON" || consoleText == "OFF"){;
      pinOnOff(consoleText);
    break;
    }else if(consoleText == "END"){
      retornMenuPrincipal();
    break;
    }else if(consoleText == "HELP"){
      helpePin();
    break;
    }else if(pinType[contagem] == -1){
      comnandError(); //ERRO
    break;
    }
    contagem++;
    }
contagem = 0;
}
//MODO DE OPERAÇÃO DO PINO SELECIONADO
void pin_mode(String consoleText){
  if(bufferArray[0] != NULL){
    bufferArray[1] = consoleText;
    int activePin = bufferArray[0].substring(1).toInt(); //BUSCA O NUMETO EM ESTRING E TRANSFORMA EM INT
      //pinMode(activePin, consoleText.toInt());
      pinomodeSuccess(consoleText);
  }
}
void pinOnOff(String consoleText){
  bufferArray[2] = consoleText;
  if(bufferArray[1] != NULL){
    onOff(bufferArray[2]);
    activePin();
  }else{
    pinomodeError();
  }
}
//ACIONAMENTO DO PINOS
void activePin(){
  int activePin = bufferArray[0].substring(1).toInt(); //BUSCA O NUMERO EM ESTRING E TRANSFORMA EM INT
  if(bufferArray[2] == "ON"){
    digitalWrite (activePin, pin_On);  
  }else if(bufferArray[2] == "OFF"){
    digitalWrite (activePin, pin_Off);
  } 
}
void comnandError() {
  returnConsoleText("error, comando null!");
}
void pinLost(String consoleText) {
  returnConsoleText("("+ consoleText +")Pino não Encontrado!");
}
//USADO PELAS FUNÇÕES pinOnOff
void pinonaoencontrado() {
  returnConsoleText("Selecione um Pino!");
}
void pinomodeSuccess(String consoleText) {
  returnConsoleText("Modo de Operação " + consoleText + " Acionado!");
}
void pinomodeError() {
  returnConsoleText("Selecione um Modo de Operação!");
}
//USADO PELAS FUNÇÕES boasVindas e comnandError
void returnConsoleText(String text){
  if(bufferArray[0] == NULL){
    errorGenerico(text, promptCLI);
  }else {
    errorGenerico(text, "ESP-NOW-" + bufferArray[0] + ">");
  }
}
//USADO PELAS FUNÇÕES returnConsoleText
void errorGenerico(String text, String modePin){
  Serial.print(text);
  Serial.println();
  Serial.print(modePin);
  Serial.println();
}
//USADO PELAS FUNÇÕES pinTypeExiste e activePin
void printTxt(String consoleText){
  Serial.print("ESP-NOW-" + consoleText + ">");
  Serial.println();
}
void onOff(String onOff){
  if(onOff == "ON"){
    ativo(onOff, "ativo");
  }else if(onOff == "OFF"){
    ativo(onOff, "desativado");
  }else{
    comnandError();
  }
}
//USADO PELAS FUNÇÕES onOff
void ativo(String onOff, String text){
    Serial.print("ESP-NOW-" + bufferArray[0] + ">" + onOff);
    Serial.println();
    Serial.print("Pino " + bufferArray[0] + " " + text +" com sucesso!");
    Serial.println();
    Serial.print("ESP-NOW-" + bufferArray[0] + ">");
    Serial.println();
}
//USADO PELAS FUNÇÕES
void retornMenuPrincipal(){
  for (int i = 0; i <= 2; i++) {
    bufferArray[i] = "\0"; 
  }
  Message promptInicial("ESP-NOW> ");
}
void helpePin(){
    Serial.print("/***********************PINOS ARDUINO NANO************************/");
    Serial.println();
    Serial.print("Portas Analogicas A = 1,2,3,4,5,6,7.");
    Serial.println();
    Serial.print("Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.");
    Serial.println();
    Serial.print("Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.");
    Serial.println();
    Serial.println();
    Serial.print("Data 12/07/2023");
    Serial.println();
    Serial.print("/*****************************************************************/");
    Serial.println();
    retornMenuPrincipal();
}

void loop(){
 console(); 
}
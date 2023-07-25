/**************************LUCAS ROCHA****************************/
/*
 * Portas Analogicas A = 1,2,3,4,5,6,7.
 * Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.
 * Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.
 *
 * Data 12/07/2023
*/
/*****************************************************************/
String promptCLI; //NOME DO MODULO
String pinType[30] = {"D13"};
String bufferArray[3]; // =>  activePin, estado}

int pin_On = HIGH; //PIN STATE ALTO = 1
int pin_Off = LOW; //PIN STATE BAIXO = 0

int contagem = 0; //CONTADOR
//CONTA O TAMANHO DO ARRAY pinNumber
int pinMode_lenght(){
  return sizeof(pinType)/ sizeof(int);
}
template< typename T, size_t N > size_t ArraySize (T (&) [N]) {
  return N; 
}
class Message {
  public:
  Message(String consoleText = "");
    void elementName(String consoleText = "ARDUINO");
    void helloWord(String consoleText  = "Hello Word");
    void consoleView();
    void messageViewMsg2();
  private:
    String consoleTextView;
    
    void digitalPins(String consoleText);
    void analogPins(String consoleText);
    void mostraPinos();
    //MODO DE OPERAÇÃO DO PINO SELECIONADO
    void pin_mode(String consoleText = "");
    void pinOnOff(String consoleText);
    void activePin();
    void onOff(String consoleText);
    void ativo(String onOff, String consoleText);
    void retornMenuPrincipal();
    void help();
    void returnConsoleText(String consoleText);
    //MENSAGEM DE TODO O PROGRAMA
    void messageViewMsg1(String consoleText);
};
Message::Message(String consoleText = ""){
    this->consoleTextView = consoleText;
}
void Message::elementName(String consoleText = "ARDUINO"){
    promptCLI = consoleText;
}
void Message::helloWord(String consoleText = "Hello Word"){
  messageViewMsg1(consoleText);
  messageViewMsg1(promptCLI + "> ");
}
void Message::consoleView(){
  if (Serial.available() > 0) {
    String consoleText = Serial.readString();
    consoleText.trim();
    if (consoleText.length() > 1) {
      consoleText.toUpperCase();
       // analogPins(consoleText);
        digitalPins(consoleText);
    }else{
      returnConsoleText("("+ consoleText +")Pino não Encontrado!");
    }
  }
}

void Message::digitalPins(String consoleText){
  while(contagem < ArraySize(pinType)) {
    if(consoleText == pinType[contagem]){ //VERIFICA SE EXISTE NO ARRAY
      if (consoleText.indexOf("D") == 0 && consoleText.length() <= 3) {
        bufferArray[0] = consoleText; //OBRIGATÓRIO
        pin_mode();
      break;
      }
    }else if(consoleText == "LISTPIN"){
      mostraPinos();
    break;
    }else if(consoleText == "INPUT" || consoleText == "OUTPUT" || consoleText == "INPUT_PULLUP"){
      pin_mode(consoleText);
    break;
    }else if(consoleText == "ON" || consoleText == "OFF"){;
      pinOnOff(consoleText);
    break;
    }else if(consoleText == "END"){
      retornMenuPrincipal();
    break;
    }else if(consoleText == "HELP"){
      help();
    break;
    }else  {
      returnConsoleText("error, comando null!"); //ERRO
    break;
    }
    contagem++;
  }
contagem = 0;
}
void Message::analogPins(String consoleText){
  messageViewMsg1(promptCLI + "-" + consoleText + ">");
}
//MOSTRA PINOS NA LISTA
void Message::mostraPinos(){
  if(pinType[1] != 0) {
    for (int i = 0; i < ArraySize(pinType); i++) {
      if(pinType[i] != 0) {
        messageViewMsg1(pinType[i]);
      }
    }
 }else{
  returnConsoleText("Apenas o pino " + pinType[0] + "(default) Cadastrado.");
 }
}  
//MENSAGEM DE TODO O PROGRAMA
void Message::pin_mode(String consoleText = ""){
  if(consoleText != "") {
    if(bufferArray[0] != NULL){
      bufferArray[1] = consoleText;
      messageViewMsg1("Modo de Operação " + consoleText + " Acionado!");
      messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
    }else{
      returnConsoleText("Selecione um Pino!"); //ERRO
    }
  }else{
      messageViewMsg1("Escolha um Modo de Operação");
      messageViewMsg1("INPUT, OUTPUT ou INPUT_PULLUP");
      messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
  }
}
void Message::pinOnOff(String consoleText){
  bufferArray[2] = consoleText;
  if(bufferArray[0] == NULL){
    returnConsoleText("Selecione um Pino!");
  }else if(bufferArray[1] != NULL){
    onOff(bufferArray[2]);
    activePin();
  }else{
    returnConsoleText("error, comando null!"); //ERRO
  }
}
void Message::activePin(){
  int activePin = bufferArray[0].substring(1).toInt(); //BUSCA O NUMERO EM STRING E TRANSFORMA EM INT
  if(bufferArray[2] == "ON"){
    digitalWrite (activePin, pin_On);  
  }else if(bufferArray[2] == "OFF"){
    digitalWrite (activePin, pin_Off);
  } 
}
void Message::onOff(String onOff){
  if(onOff == "ON"){
    ativo(onOff, "ativo");
  }else if(onOff == "OFF"){
    ativo(onOff, "desativado");
  }else{
    returnConsoleText("error, comando null!"); //ERRO
  }
}
void Message::ativo(String onOff, String consoleText){
  messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">" + onOff);
  messageViewMsg1("Pino " + bufferArray[0] + " " + consoleText +" com sucesso!");
  messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
}
void Message::retornMenuPrincipal(){
  for (int i = 0; i <= 2; i++) {
    bufferArray[i] = "\0"; 
  }
    messageViewMsg1(promptCLI + "> ");
}
void Message::help(){
  messageViewMsg1("/***********************PINOS ARDUINO NANO************************/");
  messageViewMsg1("Portas Analogicas A = 1,2,3,4,5,6,7.");
  messageViewMsg1("Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.");
  messageViewMsg1("Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.");
  messageViewMsg1("Data 12/07/2023");
  messageViewMsg1("/*****************************************************************/");
  messageViewMsg1(promptCLI + "> ");
}
void Message::returnConsoleText(String consoleText){
  if(bufferArray[0] == NULL){
    messageViewMsg1(consoleText);
    messageViewMsg1(promptCLI + "> ");
  }else if(bufferArray[1] == NULL){
    messageViewMsg1("Escolha um Modo de Operação");
    messageViewMsg1("INPUT, OUTPUT ou INPUT_PULLUP");
    messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
  }else {
    messageViewMsg1(consoleText);
    messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
  }
}
//MENSAGEM DE TODO O PROGRAMA
void Message::messageViewMsg1(String consoleText){
  Serial.println(consoleText);
}
void Message::messageViewMsg2(){
  Serial.println(consoleTextView);
}
//MENSAGENS E RETORNOS DE ERROS
Message consoleView;
void setup() {
  delay(100);
  Serial.begin(9600);
  consoleView.elementName("ESP-NOW");
  consoleView.helloWord("O Modulo Iniciou com Sucesso...");
}
/*
Message msg("NOVO");
  msg.messageViewMsg2();
}
*/
void loop(){
  consoleView.consoleView();
}

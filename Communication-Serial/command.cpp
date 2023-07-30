/****LUCAS ROCHA****/
/*
 * Portas Analogicas A = 1,2,3,4,5,6,7.
 * Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.
 * Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.
 *
 * Data 12/07/2023
*/
/*********/
int contagem = 0; //CONTADOR

//CONTA O TAMANHO DO ARRAY
template< typename T, size_t N > size_t ArraySize (T (&) [N]) {
  return N; 
}
//******BUFFER MEMORY******//
String bufferArray[5]; // =>  [PIN = type String, NUMBER PIN = type Nunber, MODE OPERATION = type Number, ON|OFF = type String]
//******BUFFER MEMORY******//

String promptCLI; //NOME DO MODULO
int digitalPinArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; //ARRAY DE PINOS
int analogPinArr[] = {14, 15, 16, 17, 18, 19, 20, 21}; //ARRAY DE PINOS
String modeOperation[3] = {"INPUT", "OUTPUT", "INPUT_PULLUP"}; //ARRAY DE MODOS

int arrayIndexOff(String nomeDoModo){
  while(contagem < ArraySize(modeOperation)) {
    if(nomeDoModo == modeOperation[contagem]){
      return contagem;
    break;
    }
    contagem++;
  }
contagem = 0;
}

//CONTA O TAMANHO DO ARRAY pinNumber
int pinMode_lenght(){
  return sizeof(digitalPinArr)/ sizeof(int);
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
    
    void arduinoPins(String consoleText);
    void subMenuFunction(String consoleText);
    void analogPins(String consoleText);
    void mostraPinos();
    //MODO DE OPERAÇÃO DO PINO SELECIONADO
    void pin_mode(String consoleText = "");
    void pinOnOff(String consoleText);
    void activePin();
    void ativo(String consoleText);
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
      arduinoPins(consoleText);
    }else{
      returnConsoleText("("+ consoleText +")Pino não Encontrado!");
    }
  }
}
//MENU PINOS DIGITAIS
void Message::arduinoPins(String consoleText){
  if(consoleText.startsWith("D") && consoleText.length() <= 3) {
    while(contagem < ArraySize(digitalPinArr)) {
      if(consoleText.substring(1).equals(String(digitalPinArr[contagem]))){ //VERIFICA SE EXISTE NO ARRAY
        bufferArray[0] = consoleText; //OBRIGATÓRIO
        bufferArray[1] = digitalPinArr[contagem]; //OBRIGATÓRIO
        pin_mode();
      break;
      }else if(consoleText.substring(1).equals(String(ArraySize(digitalPinArr)))){
        returnConsoleText("Pino não encontrado!");
      break;
      }
    contagem++;
    }
    contagem = 0;
  } else if(consoleText.startsWith("A") && consoleText.length() <= 3) {
    while(contagem < ArraySize(analogPinArr)) {
      if(consoleText.substring(1) + String(ArraySize(digitalPinArr)).equals(String(analogPinArr[contagem]))){ //VERIFICA SE EXISTE NO ARRAY
       // Serial.println();
        bufferArray[0] = consoleText; //OBRIGATÓRIO
        bufferArray[1] = analogPinArr[contagem];
        Serial.println( bufferArray[1]);
        pin_mode();
      break;
     }else if(consoleText.substring(1).endsWith(String(analogPinArr[contagem]))){
        returnConsoleText("Pino não encontrado!");
      break;
      }
    contagem++;
    }
    contagem = 0;
  }else {
    subMenuFunction(consoleText);
  }
}
//SUB-MENU
void Message::subMenuFunction(String consoleText){
  if(consoleText == "LISTPIN"){
   // mostraPinos();
  }else if(consoleText == "INPUT" || consoleText == "OUTPUT" || consoleText == "INPUT_PULLUP"){
      pin_mode(consoleText);
  }else if(consoleText == "ON" || consoleText == "OFF"){
      pinOnOff(consoleText);
  }else if(consoleText == "END"){
    retornMenuPrincipal();
  }else if(consoleText == "HELP"){
    help();
  }else  {
    returnConsoleText("error, comando null!"); //ERRO
  }
}
void Message::analogPins(String consoleText){
  messageViewMsg1(promptCLI + "-" + consoleText + ">");
}
//MOSTRA PINOS NA LISTA
void Message::mostraPinos(){
  if(digitalPinArr[1] != 0) {
    for (int i = 0; i < ArraySize(digitalPinArr); i++) {
      if(digitalPinArr[i] != 0) {
        messageViewMsg1(String(digitalPinArr[i]));
      }
    }
 }else{
  returnConsoleText("Apenas o pino " + String(digitalPinArr[0]) + "(default) Cadastrado.");
 }
}//SEM FUNCIONALIDADE NO MOMENTO
//MENSAGEM DE TODO O PROGRAMA
void Message::pin_mode(String consoleText = ""){
 if(consoleText != NULL) {
    if(bufferArray[0] != NULL){
      bufferArray[2] = arrayIndexOff(consoleText);
      pinMode(bufferArray[1].toInt(), bufferArray[2].toInt());
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
  if(bufferArray[2] != NULL){
    bufferArray[3] = consoleText;
    activePin();
  }else if(!bufferArray[0]){
    returnConsoleText("error, comando null!"); //ERRO
  }else{
    returnConsoleText("Selecione um Pino!");
  }
}
void Message::activePin(){
  if(bufferArray[3] == "ON"){
    digitalWrite (bufferArray[1].toInt(), HIGH);  
    ativo("ativo");
  }else if(bufferArray[3] == "OFF"){
    digitalWrite (bufferArray[1].toInt(), LOW);
    ativo("desativado");
  }else{
    returnConsoleText("error, comando null!"); //ERRO
  }
}
void Message::ativo(String consoleText){
  messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">" + bufferArray[4]);
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
  messageViewMsg1("/***PINOS ARDUINO NANO****/");
  messageViewMsg1("Portas Analogicas A = 1,2,3,4,5,6,7.");
  messageViewMsg1("Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.");
  messageViewMsg1("Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.");
  messageViewMsg1("Data 12/07/2023");
  messageViewMsg1("/*********/");
  messageViewMsg1(promptCLI + "> ");
}
void Message::returnConsoleText(String consoleText){
  if(bufferArray[0] == NULL){
    messageViewMsg1(consoleText);
    messageViewMsg1(promptCLI + "> ");
  }else if(bufferArray[3] == NULL){
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
  //digitalWrite(A0, HIGH);
}
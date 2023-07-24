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
    void elementName(String consoleText  = "ARDUINO");
    void helloWord(String consoleText  = "Hello Word");
    void messageView(String msg);
  private:
};
void Message::elementName(String consoleText = "ARDUINO"){
    promptCLI = consoleText;
}
void Message::helloWord(String consoleText = "Hello Word"){
  messageView(consoleText);
  messageView(promptCLI + "> ");
}
void Message::messageView(String msg){
  Serial.print(msg);
  Serial.println();
}
//MENSAGENS E RETORNOS DE ERROS
Message renameElement;
Message boasVindas;
Message promptInicial;
Message mostraPin;
Message printTxt;
Message helpPin;
Message pinAtivo;
Message errorGenerico;
Message pinomodeSuccess;

void setup() {
  Serial.begin(9600);
  renameElement.elementName("ESP-NOW");
  boasVindas.helloWord("O Modulo Iniciou com Sucesso...");
}
// VERIFICAR FILTRAR ELEMENTOS DE UM ARRAY (filter)
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

//FUNÇÃO QUE VERIFICA SE ITEM ELEMENTO EXISTE NO ARRAY pinType
int pinTypeExiste(String consoleText){ //imprimindo texto em branco*
  while(contagem < ArraySize(pinType)) {
    if(consoleText != pinType[contagem]){ //VERIFICA SE EXISTE NO ARRAY
      if (consoleText.indexOf("A") == 0 && consoleText.length() == 2 || consoleText.indexOf("D") == 0 && consoleText.length() <= 3) {
        for (int i = 0; i < ArraySize(pinType); i++) {
          if(pinType[i] != consoleText) {
            pinType[i] = consoleText;
            Serial.print(ArraySize(pinType));
          }
        }
        bufferArray[0] = consoleText; //OBRIGATÓRIO
        printTxt.messageView(promptCLI + "-" + consoleText + ">");
      break;
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
      }else if(pinType[contagem] == -1){
        comnandError(); //ERRO
      break;
      }
    }
    contagem++;
  }
contagem = 0;
}
//MOSTRA PINOS NA LISTA
void mostraPinos(){
  if(pinType[1] != 0) {
    for (int i = 0; i < ArraySize(pinType); i++) {
      if(pinType[i] != 0) {
        mostraPin.messageView(pinType[i]);
      }
    }
 }else{
  returnConsoleText("Apenas o pino " + pinType[0] + "(default) Cadastrado.");
 }
}  

//MODO DE OPERAÇÃO DO PINO SELECIONADO
void pin_mode(String consoleText){
  if(bufferArray[0] != NULL){
    bufferArray[1] = consoleText;
    pinomodeSuccess.messageView("Modo de Operação " + consoleText + " Acionado!");
    pinAtivo.messageView(promptCLI + "-" + bufferArray[0] + ">");
  }else{
    pinonaoencontrado();
  }
}
void pinOnOff(String consoleText){
  bufferArray[2] = consoleText;
  if(bufferArray[0] == NULL){
    pinonaoencontrado();
  }else if(bufferArray[1] != NULL){
    onOff(bufferArray[2]);
    activePin();
  }else{
    pinomodeError();
  }
}
//ACIONAMENTO DO PINOS
void activePin(){
  int activePin = bufferArray[0].substring(1).toInt(); //BUSCA O NUMERO EM STRING E TRANSFORMA EM INT
  if(bufferArray[2] == "ON"){
    digitalWrite (activePin, pin_On);  
  }else if(bufferArray[2] == "OFF"){
    digitalWrite (activePin, pin_Off);
  } 
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
  pinAtivo.messageView(promptCLI + "-" + bufferArray[0] + ">" + onOff);
  pinAtivo.messageView("Pino " + bufferArray[0] + " " + text +" com sucesso!");
  pinAtivo.messageView(promptCLI + "-" + bufferArray[0] + ">");
}
//USADO PELAS FUNÇÕES help
void retornMenuPrincipal(){
  for (int i = 0; i <= 2; i++) {
    bufferArray[i] = "\0"; 
  }
  promptInicial.messageView(promptCLI + "> ");
}
void help(){
    helpPin.messageView("/***********************PINOS ARDUINO NANO************************/");
    helpPin.messageView("Portas Analogicas A = 1,2,3,4,5,6,7.");
    helpPin.messageView("Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.");
    helpPin.messageView("Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.");
    helpPin.messageView("Data 12/07/2023");
    helpPin.messageView("/*****************************************************************/");
    retornMenuPrincipal();
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
void pinomodeError() {
  returnConsoleText("Selecione um Modo de Operação!");
}
//USADO PELAS FUNÇÕES boasVindas e comnandError
void returnConsoleText(String text){
  if(bufferArray[0] == NULL){
    errorGenerico.messageView(text);
    promptInicial.messageView(promptCLI + "> ");
  }else {
    errorGenerico.messageView(text);
    errorGenerico.messageView(promptCLI + "-" + bufferArray[0] + ">");
  }
}
void loop(){
 console(); 
}
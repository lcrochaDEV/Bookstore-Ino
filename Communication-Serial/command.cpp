/**************************LUCAS ROCHA****************************/
/*
 * Portas ANalogicas A = 1,2,3,4,5,6,7.
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
    void MessageView(String msg);
  private:
};
void Message::MessageView(String msg){
  Serial.print(msg);
  Serial.println();
}
//MENSAGENS E RETORNOS DE ERROS
Message boasVindas;
Message promptInicial;
Message printTxt;
Message helpPin;
Message pinAtivo;
Message errorGenerico;
Message pinomodeSuccess;

void setup() {
  Serial.begin(9600);
  boasVindas.MessageView("O Modulo Iniciou com Sucesso...");;
  promptInicial.MessageView("ESP-NOW> ");
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
  while(contagem < ArraySize(pinType)) {
    if(consoleText == pinType[contagem]){ //VERIFICA SE EXISTE NO ARRAY
      if (consoleText.indexOf("A") == 0 && consoleText.length() == 2 || consoleText.indexOf("D") == 0 && consoleText.length() <= 3) {
        bufferArray[0] = consoleText; //OBRIGATÓRIO
        printTxt.MessageView("ESP-NOW-" + consoleText + ">");
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
      help();
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
    pinomodeSuccess.MessageView("Modo de Operação " + consoleText + " Acionado!");
    pinAtivo.MessageView("ESP-NOW-" + bufferArray[0] + ">");
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
  pinAtivo.MessageView("ESP-NOW-" + bufferArray[0] + ">" + onOff);
  pinAtivo.MessageView("Pino " + bufferArray[0] + " " + text +" com sucesso!");
  pinAtivo.MessageView("ESP-NOW-" + bufferArray[0] + ">");
}
//USADO PELAS FUNÇÕES help
void retornMenuPrincipal(){
  for (int i = 0; i <= 2; i++) {
    bufferArray[i] = "\0"; 
  }
  promptInicial.MessageView("ESP-NOW> ");
}
void help(){
    helpPin.MessageView("/***********************PINOS ARDUINO NANO************************/");
    helpPin.MessageView("Portas Analogicas A = 1,2,3,4,5,6,7.");
    helpPin.MessageView("Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.");
    helpPin.MessageView("Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.");
    helpPin.MessageView("Data 12/07/2023");
    helpPin.MessageView("/*****************************************************************/");
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
    errorGenerico.MessageView(text);
    promptInicial.MessageView("ESP-NOW> ");
  }else {
    errorGenerico.MessageView(text);
    errorGenerico.MessageView("ESP-NOW-" + bufferArray[0] + ">");
  }
}
void loop(){
 console(); 
}
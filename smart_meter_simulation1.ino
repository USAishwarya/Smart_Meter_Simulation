// AUTOMAÇÃO DE LIGAR E DESLIGAR ENERGIA VIA SERIAL
// MICROCONTROLADOR: ARDUINO UNO R3

//INCLUSÃO DE BIBLIOTECAS

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//DEFINIÇÃO DE VARIAVEIS

  int rele = 8;             // PINO 8 DIGITAL UTILIZADO COM O RELÉ
  float tensao = A0;        // PINO QUE MEDE A TENSÃO
  int mover;

//INSTANCIAÇÃO DE OBJETOS

LiquidCrystal_I2C lcd(34,16,2);

    
void setup(){

// INICIA A COMUNICAÇÃO SERIAL
  
  Serial.begin(9600); 
  
// DEFINIÇÃO DAS I/O
  
  pinMode(rele, OUTPUT);      // DEFINE "RELE" COMO UMA SAÍDA
  pinMode(tensao, INPUT);     // LEITURA DE TENSÃO
  
// INICIALIZAÇÃO DO LCD
  
 lcd.init();
 lcd.backlight();
  
}

void loop(){

// LEITURA DE COMANDOS VIA SERIAL 
  
  char key = Serial.read();              // COMEÇA A ACEITAR COMANDO PELA SERIAL

// LEITURA DE TENSAO
  
  float consumo = analogRead (tensao);
  float tensaoLida = float (map(consumo,0,1023,0,5000)/1000);
 
// ENVIO DE LEITURA PELA SERIAL
  
  Serial.print ("Measured value:");
  Serial.print(tensaoLida);
  Serial.println(" V RMS being consumed");
  delay(1000);

/* ------------- COMUNICAÇÃO PELO LCD COM O CONSUMIDOR ----------------- */

// CASO O CONSUMIDOR ESTEJA CONECTADO A REDE, O COMANDO SERA 1 ...
  
  if (key == '1'){         
    
  digitalWrite(rele, HIGH);                     // LIGA O RELÉ
  Serial.println ("Reconnected consumer!");   // RETORNA MENSAGEM PARA A SERIAL

// EXIBE MENSAGEM DE RECONEXÃO AO CONSUMIDOR
    
  lcd.setCursor(0,0);
  lcd.print("    ENERGY ");
  lcd.setCursor(0,1);
  lcd.print(" ESTABLISHED ");
  delay (1000);
   
  lcd.setCursor(0,0);
  lcd.print("   SAVE! ");
  lcd.setCursor(0,1);
  lcd.print("RED RATE ");
  delay (2000);

  lcd.setCursor(0,1);
  lcd.print("WATER SCARCITY");
  delay (2000);

// CASO O CONSUMIDOR ESTEJA DESCONECTADO DA REDE, O COMANDO SERA 0 ...
    
  } if (key == '0'){  
    
  digitalWrite(rele, LOW);                    // DESLIGA O RELÉ
  Serial.println ("Termination carried out!"); // RETORNA MENSAGEM PARA A SERIAL

// DA INFORMAÇÕES PARA O CONSUMIDOR SOBRE O COrte
    
  lcd.setCursor(0,0);
  lcd.print("POWER CUT");
  lcd.setCursor(0,1);
  lcd.print("   REGULARIZE   ");
   
  } if (key == '2'){        
    
  digitalWrite(rele, HIGH);                     // LIGA O RELÉ
  Serial.println ("Green tariff!") ;
        
  lcd.setCursor(0,0);
  lcd.print("   RATE       ");
  lcd.setCursor(0,1);
  lcd.print("       GREEN   ");
  delay (2000);
  
  lcd.setCursor(0,0);
  lcd.print("   CONTINUE     ");
  lcd.setCursor(0,1);
  lcd.print(" SAVING UP  ");
  delay (2000);
  
  }
 delay(10);                 // ESPERA 10ms
}
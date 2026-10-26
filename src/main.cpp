// #include <Arduino.h>
// #include <ArduinoJson.h>
// #include <BluetoothSerial.h>
// #include <LiquidCrystal_I2C.h>

// JsonDocument pasta;
//  String frase;
// BluetoothSerial BT;
//  unsigned long marcoZero = 0;
//  unsigned long intervalo = 2000;
// LiquidCrystal_I2C lcd(0x27, 20, 4);
// uint8_t endSlave[] = {0x1C, 0x69, 0x20, 0x92, 0x2D, 0x52};

// void setup(){
//   Serial.begin(115200);
//   Serial.setTimeout(5000);
//  if (BT.begin("BTMasterNalin", true))
//   {
//     Serial.println("Bluetooth iniciado com sucesso!");
//   }
//   else
//   {
//     Serial.println("Erro ao iniciar o Bluetooth");
//   }
//   if (BT.connect(endSlave))
//   {
//     Serial.println("Conectado com sucesso");
//   }
//   else
//   {
//     Serial.println("Erro ao conectar");
//   }
// }

// void loop()
// {



//   if (BT.available())
//   {
//     String msgRecebida = BT.readStringUntil('\n');
//     DeserializationError erro = deserializeJson(pasta, msgRecebida); 

//     if (erro)
//     {
//       Serial.println("ERRO AO INTERPRETAR JSON");
//     }

//     float tempC = pasta["temp"];
//     float umidade = pasta["umi"];
    

//     frase = "Temperatura = " + String(tempC) + " e Umidade = " + String(umidade);

//     Serial.println(frase);

//     unsigned long marcoAtual = millis();
//     float ultimaTempC = -999;
//     float ultimaUmid = -999;

//     if (marcoAtual - marcoZero >= intervalo)
//     {
//       if (tempC != ultimaTempC)
//       {
//         lcd.setCursor(0, 0);
//         lcd.print("Temp em C = ");
//         lcd.print(tempC);

//         ultimaTempC = tempC;
//       }
//       else
//       {
//         lcd.setCursor(0, 0);
//         lcd.print("Temp em C = ");
//         lcd.print(ultimaTempC);

//         ultimaTempC = tempC;
//       }

//       if (umidade != ultimaUmid)
//       {
//         lcd.setCursor(0, 1);
//         lcd.print("Umidade = ");
//         lcd.print(umidade);

//         ultimaUmid = umidade;
//       }
//       else
//       {
//         lcd.setCursor(0, 1);
//         lcd.print("Umidade = ");
//         lcd.print(ultimaUmid);


//         ultimaUmid = umidade;
//       }

//       Serial.print("Temp C = ");
//       Serial.println(ultimaTempC);
//       Serial.print("Umidade = ");
//       Serial.println(ultimaUmid);
//       Serial.println("---------------");

//       marcoZero = marcoAtual;
//     }
//   }
// }

//---------------------------------Tarefa 2------------------------------------------------------------------------------

#include <Arduino.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

BluetoothSerial BT;
JsonDocument pasta;

String nome = "";
String idadeStr = "";
String habStr = "";
String msgJson = "";

int passo = 1; 

// uint8_t endSlave[] = {0x1C, 0x69, 0x20, 0x92, 0x2D, 0x52};

void setup() {
  Serial.begin(115200);
  
  BT.begin("BTMaster"); 
  // BT.connect(endSlave);      

  Serial.println("Digite o seu Nome:");
}

void loop() {
 
  if (passo == 1 && Serial.available()) {
    nome = Serial.readStringUntil('\n');
    nome.trim();

    Serial.println("Digite a sua Idade:");
    passo = 2;
  }

 
  if (passo == 2 && Serial.available()) {
    idadeStr = Serial.readStringUntil('\n');
    idadeStr.trim();

    Serial.println("Eh habilitado? (sim/nao):");
    passo = 3;
  }

  if (passo == 3 && Serial.available()) {
    habStr = Serial.readStringUntil('\n');
    habStr.trim();

    
    pasta["nome"] = nome;
    pasta["idade"] = idadeStr.toInt();

    if (habStr == "sim") {
      pasta["habilitado"] = true;
    } else {
      pasta["habilitado"] = false;
    }

   
    serializeJson(pasta, msgJson);
    BT.println(msgJson);

    Serial.println("Dados enviados!");

   
    msgJson = "";
    passo = 1;
    Serial.println("\nDigite o seu Nome:");
  }
}
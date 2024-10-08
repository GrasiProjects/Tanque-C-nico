/*
  Código geral para microcontrolador em operação com MatLab
  GRASI - UFPI
  Discente: João Marcos Vilar
  Versão: 0.0
  Data: 04/10/2024
  Descrição:
   - Base para todo funcionamento
*/

// Funções Externas
#include <Arduino.h>
#include <HX710B.h>

HX710B MPS20N0040D;

// #define READ 21
#define READ 4
#define CLK 22
#define PWM 16

const int freq = 500;
const int ledChannel = 0;
const int resolution = 11; //(contagem de bits de 0 a [2^(resolução) - 1])
int dutyCycle;
int timer = 1000;

// Config PWM
const int maxPWM = 4096; // Valor máximo de PWM

void set_PWM(float dutyCyclePor)
{
  // Converte o PWM de % para 12 bits
  dutyCycle = ((dutyCyclePor * (pow(2, resolution) - 1)) / 100);

  // Caso o dispositivo seja ativo em nível baixo, descomente:
  dutyCycle = maxPWM - dutyCycle;

  // Serial.print("PWM em bits: ");
  // Serial.println(dutyCycle);

  // Aplica o PWM no pino escolhido
  ledcWrite(ledChannel, dutyCycle);
}

// Config READ

String leitura()
{
  // return String(MPS20N0040D.pascal());
  float pressao = analogReadMilliVolts(READ);
  float altura = (pressao*280) / 860;
  char alt[10];
  sprintf(alt,"%.0f",altura);
  return alt;
}

void setup()
{
  Serial.begin(115200);

  MPS20N0040D.begin(READ, CLK, 128);

  // Setagem dos pinos
  pinMode(READ, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  ledcSetup(ledChannel, freq, resolution);
  // Define o pino de saída do PWM e o canal que gera
  ledcAttachPin(PWM, ledChannel);

  set_PWM(0);
}

unsigned long startTimer = millis();

void loop()
{
  if (Serial.available() > 0)
  {
    char input = Serial.read();

    if (input == 'w')
    {
      timer = 200;
      int i = 0;
      String value = leitura() + "\n";
      Serial.print(value);
    }

    if (input == 'p')
    {
      while (true)
      {
        if (Serial.available() > 0)
        {
          String inputString = Serial.readString();
          set_PWM(inputString.toFloat());
          Serial.flush();
          break;
        }
      }
    }
  }
  if ((millis() - startTimer) > timer)
  {
    Serial.println(">pressao: " + leitura());
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    startTimer = millis();
  }
}

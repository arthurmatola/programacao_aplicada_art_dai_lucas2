#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int botao1 = 11;
const int botao2 = 12;

int estado_botao1 = 0;
int estado_botao2 = 0;

char vogais[] = {'a', 'e', 'i', 'o', 'u'};
int contagem_vogal = 0;
char mensagem[6];
char mensagem2[17]; // Ajustar tamanho do buffer para 17 (16 + 1 para o terminador nulo)
int contagem_de_letras = 0;
bool escolha = true;
bool escolha_Ino = false;
bool mensagemRecebida = false;

void exibirMenu() {
    lcd.clear();
    lcd.print("Escolha:");
    lcd.setCursor(0, 1);
    lcd.print("(X) PC - ( ) Ino");
}

void setup() {
    pinMode(botao1, INPUT);
    pinMode(botao2, INPUT);

    lcd.begin(16, 2);

    Serial.begin(9600);

    exibirMenu();
}

void loop() {
    if (escolha) {
        estado_botao1 = digitalRead(botao1);
        estado_botao2 = digitalRead(botao2);
        
        if (estado_botao1 == HIGH) {
            escolha_Ino = !escolha_Ino;
            lcd.setCursor(1, 1);
            lcd.print(escolha_Ino ? " " : "X");
            lcd.setCursor(10, 1);
            lcd.print(escolha_Ino ? "X" : " ");
            delay(300);
        }
        
        if (estado_botao2 == HIGH) {
            escolha = false;
            if (escolha_Ino) {
                lcd.clear();
                lcd.print("Escreva:");
                lcd.setCursor(0, 1);
                lcd.print("_");
                delay(300);
            } else {
                lcd.clear();
                lcd.print("Aguardando Msg");
                lcd.setCursor(0, 1);
                lcd.print("do PC...");
                
                while (!mensagemRecebida) {
                    if (Serial.available() > 0) {
                        int bytesRead = Serial.readBytesUntil('\n', mensagem2, 16);
                        mensagem2[bytesRead] = '\0'; // Adicionar o caractere nulo no final
                        mensagemRecebida = true;
                        delay(1000);
                    }
                }
                
                lcd.clear();
                lcd.print("Mensagem do PC:");
                lcd.setCursor(0, 1);
                lcd.print(mensagem2);
                
                delay(7000);  // Exibe a mensagem por 5 segundos
                mensagemRecebida = false;
                exibirMenu();
                escolha = true;
            }
            delay(300);
        }
    } else if (escolha_Ino) {
        estado_botao1 = digitalRead(botao1);
        estado_botao2 = digitalRead(botao2);
        
        if (estado_botao1 == HIGH) {
            contagem_vogal = (contagem_vogal + 1) % 5;
            lcd.setCursor(contagem_de_letras, 1);
            lcd.print(vogais[contagem_vogal]);
            delay(300);
        }
        
        if (estado_botao2 == HIGH) {
            mensagem[contagem_de_letras] = vogais[contagem_vogal];
            contagem_de_letras++;
            if (contagem_de_letras < 5) {
                lcd.setCursor(contagem_de_letras, 1);
                lcd.print("_");
            } else {
                mensagem[5] = '\0';
                Serial.println(mensagem);
                lcd.print("Mensagem enviada");
                contagem_de_letras = 0;
                escolha = true;
                escolha_Ino = false;
                exibirMenu();
            }
            delay(300);
        }
    }
}
// Trabalho para a disciplina de Programação Aplicada do grupo composto por: Arthur Matola Moreira, Daiane Oliveira, Lucas Endringer e Lucas Vechiatti.
// Direitos reservados aos autores, com fins educacionais.

// Essa biblioteca tem como objetivo criar elementos importantes e que serão utilizados de maneira geral no projeto.

#ifndef BIBLIOTECA_H // Verifica se já existe uma biblioteca com esse nome no código.
#define BIBLIOTECA_H // Criação da biblioteca BIBLIOTECA.H

#include <stdio.h> // Bibliotecas padrão de utilização em C.
#include <stdlib.h> // Bibliotecas padrão de utilização em C.
#include <string.h> // Bibliotecas padrão de utilização em C.
#include <windows.h> // Biblioteca utilizada para a comunicação Windows/Arduino.
#include <conio.h> // Biblioteca utilizada para interagir com ações do usuário na tela.

#define SERIAL_PORT "COM4" // Define a porta serial do PC a ser usada pelo usuário, caso seja de interesse, pode ser alterada.
#define BAUD_RATE CBR_9600 // Define o Baud Rate da porta serial do arduíno.

typedef enum { // Struct usada para as interações do switch case na main.
    OPCAO_PC = 1,
    OPCAO_ARDUINO,
    OPCAO_SAIR
} OpcaoMenu;

struct Participante { // Struct utilizada para definir os participantes do grupo.
    char nome[50];
    char sobrenome[100];
};

// As declarações abaixo definem as funções localizadas na biblioteca.c de maneira global, podendo ser utilizadas em todas as páginas de código
// em que se desejar pelo programador.

void printIntegrantes(const struct Participante participantes[], int numParticipantes); // Printa os integrantes do grupo na tela.
void leitura(char *mensagem, size_t comprimento); // Lê a mensagem enviada pelo arduíno e exibe no pc.
void enviarMensagem(const char *mensagem); // Envia a mensagem escrita pelo PC para o arduíno.
void exibirMenuEscolha(); // Exibe para o usuário a legenda referente as opções do Menu.
void aguardarTecla(); // Função utilizada para troca a tela atual no menu.

#endif 
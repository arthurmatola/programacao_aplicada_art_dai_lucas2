// Trabalho para a disciplina de Programação Aplicada do grupo composto por: Arthur Matola Moreira, Daiane Oliveira, Lucas Endringer e Lucas Vechiatti.
// Direitos reservados aos autores, com fins educacionais.

// Essa página tem como objetivo criar as funções necessárias para o projeto sem poluir a main, tornando o código mais organizado.

#include "biblioteca.h" // Inclui a biblioteca criada previamente.

// Execução da função usada para adicionar os nomes dos usuários criadores do projeto.
void printIntegrantes(const struct Participante participantes[], int numParticipantes) { // Define para a execução da função a entrada da struct com o nome dos participantes e do número de participantes.
    printf("\n===============================\n"); 
    printf("  Trabalho de Programacao Aplicada\n\n");
    printf("  Nome dos participantes:\n");
    for (int i = 0; i < numParticipantes; ++i) { // Loop para printar os participantes definidos na struct e declarados na main.
        printf("  %d. %s %s\n", i + 1, participantes[i].nome, participantes[i].sobrenome);
    }
    printf("===============================\n\n");
}

void leitura(char *mensagem, size_t comprimento) { // Função utilizada para o envio da mensagem do Arduíno para o PC.
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    DWORD bytesRead;

    hSerial = CreateFile(SERIAL_PORT, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); // Trecho usado para abertura da porta serial.
    if (hSerial == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Erro ao abrir a porta serial %s\n", SERIAL_PORT);
        exit(1);
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams); // Trecho utilizado para definir se já existe alguém ocupando a porta serial.
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Erro ao obter o estado da porta serial %s\n", SERIAL_PORT);
        CloseHandle(hSerial);
        exit(1);
    }

    dcbSerialParams.BaudRate = BAUD_RATE; // Trecho usado para bloquear o acesso a porta serial enquanto o programa está rodando.
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Erro ao configurar o estado da porta serial %s\n", SERIAL_PORT);
        CloseHandle(hSerial);
        exit(1);
    }

    // Trecho utilizado para definir os prazos de tempo para que os comandos sejam executados na porta serial.
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "Erro ao configurar os timeouts para a porta serial %s\n", SERIAL_PORT);
        CloseHandle(hSerial);
        exit(1);
    }

    int index = 0;
    while (index < comprimento - 1) { // Pequeno comando que permite ao usuário retornar ao menu caso uma mensagem não chegue e evite que ele fique travado.
        if (_kbhit() && _getch() == 'r') { // Detecta que caso o usuário tecle "r" ele volta pro Menu.
            mensagem[0] = '\0';
            printf("\nRetornando ao menu...\n");
            return;
        }
        if (ReadFile(hSerial, &mensagem[index], 1, &bytesRead, NULL) && bytesRead > 0) { // Função que agrega todos os fatores criados anteriormente + o vetor recebido do arduíno.
            if (mensagem[index] == '\n') {
                break; // Terminador '\n' encontrado, fim da mensagem.
            }
            index++;
        }
    }
    mensagem[index] = '\0'; // Importante assegurar o terminador nulo para evitar bugs.

    CloseHandle(hSerial);
}

void enviarMensagem(const char *mensagem) { // Função utilizada para o envio da mensagem do PC para o Arduíno.
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    DWORD bytesWritten;

    hSerial = CreateFile(SERIAL_PORT, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); // Trecho usado para abertura da porta serial.
    if (hSerial == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Erro ao abrir a porta serial %s\n", SERIAL_PORT);
        exit(1);
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams); // Trecho utilizado para definir se já existe alguém ocupando a porta serial.
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Erro ao obter o estado da porta serial %s\n", SERIAL_PORT);
        CloseHandle(hSerial);
        exit(1);
    }

    dcbSerialParams.BaudRate = BAUD_RATE; // Trecho usado para bloquear o acesso a porta serial enquanto o programa está rodando.
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Erro ao configurar o estado da porta serial %s\n", SERIAL_PORT);
        CloseHandle(hSerial);
        exit(1);
    }

    // Trecho utilizado para definir os prazos de tempo para que os comandos sejam executados na porta serial.
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "Erro ao configurar os timeouts para a porta serial %s\n", SERIAL_PORT);
        CloseHandle(hSerial);
        exit(1);
    }

    // Trecho usado para adicionar o \n a mensagem.
    char buffer[18];
    snprintf(buffer, sizeof(buffer), "%s\n", mensagem);

    // Trecho utilizado para iniciar a escrita na Porta Serial.
    if (!WriteFile(hSerial, buffer, strlen(buffer), &bytesWritten, NULL)) {
        fprintf(stderr, "Erro ao escrever na porta serial %s\n", SERIAL_PORT);
        CloseHandle(hSerial);
        exit(1);
    }

    // Adicionamos um pequeno delay para confirmar que o Arduíno vai receber a mensagem completamente.
    Sleep(100);

    CloseHandle(hSerial);
}

// Função usada para printar o Menu.
void exibirMenuEscolha() {
    printf("Escolha a opcao:\n");
    printf("1. PC\n");
    printf("2. Arduino\n");
    printf("3. Sair\n");
}

// Função usada para passar de tela.
void aguardarTecla() {
    printf("\nPressione qualquer tecla para continuar...");
    getchar();
    system("cls");
}
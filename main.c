#include "biblioteca.h" // Inclui a biblioteca criada previamente.

int main() {
    struct Participante participantes[] = { // Define os elementos da struct Participante.
        {"Arthur", "Matola Moreira"},
        {"Daiane", "Oliveira"},
        {"Lucas", "Endringer"},
        {"Lucas", "Vechiatti Gomes"}
    };

    int numParticipantes = sizeof(participantes) / sizeof(participantes[0]); // Define o número de elementos da Struct e permite o contador de posições que é exibido em tela.

    char mensagem[6]; // Vetor da mensagem do arduino.
    char mensagemEnviar[17]; // Vetor da mensagem do PC.
    int escolha; // Escolha do usuário no switch case.

    printIntegrantes(participantes, numParticipantes); // Chama a função para printar o integrantes e o design do menu inicial.

    printf("Pressione qualquer tecla para avancar para a proxima tela...\n"); // Permite que o usuário só saia do menu inicial quando apertar uma tecla.
    getchar();

    do {
        system("cls"); // Limpa a tela anterior.

        exibirMenuEscolha(); // Exibe as opções possíveis para o usuário.
        printf("Opcao: ");
        scanf("%d", &escolha); // Detecta a opção escolhida (1, 2, 3).
        while (getchar() != '\n');

        switch (escolha) {
            case OPCAO_PC: // Caso o usuário escolha a opção PC, número 1.
                system("cls"); // Limpa a tela.
                printf("Digite a mensagem (ate 16 digitos) ou pressione '-' para retornar: "); // Explica ao usuário como utilizar a aplicação.
                fgets(mensagemEnviar, sizeof(mensagemEnviar), stdin); // Recebe a mensagem escrita pelo usuário e armazena no vetor mensagemEnviar.
                if (strchr(mensagemEnviar, '-') != NULL) { // Caso o usuário digita '-', retorna ao menu inicial.
                    printf("Retornando ao menu...\n");
                    break;
                }
                mensagemEnviar[strcspn(mensagemEnviar, "\n")] = '\0'; // Define que caso o usuário aperte ENTER, encerra a mensagem.
                enviarMensagem(mensagemEnviar); // Envia para a função criada anteriormente o vetor com a mensagem digitada.
                printf("Mensagem enviada para o Arduino: %s\n", mensagemEnviar); // Confirma ao usuário a mensagem que ele digitou.
                break;
            case OPCAO_ARDUINO: // Caso o usuário escolha a opção Arduino, número 2.
                system("cls"); // Limpa a tela.
                printf("Aguarde a mensagem ser enviada...\n");
                leitura(mensagem, sizeof(mensagem)); // Chama a função leitura e insere como variáveis o vetor mensagem e o tamanho da mensagem.
                if (mensagem[0] != '\0') { // Encerra no caracter nulo.
                    printf("\nMensagem recebida do Arduino: %s\n", mensagem);
                }
                break;
            case OPCAO_SAIR: // Caso o usuário escolha a opção SAIR, número 3.
                system("cls");
                printf("\nEncerrando o programa...\n"); 
                break; // Fecha o programa.
            default: // Opção de erro na escolha.
                system("cls");
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

        if (escolha != 3) {
            aguardarTecla(); // Utiliza a função aguardarTecla para mudar de tela.
        }

    } while (escolha != 3); // Caso a opção escolhida for a SAIR (3), encerra o programa.

    return 0;
}
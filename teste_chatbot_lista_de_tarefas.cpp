	#include <stdlib.h>
	#include <string.h>
	#include <time.h>
	
	#define MAX_TAREFAS 10
	#define TAM_DESCRICAO 50
	
	// Struct que define uma tarefa
	typedef struct {
	    char descricao[TAM_DESCRICAO];
	    time_t prazo;
	} Tarefa;
	
	// Função que verifica o prazo de uma tarefa e retorna uma cor correspondente
	char* cor_tarefa(Tarefa* tarefa) {
	    time_t agora;
	    time(&agora);
	    double dias_restantes = difftime(tarefa->prazo, agora) / (60 * 60 * 24); // calcula dias restantes até o prazo
	
	    if (dias_restantes < 1) {
	        return "\033[1;31m"; // vermelho
	    } else if (dias_restantes < 7) {
	        return "\033[1;33m"; // amarelo
	    } else {
	        return "\033[1;32m"; // verde
	    }
	}
	
	// Função que imprime uma tarefa com a cor correspondente
	void imprimir_tarefa(Tarefa* tarefa) {
	    char* cor = cor_tarefa(tarefa);
	    printf("%s%s\033[0m - Prazo: %s", cor, tarefa->descricao, ctime(&tarefa->prazo));
	}
	
	// Função que limpa o buffer do teclado
	void limpa_buffer() {
	    int c;
	    while ((c = getchar()) != '\n' && c != EOF);
	}
	
	int main() {
	    Tarefa tarefas[MAX_TAREFAS]; // define um array de tarefas com tamanho máximo de 10
	    int num_tarefas = 0; // contador de tarefas definidas pelo usuário
	
	    int opcao = 0; // variável para armazenar a opção escolhida pelo usuário
	
	    while (opcao != 6) {
	        printf("\n--- Gerenciador de Tarefas ---\n");
	        printf("1. Definir Tarefa\n");
	        printf("2. Agendar Tarefa\n");
	        printf("3. Excluir Tarefa\n");
	        printf("4. Visualizar Tarefas Agendadas\n");
	        printf("5. Redefinir Tarefas\n");
	        printf("6. Sair do Programa\n");
	
	        printf("\nEscolha uma opção (1-6): ");
	        scanf("%d", &opcao);
	        limpa_buffer();
	
	        switch (opcao) {
	            case 1: // Definir Tarefa
	                if (num_tarefas < MAX_TAREFAS) {
	                    printf("Digite a descrição da tarefa: ");
	                    char descricao[TAM_DESCRICAO];
	                    fgets(descricao, sizeof(descricao), stdin);
	                    descricao[strcspn(descricao, "\n")] = 0; // remove o caractere '\n' do final da string
	
	                    // Define a tarefa no array
	                    strcpy(tarefas[num_tarefas].descricao, descricao);
	                    num_tarefas++;
	
	                    printf("Tarefa definida com sucesso!\n");
	                } else {
	                    printf("Não é possível adicionar mais tarefas, o limite foi atingido.\n");
	                }
	                break;
	            case 2: // Agendar Tarefa
	                if (num_tarefas > 0) {
	                    printf("Escolha a tarefa que deseja agendar:\n")  // Imprime a lista de tarefas disponíveis para agendamento
	                for (int i = 0; i < num_tarefas; i++) {
	                    printf("%d. ", i+1);
	                    imprimir_tarefa(&tarefas[i]);
	                }
	
	                // Solicita ao usuário que escolha a tarefa a ser agendada
	                int escolha = 0;
	                printf("\nDigite o número da tarefa que deseja agendar: ");
	                scanf("%d", &escolha);
	                limpa_buffer();
	
	                // Verifica se a escolha é válida
	                if (escolha > 0 && escolha <= num_tarefas) {
	                    Tarefa* tarefa = &tarefas[escolha-1];
	
	                    printf("Digite a data de vencimento (dd/mm/aaaa): ");
	                    char data_str[11];
	                    fgets(data_str, sizeof(data_str), stdin);
	                    data_str[strcspn(data_str, "\n")] = 0; // remove o caractere '\n' do final da string
	
	                    // Converte a data de string para a struct tm
	                    struct tm data = {0};
	                    strptime(data_str, "%d/%m/%Y", &data);
	                    tarefa->prazo = mktime(&data);
	
	                    printf("Tarefa agendada com sucesso!\n");
	                } else {
	                    printf("Escolha inválida.\n");
	                }
	            } else {
	                printf("Não há tarefas definidas para agendar.\n");
	            }
	            break;
	        case 3: // Excluir Tarefa
	            if (num_tarefas > 0) {
	                printf("Escolha a tarefa que deseja excluir:\n");
	
	                // Imprime a lista de tarefas disponíveis para exclusão
	                for (int i = 0; i < num_tarefas; i++) {
	                    printf("%d. ", i+1);
	                    imprimir_tarefa(&tarefas[i]);
	                }
	
	                // Solicita ao usuário que escolha a tarefa a ser excluída
	                int escolha = 0;
	                printf("\nDigite o número da tarefa que deseja excluir: ");
	                scanf("%d", &escolha);
	                limpa_buffer();
	
	                // Verifica se a escolha é válida
	                if (escolha > 0 && escolha <= num_tarefas) {
	                    // Move todas as tarefas a partir da escolhida uma posição para trás
	                    for (int i = escolha-1; i < num_tarefas-1; i++) {
	                        tarefas[i] = tarefas[i+1];
	                    }
	                    num_tarefas--;
	
	                    printf("Tarefa excluída com sucesso!\n");
	                } else {
	                    printf("Escolha inválida.\n");
	                }
	            } else {
	                printf("Não há tarefas definidas para excluir.\n");
	            }
	            break;
	        case 4: // Visualizar Tarefas Agendadas
	            if (num_tarefas > 0) {
	                printf("Tarefas agendadas:\n");
	
	                // Imprime a lista de tarefas agendadas
	                for (int i = 0; i < num_tarefas; i++) {
	                    imprimir_tarefa(&tarefas[i]);
	                }
	            } else {
	                printf("Não há tarefas agendadas.\n");
	            }
	            break;
	        case 5: // Redefinir Tarefas
	        printf("Tem certeza que deseja excluir todas as tarefas? (s/n) ");
	            
	char
	 confirmacao;	
	            
	scanf("%c", &confirmacao);
limpa_buffer();

if (confirmacao == 's' || confirmacao == 'S') {
    num_tarefas = 0;
    printf("Todas as tarefas foram excluídas.\n");
} else {
    break;
    
    case 6: // Sair do Programa
        printf("Encerrando o programa...\n");
        break;
        
    default:
        printf("Opção inválida. Por favor, escolha uma opção entre 1 e 6.\n");
        break;
    }
}

return 0;


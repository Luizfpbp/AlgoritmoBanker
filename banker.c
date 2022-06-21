#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NUMBER_OF_RESOURCES;
int NUMBER_OF_CUSTOMERS;

int menorIgual(int *arr1, int *arr2);

int main (int argc, char ** argv) {

    // Quantidade de recursos
    NUMBER_OF_RESOURCES = argc - 1;
    NUMBER_OF_CUSTOMERS = 0;

    FILE *customers;
    FILE *resultado;
    FILE *commands;

    // Validação dos dados recebidos 
    // do usuario
    if (NUMBER_OF_RESOURCES == 0) {
        printf("Nenhum recurso foi digitado como argumento!\n");
        return 0;
    }

    // Se não tiver customer.txt
    if (!(customers = fopen("customer.txt", "r"))) {
        printf("O arquivo 'customer.txt' não está presente no diretorio!\n");
        return 0;
    }
    
    // Se customer.txt estiver vazio
    fseek(customers, 0, SEEK_END);
    if (ftell(customers) == 0) {
        printf("O arquivo 'customer.txt' está vazio!\n");
        return 0;
    }
    fclose(customers);

    // Se não tiver commands.txt
    if (!(commands = fopen("commands.txt", "r"))) {
        printf("O arquivo 'commands.txt' não está presente no diretorio!\n");
        return 0;
    }

    // Se customer.txt estiver vazio
    fseek(commands, 0, SEEK_END);
    if (ftell(commands) == 0) {
        printf("O arquivo 'commands.txt' está vazio!\n");
        return 0;
    }
    fclose(commands);

    // Para coletar cada linha dos arquivos
    char line[255];

    // Valida se a quantidade de recursos está correta em customers.txt
    customers = fopen("customer.txt", "r");
    while (fgets(line, 255, customers)) {
        char *str = strtok(line, ",");
        int n = 0;
        while (str != NULL) {
            str = strtok(NULL, ",");
            n++;
        }
        if (n != NUMBER_OF_RESOURCES) {
            printf("Número de recursos digitado em 'customer.txt' invalido!\n");
            return 0;
        }   
    }
    fclose(customers);

    // Valida se a quantidade de recursos está correta em commands.txt
    commands = fopen("commands.txt", "r");
    while (fgets(line, 255, commands)) {
        char *str = strtok(line, " ");
        int n = 0;
        while (str != NULL) {
            str = strtok(NULL, " ");
            n++;
        }
        if (n != NUMBER_OF_RESOURCES+2) {
            if (n != 1) {
                printf("Número de recursos digitados em 'commands.txt' invalido!\n");
                return 0;
            }
        }
    }
    fclose(commands);

    // Inicia o array dos recursos disponiveis
    int Disponivel[NUMBER_OF_RESOURCES];
    for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
        Disponivel[c] = atoi(argv[c+1]); 
    }

    // Determina quantos consumidores existem
    customers = fopen("customer.txt", "r");
    while(fgets(line, 255, customers)) {
        NUMBER_OF_CUSTOMERS++;
    }
    fclose(customers);

    // Inicia as matrizes necessarias
    int max[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int allocados[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int cCOSTU = 0;
    customers = fopen("customer.txt", "r");
    while (fgets(line, 255, customers)) {
        int nAux[NUMBER_OF_RESOURCES];
        char *str = strtok(line, ",");
        int n = 0;
        while (str != NULL) {
            nAux[n] = atoi(str);
            str = strtok(NULL, ",");
            n++;
        }

        for(int c=0; c<NUMBER_OF_RESOURCES; c++) {
            max[cCOSTU][c] = nAux[c];
            allocados[cCOSTU][c] = 0;
            need[cCOSTU][c] = max[cCOSTU][c];
        }
        cCOSTU++;
    }
    fclose(customers);

    // Leitura dos comandos
    commands = fopen("commands.txt", "r");
    while(fgets(line, 255, commands)) {
        char *lAux[NUMBER_OF_RESOURCES+2];
        char *str = strtok(line, " ");
        int n = 0;
        while (str != NULL) {
            lAux[n] = str;
            str = strtok(NULL, " ");
            n++;
        }

        // Output
        if (lAux[0][0] == '*') {
            char *h1 = "MAXIMUM ";
            char *h2 = " ALLOCATION ";
            char *h3 = " NEED";

            resultado = fopen("result.txt", "a");

            fprintf(resultado, "%s|%s|%s\n", h1, h2, h3);

            for (int c=0; c<NUMBER_OF_CUSTOMERS; c++) {
                for (int i=0; i<NUMBER_OF_RESOURCES; i++) {
                    fprintf(resultado, "%d ", max[c][i]);
                }

                fprintf(resultado, "%*c", (9-(NUMBER_OF_RESOURCES*2)), '|');
                fprintf(resultado, "%*s", 1, "");

                for (int i=0; i<NUMBER_OF_RESOURCES; i++) {
                    fprintf(resultado, "%d ", allocados[c][i]);
                }

                fprintf(resultado, "%*c", (12-(NUMBER_OF_RESOURCES*2)), '|');
                fprintf(resultado, "%*s", 1, "");

                for (int i=0; i<NUMBER_OF_RESOURCES; i++) {
                    fprintf(resultado, "%d ", need[c][i]);
                }
                
                fprintf(resultado, "\n");

            }
            fprintf(resultado, "AVAILABLE");
            for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                fprintf(resultado, " %d", Disponivel[c]);
            }
            fprintf(resultado, "\n");
            fclose(resultado);
        }

        else {
            // Coleta os recursos e armazena em um array
            int cost = atoi(lAux[1]);
            int cRes[NUMBER_OF_RESOURCES];
            int RC = 2;
            for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                cRes[c] = atoi(lAux[RC]);
                RC++;
            }

            // Request Resources
            if (lAux[0][1] == 'Q') {
                
                // Valida de os recursos requisitados
                // são realmente necessarios para o consumidor
                int valida = 0;
                int mens;
                for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                    if (cRes[c] > need[cost][c]) {
                        valida = -1;
                        mens = 1;
                        break;
                    }
                    if (cRes[c] > Disponivel[c]) {
                        valida = -1;
                        mens = 0;
                        break;
                    }
                }

                if (valida == -1) {
                    resultado = fopen("result.txt", "a");
                    if (mens == 1) {
                        fprintf(resultado, "The customer %d request", cost);
                        for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                            fprintf(resultado, " %d", cRes[c]);
                        }
                        fprintf(resultado, " was denied because exceed its maximum allocation\n");
                    }
                    else{
                        fprintf(resultado, "The resources");
                        for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                            fprintf(resultado, " %d", Disponivel[c]);
                        }
                        fprintf(resultado, " are not enough to customer %d request", cost);
                        for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                            fprintf(resultado, " %d", cRes[c]);
                        }
                        fprintf(resultado, "\n");
                    }
                    fclose(resultado);

                }

                else {
                    // Prepara o sistema para a validação
                    for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                        Disponivel[c] = Disponivel[c] - cRes[c];
                        allocados[cost][c] = allocados[cost][c] + cRes[c];
                        need[cost][c] = need[cost][c] - cRes[c];
                    }


                    // Segurança
                    int dAux[NUMBER_OF_RESOURCES];
                    int finish[NUMBER_OF_CUSTOMERS];
                    // Inicia os arrays para validar a segurança
                    for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                        dAux[c] = Disponivel[c];
                    }
                    for (int c=0; c<NUMBER_OF_CUSTOMERS; c++) {
                        finish[c] = 0;
                    }

                    while (1) {
                        int valida = 0;

                        for (int c=0; c<NUMBER_OF_CUSTOMERS; c++) {
                            if (finish[c] == 0 && menorIgual(need[c], dAux) == 0) {
                                valida = 1;
                                for (int i=0; i<NUMBER_OF_RESOURCES; i++) {
                                    dAux[i] = dAux[i] + allocados[c][i];
                                }
                                finish[c] = 1;
                                break;
                            }

                        }

                        if (valida == 0) {
                            break;
                        }

                    }

                    int safe = 1;
                    for (int c=0; c<NUMBER_OF_CUSTOMERS; c++) {
                        if (finish[c] == 0) {
                            safe = -1;
                            break;
                        }
                    }

                    resultado = fopen("result.txt", "a");
                    if (safe == 1) {
                        fprintf(resultado, "Allocate to customer %d the resources", cost);
                        for(int c=0; c<NUMBER_OF_RESOURCES; c++) {
                            fprintf(resultado, " %d", cRes[c]);
                        }
                        fprintf(resultado, "\n");
                    }
                    else {
                        // Retorna ao estado anterior
                        for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                            Disponivel[c] = Disponivel[c] + cRes[c];
                            allocados[cost][c] = allocados[cost][c] - cRes[c];
                            need[cost][c] = need[cost][c] + cRes[c];
                        }

                        fprintf(resultado, "The customer %d request", cost);
                        for(int c=0; c<NUMBER_OF_RESOURCES; c++) {
                            fprintf(resultado, " %d", cRes[c]);
                        }
                        fprintf(resultado, " was denied because result in an unsafe state\n");
                    }
                    fclose(resultado);

                }
                

            }

            // Release Resources
            if (lAux[0][1] == 'L') {

                // Verifica se existe a possibilidade
                // de liberar os recursos alocados
                int valida = 0;
                for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                    if (allocados[cost][c] < cRes[c]) {
                        valida = -1;
                        break;
                    }
                }

                resultado = fopen("result.txt", "a");
                if (valida == 0) {
                    // Libera os valores alocados ao consumidor
                    // Adiciona os valores liberados no need
                    // Adiciona os valores liberados no disponivel 
                    for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                        allocados[cost][c] = allocados[cost][c] - cRes[c];
                        need[cost][c] = need[cost][c] + cRes[c];
                        Disponivel[c] = Disponivel[c] + cRes[c];
                    }

                    fprintf(resultado, "Release from customer %d the resources", cost);
                    for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                        fprintf(resultado, " %d", cRes[c]);
                    }
                    fprintf(resultado, "\n");

                }

                else {
                    fprintf(resultado, "The resources");
                    for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
                        fprintf(resultado, " %d", cRes[c]);
                    }
                    fprintf(resultado, " are not release from customer %d\n", cost);
                }

                fclose(resultado);

            }

        }

    }
    resultado = fopen("result.txt", "a");
    fprintf(resultado, "\n");
    fclose(resultado);

    fclose(commands);

    return 0;
}

// Retorna 0 se todos os valores de arr1
// forem menores ou iguais a arr2.
// Retorna -1 se não for o caso
int menorIgual(int *arr1, int *arr2) {
    int valida = 0;
    for (int c=0; c<NUMBER_OF_RESOURCES; c++) {
        if (arr1[c] > arr2[c]) {
            valida = -1;
            break;
        }
    }
    return valida;
}

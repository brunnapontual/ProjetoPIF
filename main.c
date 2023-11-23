#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "screen.h"

#define MAX_INIMIGOS 10

int main() {
  srand(time(NULL));
  personagem *head = NULL;
  inimigo *headI = NULL;

//melhorar a saida visual no terminal
  // declaração dos personagens
  inserirH(&head, 500, 55, 100, "Guerreiro Infernal");
  inserirH(&head, 340, 32, 200, "Mago de Gelo");
  inserirH(&head, 450, 40, 114, "Arqueira florestal");

//diminuir o numero deinimigos talvez
  // declaração dos inimigos
  inserirI(&headI, 100, 8, 12, 2, "Cavaleiro Espectral");
  inserirI(&headI, 140, 4, 15, 1, "Lamina das Sombras");
  inserirI(&headI, 170, 6, 20, 3, "Guardião das Trevas");
  inserirI(&headI, 200, 24, 40, 4, "Arauto do Crepúsculo");


    printf("                    Salve o príncipe                                       \n");
    printf("                       ▄▀▄     ▄▀▄\n");
    printf("                      ▄█  ▀▀▀▀▀  █▄\n");
    printf("                  ▄▄  █           █  ▄▄\n");
    printf("                 █▄▄█ █  ▀  ┬  ▀  █ █▄▄█\n");
    printf(" --------------------------------------------------------\n");
    printf("|               Bem ao rpg Salve o Príncipe!!       |\n");
    printf("|                                                         |\n");
    printf("| Você terá que derrotar 3 vilões para salvar o príncipe. |\n");
    printf("|                                                         |\n");                       
    printf("| Para começar escolha o seu Herói.                       |\n");
    printf("|                                                         |\n");
    printf("|                       Boa Sorte!                        |\n");
    printf("|                                                         |\n");
    printf(" --------------------------------------------------------\n");
  imprimirH(head);

  
  int aux = 0;
  personagem *personagemAtual = NULL;
  inimigo *inimigoAtual;
  inimigoAtual = escolherInimigoAleatorio(headI);
  int escolha;
  do {
//trocar o personagem123 pelo nome: guerreiro etc
    printf("Escolha o seu Herói:\n");
    printf("1. Guerreiro Infernal\n");
    printf("2. Mago de Gelo\n");
    printf("3. Arqueira florestal\n");
    scanf("%d", &escolha);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    switch (escolha) {
    case 1:
      personagemAtual = escolherPersonagem(1, head);
      break;
    case 2:
      personagemAtual = escolherPersonagem(2, head);
      break;
    case 3:
      personagemAtual = escolherPersonagem(3, head);
      break;
    default:
      printf("Escolha inválida. Tente novamente.\n");
      aux = 1;
      
    }
   
  
} while (aux);

  printf("\nHeroi escolhido: %s\n", personagemAtual->nome);
  int ids[MAX_INIMIGOS];
  char inimigosBatalhados[MAX_INIMIGOS][50];
  int numInimigosBatalhados = 0;
  printf("inimigo atual: %s", inimigoAtual->nome);
  do {
//atualizar a tela Clear the screen(na lib screen.h), ou update
//tirar a opçao atacar com poder magico deixar so o ataque normal(a gnt pode colocar entre parenteses tb quanto é o dano de ataque atual)
    printf("\nOpções de ação:\n");
    printf("1. Atacar\n");
    printf("2. Atacar com poder mágico\n");
    printf("3. Defender\n");
    printf("Opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1: {
      if (personagemAtual->hp > 0) {
//nao acho que precisa de confirmação seria bom tirar pra tentar diminuir o codigo mas nao sei se pode
        int confirmacao;
        printf("\nVocê escolheu atacar. Confirme a ação (1 para confirmar, 0 "
               "para cancelar): ");
        scanf("%d", &confirmacao);
        if (confirmacao == 1) {
          ataque(personagemAtual, inimigoAtual);
          if (inimigoAtual->hp <= 0) {
            ids[numInimigosBatalhados] = inimigoAtual->id;
            strcpy(inimigosBatalhados[ids[numInimigosBatalhados] - 1],
                   inimigoAtual->nome);
            numInimigosBatalhados++;
            removerI(&headI, inimigoAtual->id);
            inimigoAtual = escolherInimigoAleatorio(headI);
            if (headI == NULL) {
              printf("\nTodos os inimigos foram derrotados!\n");
              break;
            }
          }
          printf("\nPersonagem: %s |HP: %d\n", personagemAtual->nome,
                 personagemAtual->hp);
          printf("Inimigo: %s |HP: %d\n", inimigoAtual->nome, inimigoAtual->hp);
        } else {
          printf("Ação cancelada.\n");
        }
      }
      break;
    }

    case 2: {
      if (personagemAtual->hp > 0) {
        int confirmacao;
        printf("Você escolheu atacar com poder mágico. Confirme a ação (1 para "
               "confirmar, 0 para cancelar): ");
        scanf("%d", &confirmacao);
        if (confirmacao == 1) {
          ataqueMagico(personagemAtual, inimigoAtual);
          if (inimigoAtual->hp <= 0) {
            ids[numInimigosBatalhados] = inimigoAtual->id;
            strcpy(inimigosBatalhados[ids[numInimigosBatalhados]],
                   inimigoAtual->nome);
            numInimigosBatalhados++;
            removerI(&headI, inimigoAtual->id);
            if (headI != NULL) {
              inimigoAtual = escolherInimigoAleatorio(headI);
            }
            if (headI == NULL) {
              printf("\nTodos os inimigos foram derrotados!\n");
              break;
            }

          }
          printf("\nPersonagem: %s |HP: %d\n", personagemAtual->nome,
                 personagemAtual->hp);
          printf("Inimigo: %s |HP: %d\n", inimigoAtual->nome, inimigoAtual->hp);
        } else {
          printf("Ação cancelada.\n");
        }
      }
      break;
    }
      
    case 3: {
      if (personagemAtual->hp > 0) {
        int confirmacao;
        printf("Você escolheu defender. Confirme a ação (1 para confirmar, 0 "
               "para cancelar): ");
        scanf("%d", &confirmacao);
        if (confirmacao == 1) {
          defesa(personagemAtual, inimigoAtual);
          printf("\nPersonagem: %s (HP: %d)\n", personagemAtual->nome,
                 personagemAtual->hp);
          printf("Inimigo: %s (HP: %d)\n", inimigoAtual->nome,
                 inimigoAtual->hp);
        } else {
          printf("Ação cancelada.\n");
        }
      }
      break;
    }
     
    default:
      printf("\nOpção inválida. Tente novamente.\n");
      break;
    }
   

  } while (personagemAtual->hp > 0 && headI != NULL);

  if (personagemAtual->hp <= 0) {
    printf("\nVocê foi derrotado. Fim de jogo.\n");
    free(personagemAtual);
  } else {
    printf("                  ▄▀▄     ▄▀▄\n");
    printf("                 ▄█  ▀▀▀▀▀  █▄     VOCE SALVOU O PRINCIPE!\n");
    printf("             ▄▄  █           █  ▄▄\n");
    printf("            █▄▄█ █  ▀  ┬  ▀  █ █▄▄█\n");
    printf("\nParabéns! Você derrotou todos os inimigos. Fim de jogo.\n");
  }

  liberarMemoriaH(head);
  liberarMemoriaI(headI);

  return 0;
}

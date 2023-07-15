#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replaceWord(char* sentence, const char* wordToReplace, const char* replacement) {
    char* foundWord = strstr(sentence, wordToReplace);
    if (foundWord != NULL) {
        size_t wordToReplaceLength = strlen(wordToReplace);
        size_t replacementLength = strlen(replacement);

        int offset = replacementLength - wordToReplaceLength;
        size_t newSentenceLength = strlen(sentence) + offset + 1;

        // Aloca memória para a nova string
        char* newSentence = malloc(newSentenceLength);
        if (newSentence == NULL) {
            printf("Erro ao alocar memória\n");
            return;
        }

        // Copia a parte da string antes da palavra a ser substituída
        strncpy(newSentence, sentence, foundWord - sentence);
        newSentence[foundWord - sentence] = '\0';

        // Concatena a substituição na nova string
        strcat(newSentence, replacement);

        // Concatena a parte da string após a palavra a ser substituída
        strcat(newSentence, foundWord + wordToReplaceLength);

        // Copia a nova string de volta para a string original
        strcpy(sentence, newSentence);

        // Libera a memória alocada
        free(newSentence);
    }
}

int main() {
    char sentence[] = "echo teste1 $? teste2";
    char wordToReplace[] = "$?";
    char replacement[] = "ReplacementWith20Charsor more characters alem do necessario";

    printf("Antes: %s\n", sentence);
    replaceWord(sentence, wordToReplace, replacement);
    printf("Depois: %s\n", sentence);

    return 0;
}

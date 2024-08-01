#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LENGTH 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordFreq;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int isWordChar(char c) {
    return isalpha(c) || c == '\'';
}

void processParagraph(char *paragraph, WordFreq *wordFreqs, int *wordCount) {
    char word[MAX_WORD_LENGTH];
    int index = 0;
    int count = 0;

    for (int i = 0; paragraph[i]; i++) {
        if (isWordChar(paragraph[i])) {
            word[index++] = paragraph[i];
        } else if (index > 0) {
            word[index] = '\0';
            index = 0;
            toLowerCase(word);

            int found = 0;
            for (int j = 0; j < count; j++) {
                if (strcmp(word, wordFreqs[j].word) == 0) {
                    wordFreqs[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(wordFreqs[count].word, word);
                wordFreqs[count].count = 1;
                count++;
            }
        }
    }
    // Handle the last word if the paragraph doesn't end with a non-word character
    if (index > 0) {
        word[index] = '\0';
        toLowerCase(word);

        int found = 0;
        for (int j = 0; j < count; j++) {
            if (strcmp(word, wordFreqs[j].word) == 0) {
                wordFreqs[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(wordFreqs[count].word, word);
            wordFreqs[count].count = 1;
            count++;
        }
    }
    *wordCount = count;
}

int main() {
    char paragraph[10000];
    WordFreq wordFreqs[MAX_WORDS];
    int wordCount = 0;

    printf("Enter a paragraph:\n");
    // Use fgets to read the paragraph including spaces
    if (fgets(paragraph, sizeof(paragraph), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Process the paragraph to count word frequencies
    processParagraph(paragraph, wordFreqs, &wordCount);

    // Print the word frequencies
    printf("\nWord Frequencies:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s: %d\n", wordFreqs[i].word, wordFreqs[i].count);
    }

    return 0;
}

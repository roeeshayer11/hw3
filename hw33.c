#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TXT 1024
#define WORD 30

#define CHAR_COUNT 256

int big1(char *b, int i, int j) {
    int res = 0;

    for (; i <= j; i++) {
        if (b[i] == ' ')
            continue;
        if (b[i] >= 'a' && b[i] <= 'z') {
            res += b[i] - 'a' + 1;
        } else if (b[i] >= 'A' && b[i] <= 'Z') {
            res += b[i] - 'A' + 1;
        }
    }
    return res;
}

void printSubstring(char* str, int i, int j, int first) {
    if (!first)
        printf("~");
    for (; i <= j; i++)
        printf("%c", str[i]);
}

char* toAtbash(char* str) {
    int len = strlen(str);
    char* res = malloc(len + 1);
    for (size_t i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            res[i] = 'z' - (str[i] - 'a');
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            res[i] = 'z' - (str[i] - 'A');
        }
    }
    res[len] = 0;
    return res;
}

void a(char* word, char* text) {
    int wordGimatria = big1(word, 0, strlen(word));
    int first = 1;
    for (size_t i = 0, end = strlen(text); i < end; i++)
    {
        int currGimatria = big1(text, i, i);
        if (currGimatria == 0)
            continue;
        for (size_t j = i; j < end; j++)
        {
            int substringGimatria = big1(text, i, j);
            if (substringGimatria > wordGimatria)
                break;
            else if (substringGimatria == wordGimatria) {
                printSubstring(text, i, j, first);
                first = 0;
                break;
            }
        }
    }
}

void reverse(char* str) {
    int len = strlen(str);
    for (size_t i = 0; i < len / 2; i++)
    {
        char c = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = c;
    }
}

int search(char* word, char* text, int first) {
    int len = strlen(word);
    for (size_t i = 0, end = strlen(text); i < end; i++)
    {
        int k = 0;
        int kRev = len - 1;
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') 
            continue;
        int dismissedNormal = 0, dismissedReverse = 0;
        for (size_t j = i; j < end && (!dismissedNormal || !dismissedReverse); j++)
        {
            if (text[j] == word[k] && text[j] != ' ' && text[j] != '\n' && text[j] != '\t') {
                k++;
                if (k == len) {
                    printSubstring(text, i, j, first);
                    first = 0;
                    break;
                }
            } else
                dismissedNormal = 1;
            if (text[j] == word[kRev] && text[j] != ' ' && text[j] != '\n' && text[j] != '\t') {
                kRev--;
                if (kRev == -1) {
                    printSubstring(text, i, j, first);
                    first = 0;
                    break;
                }
            } else
                dismissedReverse = 1;
        }
    }
    return first;
}

void b(char* word, char* text) {
    char* atbash = toAtbash(word);
    int first = 1;
    first = search(atbash, text, first);
    free(atbash);
}

int isPermutation(char* word, char* text, int i, int j) {
    int countText[CHAR_COUNT] = {0};
    int countWord[CHAR_COUNT] = {0};

    for (; i <= j; i++) {
        countText[text[i]]++;
    }

    int len = strlen(word);
    for (i = 0; i < len; i++)
        countWord[word[i]]++;

    for (int c = 0; c < CHAR_COUNT; c++)
    {
        if (c == ' ' || c == '\n' || c == '\t')
            continue;
        if (countWord[c] != countText[c]) {
            return 0;
        }
    }
    return 1;
}

void c(char* word, char* text) {
    int first = 1;
    for (size_t i = 0, end = strlen(text); i < end; i++)
    {
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t') 
            continue;
        for (size_t j = i; j < end; j++)
        {
        
            if(isPermutation(word, text, i, j)) {
                printSubstring(text, i, j, first);
                first = 0;
                break;
            }
        }
    }
}

int main()
{
    char text[TXT];
    char word[WORD];

    for (size_t i = 0; i < WORD; i++)
    {
        scanf("%c", &word[i]);
        if (word[i] == ' ' || word[i] == '\n' || word[i] == '\t') {
            word[i] = 0;
            break;
        }
    }
    for (size_t i = 0; i < TXT; i++)
    {
        scanf("%c", &text[i]);
        if (text[i] == '~') {
            text[i] = 0;
            break;
        }
    }
    printf("Gematria Sequences: ");
    a(word, text);
    printf("\nAtbash Sequences: ");
    b(word, text);
    printf("\nAnagram Sequences: ");
    c(word, text);

    return 0;
}
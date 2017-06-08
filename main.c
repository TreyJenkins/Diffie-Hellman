#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STRINGIFY(x) #x
#define MACRO(x)     STRINGIFY(x)

char *readIn() {
    char *line = NULL;
    size_t size;
    if (getline(&line, &size, stdin) != -1) {
        return line;
    }
    return "";
}

int readInt() {
    return atoi(readIn());
}

int isPrime(int num) {
     if (num <= 1) return 0;
     if (num % 2 == 0 && num > 2) return 0;
     for(int i = 3; i < num / 2; i+= 2) {
         if (num % i == 0)
             return 0;
     }
     return 1;
}

int genPrime() {
    while (true) {
        int ran = rand() % 128;
        if (isPrime(ran)) {
            return ran;
        }
    }
}

int power(int base, int expon) {
    int i, res = 1;
    for (i = 0; i < expon; i++) {
        res = res * base;
    }
    return res;
 }

int main(int argc, char const *argv[]) {
    #ifdef DEBUG
    printf("+--------------------+\n| Build ID: %s |\n+--------------------+\n\n", MACRO(BUILDID));
    #endif

    srand(time(NULL));

    bool dominant;
    while (true) {
        printf("Server/Client [S/C]: ");
        char* tmp = readIn();
        if (strcmp(tmp, "S\n") == 0) {
            printf("Server Selected\n");
            dominant = true;
            break;
        } else if (strcmp(tmp, "C\n") == 0) {
            printf("Client Selected\n");
            dominant = false;
            break;
        }
    }

    long p, g, a, A, b, c;

    if (dominant == true) {
        p = genPrime();
        g = genPrime();

        printf("P: %li, G: %li\n", p, g);
    } else {
        printf("Enter P: ");
        p = readInt();
        printf("Enter G: ");
        g = readInt();
    }

    a = rand() % 32;
    A = power(g, a) % p;

    if (dominant == true) {
        printf("A: %li\n", A);
        printf("Enter B: ");
        b = readInt();
    } else {
        printf("B: %li\n", A);
        printf("Enter A: ");
        b = readInt();
    }

    c = power(b, a) % p;

    printf("\nC: %li\n\n", p);

    return 0;
}

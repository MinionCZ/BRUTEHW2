#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MEGA 1000000
#define OPTINAL_LENGTH 100
bool primeNumbers[MEGA];  // array of primenumbers used for division
int optionalInput[OPTINAL_LENGTH];

//removes multiples of prime numbers which is passed as argument
void removeMultiplesOfNumber(int number) {
    for (int i = number * 2; i < MEGA; i += number) {
        primeNumbers[i] = false;
    }
}

//marks indexes in array prime number with true, if it is prime number else it is false
void createPrimeNumbers(void) {
    for (int i = 2; i < MEGA; i++) {
        primeNumbers[i] = true;
    }
    for (int i = 2; i < MEGA; i++) {
        if (primeNumbers[i]) {
            removeMultiplesOfNumber(i);
        }
    }
}

/*
* function firstly sets all ints in array optinalInput to -1 to indetify, where the input ends
* reads whole line from input and insert it into 
* also calculates if the number of inserted ciphers
*/
int readOptionalInput() {
    char input[100];
    for (int i = 0; i < OPTINAL_LENGTH; i++) {
        input[i] = 0;
        optionalInput[i] = -1;
    }
    scanf("%100s", input);
    int lengthCounter = 0;
    for (int i = 0; i < OPTINAL_LENGTH; i++) {
        if ((int)input[i] > 0) {
            optionalInput[i] = (int)input[i] - 48;
            lengthCounter++;
        }
    }
    return lengthCounter;
}

//returns true if optional array is not at the end of its length and also the next character is not -1
//-1 is signed that there are no more ciphers in optional array
bool hasOptionalNextCipher(int index) {
    if (index + 1 < OPTINAL_LENGTH) {
        return optionalInput[index + 1] != -1;
    }
    return false;
}

/*
* function divides optional input with parameter diviser
* if the result after dividing is zero the result is copied into optional array 
* function returns true if optional number is divisible by parameter or false when it is not
*/
bool divideOptionalNumber(long diviser) {
    long helpVariable = 0;
    int resultIndex = 0;
    int result[OPTINAL_LENGTH];
    for (int i = 0; i < OPTINAL_LENGTH; i++) {
        result[i] = -1;
    }

    for (int i = 0; i < OPTINAL_LENGTH; i++) {
        helpVariable *= 10;
        helpVariable += optionalInput[i];
        if (helpVariable >= diviser) {
            long restAfterDivison = helpVariable % diviser;
            result[resultIndex] = (int)(helpVariable / diviser);
            helpVariable = restAfterDivison;
        } else {
            result[resultIndex] = 0;
        }
        resultIndex++;
        if (!hasOptionalNextCipher(i)) {
            break;
        }
    }
    if (helpVariable == 0) {
        for (int i = 0; i < OPTINAL_LENGTH; i++) {
            optionalInput[i] = result[i];
        }
        return true;
    }
    return false;
}

/*
* prints output of prime number divisor of input number and its power
* also checks if next optional number is not 1 and when is not, the it prints x between numbers
*/
void printOptionalOutput(int primeNumber, int power) {
    if (power == 0) {
        return;
    }
    if (power == 1) {
        printf("%d", primeNumber);
    } else if (power > 0) {
        printf("%d^%d", primeNumber, power);
    }
    int numberCounter = 0;
    int higherThanOneCounter = 0;
    for (int i = 0; i < OPTINAL_LENGTH; i++) {
        if (optionalInput[i] > 0) {
            numberCounter++;
        }
        if (optionalInput[i] > 1) {
            higherThanOneCounter++;
        }
    }
    if (numberCounter > 1) {
        printf(" x ");
    } else if (higherThanOneCounter >= 1) {
        printf(" x ");
    } else {
        printf("\n");
    }
}

//prints on the output first line of output: Prvociselny rozklad cisla xxx je:\n
void printOptionalHeader() {
    printf("Prvociselny rozklad cisla ");
    for (int i = 0; i < OPTINAL_LENGTH; i++) {
        if (optionalInput[i] >= 0) {
            printf("%d", optionalInput[i]);
        } else {
            break;
        }
    }
    printf(" je:\n");
}
/*
* checks if the inserted input is correct or it is 0
* returns 0 if input is correct
* returns -1 when is input 0
* returns 100 when input is bad
* also filters number 1 which could cause endless for loop
* returns 1 if number 1 is in input meaning that one loop will be skipped in main alghoritm
*/
int checkOptionalInput(int inputLength) {
    for (int i = 0; i < OPTINAL_LENGTH; i++) {
        if (optionalInput[i] > 9 || optionalInput[i] < -1) {
            fprintf(stderr, "Error: Chybny vstup!\n");
            return 100;
        }
    }
    if (optionalInput[0] == 0 && inputLength == 1) {
        return -1;
    } else if (inputLength == 1 && optionalInput[0] == 1) {
        printf("Prvociselny rozklad cisla 1 je:\n1\n");
        return 0;
    } else {
        printOptionalHeader();
        return 0;
    }
}
//handles optional type of input and calculates prime numbers division
int handleOptionalInput(void) {
    int inputLength = readOptionalInput();
    int checkedInputValue = checkOptionalInput(inputLength);
    while (0 == checkedInputValue) {
        for (int i = 2; i < MEGA; i++) {
            if (primeNumbers[i]) {
                int power = 0;
                while (divideOptionalNumber((long)i)) {
                    power++;
                }
                printOptionalOutput(i, power);
            }
        }
        inputLength = readOptionalInput();
        checkedInputValue = checkOptionalInput(inputLength);
    }
    if (checkedInputValue == 100) {
        return 100;
    }
    return 0;
}

/*
* reads one number from input 
* if is correct, function returns that number from input
* if it is incorrect returns -1
*/
long getInput() {
    long input;
    int scanned = scanf("%ld", &input);
    if (scanned == 0 || input < 0) {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return -1;
    }
    return input;
}

/*
* divides number by prime number and gets prime number power in divided number
* writes prime number and its power
* returns divided number
*/
long divideByPrimeNumber(long numberToDivide, long primeNumber) {
    int powerCounter = 0;
    while (numberToDivide % primeNumber == 0) {
        powerCounter++;
        numberToDivide /= primeNumber;
    }
    if (powerCounter > 1) {
        printf("%ld%1s%d", primeNumber, "^", powerCounter);
    } else {
        printf("%ld", primeNumber);
    }
    if (numberToDivide > 1) {
        printf(" x ");
    }
    return numberToDivide;
}

//creates decomposition of a number in standard version
void createDecomposition(long numberToDecompose) {
    for (int i = 2; i < MEGA; i++) {
        if (primeNumbers[i]) {
            if (numberToDecompose % (long)i == 0) {
                numberToDecompose = divideByPrimeNumber(numberToDecompose, (long)i);
                if (numberToDecompose == 1) {
                    return;
                }
            }
        }
    }
}

//handles standart version of input
int handleStandartInput(void) {
    while (true) {
        long numberToDivide = getInput();
        if (numberToDivide == -1) {
            return 100;
        } else if (numberToDivide == 0) {
            return 0;
        } else if (numberToDivide == 1) {
            printf("Prvociselny rozklad cisla 1 je:\n1");
        } else {
            printf("%s %ld %s", "Prvociselny rozklad cisla", numberToDivide, "je:\n");
            createDecomposition(numberToDivide);
        }
        printf("\n");
    }
}






int main(int argc, char *argv[]) {
    createPrimeNumbers();
    if (argc > 1 && strcmp("-prg-optional", argv[1]) == 0) {
        return handleOptionalInput();
    }else{
        return handleStandartInput();
    }
}

/// Author of the program : Justas Mileika
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define msgProgramPurpose "The program takes in positive integers and tells whether they are prime and if they aren't, the program tells the closest prime(-es)\n"
#define msgRangeOfInput "The input can be in the range [" minNumberAvailable "; " maxNumberAvailable "]\n"
#define msgWhenDoesProgramEnd "To terminate the program, input 0\n"
#define askingForInput "Please enter an integer\n"
#define maxNumberAvailable "999999999"
#define minNumberAvailable "0"
#define inputNumberExceedsBoundaries "The number you have entered is not in the range specified, please enter an integer in the range that is specified\n"
#define inputContainsWrongSymbols "Your input contains unavailable symbols\n"
#define askingForNextInput "Please enter a number\n"
#define inputConfirmation "Data entered succesfully\n"
#define reaskingForInput "Please reenter the input\n"
#define msgTwoClosestPrimes "The two closest primes to the number you have entered are: "
#define msgClosestPrime "The closest prime to the number you have entered is: "
#define msgPrime " is prime\n"
#define msgNotPrime " is not prime\n"
#define msgProgramHasBeenTerminated "The program ends....\n"
#define msgInputIsNeither " is neither a prime nor a composite number\n"

/// function that returns 1, if number is prime, and 0 otherwise
int isPrime(int number)
{
    if(number == 1)
        return 0;
    for(int i = 2; i <= sqrt(number); i++)
    {
        if(number % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
/// function that finds the higher prime
int upperPrime(int number)
{
    for(int i = number+1; 1; i++)
    {
        if(isPrime(i))
        {
            return i;
        }
    }
}
/// function that finds the lower prime
int lowerPrime(int number)
{
    for(int i = number-1; 1; i--)
    {
        if(isPrime(i))
        {
            return i;
        }
    }
}
int validatingInput(char msgReaskingForInput[], char msgInputContainsInvalidSymbols[], char msgInvalidInputSize[]) {
    int inputData;
    int isInvalidInputSize = 0;
    while(1)
    {
        inputData = 0;
        int isInputValid  = 1;
        char helperCharacter = getc(stdin);
        /// seperate case if user presses enter at the start
        if(helperCharacter == '\n')
        {
            continue;
        }

        /// removing the leading 0s and scanning the number
        while(helperCharacter == '0')
        {
            helperCharacter = getc(stdin);
        }
        if(helperCharacter != '\n')
        {
            ungetc(helperCharacter, stdin);
            isInputValid = scanf("%9d", &inputData);
        }
        else
        {
            ungetc(helperCharacter, stdin);
        }

        /// checking whether input is valid symbol-wise and scanning the rest of the line if the input is not valid
        char charToReadUnavailableSymbols;
        if(!isInputValid)
        {
            /// removing the size overflow flag if it is on
            if(isInvalidInputSize)
                isInvalidInputSize = !isInvalidInputSize;
            printf("%s%s", msgInputContainsInvalidSymbols,
                   msgReaskingForInput);
            charToReadUnavailableSymbols = getchar();
            while(charToReadUnavailableSymbols != '\n' && charToReadUnavailableSymbols != ' ')
            {
                charToReadUnavailableSymbols = getchar();
            }
            continue;
        }

        helperCharacter = getc(stdin);
        /// ending the loop if the input ends
        if(helperCharacter == '\n' || helperCharacter == ' ')
        {
            /// continuing the loop if the input is overflown in size
            if(isInvalidInputSize || inputData < 0)
            {
                printf("%s%s", msgInvalidInputSize,
                       msgReaskingForInput);
                if(isInvalidInputSize)
                    isInvalidInputSize = !isInvalidInputSize;
                continue;
            }
            ungetc(helperCharacter, stdin);
            break;
        }
        /// if the 9 digits are valid and the 10th one is a valid digit, we put the size overflow flag on and continue looping
        else if(helperCharacter >= '0' && helperCharacter <= '9')
        {
            ungetc(helperCharacter, stdin);
            if(inputData!=0)
                isInvalidInputSize = 1;
            continue;
        }
        else
        {
            if(isInvalidInputSize)
                isInvalidInputSize = !isInvalidInputSize;
            printf("%s%s", msgInputContainsInvalidSymbols,
                   msgReaskingForInput);
            charToReadUnavailableSymbols = getchar();
            while(charToReadUnavailableSymbols != '\n' && charToReadUnavailableSymbols != ' ')
            {
                charToReadUnavailableSymbols = getchar();
            }
        }
    }
    return inputData;
}
int main() {
    int inputNumber = 1;
    printf("%s%s%s%s",msgProgramPurpose,
           askingForInput,
           msgRangeOfInput,
           msgWhenDoesProgramEnd);
    /// looping while entered number isn't 0
    while(inputNumber)
    {
        /// scanning and validating input
        inputNumber = validatingInput(reaskingForInput, inputContainsWrongSymbols, inputNumberExceedsBoundaries);
        char nextChar = getc(stdin);
        /// ending the program if input is 0
        if(!inputNumber)
        {
            printf(msgProgramHasBeenTerminated);
            break;
        }

        /// seperate case for 1
        if(inputNumber == 1)
        {
            printf("%d%s%s%d\n", inputNumber, msgInputIsNeither, msgClosestPrime, 2);
            if(nextChar == '\n')
            {
                printf(askingForNextInput
                       msgRangeOfInput);
            }
            continue;
        }

        /// printing the results based on what function returns
        if(!isPrime(inputNumber))
        {
            printf("%d%s", inputNumber, msgNotPrime);
            int upperClosestPrime = upperPrime(inputNumber);
            int lowerClosestPrime = lowerPrime(inputNumber);
            /// checking if closest lower prime and closest higher prime are even in distance from the actual number
            if(abs(inputNumber - upperClosestPrime) == abs(inputNumber - lowerClosestPrime))
            {
                printf("%s%d %d\n", msgTwoClosestPrimes, lowerClosestPrime, upperClosestPrime);
            }
            else
            {
                printf("%s%d\n", msgClosestPrime, (abs(inputNumber - upperClosestPrime) <= abs(inputNumber - lowerClosestPrime))? upperClosestPrime : lowerClosestPrime);
            }
        }
        else
        {
            printf("%d%s", inputNumber, msgPrime);
        }

        /// printing a message if the user presses enter after the input
        if(nextChar == '\n')
        {
            printf(askingForNextInput
                   msgRangeOfInput
                   msgWhenDoesProgramEnd
                   );
        }
    }
}

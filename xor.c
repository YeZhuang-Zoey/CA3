#include "xor.h"

/*
    Performs the encryption on the text provided from input
    Most likely use RSA
    Author: Vincent
*/
void encryption(){
    FILE *inputFile, *outputFile;
    char *buffer, *ciphered, fileName[256], xorKey[256];
    long fileLen;

    printf("Please enter the text file which contains the data: ");
    scanf("%255s", fileName);
    fflush(stdin);
    printf("Please enter the key to decrypt: ");
    scanf("%255s", xorKey);
    fflush(stdin);

    inputFile = fopen(fileName, "rb");
    if(inputFile == NULL) {
        perror("Failed to open file\n");
        return;
    }

    fseek(inputFile, 0, SEEK_END);
    fileLen = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    buffer = (char *) malloc(fileLen);
    if(buffer == NULL) {
        perror("Failed to allocate memory");
        fclose(inputFile);
        return;
    }

    fread(buffer, fileLen, 1, inputFile);
    fclose(inputFile);

    ciphered = XORCipher(buffer, fileLen, xorKey);
    if(ciphered == NULL) {
        perror("Failed to encrypt data");
        free(buffer);
        return;
    }

    outputFile = fopen("encrypted.txt", "wb");
    if(outputFile == NULL) {
        perror("Failed to open encrypted.txt");
        free(buffer);
        free(ciphered);
        return;
    }

    fwrite(ciphered, fileLen, 1, outputFile);
    fclose(outputFile);

    free(buffer);
    free(ciphered);
}

/*
    Perform the decryption after decompressing the file
    Author: Vincent
*/
void decryption(){
    FILE *inputFile, *outputFile;
    char *buffer, *ciphered, fileName[256], xorKey[256];
    long fileLen;

    printf("Please enter the text file which contains the encrypted data: ");
    scanf("%255s", fileName);
    fflush(stdin);

    printf("Please enter the key to encrypt: ");
    scanf("%255s", xorKey);
    fflush(stdin);


    inputFile = fopen(fileName, "rb");
    if(inputFile == NULL) {
        perror("Failed to open file\n");
        return;
    }

    fseek(inputFile, 0, SEEK_END);
    fileLen = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    buffer = (char *) malloc(fileLen);
    if(buffer == NULL) {
        perror("Failed to allocate memory");
        fclose(inputFile);
        return;
    }

    fread(buffer, fileLen, 1, inputFile);
    fclose(inputFile);

    ciphered = XORCipher(buffer, fileLen, xorKey);
    if(ciphered == NULL) {
        perror("Failed to encrypt data");
        free(buffer);
        return;
    }

    outputFile = fopen("decrypted.txt", "wb");
    if(outputFile == NULL) {
        perror("Failed to open encrypted.txt");
        free(buffer);
        free(ciphered);
        return;
    }

    fwrite(ciphered, fileLen, 1, outputFile);
    fclose(outputFile);

    free(buffer);
    free(ciphered);
}

/*
    This performs the actual XOR encrpytion/decryption
    Author: Vincent
*/
char* XORCipher(char *originalString, int len, char *xorKey) {
    int i;
    char *cipheredString = (char *) malloc(len + 1);
    for(i = 0; i < len; i++) {
        cipheredString[i] = originalString[i] ^ *xorKey;
    }
    cipheredString[len] = '\0';
    return cipheredString;

}

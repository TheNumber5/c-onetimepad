#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHUNK_SIZE 200000

//One-Time Pad encryption for files.
//Version:v1.0, date:08/08/2023
//https://github.com/TheNumber5/c-onetimepad

void xorChunkWithKey(unsigned char *data, const unsigned char *key, size_t size) {
    for (size_t i = 0; i < size; i++) {
        data[i] ^= key[i];
    }
}

int main(int argc, char **argv) {
    if (argc != 5) {
        printf("Usage: %s -e/-d input_file output_file key_file\n", argv[0]);
        return 1;
    }

    int encryptMode = 0;
    if (strcmp(argv[1], "-e") == 0) {
        encryptMode = 1;
    } else if (strcmp(argv[1], "-d") == 0) {
        encryptMode = 0;
    } else {
        printf("Invalid mode. Use -e for encryption or -d for decryption.\n");
        return 1;
    }

    const char *inputFilename = argv[2];
    const char *outputFilename = argv[3];
    const char *keyFilename = argv[4];

    FILE *inputFile = fopen(inputFilename, "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen(outputFilename, "wb");
    if (outputFile == NULL) {
        perror("Error creating output file");
        fclose(inputFile);
        return 1;
    }

    FILE *keyFile = NULL;
    if (encryptMode == 0) {
        keyFile = fopen(keyFilename, "rb");
        if (keyFile == NULL) {
            perror("Error opening key file");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }
    } else {
        keyFile = fopen(keyFilename, "wb");
        if (keyFile == NULL) {
            perror("Error creating key file");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    srand(time(NULL));

    unsigned char *inputChunk = malloc(CHUNK_SIZE * sizeof(unsigned char));
    unsigned char *keyChunk = malloc(CHUNK_SIZE * sizeof(unsigned char));
    if (inputChunk == NULL || keyChunk == NULL) {
        perror("Error allocating memory");
        fclose(inputFile);
        if (keyFile) fclose(keyFile);
        fclose(outputFile);
        return 1;
    }

    size_t numBytesToProcess = fileSize;

    clock_t startTime = clock();

    while (numBytesToProcess > 0) {
        size_t chunkSize = numBytesToProcess < CHUNK_SIZE ? numBytesToProcess : CHUNK_SIZE;

        fread(inputChunk, sizeof(unsigned char), chunkSize, inputFile);
        if (encryptMode == 0) {
            fread(keyChunk, sizeof(unsigned char), chunkSize, keyFile);
        } else {
            for (size_t i = 0; i < chunkSize; i++) {
                keyChunk[i] = rand() % 256;
            }
            fwrite(keyChunk, sizeof(unsigned char), chunkSize, keyFile);
        }

        xorChunkWithKey(inputChunk, keyChunk, chunkSize);

        fwrite(inputChunk, sizeof(unsigned char), chunkSize, outputFile);
        numBytesToProcess -= chunkSize;
    }

    free(inputChunk);
    free(keyChunk);

    fclose(inputFile);
    if (keyFile) fclose(keyFile);
    fclose(outputFile);

    clock_t endTime = clock();
    double processTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    printf("%s completed for %ld bytes in %.4f seconds.\n",
           encryptMode ? "Encryption" : "Decryption", fileSize, processTime);

    return 0;
}
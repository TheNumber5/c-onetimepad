# One-Time Pad

How to use it:

1. Clone the repository to your computer.
2. Compile the program with a compiler like gcc:
`gcc onetimepad.c -o onetimepad`
3. Run the program with the following command: `onetimepad -e input.bin output.bin key.bin`

This will encrypt the file input.bin and save the ciphertext to the file output.bin. The key is saved to the file key.bin.

To decrypt the file, use: `onetimepad -d input.bin output.bin key.bin`
You can run `Autodecrypt.bat` to automatically decrypt all the example files from the repository.

# How it works

The one-time pad encryption program uses the XOR operation to encrypt and decrypt files. The XOR operation is a bitwise operation that takes two binary numbers as input and returns a binary number with the same length as the input numbers. The output bit is 1 if and only if the corresponding input bits are different.

To encrypt a file, it generates a random key that is the same length as the file. The program then XORs each byte of the file with the corresponding byte of the key. The resulting ciphertext is the encrypted version of the file.

To decrypt a file, the program XORs each byte of the ciphertext with the corresponding byte of the key. The resulting plaintext is the original version of the file.

The one-time pad encryption algorithm is unbreakable since the key is completely random and has a complexity of `256^n` where `n` is the size of the file in bytes.

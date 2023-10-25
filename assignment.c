/**********************************
 * List header
**********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "assignment.h"
#include "xor.h"
#include "huffman.h"

/*******************************************************************************
 * List preprocessing directives
*******************************************************************************/


/**********************************
 * Function Prototype
**********************************/
void compress();
void decompress();
void input();
void displayUsers();
/**********************************
 * main
**********************************/
int main() {
    encryption();
    decryption();

    char* table[NUM_CHARS] = {0};
    char initialCode[256] = "";
    char fileName[256];
    printf("Please enter the name of the file you would like to compress: ");
    scanf("%s", fileName);
    TreeNode_t* root = buildHuffmanTree(fileName);
    buildHuffmanCodeTable(root, initialCode, table);

    encodeFile(fileName, "huffman.huf", table);
    printf("%s compressed as huffman.huf\n", fileName);
    decodeFile("huffman.huf", "decoded.txt", root);
    printf("huffman.huf is decompressed into decoded.txt\n");


    return 0;
}

/*
    Provide the basic input for the client to go through. 
    Will mostly be supplying a name and file to tie to the client struct
*/

/*Lachlan*/
void input(){
    
}

/*
    search by name
void search() {

}

     Bubble sort / Insertion sort / Selection sort
void sort() {
    
}
*/


/*
    Display all the users
    Lachlan
*/ 
void displayUsers() {

}











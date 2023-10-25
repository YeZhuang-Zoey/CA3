#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS 256

typedef struct TreeNode{
    int frequency;
    unsigned char character;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode_t;

typedef struct {
    int size;
    TreeNode_t *nodes[NUM_CHARS];
} PriorityQueue_t;

/* Function prototypes */
PriorityQueue_t* createPriorityQueue();
void insertPriorityQueue(PriorityQueue_t* pq, TreeNode_t* node);
TreeNode_t* extractMinPriorityQueue(PriorityQueue_t* pq);
TreeNode_t* buildHuffmanTree(char* filename);
void buildHuffmanCodeTable(TreeNode_t* root, char* code, char** table);
void encodeFile(char* inputFilename, char* outputFilename, char** table);
void decodeFile(char* inputFilename, char* outputFilename, TreeNode_t* root);

#endif /* HUFFMAN_H */


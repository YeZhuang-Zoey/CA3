#include "huffman.h"

void calculateFrequency(char* filename, int* freq) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    unsigned char ch;
    while (fread(&ch, sizeof(unsigned char), 1, file)) {
        freq[ch]++;
    }

    fclose(file);
}

PriorityQueue_t* createPriorityQueue() {
    PriorityQueue_t* pq = (PriorityQueue_t*) malloc(sizeof(PriorityQueue_t));
    if (!pq) {
        perror("Failed to allocate memory for priority queue");
        exit(1);
    }
    pq->size = 0;
    return pq;
}

void insertPriorityQueue(PriorityQueue_t* pq, TreeNode_t* node) {
    int i = pq->size++;
    while (i && node->frequency < pq->nodes[(i - 1) / 2]->frequency) {
        pq->nodes[i] = pq->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq->nodes[i] = node;
}

TreeNode_t* extractMinPriorityQueue(PriorityQueue_t* pq) {
    if (pq->size == 0) return NULL;

    TreeNode_t* min = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];

    int i = 0;
    while (2 * i + 1 < pq->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = left;
        if (right < pq->size && pq->nodes[right]->frequency < pq->nodes[left]->frequency) {
            smallest = right;
        }
        if (pq->nodes[i]->frequency <= pq->nodes[smallest]->frequency) break;
        TreeNode_t* temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[smallest];
        pq->nodes[smallest] = temp;
        i = smallest;
    }

    return min;
}

TreeNode_t* buildHuffmanTree(char* filename) {
    int freq[NUM_CHARS] = {0};
    int i;
    calculateFrequency(filename, freq);

    PriorityQueue_t* pq = createPriorityQueue();

    for (i = 0; i < NUM_CHARS; i++) {
        if (freq[i]) {
            TreeNode_t* node = (TreeNode_t*) malloc(sizeof(TreeNode_t));
            if (!node) {
                perror("Failed to allocate memory for tree node");
                exit(1);
            }
            node->frequency = freq[i];
            node->character = (unsigned char)i;
            node->left = node->right = NULL;
            insertPriorityQueue(pq, node);
        }
    }

    while (pq->size > 1) {
        TreeNode_t* left = extractMinPriorityQueue(pq);
        TreeNode_t* right = extractMinPriorityQueue(pq);

        TreeNode_t* parent = (TreeNode_t*) malloc(sizeof(TreeNode_t));
        if (!parent) {
            perror("Failed to allocate memory for tree node");
            exit(1);
        }
        parent->frequency = left->frequency + right->frequency;
        parent->left = left;
        parent->right = right;
        insertPriorityQueue(pq, parent);
    }

    return extractMinPriorityQueue(pq);
}

void buildHuffmanCodeTable(TreeNode_t* root, char* code, char** table) {
    extern char* strdup(const char*);

    if (!root) return;

    if (!root->left && !root->right) {
        table[root->character] = strdup(code);
        return;
    }

    int length = strlen(code);
    char* leftCode = (char*) malloc(length + 2);
    char* rightCode = (char*) malloc(length + 2);
    strcpy(leftCode, code);
    strcpy(rightCode, code);
    strcat(leftCode, "0");
    strcat(rightCode, "1");

    buildHuffmanCodeTable(root->left, leftCode, table);
    buildHuffmanCodeTable(root->right, rightCode, table);

    free(leftCode);
    free(rightCode);
}

void encodeFile(char* inputFilename, char* outputFilename, char** table) {
    FILE* inputFile = fopen(inputFilename, "r");
    FILE* outputFile = fopen(outputFilename, "wb");
    if (!inputFile || !outputFile) {
        perror("Failed to open file");
        exit(1);
    }

    unsigned char ch;
    unsigned char buffer = 0; 
    int bitCount = 0;
    int i; 

    while (fread(&ch, sizeof(unsigned char), 1, inputFile)) {
        char* code = table[ch];
        for (i = 0; code[i]; i++) {
            buffer = (buffer << 1) | (code[i] == '1');
            bitCount++;
            if (bitCount == 8) {
                fwrite(&buffer, sizeof(unsigned char), 1, outputFile);
                buffer = 0;
                bitCount = 0;
            }
        }
    }


    if (bitCount) {
        buffer <<= (8 - bitCount); 
        fwrite(&buffer, sizeof(unsigned char), 1, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
}


void decodeFile(char* inputFilename, char* outputFilename, TreeNode_t* root) {
    FILE* inputFile = fopen(inputFilename, "rb");
    FILE* outputFile = fopen(outputFilename, "w");
    if (!inputFile || !outputFile) {
        perror("Failed to open file");
        exit(1);
    }

    TreeNode_t* current = root;
    unsigned char byte;
    while (fread(&byte, sizeof(unsigned char), 1, inputFile)) {
        int i;
        for (i = 0; i < 8; i++) {
            if (byte & (0x80 >> i)) { 
                current = current->right;
            } else {
                current = current->left;
            }

            if (!current->left && !current->right) {
                fputc(current->character, outputFile);
                current = root;
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}



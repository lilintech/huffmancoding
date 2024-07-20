#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for the nodes in the Huffman tree
typedef struct Node {
    char ch;
    int freq;
    struct Node* left;
    struct Node* right;
} Node;

// Structure for the priority queue
typedef struct {
    Node** array;
    int size;
    int capacity;
} PriorityQueue;

// Function to create a new node
Node* createNode(char ch, int freq) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->ch = ch;
    newNode->freq = freq;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a priority queue
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->array = (Node**)malloc(capacity * sizeof(Node*));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

// Function to swap two nodes
void swapNodes(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the priority queue
void heapify(PriorityQueue* pq, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < pq->size && pq->array[left]->freq < pq->array[smallest]->freq) {
        smallest = left;
    }

    if (right < pq->size && pq->array[right]->freq < pq->array[smallest]->freq) {
        smallest = right;
    }

    if (smallest != idx) {
        swapNodes(&pq->array[smallest], &pq->array[idx]);
        heapify(pq, smallest);
    }
}

// Function to insert a node into the priority queue
void insertPriorityQueue(PriorityQueue* pq, Node* node) {
    if (pq->size == pq->capacity) {
        return;
    }

    pq->size++;
    int idx = pq->size - 1;
    pq->array[idx] = node;

    while (idx != 0 && pq->array[(idx - 1) / 2]->freq > pq->array[idx]->freq) {
        swapNodes(&pq->array[(idx - 1) / 2], &pq->array[idx]);
        idx = (idx - 1) / 2;
    }
}

// Function to extract the minimum node from the priority queue
Node* extractMin(PriorityQueue* pq) {
    if (pq->size == 0) {
        return NULL;
    }

    Node* root = pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    heapify(pq, 0);

    return root;
}

// Function to build the Huffman tree
Node* buildHuffmanTree(char* data, int* freq, int size) {
    PriorityQueue* pq = createPriorityQueue(size);

    for (int i = 0; i < size; i++) {
        insertPriorityQueue(pq, createNode(data[i], freq[i]));
    }

    while (pq->size > 1) {
        Node* left = extractMin(pq);
        Node* right = extractMin(pq);
        Node* top = createNode('\0', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertPriorityQueue(pq, top);
    }

    Node* root = extractMin(pq);
    free(pq->array);
    free(pq);
    return root;
}

// Function to build the Huffman codes
void buildHuffmanCodes(Node* root, char* code, int top, char codes[256][256]) {
    if (root->left) {
        code[top] = '0';
        buildHuffmanCodes(root->left, code, top + 1, codes);
    }

    if (root->right) {
        code[top] = '1';
        buildHuffmanCodes(root->right, code, top + 1, codes);
    }

    if (!root->left && !root->right) {
        code[top] = '\0';
        strcpy(codes[(int)root->ch], code);
    }
}

// Function to encode the text using the Huffman codes
char* encode(char* text, char codes[256][256]) {
    char* encodedText = (char*)malloc(1024 * sizeof(char));
    encodedText[0] = '\0';
    for (int i = 0; text[i] != '\0'; i++) {
        strcat(encodedText, codes[(int)text[i]]);
    }
    return encodedText;
}

// Function to decode the encoded text using the Huffman codes
char* decode(char* encodedText, Node* root) {
    char* decodedText = (char*)malloc(1024 * sizeof(char));
    int index = 0;
    Node* currentNode = root;

    for (int i = 0; encodedText[i] != '\0'; i++) {
        if (encodedText[i] == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        if (!currentNode->left && !currentNode->right) {
            decodedText[index++] = currentNode->ch;
            currentNode = root;
        }
    }

    decodedText[index] = '\0';
    return decodedText;
}

// Main function
int main() {
    char text[] = "this is an example for huffman encoding";
    int freq[256] = {0};

    for (int i = 0; text[i] != '\0'; i++) {
        freq[(int)text[i]]++;
    }

    char data[256];
    int frequency[256];
    int size = 0;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            frequency[size] = freq[i];
            size++;
        }
    }

    Node* root = buildHuffmanTree(data, frequency, size);
    char codes[256][256] = {{0}};
    char code[256];
    buildHuffmanCodes(root, code, 0, codes);

    char* encodedText = encode(text, codes);
    char* decodedText = decode(encodedText, root);

    printf("Original Text: %s\n", text);
    printf("Encoded Text: %s\n", encodedText);
    printf("Decoded Text: %s\n", decodedText);

    free(encodedText);
    free(decodedText);

    return 0;
}

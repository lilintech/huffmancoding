# Greedy Algorithm for Huffman Coding
This code implements Huffman Coding for data compression. Huffman coding uses a greedy algorithm to create an optimal prefix-free binary code for a set of symbols based on their frequncies.

## How the Code works
In the main function, the code below takes the input of characters from the user to encode

```c
char text[] = "this is an example for huffman encoding";
```

Once the input is inputted the function `buildHuffmanTree` builds a tree for each character as nodes in the tree. Then the function `buildHuffmanCodes` assigns binary codes for each character depending on the placement of the nodes. If on the right node, the character is assigned a '1', and if on the left node it is assigned a '0'.

## Project Team Members
1. Mercy Jelimo	
2. Victor Ngigi		
3. Lilian Wanjiku	
4. Preston Wachira	
5. Ananda Marion Midega	
6. Cherise Gachambi	
7. Peace Ndungu	
8. Otieno Donnex
9. Keith Chomba

## Conclusion
Greedy Algorithm is used in Huffman coding by combining the least frequent nodes first to ensure an optimal encoding.



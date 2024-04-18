// Seth Relampagos | 18th April 2024
// COP 3502C | Computer Science 1
// Lab Assignment 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
  struct Trie * nextNode[26];
  int numWords;
};

// deallocate the trie structure
struct Trie * deallocateTrie(struct Trie *pTrie)
{
  //This will free the TrieNode

  for (int i = 0; i < 26; i++) {
    if (pTrie -> nextNode[i] != NULL) {
      deallocateTrie(pTrie -> nextNode[i]);
    }
  }

  free(pTrie);

  return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
  struct Trie * currentNode = (struct Trie*)malloc(sizeof(struct Trie));

  for (int i = 0; i < 26; i++) {
    currentNode -> nextNode[i] = NULL;
  }
  currentNode -> numWords = 0;

  return currentNode;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
  
  for (int i = 0; i < strlen(word); i++) {
    int nextLetter = word[i] - 'a';
    
    if (pTrie -> nextNode[nextLetter] == NULL) {
      pTrie -> nextNode[nextLetter] = createTrie();
    }

    pTrie = pTrie -> nextNode[nextLetter];
  }

  pTrie -> numWords += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
  
  for (int i = 0; i < strlen(word); i++) {

    int nextLetter = word[i] - 'a';

    if (pTrie -> nextNode[nextLetter] == NULL) {
      return 0;
    }

    pTrie = pTrie -> nextNode[nextLetter];
  }
  
  return pTrie -> numWords;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
  FILE * fPtr = fopen(filename, "r");

  int numWords;
  fscanf(fPtr, "%d", &numWords);

  for (int i = 0; i < numWords; i++) {

    pInWords[i] = (char*)malloc(256 * sizeof(char));
    fscanf(fPtr, "%s", pInWords[i]);
    
  }

  return numWords;
}

int main(void)
{
  char *inWords[256];

  //read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  printf("%s\n", "This dictionary holds the words: ");
  puts("============================");
  for (int i=0;i<numWords;++i)
  {
    printf("%s\n",inWords[i]);
  }

  printf("%s\n", "================");
  puts("");

  struct Trie *pTrie = createTrie();
  for (int i=0;i<numWords;i++)
  {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

  for (int i=0;i<5;i++)
  {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}
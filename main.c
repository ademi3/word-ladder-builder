//
//  main.c
//  cs211_Project3
//
//  Created by Alexandru Demidetchi on 10/5/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int strCmpCnt(char* word1, char* word2) {
//-------------------------------------------------------------------
// TODO - Task I: write the strCmpCnt() function, which returns the
//                count of character differences between two words
//                (i.e. strings); include the extra characters in the
//                longer word if the strings have different lengths
// Exs: word1 = magic, word2 = magic, returns 0
//      word1 = wands, word2 = wants, returns 1
//      word1 = magic, word2 = wands, returns 4
//      word1 = magic, word2 = mag, returns 2
//      word1 = magic, word2 = magicwand, returns 4
//      word1 = magic, word2 = darkmagic, returns 8
//-------------------------------------------------------------------
    int ctCharDifferences = 0; // counter to keep track of char differences

    // loop runs as long as at least one of the words still has more characters to iterate through
    while ((*word1 != '\0') || (*word2 != '\0')) {

        // counter is updated if the current characters are different
        if (*word1 != *word2) {
            ctCharDifferences++;
        }
        // if the end of word1 has not been reached, the pointer is incremented to move to the next character in the string
        if (*word1 != '\0') {
            word1++;
        }
        // if the end of word2 has not been reached, the pointer is incremented to move to the next character in the string
        if (*word2 != '\0') {
            word2++;
        }
    }
    return ctCharDifferences;
}


int strCmpInd(char* word1, char* word2) {
    //-------------------------------------------------------------------
    // TODO - Task II: write the strCmpInd() function, which returns the
    //                 index of the character where two strings first
    //                 differ, & returns -1 if there are no differences
    // Exs: word1 = magic, word2 = magic, returns -1
    //      word1 = wands, word2 = wants, returns 3
    //      word1 = magic, word2 = wands, returns 0
    //      word1 = magic, word2 = mag, returns 3
    //      word1 = magic, word2 = magicwand, returns 5
    //      word1 = magic, word2 = darkmagic, returns 0
    //-------------------------------------------------------------------
    
    int index = 0; // keeps track of where the two strings first differ
    bool diffWords = false; // bool to indicate whether the two strings are different or not
    
    // loop runs as long as one of the words still has more characters to iterate through
    while ((*word1 != '\0') || (*word2 != '\0')) {
        // if the current characters are the same, the pointers are moved to the next character and the index variable is incremented
        if (*word1 == *word2) {
            word1++;
            word2++;
            index++;
        }
        // if the current characters differ, the index at which this difference occurs is returned
        else {
            diffWords = true;
            return index;
        }
    }
    // if the words are identical, -1 is returned
    if (!diffWords) {
        return -1;
    }
    return 0;
}


void appendWord(char*** pWords, int* pNumWords, int* pMaxWords, char* newWord) {
//---------------------------------------------------------------------
// TODO - Task III: write appendWord() function, which adds a new word
//      to a dynamic heap-allocated array of C-strings; heap-space must
//      be allocated for the new word inside this function, then copy
//      the chars from [newWord] to the newly allocated heap-space;
//      if adding a new word pushes *pNumWords greater than *pMaxWords,
//      then realloate the *pWords array with double the capacity.
//      parameters:
//          [char*** pWords] - array of C-strings passed-by-pointer
//              note: *pWords is an array of pointers
//                    **pWords is an array of chars
//                    ***pWords is a char
//                    (*pWords)[0] is the 1st C-string in the array
//                    (*pWords)[1] is the 2nd C-string in the array
//                    (*pWords)[0][0] is 1st char of 1st C-string
//                    (*pWords)[1][2] is 3rd char of 2nd C-string
//                    etc.
//          [int* pNumWords] - current # of words in *pWords array
//               note: *pNumWords will increase by 1 here,
//                     so it is passed-by-pointer
//          [int* pMaxWords] - current capacity of *pWords array
//               note: *pMaxWords may increase by x2 here,
//                     so it is passed-by-pointer
//          [char* newWord] - C-string word to be added to *pWords
//               note: [newWord] is a C-string, naturally a pointer
//---------------------------------------------------------------------

// checking if adding an additional word makes the number of words in the *pWords array greater than the capacity of the array
if ((*pNumWords + 1) > *pMaxWords) {

    char** tempArray = malloc(((*pMaxWords) * 2) * sizeof(char*)); // allocating an array of pointers to C-strings with double the capacity of the original array

    // copying all elements to the temp array
    for (int i = 0; i < *pNumWords; ++i) {
        tempArray[i] = (*pWords)[i];
    }
    
    (*pMaxWords) *= 2; // doubling the capacity of the array
    free(*pWords); // freeing the memory associated with the original array since we only need the updated one now
    *pWords = tempArray; // reassigning the array pointer to the updated array
}

(*pWords)[*pNumWords] = malloc((strlen(newWord) + 1) * sizeof(char)); // allocating space for the new word; 1 is added to the string length to account for '\0'
strcpy((*pWords)[*pNumWords], newWord); // copying the new word into the allocated space at the end of the array

(*pNumWords)++; // updating the counter that keeps track of the number of words in the array
}


int linSearchForWord(char** words, int numWords, char* findWord) {
//-------------------------------------------------------------------
// TODO - Task V: write the linSearchForWord() function that returns
//      the index in the [words] C-string array where a match to the
//      C-string [findWord] is found, using a linear search;
//      return -99 if [findWord] is NOT found in [words] array;
//      note: [words] is an array of pointers to [numWords] C-strings
//-------------------------------------------------------------------
    // loop that iterates over the words C-string array
    for (int i = 0; i < numWords; ++i) {
        // if the word that is being searched for is found in the array, then the index where it's found is returned
        if (strcmp(words[i], findWord) == 0) {
            return i;
        }
    }
    return -99; // if the word is not found in the array, -99 is returned
}


bool checkForValidWord(char** words, int numWords, int wordLen, char** ladder, int ladderHeight, char* aWord) {
//-------------------------------------------------------------------
// TODO - Task VI: write the checkForValidWord() function, which checks
//      if [aWord] is valid for the next word in the word ladder;
//
//      return TRUE for the following cases:
//        - [aWord] is "DONE" beacuse the user wants to stop;
//              this case takes highest precedence;
//              before returning TRUE, first print:
//                  "Stopping with an incomplete word ladder..."
//        - [aWord] is valid and will be added to the word ladder
//              before returning TRUE, first print:
//                  "Entered word is valid and will be added to the word ladder."
//
//      return FALSE for the following cases
//      (precedence for invalidity measures follows the order given here):
//        - [aWord] is invalid because it has the wrong word length;
//              before returning FALSE, first print:
//                  "Entered word does NOT have the correct length. Try again..."
//        - [aWord] is invalid because it is not in the words array,
//              i.e. not in the dictionary;
//              before returning FALSE, first print:
//                  "Entered word NOT in dictionary. Try again..."
//        - [aWord] is invalid because it is NOT a single-char
//              difference from the previous word in the ladder;
//              e.g. previous word is "code" and [aWord] is "cave";
//              e.g. previous word is "code" and [aWord] is "code";
//              before returning FALSE, first print:
//                  "Entered word is NOT a one-character change from the previous word. Try again..."
//
//      [words] is an array of [numWords] C-strings that contains all
//              words in the dictionary of word length [wordLen]
//      [ladder] is an array of [ladderHeight] C-strings that
//              represents an incomplete word ladder
//      [aWord] is a C-string that must be checked for validity here
//
//  HINT: call linSearchWord(), strCmpCnt(), & string.h function(s)
//-------------------------------------------------------------------
    
    // checking if the user entered Done, in which case true is returned
    if (strcmp(aWord, "DONE") == 0) {
        printf("Stopping with an incomplete word ladder...");
        return true;
    }
    // checking if the entered word does not have the correct length; false is returned
    if (strlen(aWord) != wordLen) {
        printf("Entered word does NOT have the correct length. Try again...");
        return false;
    }
    // checking if the entered word is not in the words array; false is returned
    if (linSearchForWord(words, numWords, aWord) == -99) {
        printf("Entered word NOT in dictionary. Try again...");
        return false;
    }
    // checking if the ladder contains a previous word
    if (ladderHeight >= 1) {
        char* prevWord = ladder[ladderHeight - 1]; // capturing the last word in the ladder array
        int numCharDifferences = strCmpCnt(prevWord, aWord);
        // checking if the entered word is not a one character difference from the previous word; false is returned
        if (numCharDifferences != 1) {
            printf("Entered word is NOT a one-character change from the previous word. Try again...");
            return false;
        }
    }
    printf("Entered word is valid and will be added to the word ladder.\n");
    return true; // true is returned if the entered word is valid
}


bool isLadderComplete(char** ladderWords, int height, char* finalWord) {
//-------------------------------------------------------------------
// TODO - Task VII: write the isLadderComplete() Boolean function,
//      which should simply check for a completed word ladder, i.e.
//      return true if the final word in [ladderWords] is a match to
//      [finalWord]; otherwise, return false; the number of words in
//      the word ladder is [height]
//-------------------------------------------------------------------
    // checking if the last word in the ladderWords array is equal to the finalWord string; if yes, true is returned
    
    if (strcmp(ladderWords[height - 1], finalWord) == 0) {
        return true;
    }
    // if the two strings are not equal, false is returned
    //else {
        //return false;
    //}
    return false;
}


void displayIncompleteLadder(char** ladderWords, int height) {
//-------------------------------------------------------------------
// TODO - Task IX: write the displayIncompleteLadder() function,
//      which should display the C-strings in the [ladderWords]
//      array with the first word at the bottom of the ladder, and
//      each successive C-string one rung higher on the ladder.
//      The ladder [height] is the number of words it contains.
//      To signify the ladder as incomplete, display three lines of
//      "..." at the top of the ladder. The ladder must be displayed
//      with an indentation of two whitespaces on every line;
//      Ex: if the start word is "data" and final word is "code" and
//          the incomplete ladder is data->date->gate->gave, then the
//          output display should be as follows (where the quotation
//          marks are NOT a part of the actual display):
//              "  ..."
//              "  ..."
//              "  ..."
//              "  gave"
//              "  gate"
//              "  date"
//              "  data"
//-------------------------------------------------------------------

    for (int i = height - 1; i >= 0; i--) {
        printf(" %s\n", ladderWords[i]);

    }



}


void displayCompleteLadder(char** ladderWords, int height) {
//-------------------------------------------------------------------
// TODO - Task X: write the displayCompleteLadder() function,
//      which should display the C-strings in the [ladderWords] array
//      with the first word at the bottom of the ladder, and each
//      successive C-string one rung higher on the ladder.
//      The ladder [height] is the number of words it contains.
//      In between each ladder rung, display the symbol '^' to
//      signify the character that changes between the two rungs of
//      the ladder. The ladder should be displayed with an indentation
//      of two whitespaces to the left of every word;
//
//      HINT: call strCmpInd() here
//
//      Ex: if the start word is "data" and final word is "code"
//          then the output display for a complete ladder should be
//          as follows (where the quotation marks are NOT a part of
//          the actual display):
//              "  code"
//              "    ^ "
//              "  cove"
//              "   ^  "
//              "  cave"
//              "  ^   "
//              "  gave"
//              "    ^ "
//              "  gate"
//              "  ^   "
//              "  date"
//              "     ^"
//              "  data"
//-------------------------------------------------------------------
    
    for (int i = height - 1; i >= 0; --i) {
        printf(" %s\n", ladderWords[i]);

        if (i > 0) {    
        
            int indexOfDiff = strCmpInd(ladderWords[i], ladderWords[i + 1]);
        
            char* cursorString = malloc((strlen(ladderWords[i]) + 1) * sizeof(char));
        
            int len = strlen(ladderWords[i]);
            for (int j = 0; j < len; j++) {
                cursorString[j] = ' ';
            }
            cursorString[len] = '\0';
            cursorString[indexOfDiff] = '!';
            printf("  %s\n", cursorString);
            free(cursorString);
        }
    }

}


int main(int argc, char* argv[]) {

    printf("\nProcessing command-line arguments...\n");

    int wordLen = 0;
    int maxLadder = 1;
    char dict[100] = "notAfile";
    char startWord[30] = "notAword";
    char finalWord[30] = "notValid";



    printf("Interactively resetting invalid parameters:\n");

    // set word length using interactive user-input if necessary
    int numInputs = 1;
    while (numInputs > 0 && (wordLen < 2 || wordLen > 20)) {
        printf("Invalid word length = %d\n", wordLen);
        printf("Enter a valid word length (must be 2-20): ");
        numInputs = scanf("%d",&wordLen);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    // set max ladder height using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && maxLadder < 2) {
        printf("Invalid max ladder height = %d\n", maxLadder);
        printf("Enter a valid max ladder height (must be >1): ");
        numInputs = scanf("%d",&maxLadder);
        printf("\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    FILE* fileTry = fopen(dict,"r");
    numInputs = 1;
    while (numInputs > 0 && fileTry == NULL) {
        printf("Enter filename for dictionary: ");
        numInputs = scanf("%s", dict);
        printf("\n");

        fileTry = fopen(dict,"r");

        if (fileTry == NULL) {
            printf("Dictionary file is not found. Try again...");
        }


    }
    fclose(fileTry);
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }
    
    // build the [words] array, a heap-allocated array of C-strings
    // where the words are a read-in from the dictionary file
    // and only those words of the desired length [wordLen]

    int numWords = 0; // initially, no words in the array
    int maxWords = 4; // initially, capacity = 4

    char** words = (char**)malloc(maxWords*sizeof(char*));

    FILE *inFile = NULL;

    inFile = fopen(dict, "r"); // opening the dictionary file
    char fileWord[30];
    

    if (inFile == NULL) {
        printf("Could not open dictionary.\n");
        return -1;
    }
    // while loop runs as long as a string is succesfully read
    while (fscanf(inFile, "%s", fileWord) == 1) {
        // checking if the word has the correct length
        if (strlen(fileWord) == wordLen) {
            appendWord(&words, &numWords, &maxWords, fileWord); // adding the word to the words array
        }
    }
    fclose(inFile); // closing the dictionary file

    printf("The dictionary contains %d words of length %d.\n",numWords,wordLen);
    printf("Max size of the dynamic words array is %d.\n",maxWords);
    printf("\n");

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("Dictionary %s contains insufficient %d-letter words...\n",dict,wordLen);
        printf("Terminating program...\n");
        return -1;
    }

    // resetting start word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,startWord) < 0) {
        printf("Enter a valid start word: ");
        numInputs = scanf("%s", startWord);
        printf("\n");

        if (linSearchForWord(words, numWords, startWord) >= 0) {
            break;
        }

        printf("Start word is not valid. Try again...\n");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }

    // resetting final word using interactive user-input if necessary
    numInputs = 1;
    while (numInputs > 0 && linSearchForWord(words,numWords,finalWord) < 0 ) {
        printf("Enter a valid final word: ");
        numInputs = scanf("%s", finalWord);
        printf("\n");

        if (linSearchForWord(words, numWords, finalWord) >= 0) {
            break;
        }

        printf("Final word is not valid. Try again...");
    }
    if (numInputs == 0) {
        printf("Invalid input. Cannot set program parameters. Terminating program...\n");
        return 0;
    }


    //printf("\nWelcome to the CS 211 Word Ladder Builder!\n");
    printf("\nWORD LADDER BUILDER\n");
    printf("\n");

    printf("Your goal is to make a word ladder between two ");
    printf("%d-letter words: \n  %s -> %s\n\n",wordLen, startWord,finalWord);
    
    // Allocating the word ladder for the maximum allowed height
    char** ladder = (char**)malloc(maxLadder*sizeof(char*));

    int ladderHeight = 0; // initially, the ladder is empty
    
    // add the start word to the ladder, i.e. the "bottom rung"
    appendWord(&ladder,&ladderHeight,&maxLadder,startWord);
    
    char aWord[30] = "XYZ";
    printf("\n");

    // Let the user build a word ladder interactively & iteratively.
    // First, check that ladder is not too long AND not complete.
    //-------------------------------------------------------------------
    // TODO - Task VIII: modify the while loop condition such that the
    //          word ladder building process continues only if ALL of
    //          the following conditions are met:
    //              1. the ladder still has at least one available rung
    //                 before reaching the maximum allowed height
    //              2. the user is NOT attempting to stop the word ladder
    //                 building process, which occurs if the entered word
    //                 [aWord] from the last iteration is "DONE"
    //              3. the ladder is still incomplete; i.e. the last word
    //                 added to ladder is not the final word;
    //                 note: this should use a call to isLadderComplete()
    //-------------------------------------------------------------------
    // loop runs as long as the ladder has at least one available rung, the user did not enter DONE, and the ladder is not complete
    //while ((ladderHeight < maxLadder) && (strcmp(aWord, "DONE") != 0) && ((!isLadderComplete(ladder, ladderHeight, aWord)))) {
    while (ladderHeight < maxLadder && strcmp(aWord, "DONE") != 0 && !isLadderComplete(ladder, ladderHeight, finalWord)) {
        printf("The goal is to reach the final word: %s\n",finalWord);
        printf("The ladder is currently: \n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Current ladder height: %d\n",ladderHeight);
        printf("Maximum ladder height: %d\n",maxLadder);
        printf("Enter the next word (or DONE to stop): ");
        scanf("%s",aWord);
        printf("\n");

        // Make sure the entered word is valid for the next ladder rung;
        // if not, repeatedly allow user to enter another word until one is valid
        while (!checkForValidWord(words, numWords, wordLen, ladder, ladderHeight, aWord)) {
            printf("Enter another word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");
        }

        // add the entered word to the ladder (unless it is "DONE")
        if (strcmp(aWord,"DONE") != 0) {
            appendWord(&ladder,&ladderHeight,&maxLadder,aWord);
        }
        printf("\n");

    }
    

    // Check if the built word ladder is complete and
    // display the word ladder appropriately.
    if (isLadderComplete(ladder, ladderHeight, finalWord)) {
        printf("Word Ladder complete!\n");
        displayCompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you find a shorter Word Ladder next time??? \n");
    } else {
        if (ladderHeight == maxLadder) printf("The Word Ladder reached the maximum height.\n");
        printf("The final Word Ladder is incomplete:\n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you complete the Word Ladder next time??? \n");
    }
    
    
    //-------------------------------------------------------------------
    // TODO - Task XI: free all heap-allocated memory to avoid potential
    //                 memory leaks. Since the word length for the word
    //                 ladder is variable (i.e. set by a command-line
    //                 argument or interactive user-input) any array
    //                 whose size depends on the word length should be
    //                 dynamically heap-allocated, and thus, must be
    //                 tracked and freed before program termination
    //-------------------------------------------------------------------


    return 0;
}

This is a command-line program that builds a word ladder between two words, where each step changes only one character. The user interactively enters words to form a 
valid sequence from a start word to a final word.

The program is written in C using standard libraries and reads a dictionary file, filtering words based on a user-specified length. It uses dynamic memory with heap
allocation and resizing to store words efficiently.

User input is validated by checking that each word has the correct length, exists in the dictionary, and differs by exactly one character from the previous word. The
program also includes functions to compare words by counting differences and finding where they first differ, and uses a linear search to verify that words exist in the
dictionary.


Sample Example:

Going from "head" to "tail" 

head -> heal -> teal -> tell -> tall -> tail

<img width="259" height="684" alt="Screenshot 2026-04-19 at 9 28 30 PM" src="https://github.com/user-attachments/assets/7df32610-7feb-46c9-84d6-ef61598eaafd" />


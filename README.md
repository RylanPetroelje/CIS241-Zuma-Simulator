# CIS241 Zuma/Clearing Orbs in C
## Instructions/Overview
This is a project given to me in CIS 241: System-Level Programming and Utilities. The program itself uses getline to read in a string of letters, for example `bbrrggrbr`. It then reads a second line formatted as so "%c %d", for example `g 5`, where the character is a letter, representing an orb of a certain color,  and the double is an integer representing the index that the previous character will be inserted. Imagining that each character represents a different colored orb, following the rules of [Zuma](https://en.wikipedia.org/wiki/Zuma_(video_game)), once 3 consecutive orbs are the same color, they will disappear. If that disappearance results in the surrounding orbs making another pattern of at least 3 consecutive orbs being the same color, then those orbs pop as well. The process continues until no more orbs can be popped. The program then returns the length of the final string. Using our example from before, if we were to give it the string `bbrrggrbr` in the first line, and `g 5` in the second, the character `g` would be inserted at the 5th index, creating `bbrrgggrbr`. Since we have a group of three g's, we can pop those from the list, creating `bbrrrbr`. Notice how the r's that were originally separated by g's are now together, so we pop those too. We are left with `bbbr`, so we pop the b's and finally just have `r`, so the program returns `1`.
## C Concepts Applied
+ Dynamic Memory Allocation and Freeing
  - Space for each string of characters is allocated on the heap and free-d after the program is finished to avoid memory leaks.
  - Dynamically allocates more memory in case required memory exceeds expectations.
+ Structures
  - Final zuma structure is a stack that stores nodes. Each node has two variables, the color, and a run count.
  - As the program reads the char string, the stack is updated. For the substring `rrbbgg` the stack would read `r:2,b:2,g:2`. If the next char in that string is `g`, the most recent node would become  `g:3`, and the subsequently get popped from the stack, making the new "most recent" node  `b:2`.
  - Once the whole string is finished, the length is just the sum of all the run counts.
## Run Instructions
1. Fork this repository.
2. Compile the main.c in your terminal. Make sure you have C Extensions downloaded.
3. Run ./a.out.
4. Follow the instructions given by the program.

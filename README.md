# Word-Prediction
Word prediction using trie tree
Each word of a English language is made using 26 alphabets. Trie data structure uses this property as a base for storing words. A word can be started (first character of a word) from either a, either b, either c .... or either z.

So there are total 26 possibilities, from which first character of a word will be started.Second character can also be started from either a, either b, either c ... or either z. 

So there are total 26 possibilities, from which second character of a word will be started same for third character and so on. There is example below how it looks: 
![image](https://user-images.githubusercontent.com/97192866/171907998-6bcc9510-91c2-48f4-9fc8-a0c3a0790ec8.png)

In my case, trie node contains:
- array of 26 Node pointers
- pointer to parent node
- word
- number of repetitions for word

The program works in that way when you type some word, it returns 3 words with the highest frequency that match the entered word, One Word match another if the word is prefix of another. But not only that, there is a maximum of three errors that are included if the user accidentally press a letter next to the desired letter. For example if you wanted letter 'J' and accidentally press the letter 'K' it will check all letters around:

![image](https://user-images.githubusercontent.com/97192866/171915045-fca528c2-9b4e-497d-b341-a21e7fb4ad02.png)

There is an example if you tye word 'booj' instead of 'book'


https://user-images.githubusercontent.com/97192866/171925672-d022ab12-ab59-44a2-aab4-31538e9d5671.mp4


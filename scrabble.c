/*  Kevin Ramos
    COP3502
    Scrabble Project
*/

#include <stdio.h>
#include <string.h>
#define NUMTILES 7
#define WORDLENGTH 8

//  Function prototypes
int wordverify(char* word, char* tiles);
int scoring(char* word, int* letmult, int* wordmults, const int* TILESCORES);

int main()
{
    const int TILESCORES[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    char dictionary[100][8];
    char tiles[NUMTILES];
    char word[WORDLENGTH];
    
    // Scoring variables
    int letmult[NUMTILES];
    int wordmults[NUMTILES];
    int wordscore;
    
    int i, j, c, n;
    
    printf("Please enter the number of input cases.\n");
    scanf("%d", &c);
    
    //  Case loop. Outputs max score per case
    for(i = 0; i < c; i++)
    {
        int bestscore = 0;
        //  Prompt the user for number of words in the dictionary
        printf("Enter the number of words in our dictionary.\n");
        scanf("%d", &n);
        
        // Prompt the user for each word
        for(j = 0; j < n; j++)
        {
            printf("Enter word %d:\n", j+1);
            scanf("%s", dictionary[j]);
        }
        
        //  Prompt the user for their tiles
        printf("Enter your tiles:\n");
        scanf("%s", tiles);

        //  Prompt the user for the letter multiplier on each space
        //  Store the value in a letter multiplier array
        printf("Enter the letter multiplier space values:\n");
        scanf("%d %d %d %d %d %d %d", &letmult[0],&letmult[1], &letmult[2], &letmult[3], &letmult[4], &letmult[5], &letmult[6]);
        
        //  Prompt the user for the word multiplier on each space
        //  Store the value in a wordmultiplier array
        printf("Enter the word multiplier space values:\n");
        scanf("%d %d %d %d %d %d %d", &wordmults[0],&wordmults[1], &wordmults[2], &wordmults[3], &wordmults[4], &wordmults[5], &wordmults[6]);
        
        //  Use the wordverify and scoring functions to determine what the best score possible is
        for(int l = 0; l < n; l++)
        {
            strcpy(word, dictionary[l]);
            
            int z = wordverify(word, tiles);
            
            if(z == 1)
            {
                //  call scoring function
                wordscore = scoring(word, letmult, wordmults, TILESCORES);
                if(wordscore >= bestscore)
                {
                    bestscore = wordscore;
                }
            }
            else;
        }
        printf("%d\n", bestscore);
    }
    return 0;
}

//  Pre-condition: This function takes in a word in the dictionary and the user's tiles
//  Post-condtion: Returns 1 if the word can be assembled from the user's tiles; 0 otherwise.

int wordverify(char* word, char* tiles)
{
    int i = 0, j = 0, k = 0;
    char s[WORDLENGTH], p[WORDLENGTH];
    char c;
    int intiles = 0;
    int count1, count2;

    strcpy(s, word);
    strcpy(p, tiles);

    for(i = 0; i < strlen(word);i++)
    {
        c = s[i];
        
        count1 = 1;
        count2 = 0;
      
        for(j = i+1; j < strlen(word); j++)
        {
            if(c == s[j])
            {
                count1++;
            }
        }
        
        for(k = 0; k < NUMTILES; k++)
        {
            if(c == tiles[k])
            {
                count2++;
            }
        }
        
        if(count1 <= count2)
        {
            intiles = 1;
        }
        else
        {
            intiles = 0;
            break;
        }
    }

    return intiles;
}

//  Scoring Function
//  Pre-condition: Takes the word, letter multipliers, max word multiplier and TILESCORES
//  Post-condition: Multiplies each letter to its multiplier, multiplies by the word multiplier and returns total score
int scoring(char* word, int* letmult, int* wordmults, const int* TILESCORES)
{
    //  Get the value of each letter, respectively. Multiply this by it's letter multiplier. Sum as you go.
    //  Once we've finished and reached a final sum, determine and multiply the letter by the maxwordmult and return the word score
    
    int i = 0;
    int m = 0, n = 0;
    char let = "NULL";
    int letvalue = 0;
    int maxwordmult = 1;
    int sum = 0;
    
    //  Find the max word multiplier
    for(m = 0; m < strlen(word); m++)
    {
        for(n = m+1; n < strlen(word); n++)
        {
            if(wordmults[m] < wordmults[n])
            {
                maxwordmult = wordmults[n];
            }
        }
    }
    
    //  Get value of each letter, multiply it by its letmultiplier
    for(i = 0; i < strlen(word); i++)
    {
        let = word[i];
        letvalue = TILESCORES[let - 'A'];
        sum += (letvalue*letmult[i]);
    }
    
    sum *= maxwordmult;
    return sum;
}


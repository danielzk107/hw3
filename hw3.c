#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#define TXT 1024
#define WORD 30

int GetGematriaOfLetter(char let){
    if (!isalpha(let)) return 0;
    return tolower(let) - 'a' + 1;
}
int GetGematriaOfWord(char word[WORD], int sizeofword){
    int output=0;
    for (int i = 0; i < sizeofword; i++)
    {
    	output+= GetGematriaOfLetter(word[i]);
    }
    return output;
}
void PrintAllGematria(char word[WORD], char text[TXT], int sizeoftext, int sizeofword){
    int gematria= GetGematriaOfWord(word, sizeofword); // Get gem. of word
    int foundfirst=0; // For wave printing
    printf("Gematria Sequences: ");
    for(int i=0; i<sizeoftext;i++){ // We are checking combination with a spesific char each time.
        if (!isalpha(text[i])) // Ignore characters unalphabetic chars
		continue;
        
        int sum= 0;
        int letGem;
        int ends = i;
        for(; ends < sizeoftext && sum < gematria; ends++){ // Go through all other letters and check for sum.
        	letGem = GetGematriaOfLetter(text[ends]);
        	if (sum + letGem > gematria) break;
        	sum += letGem;
        } 
        if(sum==gematria){ // Print if we found the right sum.
            if(foundfirst>0)
                printf("~");
            foundfirst=1;
            for (int k = i; k < ends; k++) // Print word in range
            {
                printf("%c", text[k]);
            }
        }
    }
}
char* GetAtbashOfWord(char word[WORD]){
    for (int i = 0; i < WORD; i++)
    {
        if(word[i]>='A' &&word[i]<='Z'){
            word[i]= 'Z'- word[i]+'A';
        }
        else if(word[i]>='a' &&word[i]<='z'){
            word[i]= 'z'- word[i]+'a';
        }
    }
    return word;
}

void Atbash(char word[WORD], char text[TXT], int sizeoftext, int sizeofword){
    printf("Atbash Sequences: ");
    int foundfirst=0;
    char atbashword[sizeofword+1];
    memset(atbashword, 0, sizeofword+1);
    for (int i = 0; i < sizeofword; i++)
    {
        if(word[i]>='A' &&word[i]<='Z'){
            atbashword[i]= 'Z'- word[i]+'A';
        }
        else if(word[i]>='a' &&word[i]<='z'){
            atbashword[i]= 'z'- word[i]+'a';
        }
    }
    for (int i = 0; i <= sizeoftext-sizeofword; i++)
    {
        int condition=1;
        int counter=0;
        for (int j = i; j < sizeofword+i && j< sizeoftext; j++)//checks for the regular order:
        {
            if(text[j]!=' ' && text[j]!=atbashword[counter]){
                // printf("The condition is false\n");
                condition=0;
                break;
            }
            counter++;
        }
        if(condition){
            if(foundfirst>0){
                printf("~");
            }
            foundfirst=1;
            for (int j = i; j < i+sizeofword && j<sizeoftext; j++)
            {
                // printf("j is %d and i is %d\n", j, i);
                printf("%c", text[j]);
            }
        }//reset variables for the next traversal:
        condition=1;
        counter=sizeofword-1;
        for (int j = i; j < sizeofword+i &&j< sizeoftext; j++)//checks for the reverse order:
        {
            if(text[j]!=' ' && text[j]!=atbashword[counter]){
                // printf("The condition is false for the reverse traversal\n");
                condition=0;
                break;
            }
            counter--;
        }
        if(condition){
            if(foundfirst>0){
                printf("~");
            }
            foundfirst=1;
            for (int j = i; j < i+sizeofword &&j<sizeoftext; j++)
            {
                printf("%c", text[j]);
            }
        }
    }
    printf("\n");
}

int IsIn(char word[WORD], char letter){
    for(int i=0; i<WORD;i++){
        if(word[i]==letter){
            // printf("The letter %c is at index %d\n", letter, i);
            return i;
        }
    }
    // printf("The letter %c is not in word %s\n", letter, word);
    return -1;
}

void SetArray(char original[WORD], char output[WORD], int wordsize){
    for(int i=0; i<wordsize;i++){
        output[i]= original[i];
    }
}

void NewPrintAnagrams(char word[WORD], char text[TXT], int textsize, int wordsize){
    printf("Anagram Sequences: ");
    int foundfirst=0;
    for(int i=0; i<textsize;i++){
        char temp[WORD];
        SetArray(word, temp, wordsize);
        char op[TXT];
        memset(op, 0, TXT);
        int pos=0;
        int tempcounter=wordsize;
        if(text[i]==' '){
            continue;
        }
        for(int j=i; j<textsize;j++){
            if(tempcounter<=0){
                break;
            }
            if(text[j]==' '){
                if(pos!=0){
                    op[pos]=' ';
                    pos++;
                }
                continue;
            }
            int place= IsIn(temp, text[j]);
            if(place==-1){
                break;
            }
            op[pos]= temp[place];
            pos++;
            temp[place]='\0';
            tempcounter--;
        }
        if(tempcounter<=0){
            if(foundfirst>0){
                printf("~");
            }
            foundfirst=1;
            printf("%s", op);
        }
    }
}

int main(){
    char text[TXT];
    char firstword[WORD];
    int textsize=0;
    int firstwordsize=0;
    char c;
    memset(text, 0, TXT);
    while(firstwordsize<WORD && c!='~' && c!=' ' && c!='\t' && c!='\n'){
        c=getchar(); 
        if(c!='~'&& c!=' ' && c!='\t' && c!='\n'){
            firstword[firstwordsize]=c;
            firstwordsize++;
        }
    }
    while(textsize<TXT && c!='~'){
        c= getchar();
        if(c==EOF){
            break;
        }
        if(c!='~'){
            text[textsize]=c;
            textsize++;
        }
    }
    PrintAllGematria(firstword, text, textsize, firstwordsize);
    printf("\n"); 
    Atbash(firstword, text, textsize, firstwordsize);
    NewPrintAnagrams(firstword, text, textsize, firstwordsize);
}

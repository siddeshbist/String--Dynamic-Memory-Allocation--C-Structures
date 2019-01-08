//Siddesh Bist
//LO5
//400072076
//Lab 3
//Q1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *my_strcat(const char* const str1,const char*const str2);
int main(void)
{
    const char a[]="Hello";
    const char b[]="World     ";
    printf("%s\n",my_strcat(a,b));//function call to concatenate
    return 0;

}
char *my_strcat(const char* const str1,const char*const str2)
    {
        char*c=NULL; //initialize pointer that will store memory of new array with concatenated words
        c= (char*)malloc((strlen(str1)+strlen(str2))*sizeof(char)+4); //the memory block will be the sum of the length of each string and the null character of 4 bytes
        int i,j;
        for(i=0;str1[i]!='\0';i++)
        {
            c[i]=str1[i];//adds each character of the first string to the new array
        }
        for(j=0;str2[j]!='\0';j++)
        {
            c[i]=str2[j]; //i continues on from the for loop before and j refers to the position of the characters in the new string
            i++;
        }
        c[i]=0;//add NuLL character at the end
        return c;
    }




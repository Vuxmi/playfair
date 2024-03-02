#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
char matrix[5][5]={0};
int c[26]={0};
int value1[2];
int value2[2];
void creatematrix(char* key)
{
      int row=0,col=0;
      for(int i=0;key[i]!='\0';i++)
      {
        if(c[key[i]-'a']==0)
        {
            matrix[row][col]=key[i];
            col++;
            if(col>4)
            {
                row++;
                col=0;
            }
        }
        if(key[i]=='i'||key[i]=='j')
        {
            c['i'-'a']++;
            c['j'-'a']++;
        }
        else
        {
            c[key[i]-'a']++;
        }
      }
      for(int i=0;i<26;i++)
      {
        if(c[i]==0 && row<5 && col<5 && i!=('j'-'a'))
        {
            matrix[row][col]=i+'a';
            col++;
            if(col>4)
            {
                col=0;
                row++;
            }
        }
      }
}
void findchar(char c1,int* a)
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(c1==matrix[i][j] || (c1=='j'&&matrix[i][j]=='i'))
            {
                a[0]=i;
                a[1]=j;
                return;
            }
        }
    }
}
void encrypt(char* text,char* result)
{
    int i=0;
    int row,col;
    while(text[i]!='\0')
    {   
        findchar(text[i],value1);
        findchar(text[i+1],value2);
        if(value1[1]==value2[1])
        {
            col=value1[1];
            if(value1[0]+1>4)
              row=0;
            else
             row=value1[0]+1;
            result[i]=matrix[row][col];

            if(value2[0]+1>4)
              row=0;
            else
              row=value2[0]+1;
            result[i+1]=matrix[row][col];
        }
        else if(value1[0]==value2[0])
        {
            row=value1[0];
            if(value1[1]+1>4)
              col=0;
            else
             col=value1[1]+1;
            result[i]=matrix[row][col];

            if(value2[1]+1>4)
              col=0;
            else
              col=value2[1]+1;
            result[i+1]=matrix[row][col];
        }
        else
        {
            row=value1[0];
            col=value2[1];
            result[i]=matrix[row][col];
            row=value2[0];
            col=value1[1];
            result[i+1]=matrix[row][col];
        }
      i=i+2;
    }
}

int main()
{
    char key[]="nhungiot";
    creatematrix(key);
    int n;
    printf("Enter number of character: ");
    scanf("%d",&n);
    char text[n];
    for(int i=0;i<n;i++)
    {
       printf("\nEnter: ");
       getchar();
       text[i]=getchar();
    }
    char modifytext[n+2];
    
    if(n%2==1)
    {
        modifytext[n]='x';
        modifytext[n+1]='\0';
    }
    else
    modifytext[n]='\0';
    for(int i=0;i<n-1;i=i+2)
    {
        modifytext[i]=text[i];
        if(text[i+1]==text[i])
        {
            modifytext[i+1]='x';
        }
        else if((text[i+1]=='i'&& text[i]=='j') || (text[i+1]=='j'&&text[i]=='i'))
        {
            modifytext[i+1]='x';
        }
        else
        {
            modifytext[i+1]=text[i+1];
        }
    }
    if(text[n-1]!=text[n-2])
    modifytext[n-1]=text[n-1];
    else
    modifytext[n-1]='x';
    char result[n+2];
    result[n+1]='\0';
    printf("%s\n",modifytext);
    encrypt(modifytext,result);
    for(int i=0;result[i]!='\0';i++)
    {
        printf("%c",result[i]);
    }
    printf("\n");
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        printf("%c ",matrix[i][j]);
        printf("\n");
    }
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define mx 50
/*Abhijit Prasad Mallick 
20252501001*/
char opstck[mx];
int top=-1;
void push(char c) 
{ 
    opstck[++top] = c; 
}
char pop() 
{ 
    return opstck[top--]; 
}
char peek() 
{ 
    return opstck[top]; 
}
int precedence(char c) 
{
    if(c=='+' || c=='-') 
        return 1;
    if(c=='*' || c=='/') 
        return 2;
    return 0;
}
void reverseAndSwap(char infx[],char rev[]) 
{
    int i,j=0;
    for(i=strlen(infx)-1;i>=0;i--) 
    {
        if(infx[i]=='(') 
            rev[j++]=')';
        else if(infx[i]==')') 
            rev[j++]='(';
        else rev[j++]=infx[i];
    }
    rev[j]='\0';
}
void infixToPostfix(char infx[],char pofx[]) 
{
    int i,k=0;
    char ch;
    printf("\nCharacter       Action          Output  Stack\n");
    printf("-------------------------------------------------\n");
    for(i=0;infx[i];i++) 
    {
        ch=infx[i];
        if(isdigit(ch)) 
        {
            pofx[k++]=ch;
            pofx[k]='\0';
            printf("%c       Added to output %s       [", ch, pofx);
        }
        else if(ch=='(') 
        {
            push(ch);
            printf("%c       Pushed to stack %s       [", ch, pofx);
        }
        else if(ch==')') 
        {
            while(peek()!='(') 
            {
                pofx[k++]=pop();
                pofx[k]='\0';
            }
            pop(); 
            printf("%c       Pop until '('   %s    [", ch, pofx);
        }
        else 
        {
            while(top!=-1 && precedence(peek())>=precedence(ch)) 
            {
                pofx[k++]=pop();
                pofx[k]='\0';
                printf("%c       Pop from stack  %s     []\n", ch, pofx);
            }
            push(ch);
            printf("%c       Pushed to stack %s       [", ch, pofx);
        }
        for(int s=0;s<=top;s++) 
        {
            printf("%c",opstck[s]);
            if(s<top) 
                printf(", ");
        }
        printf("]\n");
    }
    while(top!=-1) 
    {
        pofx[k++]=pop();
        pofx[k]='\0';
        printf("        Pop remaining   %s   []\n", pofx);
    }
}
void reverse(char s[]) 
{
    int i;
    char t;
    for(i=0;i<strlen(s)/2;i++) 
    {
        t=s[i];
        s[i]=s[strlen(s)-i-1];
        s[strlen(s)-i-1]=t;
    }
}
int evaluatePrefix(char prefix[]) 
{
    int stack[mx];
    int top2=-1;
    printf("\nPrefix Evaluation Steps\n");
    printf("-------------------------------------------------\n");
    for(int i=strlen(prefix)-1;i>=0;i--) 
    {
        char ch=prefix[i];
        if(isdigit(ch)) 
        {
            stack[++top2]=ch - '0';
            printf("Pushed operand: %d\n",ch-'0');
        }
        else 
        {
            int a=stack[top2--];
            int b=stack[top2--];
            int r;
            printf("Processing operator: %c\n", ch);
            printf("  Popped %d and %d\n",a,b);
            if(ch=='+') 
                r=a+b;
            else if(ch=='-') 
                r=a-b;
            else if(ch=='*') 
                r=a*b;
            else 
                r=a/b;
            printf("  Calculated: %d %c %d = %d\n",a,ch,b,r);
            stack[++top2]=r;
            printf("  Pushed result: %d\n", r);
        }
        printf("Stack: [");
        for (int j=0;j<=top2;j++) 
        {
            printf("%d", stack[j]);
            if (j < top2) printf(", ");
        }
        printf("]\n\n");
    }
    return stack[top2];
}
int main() {
    char infx[mx],rev[mx],pofx[mx],prefix[mx];
    scanf("%s",infx);
    printf("Step 1: Reverse and Swap Parentheses\n");
    printf("Original infix: %s\n",infx);
    reverseAndSwap(infx,rev);
    printf("Reversed and modified infix: %s\n",rev);
    printf("\nStep 2: Convert Reversed Infix to Postfix\n");
    infixToPostfix(rev,pofx);
    printf("Postfix of reversed infIx: %s\n",pofx);
    strcpy(prefix,pofx);
    reverse(prefix);
    printf("\nStep 3: Final Prefix Notation\n");
    printf("Final Prefix Notation: %s\n",prefix);
    printf("-------------------------------------------------\n");
    printf("Given infix Notation: %s\n",infx);
    printf("Prefix Notation: %s\n",prefix);
    int res=evaluatePrefix(prefix);
    printf("\nFinal Prefix Evaluation result: %d\n",res);
    return 0;
}
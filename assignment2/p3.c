#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define mx 30
/*Abhijit Prasad Mallick 
20252501001*/
char opstck[mx];
int top=-1;
int valstck[mx];
int valTop=-1;
void push(char c) 
{
    opstck[++top]=c;
}
char pop() 
{
    return opstck[top--];
}
int pre(char c) 
{
    if(c=='+' || c=='-') 
        return 1;
    if(c=='*' || c=='/') 
        return 2;
    return 0;
}
void prints() 
{
    for(int i=0;i<=top;i++) 
    {
        printf("%c",opstck[i]);
        if(i!=top) 
            printf(" ");
    }
}
int app(int a,int b,char op) 
{
    if(op=='+') 
        return a + b;
    if(op=='-') 
        return a - b;
    if(op=='*') 
        return a * b;
    if(op=='/') 
        return a / b;
    return 0;
}
int main() 
{
    char infx[mx],pofx[mx];
    int k=0;
    scanf("%s",infx);
    printf("Step-by-Step Processing:\n");
    printf("Scanned         Stack           Output\n");
    printf("-------------------------------------------------\n");
    for(int i=0;i<strlen(infx);i++) 
    {
        char ch=infx[i];
        printf("Scanned: %-6c Stack: ",ch);
        if(isdigit(ch)) 
            pofx[k++]=ch;
        else if(ch=='(') 
            push(ch);
        else if(ch==')') 
        {
            while(top!=-1 && opstck[top]!='(')
                pofx[k++]=pop();
            pop();
        }
        else 
        {
            while(top!=-1 && pre(opstck[top])>=pre(ch))
                pofx[k++]=pop();
            push(ch);
        }
        prints();
        printf("        Output: ");
        if(k==0)
            printf(" Z│");
        else
            for(int j=0;j<k;j++)
                printf("%c",pofx[j]);
        printf("\n");
    }
    while(top!=-1)
        pofx[k++]=pop();
    pofx[k]='\0';
    printf("\nFinal Postfix Expression: %s\n\n", pofx);
    printf("Given Infix:%s\n", infx);
    printf("Conversion Postfix: %s\n", pofx);
    printf("Postfix evaluation steps:\n");
    printf("-------------------------------------------------\n");
    for(int i=0;i<strlen(pofx);i++) 
    {
        char ch=pofx[i];
        if(isdigit(ch)) 
        {
            valstck[++valTop]=ch-'0';
            printf("Pushed operand: %d\n",ch-'0');
        } 
        else 
        {
            int b=valstck[valTop--];
            int a=valstck[valTop--];
            int res=app(a,b,ch);
            printf("Processing operator: %c\n",ch);
            printf("  Popped %d and %d\n",a,b);
            printf("  Calculated: %d %c %d = %d\n",a,ch,b,res);
            printf("  Pushed result: %d\n",res);
            valstck[++valTop]=res;
        }
        printf("Stack: [");
        for(int j=0;j<=valTop;j++) 
        {
            printf("%d",valstck[j]);
            if (j!=valTop) 
                printf(", ");
        }
        printf("]\n\n");
    }
    printf("Final Postfix evaluation result: %d\n",valstck[valTop]);
    return 0;
}
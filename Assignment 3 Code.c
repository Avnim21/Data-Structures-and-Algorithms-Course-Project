#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
struct StackNode
{
    int val;
    struct StackNode* prev;
};
struct Stack
{
    struct StackNode* top;
};
void push(int x,struct Stack *S)
{
    struct StackNode* temp = (struct StackNode*)malloc(sizeof(struct StackNode));
    (*temp).val=x;
    (*temp).prev=(*S).top;
    (*S).top=temp; 
}
int pop(struct Stack *S)
{
    struct StackNode* temp;
    temp=(*S).top;
    (*S).top=(*((*S).top)).prev;
    return (*temp).val;
}
int evaluate(int o1,int o2,int x)
{
    int y=0;
    switch(x)
    {
        case '+':y=o1+o2;break;
        case '-':y=o2-o1;break;
        case '*':y=o1*o2;break;
        case '/':y=o2/o1;break;
        case '^':y=pow(o2,o1);break;
    }
    return y;
}
int main() 
{
    char c;
    int n,x,operand,num_brackets,priority,associativity;
    int operand1,operand2,y;
    scanf("%d\n",&n);
    struct Stack Opriority,Ostack,Nstack;
    Ostack.top=NULL;
    Nstack.top=NULL;
    Opriority.top=NULL;
    push('$',&Ostack);
    push(0,&Opriority);
    priority=0;
    associativity=0;
    num_brackets=0;
    while(n>0)
    {
        scanf("%c",&c);
        x=c;
        if(x<='9'&&x>='0')
        {
            operand=0;
            while(x<='9'&&x>='0'&&n>0)
            {
                operand=operand*10+x-'0';
                if(n>0)
                {scanf("%c",&c);
                x=c;
                n--;}
            }
            push(operand,&Nstack);
        }
        if(n==0)break;
        if(x=='(')
        {
            num_brackets++;
        }
        else if(x==')')
        {
            num_brackets--;
        }
        else 
        {
            // storing priorities
            switch(x)
            {
                case '+':priority=4*num_brackets+1;associativity=1;break;
                case '-':priority=4*num_brackets+1;associativity=2;break;
                case '*':priority=4*num_brackets+2;associativity=1;break;
                case '/':priority=4*num_brackets+2;associativity=2;break;
                case '^':priority=4*num_brackets+3;associativity=2;break;
            }
            // taking associativity in account
            if(associativity==1)
            {
                while((*(Opriority.top)).val>=priority)
                {
                    operand1=pop(&Nstack);
                    operand2=pop(&Nstack);
                    y=pop(&Ostack);
                    pop(&Opriority);
                    y=evaluate(operand1,operand2,y);
                    push(y,&Nstack);
                }
            }
            else if(associativity==2)
            {
                while((*(Opriority.top)).val>priority)
                {
                    operand1=pop(&Nstack);
                    operand2=pop(&Nstack);
                    y=pop(&Ostack);
                    pop(&Opriority);
                    y=evaluate(operand1,operand2,y);
                    push(y,&Nstack);
                }
            }
            push(x,&Ostack);
            push(priority,&Opriority);
        }
        n--;
    }
    while((*(Ostack.top)).val!='$')
    {
        operand1=pop(&Nstack);
        operand2=pop(&Nstack);
        y=pop(&Ostack);
        pop(&Opriority);
        y=evaluate(operand1,operand2,y);
        push(y,&Nstack);
    }
    x=pop(&Nstack);
    printf("%d",x);
    return 0;
}

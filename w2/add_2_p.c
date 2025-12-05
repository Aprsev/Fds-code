#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

/* Your function will be put here */

Polynomial Add( Polynomial a, Polynomial b ){
    Polynomial sum = (Polynomial)malloc(sizeof(struct Node));
    Polynomial tail = NULL;
    b = b -> Next;
    a = a -> Next;
    while (a != NULL && b != NULL){
        Polynomial newnode = (Polynomial)malloc(sizeof(struct Node));
        // printf("%d %d\n",a -> Exponent,b -> Exponent);
        if (a -> Exponent > b -> Exponent){
            newnode -> Coefficient = a -> Coefficient;
            newnode -> Exponent = a -> Exponent;
            a = a -> Next;
            // printf("%d\n",a -> Coefficient);
        }else if (a -> Exponent < b -> Exponent){
            newnode -> Coefficient = b -> Coefficient;
            newnode -> Exponent = b -> Exponent;
            b = b -> Next;
            // printf("%d\n",b -> Coefficient);
        }else{
            if ((b -> Coefficient + a -> Coefficient )== 0){
                // free(newnode);
                b = b -> Next;
                a = a -> Next;
                continue;
            }else{
                newnode -> Coefficient = b -> Coefficient + a -> Coefficient;
                newnode -> Exponent = b -> Exponent;
                b = b -> Next;
                a = a -> Next;
            }
        }
        
        if (sum -> Next == NULL){
            sum -> Next = newnode;
        }else{
            tail -> Next= newnode;
        }
        tail = newnode;
    }
    while(a != NULL){
        Polynomial newnode = (Polynomial)malloc(sizeof(struct Node));
        newnode -> Coefficient = a -> Coefficient;
        newnode -> Exponent = a -> Exponent;
        a = a -> Next;
        if (sum -> Next == NULL){
            sum -> Next = newnode;
        }else{
            tail -> Next= newnode;
        }
        tail = newnode;
    }
    while(b != NULL){
        Polynomial newnode = (Polynomial)malloc(sizeof(struct Node));
        newnode -> Coefficient = b -> Coefficient;
        newnode -> Exponent = b -> Exponent;
        b = b -> Next;
        if (sum -> Next == NULL){
            sum -> Next = newnode;
        }else{
            tail -> Next= newnode;
        }
        tail = newnode;
    }
    return sum;
}
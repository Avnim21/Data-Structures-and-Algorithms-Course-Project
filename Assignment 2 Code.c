// This is a program used to calculate matrix multiplication of sparse matrices
#include<stdio.h>
#include<stdlib.h>
struct Node//This structure is used for storing value and location of non zero enteries of matrix
{
    int val,row_number,column_number;
    struct Node* next;
};
//Index here refers to row /column
struct Index
{
    struct Index* next;// to link non zero indexes(rows/columns)
    struct Node* index_head;//to store index(row/column) head
};
struct Matrix// This structure is used to store matrix
{
    struct Index* head;// used to store matrix index head of non zero entries
};
int main()
{
    int n,matrix_number,row,column,value;
    scanf("%d",&n);
    struct Node *t,*t2;//used for traversing through indexes(rows/columns)
    struct Matrix M1,M2,M3;//the matrices, M3 is the product matrix
    struct Node** M1_index_start=(struct Node**) malloc (n*sizeof(struct Node*));
    struct Node** M1_index_end=(struct Node**) malloc (n*sizeof(struct Node*));
    struct Node** M2_index_start=(struct Node**) malloc (n*sizeof(struct Node*));
    struct Node** M2_index_end=(struct Node**) malloc (n*sizeof(struct Node*));
    struct Node** M3_index_start=(struct Node**) malloc (n*sizeof(struct Node*));
    struct Node** M3_index_end=(struct Node**) malloc (n*sizeof(struct Node*));
    M1.head=NULL;
    M2.head=NULL;
    M3.head=NULL;
    scanf("%d",&matrix_number);
    while(matrix_number!=0)
    {
        struct Node* temp = (struct Node*)malloc(sizeof(struct Node));//to create nodes of linked list
        scanf("%d %d %d",&row,&column,&value);
        (*temp).val= value;
        (*temp).row_number=row;
        (*temp).column_number=column;
        (*temp).next=NULL;
        switch(matrix_number)
        {
            // M1 is linked row wise
            case 1: if(M1_index_start[row-1]==NULL)
                    {
                        M1_index_start[row-1]=temp;
                    }
                    else
                    {
                        (*(M1_index_end[row-1])).next=temp;
                    }
                    M1_index_end[row-1]=temp;
                    break;
            // M2 is linked column wise
            case 2: if(M2_index_start[column-1]==NULL)
                    {
                        M2_index_start[column-1]=temp;
                    }
                    else
                    {
                        (*(M2_index_end[column-1])).next=temp;
                    }
                    M2_index_end[column-1]=temp;
                    break;
        }
        scanf("%d",&matrix_number);
    }    
    /*Since all those rows of M1 and columns of M2 which have all elements as 0 will not contribute 
    to any non zero entries of the final multiplicated matrix. We can delete such index heads (row/column heads)*/
    int i,j,sum,f=0;//f is used to check for null matrix
    struct Index *p,*p2;//for traversing between indexes
    for(i=0;i<n;i++)
    {
        if(M1_index_start[i]!=NULL)
        {
            struct Index* a=(struct Index*)malloc(sizeof(struct Index));//used to store addresses of index heads having non zero entries
            (*a).index_head=M1_index_start[i];
            (*a).next=NULL;
            if(M1.head==NULL)
            {
                M1.head=a;
                p=a;
            }
            else
            {
                (*p).next=a;
                p=a;
            }
        }
        if(M2_index_start[i]!=NULL)
        {
            struct Index* a=(struct Index*)malloc(sizeof(struct Index));//used to store addresses of index heads having non zero entries
            (*a).index_head=M2_index_start[i];
            (*a).next=NULL;
            if(M2.head==NULL)
            {
                M2.head=a;
            }
            else
            {
                (*p2).next=a;
            }
            p2=a;
        }
    }
    //freeing extra space used in order to achieve O(m) where m= number of non-zero entries in the matrix 
    //to achieve O(m) space complexity
    free(M1_index_start);
    free(M2_index_start);
    free(M1_index_end);
    free(M2_index_end);
    // Calulating the non zero entries of final matrix(A) 
    //f is used to keep a track of occurrence of non zero entries
    p=M1.head;
    while(p!=NULL)
    {
        p2=M2.head;
        while(p2!=NULL)
        {
            sum=0;
            t=(*p).index_head;
            t2=(*p2).index_head;
            while(t!=NULL&&t2!=NULL)
            {
                i=(*t).row_number;
                j=(*t2).column_number;
                if((*t).column_number==(*t2).row_number)
                {// calculating A[i-1][j-1]
                    sum=sum+((*t).val)*((*t2).val);
                    t=(*t).next;
                    t2=(*t2).next;
                }
                else if((*t).column_number>(*t2).row_number)t2=((*t2).next);
                else t=(*t).next;
            }
            if(sum!=0)
            {
                // Storing Non zero entries in matrix 3 and linking them row wise
                f=1;
                struct Node* temp = (struct Node*)malloc(sizeof(struct Node));//to create nodes of linked list
                (*temp).val= sum;
                (*temp).row_number=i;
                (*temp).column_number=j;
                (*temp).next=NULL;
                if(M3_index_start[i-1]==NULL)
                {
                    M3_index_start[i-1]=temp;
                }
                else
                {
                    (*(M3_index_end[i-1])).next=temp;
                }
                M3_index_end[i-1]=temp;
            }
            p2=(*p2).next;
        }
        p=(*p).next;
    }
    for(i=0;i<n;i++)
    {
        //Removing all the rows having only zeros as entries
        if(M3_index_start[i]!=NULL)
        {
            struct Index* a=(struct Index*)malloc(sizeof(struct Index));
            (*a).index_head=M3_index_start[i];
            (*a).next=NULL;
            if(M3.head==NULL)
            {
                M3.head=a;
                p=a;
            }
            else
            {
                (*p).next=a;
                p=a;
            }
        }
    }
    free(M3_index_start);
    free(M3_index_end);
    if(f==0)printf("NULL MATRIX!");
    else
    {// Printing non zero entries for multiplied matrix
        p=M3.head;
        while(p!=NULL)
        {
            t=(*p).index_head;
            while(t!=NULL)
            {
                printf("%d %d %d\n",(*t).row_number,(*t).column_number,(*t).val);
                t=(*t).next;
            }
            p=(*p).next;
        }
    }
}
// The matrices 1 and 2 are linked differently 
//The reason being :for matrix multiplication we require matrix 1 to run row wise and matrix 2 to run column wise
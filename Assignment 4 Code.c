#include<stdio.h>
#include<stdlib.h>
#include<time.h> // for clock_t, clock()
struct BinaryTreeNode
{
    int value;
    struct BinaryTreeNode *left,*right;
};
int i;
struct BinaryTreeNode nodes[10000000];
double total_t[10000000];
int IsNearlyBalanced(int n,struct BinaryTreeNode* head)
{
    if(head==NULL)return -1;
    struct BinaryTreeNode* temp=head;int min,total_size,right_size;
    while((*temp).left!=NULL)
    {
        temp=(*temp).left;
    }
    min=(*temp).value;
    total_size=n-min+1;
    right_size=n-(*head).value;
    if(right_size>total_size*3/4&&2*right_size-1!=total_size)return min-1;
    return -1;
    //returns -1 if nearly balanced or the node index of the node whose subtree is not nearly balanced
}
struct BinaryTreeNode* creatingPerfectlyBalancedTree(int i,int j)
{
    if(i>=j)return NULL;
    for(int k=i;k<j;k++)
    {
        nodes[k].left=nodes[k].right=NULL;
    }
    nodes[(i+j)/2].left=creatingPerfectlyBalancedTree(i,(i+j)/2);
    nodes[(i+j)/2].right=creatingPerfectlyBalancedTree(1+(i+j)/2,j);
    return &(nodes[(i+j)/2]);
}
struct BinaryTreeNode* Conversion(int n,struct BinaryTreeNode* root)
{
    struct BinaryTreeNode* temp= root,*prev=NULL;
    int flag=-1;
    while((*temp).right!=NULL)
    {
        flag=IsNearlyBalanced(n,temp);
        if(flag!=-1)break;
        prev=temp;
        temp=(*temp).right;
    }
    if(flag!=-1)
    {
        temp=creatingPerfectlyBalancedTree(flag,n);
        if(prev==NULL)
        {
            root=temp;
        }
        else 
        {
            (*prev).right=temp;
        }
    }
    return root;
}
struct BinaryTreeNode* insert(int n,struct BinaryTreeNode* root)
{
    if(n==1)
    {
        root=&(nodes[n-1]);
        return root;
    }
    nodes[n-2].right=&(nodes[n-1]);
    root=Conversion(n,root);
    return root;
}
int main()
{
    int n;
    struct BinaryTreeNode* root;
    double sum=0;
    FILE* file=fopen("Data.csv","w+");
    for(i=0;i<10000000;i++)
{
    nodes[i].value=i+1;
    nodes[i].left=nodes[i].right=NULL;
}
    clock_t start_t, end_t;
    for(n=1;n<=10000000;n++)
    {
        start_t = clock();
        root = insert(n,root);
        end_t = clock();
        total_t[n-1]=(double)((end_t - start_t)*1000/ CLOCKS_PER_SEC);
        sum=sum+total_t[n-1];
        if(n%50000==0)
        {
            fprintf(file,"%lf\n",sum/1000);
        }
    }
    fclose(file);
    return 0;
}

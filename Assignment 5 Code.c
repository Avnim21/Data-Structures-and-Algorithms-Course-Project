#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
int array[10000000];
long long int Comparision_Merge_Sort=0,Comparision_Quick_Sort=0,Comparision_Improve_Merge_Sort=0;
int random_array_values() 
{   
    srand((unsigned)time(NULL));
    return (rand() % 10000000); 
}
void Improve_Merge(int i,int j, int* temporary_array)
{
    int mid=(i+j)/2;
    int i_traversal=i,j_traversal=mid+1,k_traversal=0;
    while ((i_traversal<mid+1) && (j_traversal<j+1))
    {
        if((Comparision_Improve_Merge_Sort++,array[i_traversal]<array[j_traversal]))
        {
            temporary_array[k_traversal]=array[i_traversal];
            k_traversal++;
            i_traversal++;
        }
        else
        {
            temporary_array[k_traversal]=array[j_traversal];
            k_traversal++;
            j_traversal++;
        }
    }
    while((i_traversal<mid+1))
    {
        temporary_array[k_traversal]=array[i_traversal];
        k_traversal++;
        i_traversal++;
    }
    while((j_traversal<j+1))
    {
        temporary_array[k_traversal]=array[j_traversal];
        k_traversal++;
        j_traversal++;
    }
}
void Merge(int i,int j, int* temporary_array)
{
    int mid=(i+j)/2;
    int i_traversal=i,j_traversal=mid+1,k_traversal=0;
    while ((i_traversal<mid+1) && (j_traversal<j+1))
    {
        if((Comparision_Merge_Sort++,array[i_traversal]<array[j_traversal]))
        {
            temporary_array[k_traversal]=array[i_traversal];
            k_traversal++;
            i_traversal++;
        }
        else
        {
            temporary_array[k_traversal]=array[j_traversal];
            k_traversal++;
            j_traversal++;
        }
    }
    while((i_traversal<mid+1))
    {
        temporary_array[k_traversal]=array[i_traversal];
        k_traversal++;
        i_traversal++;
    }
    while((j_traversal<j+1))
    {
        temporary_array[k_traversal]=array[j_traversal];
        k_traversal++;
        j_traversal++;
    }
}
void Improved_Merge_Sort(int i,int j)
{
    if(i<j)
    {
        int t;
        if(j-i==1)
        {
            if(Comparision_Improve_Merge_Sort++,array[i]>array[j])
            {
                t = array[i];
                array[i]=array[j];
                array[j]=t;
            }
            return;
        }
        int mid = (i+j)/2;
        Improved_Merge_Sort(i,mid);
        Improved_Merge_Sort(mid+1,j);
        int* temporary_array = (int*)malloc((j-i+1)*sizeof(int));
        Improve_Merge(i,j,temporary_array);
        int k;
        for(k=i;k<j+1;k++)
        {
            array[k]=temporary_array[k-i];
        }
        free(temporary_array);
    }
}
int Partition(int l,int r)
{
    int t;
    int i,j;
    i = l+1;
    j = r;
    while((i<j))
    {
        if((Comparision_Quick_Sort++,array[j]<array[l])&&(i<=j))
        {
            t = *(array+i);
            *(array+i) = *(array+j);
            *(array+j) = t;
            i++;
        }
        else
        j--;
    }
    if((Comparision_Quick_Sort++,array[i]>array[l]))
    {   
        t = *(array+i-1);
        *(array+i-1) = *(array+l);
        *(array+l)=t;
        return i-1;
    }
    else{
        t = *(array+i);
        *(array+i) = *(array+l);
        *(array+l)=t;
        return i;
    }
    
}
void quicksort(int l,int r)
{
    if ((l<r))
    {
        int i = Partition(l,r);
        quicksort(l,i-1);
        quicksort(i+1,r);
    }
}
void Merge_Sort(int i,int j)
{
    if((i<j))
    {
        int mid = (i+j)/2;
        Merge_Sort(i,mid);
        Merge_Sort(mid+1,j);
        int* temporary_array = (int*)malloc((j-i+1)*sizeof(int));
        Merge(i,j,temporary_array);
        int k;
        for(k=i;k<j+1;k++)
        {
            array[k]=temporary_array[k-i];
        }
        free(temporary_array);
    }
}
void Array_Formation(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        array[i]= random_array_values();
    }
}
void Merge_Sort_Program(int n)
{
    Merge_Sort(0,n-1);
}
void Quick_Sort(int n)
{
    quicksort(0,n-1);
}
void Improve(int n)
{
    Improved_Merge_Sort(0,n-1);
}
int main()
{
    int n;
    scanf("%d",&n);
    int mer=0,imp=0;
    clock_t start_t, end_t;
    double total_t_merge,total_t_quick,total_t_improve;
    Array_Formation(n);
    for(int i=0;i<500;i++)
    {
        start_t = clock();
        Merge_Sort_Program(n);
        end_t = clock();
        total_t_merge = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        start_t = clock();
        Quick_Sort(n);
        end_t = clock();
        total_t_quick = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        start_t = clock();
        Improve(n);
        end_t = clock();
        total_t_improve = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        if(total_t_merge<total_t_quick)mer++;
        if(total_t_improve<total_t_quick)imp++;
    }
    return 0;
}
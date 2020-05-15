#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <string.h>

void set_bin_rep(int number, int* array);
int get_number_from_bin_array(int* array);
void set_tern_rep(int number, int* array);
int get_number_from_tern_array(int* array);
int num(int* array);
int main()
{
    int dinamic[5][64], reconstruct[5][64];
    std::vector<int> example;
    //int n1=243
    int a1[6],a2[6],b[5];
    int key=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<64;j++)
        {
           dinamic[i][j]=0;
        }
    }
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<64;j++)
        {

            for(int tern=242;tern>=0;tern--)
            {
                set_bin_rep(0,a1);
                set_bin_rep(j,a2);
                set_tern_rep(tern,b);
                key=0;
                for(int k=0;k<5;k++)
                {
                    if(1==b[k])
                    {
                        a1[k+1]+=1;
                        a2[k]+=1;
                    }
                    if(2==b[k])
                    {
                        a1[k]+=1;
                        a2[k+1]+=1;
                    }
                }
                for(int k=0;k<6;k++)
                {
                    if(a1[k]>1||a2[k]>1)
                    {
                        key=1;
                        break;
                    }
                }
                if(1==key)
                {
                    continue;
                }
                if(0==i)
                {
                    if(dinamic[i][j]<num(b))
                    {
                        dinamic[i][j]=num(b);
                        reconstruct[i][j]=tern;
                    }
                }
                else
                {
                    if(dinamic[i][j]<dinamic[i-1][get_number_from_bin_array(a1)]+num(b))
                    {
                        dinamic[i][j]=dinamic[i-1][get_number_from_bin_array(a1)]+num(b);
                        reconstruct[i][j]=tern;
                    }
                }
            }
        }
    }
    printf("%d\n",dinamic[4][0]);
    int tec_bin_mask=0;
    for(int i=4;i>=0;i--)
    {

        example.push_back(reconstruct[i][tec_bin_mask]);
        set_tern_rep(example.back(),b);
        set_bin_rep(0,a1);
        for(int k=0;k<5;k++)
        {
            if(1==b[k])
            {
                a1[k+1]+=1;
            }
            if(2==b[k])
            {
                a1[k]+=1;
            }
        }
        tec_bin_mask=get_number_from_bin_array(a1);
    }
    int matrix[5][5];
    for(int i=0;i<5;i++)
    {
        set_tern_rep(example[4-i],b);
        for(int j=0;j<5;j++)
        {
            matrix[j][i]=b[j];
        }
    }

    const char* chars="0/\\";

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("%c ",chars[matrix[i][j]]);
        }
        printf("\n");
    }
    return 0;
}
void set_bin_rep(int number, int* array)
{
    for(int i=0;i<6;i++)
    {
        array[5-i]=number%2;
        number/=2;
    }
}
void set_tern_rep(int number, int* array)
{
    for(int i=0;i<5;i++)
    {
        array[4-i]=number%3;
        number/=3;
    }
}
int num(int* array)
{
    int res=0;
    for(int i=0;i<5;i++)
    {
        res+=array[i]>0?1:0;
    }
    return res;
}
int get_number_from_bin_array(int* array)
{
    int res=0;
    for(int i=0;i<6;i++)
    {
        res=2*res+array[i];
    }
    return res;
}
int get_number_from_tern_array(int* array)
{
    int res=0;
    for(int i=0;i<6;i++)
    {
        res=3*res+array[i];
    }
    return res;
}

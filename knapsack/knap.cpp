#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <bitset>
#include <time.h>
#include "genetic_algorithm.hpp"

int greedy_algorithm(int n, int w_max, int* w, int* p);
int dinamic_algorithm_1(int n, int w_max, int* weights, int* p, bool* answer_array);
int dinamic_algorithm_2(int n, int w_max, int* weights, int* p, bool* answer_array);
int approximate_method(int n, int w_max, int* weights, int* p, bool* answer_array, double eps);
bool comp(std::pair<double,int> a,std::pair<double,int> b);
int maximum(int a, int b);
int minimum(int a, int b);
int main(int argc, char**argv)
{
    int n;
    char s[256];
    char c;
    int w_max, solution, cur;
    int *w,*p,*x;
    bool* answer_array;
    int create_flg=0;
    double time1, time2;
    FILE*fp=fopen(argv[1],"rw");
    FILE*fp_greedy_accuracy=fopen("greedy_accuracy.txt", "w");
    FILE*fp_greedy_time=fopen("greedy_time.txt", "w");
    FILE*fp_dinamic_1_accuracy=fopen("dinamic_1_accuracy.txt", "w");
    FILE*fp_dinamic_1_time=fopen("dinamic_1_time.txt", "w");
    FILE*fp_dinamic_2_accuracy=fopen("dinamic_2_accuracy.txt", "w");
    FILE*fp_dinamic_2_time=fopen("dinamic_2_time.txt", "w");
    FILE*fp_approximate_1_accuracy=fopen("approximate_1_accuracy.txt", "w");
    FILE*fp_approximate_1_time=fopen("aproximate_1_time.txt", "w");
    FILE*fp_approximate_2_accuracy=fopen("approximate_2_accuracy.txt", "w");
    FILE*fp_approximate_2_time=fopen("aproximate_2_time.txt", "w");
    FILE*fp_genetic_accuracy=fopen("genetic_accuracy.txt", "w");
    FILE*fp_genetic_time=fopen("genetic_time.txt", "w");
    for(int j=0;j<210;j++)
    {
        fscanf(fp,"%s\n",s);
        fscanf(fp,"n %d\n",&n);
        if(0==create_flg)
        {
            w=new int[n];
            p=new int[n];
            x=new int[n];
            answer_array=new bool[n];
        }
        fscanf(fp,"c %d\n",&w_max);
        fscanf(fp,"z %d\n",&solution);
        //printf("%d %d %d",n,w_max,solution);
        fscanf(fp,"time %s\n",s);
        //printf("%s\n",s);
        for(int i=0;i<n;i++)
        {
            fscanf(fp,"%d,%d,%d,%d\n",&cur,&p[i],&w[i],&x[i]);
            //printf("%d %d %d\n",p[i],w[i],x[i]);
        }
        fscanf(fp,"%s\n\n",s);
        //printf("%s\n",s);
        time1=clock();
        fprintf(fp_greedy_accuracy,"%f\n",(greedy_algorithm(n,w_max,w,p)+0.)/(solution+0.));
        time2=clock();
        fprintf(fp_greedy_time,"%f\n",(time2-time1)/CLOCKS_PER_SEC);
        time1=clock();
        fprintf(fp_dinamic_1_accuracy,"%f\n",(dinamic_algorithm_1(n,w_max,w,p,answer_array)+0.)/(solution+0.));
        time2=clock();
        fprintf(fp_dinamic_1_time,"%f\n",(time2-time1)/CLOCKS_PER_SEC);
        time1=clock();
        fprintf(fp_dinamic_2_accuracy,"%f\n",(dinamic_algorithm_2(n,w_max,w,p,answer_array)+0.)/(solution+0.));
        time2=clock();
        fprintf(fp_dinamic_2_time,"%f\n",(time2-time1)/CLOCKS_PER_SEC);
        time1=clock();
        fprintf(fp_approximate_1_accuracy,"%f\n",(approximate_method(n,w_max,w,p,answer_array,0.1)+0.)/(solution+0.));
        time2=clock();
        fprintf(fp_approximate_1_time,"%f\n",(time2-time1)/CLOCKS_PER_SEC);
        time1=clock();
        fprintf(fp_approximate_2_accuracy,"%f\n",(approximate_method(n,w_max,w,p,answer_array,0.01)+0.)/(solution+0.));
        time2=clock();
        fprintf(fp_approximate_2_time,"%f\n",(time2-time1)/CLOCKS_PER_SEC);
        time1=clock();
        fprintf(fp_genetic_accuracy,"%f\n",(genetic_algorithm(n,w_max,w,p,1000,30,0.1,0.1)+0.)/(solution+0.));
        time2=clock();
        fprintf(fp_genetic_time,"%f\n",(time2-time1)/CLOCKS_PER_SEC);

        //dinamic_algorithm_1(n,w_max,w,p);


        //break;
    }
    delete [] w;
    delete [] p;
    delete [] x;
    delete [] answer_array;
    fclose(fp);
    fclose(fp_approximate_1_accuracy);
    fclose(fp_approximate_1_time);
    fclose(fp_approximate_2_accuracy);
    fclose(fp_approximate_2_time);
    fclose(fp_dinamic_1_accuracy);
    fclose(fp_dinamic_1_time);
    fclose(fp_dinamic_2_accuracy);
    fclose(fp_dinamic_2_time);
    fclose(fp_greedy_accuracy);
    fclose(fp_greedy_time);
    fclose(fp_genetic_accuracy);
    fclose(fp_genetic_time);
    return 0;
}

int greedy_algorithm(int n, int w_max,int* w, int*p)
{
    int sum_weight=0,sum_price=0;
    std::pair<double,int>* specific_values=new std::pair<double,int>[n];
    for(int i=0;i<n;i++)
    {
        specific_values[i].first=p[i]/w[i];
        specific_values[i].second=i;
    }
    sort(specific_values,specific_values+n,comp);
    for(int i=0;i<n;i++)
    {
        if (sum_weight+w[specific_values[i].second]>w_max)
        {
            break;
        }
        sum_weight+=w[specific_values[i].second];
        sum_price+=p[specific_values[i].second];
    }
    for(int i=0;i<n;i++)
    {
        if(p[i]>sum_price && w[i]<w_max)
        {
            sum_price=p[i];
        }
    }
    delete [] specific_values;
    return sum_price;
}
bool comp(std::pair<double,int> a,std::pair<double,int> b)
{
    return a.first>b.first;
}
int dinamic_algorithm_1(int n, int w_max, int* weights, int* p, bool* answer_array)
{
    int** dinamic_array=new int* [n+1];
    for(int i=0;i<n+1;i++)
    {
        dinamic_array[i]=new int [w_max+1];

    }
    for(int i=0;i<w_max+1;i++)
    {
        dinamic_array[0][i]=0;
    }
    for(int i=1;i<n+1;i++)
    {
        for(int w=0;w<w_max+1;w++)
        {
            if(w<weights[i-1])
            {
                dinamic_array[i][w]=dinamic_array[i-1][w];
            }
            else
            {
                dinamic_array[i][w]=maximum(dinamic_array[i-1][w],dinamic_array[i-1][w-weights[i-1]]+p[i-1]);
            }
        }
    }
    int res=dinamic_array[n][w_max];

    while(n>0)
    {
        if(dinamic_array[n][w_max]==dinamic_array[n-1][w_max])
        {
            n--;
            answer_array[n]=false;
        }
        else
        {
            n--;
            answer_array[n]=true;
            w_max-=weights[n];
        }

    }
    delete [] dinamic_array;
    return res;

}
int dinamic_algorithm_2(int n, int w_max, int* weights, int* p, bool* answer_array)
{
    int sum=0,res=0;
    for(int i=0;i<n;i++)
    {
        sum+=p[i];
    }
    int** dinamic_array=new int* [n+1];
    for(int i=0;i<n+1;i++)
    {
        dinamic_array[i]=new int [sum+1];
    }
    dinamic_array[0][0]=0;
    for(int i=1;i<sum+1;i++)
    {
        dinamic_array[0][i]=w_max+1;
    }
    for(int i=1;i<n+1;i++)
    {
        for(int profit=0;profit<sum+1;profit++)
        {
            if(profit<p[i-1])
            {
                dinamic_array[i][profit]=dinamic_array[i-1][profit];
            }
            else
            {
                dinamic_array[i][profit]=minimum(dinamic_array[i-1][profit],dinamic_array[i-1][profit-p[i-1]]+weights[i-1]);
            }
        }
    }
    for(int i=sum;i>=0;i--)
    {
        if(dinamic_array[n][i]<=w_max)
        {
            res=i;
            break;
        }
    }
    int res1=res;
    while(n>0)
    {
        if(dinamic_array[n][res1]==dinamic_array[n-1][res1])
        {
            n--;
            answer_array[n]=false;
        }
        else
        {
            n--;
            answer_array[n]=true;
            res1-=p[n];
        }

    }
    delete [] dinamic_array;
    return res;
}
int approximate_method(int n, int w_max, int* weights, int* p, bool* answer_array, double eps)
{
    int* new_p=new int [n];
    int p_max=-1, res=0;
    for(int i=0;i<n;i++)
    {
     if(p[i]>p_max)
     {
         p_max=p[i];
     }
    }
    for(int i=0;i<n;i++)
    {
        new_p[i]=(int)((n*p[i]+0.)/(eps*p_max+0.));
    }
    dinamic_algorithm_2(n,w_max,weights,new_p,answer_array);
    for(int i=0;i<n;i++)
    {
        if(answer_array[i])
        {
            res+=p[i];
        }
    }
    delete [] new_p;
    return res;
}
int maximum(int a, int b)
{
    return a>b?a:b;
}
int minimum(int a, int b)
{
    return a<b?a:b;
}

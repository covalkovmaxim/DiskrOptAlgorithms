#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<set>
#include<vector>


int greedy_algorithm(int n, int w_max, int* w, int* p);
int dinamic_algorithm_1(int n, int w_max, int* weights, int* p);
int dinamic_algorithm_2(int n, int w_max, int* weights, int* p);
bool comp(std::pair<double,int> a,std::pair<double,int> b);
int main(int argc, char**argv)
{
    int n;
    char s[256];
    char c;
    int w_max, solution, cur;
    int *w,*p,*x;
    int create_flg=0;
    FILE*fp=fopen(argv[1],"rw");
    for(int j=0;j<100;j++)
    {
        fscanf(fp,"%s\n",s);
        fscanf(fp,"n %d\n",&n);
        if(0==create_flg)
        {
            w=new int[n];
            p=new int[n];
            x=new int[n];
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
        //printf("%f\n",(solution+0.)/(greedy_algorithm(n,w_max,w,p)+0.));
        printf("eeeeeeee\n");
        dinamic_algorithm_1(n,w_max,w,p);
        printf("ffffffff\n");
        //printf("%f\n",(solution+0.)/(dinamic_algorithm_1(n,w_max,w,p)+0.));
        //break;
    }
    delete[] w;
    delete[] p;
    delete[] x;
    fclose(fp);

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
int dinamic_algorithm_1(int n, int w_max, int* weights, int* p)
{
    printf("hello\n");
    int* results=new int [w_max+1];
    std::set<int>* choice_lists=new std::set<int> [w_max+1];
    /*results[0]=0;

    for(int w=1;w<w_max+1;w++)
    {
        results[w]=results[w-1];
        choice_lists[w]=choice_lists[w-1];
        for(int i=0;i<n;i++)
        {
            if(w-weights[i]>=0 && results[w-weights[i]]+p[i]>results[w] &&
               choice_lists[w-weights[i]].find(i)==choice_lists[w-weights[i]].end())
            {
                results[w]=results[w-weights[i]]+p[i]>results[w];
                choice_lists[w]=choice_lists[w-weights[i]];
                choice_lists[w].insert(i);
            }
        }

    }
    printf("%d",results[w_max]);
    delete [] results;
    delete [] choice_lists;
    return results[w_max];*/
    return 1;

}
int dinamic_algorithm_2(int n, int w_max, int* w, int* p)
{
    
}

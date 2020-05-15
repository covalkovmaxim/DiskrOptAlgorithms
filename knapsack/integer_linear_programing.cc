#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <bitset>
#include <string>
#include <time.h>
#include "ortools/linear_solver/linear_solver.h"


namespace operations_research {
int integer_programming(int n, int w_max, int* weights, int* p, bool* answer_array) {

  MPSolver solver("IntegerExample",
                  MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);

  MPVariable** const vars=new MPVariable*[n];
  for(int i=0;i<n;i++)
  {
    vars[i]=solver.MakeIntVar(0.0, 1.0, "x"+std::to_string(i));
  }

  MPConstraint* const constraint =
      solver.MakeRowConstraint(-solver.infinity(), w_max);
  for(int i=0;i<n;i++)
  {
      constraint->SetCoefficient(vars[i],weights[i]);
  }

  MPObjective* const objective = solver.MutableObjective();
  for(int i=0;i<n;i++)
  {
      objective->SetCoefficient(vars[i],p[i]);
  }
  objective->SetMaximization();

  const MPSolver::ResultStatus result_status = solver.Solve();

  if (result_status != MPSolver::OPTIMAL) {
    LOG(FATAL) << "The problem does not have an optimal solution!";
  }
  for(int i=0;i<n;i++)
  {
      answer_array[i]=vars[i]->solution_value();
  }

  return (int)objective->Value();

  // [END print_solution]
}
}  // namespace operations_research
int main(int argc, char**argv)
{
    int n;
    char s[256];
    char c;
    int w_max, solution, cur;
    int *w,*p,*x;
    bool* answer_array;
    int create_flg=0;
    double time1,time2;
    FILE*fp=fopen(argv[1],"rw");
    FILE*fp_integer_linprog_accuracy=fopen("integer_linprog_accuracy.txt","w");
    FILE*fp_integer_linprog_time=fopen("integer_linprog_time.txt","w");
    for(int j=0;j<300;j++)
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
        fprintf(fp_integer_linprog_accuracy,"%f\n",(operations_research::integer_programming(n,w_max,w,p,answer_array)+0.)/(solution+0.));
        time2=clock();
        fprintf(fp_integer_linprog_time,"%f\n",(time2-time1)/CLOCKS_PER_SEC);
        //dinamic_algorithm_1(n,w_max,w,p);


        //break;
    }
    delete [] w;
    delete [] p;
    delete [] x;
    delete [] answer_array;
    fclose(fp);
    fclose(fp_integer_linprog_accuracy);
    fclose(fp_integer_linprog_time);

    return EXIT_SUCCESS;
}

#include "genetic_algorithm.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> int_un_dist(0,1);
static std::uniform_real_distribution<> real_un_dist(0.0,1.0);

CUnit::CUnit(int size)
{
    _DNA_size=size;
    _DNA=new int [size];
    std::for_each(_DNA,_DNA+size,
                  [](int& tec)
                  {
                    tec=int_un_dist(gen);
                  });
    fitness_value=0;
}

CUnit::CUnit(CUnit&& elem)
{
    _DNA_size=elem._DNA_size;
    _DNA=new int [_DNA_size];
    for(int i=0;i<_DNA_size;i++)
    {
        _DNA[i]=elem._DNA[i];
    }
    fitness_value=0;
}

void CUnit::mutation(double mutation_probability)
{
    std::for_each(_DNA,_DNA+_DNA_size,
                  [&mutation_probability](int& tec)
                  {
                    tec=real_un_dist(gen)<mutation_probability?int_un_dist(gen):tec;
                  });
}

CUnit CUnit::operator+(const CUnit& second_parent) const
{
    CUnit child(this->_DNA_size);
    int size=child._DNA_size;
    for(int i=0;i<size;i++)
    {
        child._DNA[i]=real_un_dist(gen)<0.5?this->_DNA[i]:second_parent._DNA[i];
    }
    return child;
}

int CUnit::comp_fitness_function(int w_max, int* weights, int* prices)
{
    int result=0, size=this->_DNA_size, W=0;
    for(int i=0;i<size;i++)
    {
        if(1==this->_DNA[i])
        {
            result+=prices[i];
            W+=weights[i];
        }
    }
    if(W>w_max)
    {
        result=0;
    }
    fitness_value=result;
    return result;
}

void CUnit::write()
{
    std::for_each(_DNA,_DNA+_DNA_size,[](int& tec){printf("%d ",tec);});
    printf("\n");
}

CUnit::~CUnit()
{
    delete [] _DNA;
}
bool compare1(CUnit* a,CUnit* b)
{
    return a->fitness_value>b->fitness_value;
}
int genetic_algorithm(
    int    n,
    int    w_max,
    int*   weights,
    int*   prices,
    int    units_num,
    int    generaton_num,
    double choice_percent,
    double mutation_probability)
{
    CUnit** units;
    units=new CUnit* [units_num];
    int first_num,second_num;
    int best_num=(int)units_num*choice_percent;
    std::normal_distribution<> real_normal_dist{0,best_num};
    int res;

    for(int i=0;i<units_num;i++)
    {
        units[i]=new CUnit(n);
        units[i]->comp_fitness_function(w_max,weights,prices);
    }
    std::sort(units,units+units_num,compare1);

    for(int i=1;i<generaton_num;i++)
    {
        //printf("%d generation => %d\n",i,units[0]->fitness_value);
        for(int j=best_num;j<units_num-best_num;j++)
        {
            delete units[j];
            first_num=(int)(fabs(real_normal_dist(gen)))%best_num;
            second_num==(int)(fabs(real_normal_dist(gen)))%best_num;
            units[j]=new CUnit(std::forward<CUnit>((*units[first_num])+(*units[second_num])));
            units[j]->mutation(mutation_probability);
            units[j]->comp_fitness_function(w_max,weights,prices);
        }
        for(int j=units_num-best_num;j<units_num;j++)
        {
            delete units[j];
            units[j]=new CUnit(n);
            units[j]->comp_fitness_function(w_max,weights,prices);
        }
        std::sort(units,units+units_num,compare1);
    }
    res=units[0]->fitness_value;
    for(int i=0;i<units_num;i++)
    {
        delete units[i];
    }
    delete [] units;

    return res;
}




#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

class CUnit
{
    private:
        int _DNA_size;
        int* _DNA;

    public:
        int fitness_value;
        CUnit(int size);
        CUnit(CUnit&& elem);
        void mutation(double mutation_probability);
        CUnit operator+(const CUnit& second_parent) const;
        int comp_fitness_function(int w_max, int* weights, int* prices);
        void write();
        ~CUnit();
};
int genetic_algorithm(
    int    n,
    int    w_max,
    int*   weights,
    int*   prices,
    int    units_num,
    int    generaton_num,
    double choice_percent,
    double mutation_probability);

#include <iostream>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <vector>
#include "histogram.h"
#include "SVG.h"
#include<windows.h>
#pragma hdrstop
using namespace std;

vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}

vector<size_t>
make_histogram(Input data){

    double min, max;
   find_minmax(data.numbers, min, max);
    vector<size_t> bins(data.bin_count, 0);
    for (double number : data.numbers) {
        size_t bin = (size_t)(((number - min) / (max - min)) * data.bin_count);
        if (bin == data.bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

void
show_histogram( const auto& bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)

        {
            cout << '*';
        }
        cout << '\n';
    }
}



int main()
{
    // ���� ������
    Input data;
    data=read_input(cin);

    // ��������� ������
    const auto bins = make_histogram(data);

    // ����� ������
    show_histogram_svg(bins);
    return 0;
}

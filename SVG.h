#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector <double> bin_size(const vector<double> &numbers, const size_t &bin_count);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height,string stroke = "black", string fill = "#3CB371" );
void show_histogram_svg(const vector<size_t>& bins,const vector<double>& bin_size);

#endif // SVG_H_INCLUDED

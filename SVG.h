#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <iostream>
#include <vector>
#include <sstream>
#include <windows.h>
#include <algorithm>
using namespace std;
void svg_begin(double width, double height);
void svg_end();
void svg_rect(double x, double y, double width, double height, string fill = "black", string stroke = "black");
void svg_text(double left, double baseline, string text);
void show_histogram_svg(const vector<size_t>& bins,string fill = "black");
string make_info_text(char T = '1');
void show_histogram_svg(const vector<size_t>& bins);


#endif // SVG_H_INCLUDED

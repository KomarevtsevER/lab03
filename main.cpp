#include <iostream>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <vector>
#include<windows.h>
#pragma hdrstop
using namespace std;



using namespace std;

vector<double>
input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void
find_minmax(const vector<double> &numbers, double& min, double& max)
{
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers)
    {
        if (number < min)
        {
            min = number;
        }
        if (number > max)
        {
            max = number;
        }
    }
}

vector<size_t>
make_histogram(const vector<double> &numbers, const size_t &bin_count){

    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count, 0);
    for (double number : numbers) {
        size_t bin = (size_t)(((number - min) / (max - min)) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

void
show_histogram( const auto& bins){
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

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='"<< baseline << "'>"<< text <<"</text>" <<endl;
}

void svg_rect(double x, double y, double width, double height,string stroke, string fill){

    cout<<"<rect x='" << x <<"' y='"<< y <<"' width='"<< width <<"' height='"<< height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />" <<endl;
}


void
show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const string stroke = "black";
    const string fill = "#3CB371";
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        const double text_wid= IMAGE_WIDTH-bin_width-30;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"black", "#3CB371");
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    svg_end();
}


int main()
{
    // ���� ������
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count );
    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;

    // ��������� ������
    const auto bins = make_histogram(numbers, bin_count);
    // ����� ������
    show_histogram_svg(bins);
    return 0;
}

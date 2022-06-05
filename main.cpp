#include <sstream>
#include <string>
#include <iostream>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <vector>
#include "histogram.h"
#include "SVG.h"
#include<windows.h>
#pragma hdrstop
#include <curl/curl.h>
using namespace std;

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);
    return data_size;
}

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
read_input(istream& in, bool prompt)
{
    Input data;

    if (prompt)
        cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (prompt)
        cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}

vector<size_t>
make_histogram(Input data)
{

    double min, max;
    find_minmax(data.numbers, min, max);
    vector<size_t> bins(data.bin_count, 0);
    for (double number : data.numbers)
    {
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

Input
download(const string& address)
{
    curl_global_init(CURL_GLOBAL_ALL);
    stringstream buffer;
    CURL* curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res != CURLE_OK)
        {
            cerr<<" Error text  = "<<curl_easy_strerror(res);
            exit(1);
        }

        return read_input(buffer, false);
    }

}
    int main(int argc, char* argv[])
    {
        size_t ncolor;
        for(size_t i =0; i<argc ; i++){
            if (strstr(argv[i], "-fill")){
                ncolor=i+1;
                if((argc - ncolor) < 2 ){
                    cerr<<" No color";
                    return 0;
                }
                break;
            }
        }
        string color = argv[ncolor];
        Input input;
        if (argc > 1)
        {
            size_t index;
            if(ncolor==2){
                    index=3;
            }
            else{
                index=1;
            }
            input = download(argv[index]);
        }
        else
        {
            input = read_input(cin, true);
        }

        // Обработка данных

        const auto bins = make_histogram(input);

        // Вывод данных
        show_histogram_svg(bins, color);
        return 0;
    }

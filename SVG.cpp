#include "SVG.h"
#include "histogram.h"

vector <double>
bin_size(const vector<double> &numbers, const size_t &bin_count){
    double max, min;
    find_minmax (numbers, min, max);
    vector <double> bin = {(max - min)/ bin_count, min};
    return bin;
}

void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end()
{
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='"<< baseline << "'>"<< text <<"</text>" <<endl;
}

void svg_rect(double x, double y, double width, double height,string stroke, string fill)
{

    cout<<"<rect x='" << x <<"' y='"<< y <<"' width='"<< width <<"' height='"<< height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />" <<endl;
}


void
show_histogram_svg(const vector<size_t>& bins,const vector<double>& bin_size)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20+20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50+20;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t i=0; i<bins.size(); i++)
    {
        size_t bin=bins[i];
        const double bin_width = BLOCK_WIDTH * bin;
        const double text_wid= IMAGE_WIDTH-bin_width-30;
        if( i > 0){
            svg_text(TEXT_LEFT-20, top + TEXT_BASELINE, to_string(bin_size[1] + bin_size[0]*i));
            top+=BIN_HEIGHT;
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    svg_end();
}

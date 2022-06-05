#include "SVG.h"
void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_end() {
    cout << "</svg>\n";
}
void svg_rect(double x, double y, double width, double height, string stroke, string fill){
    cout << "<rect x='" << x <<"' y='" << y << "' width='" << width <<"' height='" << height <<"' stroke='"<< stroke <<"' fill='#"<< fill <<"' />";
}
void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text <<"</text>";
}

void show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto MAX_ASTERISK = IMAGE_WIDTH - TEXT_WIDTH;
    size_t max_count = 0;
    for (size_t bin : bins) {
        if (bin * BLOCK_WIDTH > max_count) {
            max_count = bin * BLOCK_WIDTH;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        size_t bin_scale = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            bin_scale = (size_t)(bin * scaling_factor);
        }
        const double bin_width = BLOCK_WIDTH * bin_scale;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_end();
}

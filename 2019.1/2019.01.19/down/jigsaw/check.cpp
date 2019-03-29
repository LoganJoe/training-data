#include <bits/stdc++.h>
using namespace std;

#define RGB vector <float>
#define Image_Row vector <RGB>
#define Image vector <Image_Row>

#define pInt pair <int, int>
#define Answer_Row vector <pInt>
#define Answer vector <Answer_Row>

void read_image(const char *file_name, Image &img)
{
    ifstream fin(file_name, ifstream::binary);
    string tmp; int H, W, X;
    fin >> tmp >> W >> H >> X;
    string rgb((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    img = Image(H, Image_Row(W, RGB(3)));
    for (size_t h = 0, p = 0; h < H; ++ h)
        for (size_t w = 0; w < W; ++ w, ++ p)
            for (size_t c = 0; c < 3; ++ c)
                img[h][w][c] = 1. * (unsigned char)rgb[p * 3 + c + 1] / X;
}

void save_image(const char *file_name, const Image &img)
{
    ofstream fout(file_name, ofstream::binary);
    int H = img.size(), W = img[0].size(), X = 255;
    fout << "P6\n" << W << " " << H << "\n" << X << "\n";
    for (size_t h = 0; h < H; ++ h)
        for (size_t w = 0; w < W; ++ w)
            for (size_t c = 0; c < 3; ++ c)
                fout << (unsigned char)round(img[h][w][c] * X);
}

int main(int argc, char *argv[])
{
    string file_name = argv[1];
    Image input;
    read_image(("in_image/" + file_name + ".ppm").c_str(), input);
    int H = input.size(), W = input[0].size();

    int h, w;
    ifstream in("jigsaw.in");
    while (1)
    {
        string tmp;
        in >> tmp >> h >> w;
        if (tmp == file_name) break;
    }
    in.close();

    int h_cnt, w_cnt;
    Answer res;
    ifstream out("jigsaw.out");
    while (1)
    {
        string tmp;
        out >> tmp >> h_cnt >> w_cnt; h_cnt += 2; w_cnt += 2;
        res = Answer(h_cnt, Answer_Row(w_cnt));
        for (int hi = 1; hi <= h_cnt - 2; ++ hi)
            for (int wi = 1; wi <= w_cnt - 2; ++ wi)
                out >> res[hi][wi].first >> res[hi][wi].second;
        if (tmp == file_name) break;
    }
    out.close();

    Image output = input;
    for (int hi = 1; hi <= h_cnt - 2; ++ hi)
        for (int wi = 1; wi <= w_cnt - 2; ++ wi)
        {
            int h_ = res[hi][wi].first, w_ = res[hi][wi].second;
            for (int hj = 0; hj < h; ++ hj)
                for (int wj = 0; wj < w; ++ wj)
                    output[hi * h + hj][wi * w + wj] = input[h_ * h + hj][w_ * w + wj];
        }
    save_image(("out_image/" + file_name + ".ppm").c_str(), output);
}

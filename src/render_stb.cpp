#include "../include/render_stb.h"

int Req = 6378160;

double ang_to_rad(double angel) {
    return pi_v<double> * angel / 180;
}

void convert_to_pix(double lon, double lat, vector<int> &vec_pix) {
    int x = Req * ang_to_rad(lon);
    int y = Req * log(tan((pi_v<double> / 4) + (ang_to_rad(lat) / 2)));
    vec_pix[0] = x;
    vec_pix[1] = y;
    // return vector<int>{x,y};
}

void get_image_cord(vector<int> cord, int size_x_min, int size_y_max, vector<int> &vec_img_cord) {
    int x = (size_y_max - cord[1])/5;
    int y = (cord[0] - size_x_min)/5;
    vec_img_cord[0] = y;
    vec_img_cord[1] = x;
    // return vector<int>{y,x};
}

void saveSurfaceToJPG(SDL_Surface* surface, const char* filename) {
    if (stbi_write_jpg(filename, surface->w, surface->h, 4, surface->pixels, 100) == 0) {
        std::cerr << "Failed to save image" << std::endl;
    }
}

void render(string file, vector<unordered_map<string, vector<unordered_map<string, double>>>> &points, unordered_map<string, double> bounds) {
    vector<int> size_min = {0,0};
    vector<int> size_max = {0,0};
    convert_to_pix(bounds["minlon"], bounds["minlat"], size_min);
    convert_to_pix(bounds["maxlon"], bounds["maxlat"], size_max);

    vector<int> size = {abs(size_max[0] - size_min[0])/5, abs(size_max[1] - size_min[1])/5};

    // CImg<unsigned char> image(size[0], size[1], 1, 3, 0);
    // unsigned char black[] = { 255, 255, 255 };

    SDL_Surface* surface = SDL_CreateRGBSurface(0, size[0], size[1], 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    vector<int> node_f = {0,0};
    vector<int> node_s = {0,0};
    vector<int> f = {0,0};
    vector<int> s = {0,0};
    for (auto way :  points) {
        for (int x = 0; x < way["nodes"].size()-1; x++) {
            convert_to_pix(way["nodes"][x]["lon"], way["nodes"][x]["lat"], node_f);
            convert_to_pix(way["nodes"][x+1]["lon"], way["nodes"][x+1]["lat"], node_s);
            get_image_cord(node_f, size_min[0], size_max[1], f);
            get_image_cord(node_s, size_min[0], size_max[1], s);

            // image.draw_line(f[0], f[1], s[0], s[1], black);
            SDL_RenderDrawLine(renderer, f[0], f[1], s[0], s[1]);
        }
    }
    // image.save(file.data());
    SDL_RenderPresent(renderer);
    saveSurfaceToJPG(surface, file.data());
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
    SDL_Quit();
}

#include <functional>
#include <../include/rapidxml_ext.hpp>
#include <../include/osm_parser.h>
#include <../include/render.h>

using namespace rapidxml;
using namespace std;

int main(int argc, char *argv[]) {
    timeval a,b,c,d,e,f,g;
    // clock_t a = clock();
    gettimeofday(&a, NULL);
    std::string osm_file = argv[1];
    std::string output_file = argv[2];
    xml_document<> doc;
    get_tree(osm_file, doc);
    // clock_t b = clock();
    gettimeofday(&b, NULL);

    unordered_map<string, double> bounds = get_bounds(doc);
    // clock_t c = clock();
    gettimeofday(&c, NULL);

    vector<xml_node<>*> ways;
    get_ways(doc, ways);
    // clock_t d = clock();
    gettimeofday(&d, NULL);

    unordered_map<string, xml_node<>*> nodes;
    get_nodes(doc, nodes);
    // clock_t e = clock();
    gettimeofday(&e, NULL);

    vector<unordered_map<string, vector<unordered_map<string, double>>>> points;
    get_points(ways, nodes, points);
    // clock_t f = clock();
    gettimeofday(&f, NULL);

    render(output_file, points, bounds);
    // clock_t g = clock();
    gettimeofday(&g, NULL);

    // xml_node<> *curNode = doc.first_node("osm") -> first_node("node");

    // cout << doc;

    double all = ((g.tv_sec - a.tv_sec) * 1e6 + (g.tv_usec - a.tv_usec)) * 1e-6;
    double t1 = ((b.tv_sec - a.tv_sec) * 1e6 + (b.tv_usec - a.tv_usec)) * 1e-6;
    double t2 = ((c.tv_sec - b.tv_sec) * 1e6 + (c.tv_usec - b.tv_usec)) * 1e-6;
    double t3 = ((d.tv_sec - c.tv_sec) * 1e6 + (d.tv_usec - c.tv_usec)) * 1e-6;
    double t4 = ((e.tv_sec - d.tv_sec) * 1e6 + (e.tv_usec - d.tv_usec)) * 1e-6;
    double t5 = ((f.tv_sec - e.tv_sec) * 1e6 + (f.tv_usec - e.tv_usec)) * 1e-6;
    double t6 = ((g.tv_sec - f.tv_sec) * 1e6 + (g.tv_usec - f.tv_usec)) * 1e-6;

    cout << "Время выполнения парсинга дерева ";
    cout << t1/all << endl;
    cout << "Время выполнения парсинга границ ";
    cout << t2/all << endl;
    cout << "Время выполнения парсинга путей ";
    cout << t3/all << endl;
    cout << "Время выполнения парсинга нод ";
    cout << t4/all << endl;
    cout << "Время выполнения создания точек ";
    cout << t5/all << endl;
    cout << "Время рендера пикчи ";
    cout << t6/all << endl;
    cout << "Итоговое время ";
    cout << all << endl;


    return 0;
}
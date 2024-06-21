#ifndef OSM_PARSER_H
#define OSM_PARSER_H
#include "rapidxml_ext.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <cstring>


using namespace rapidxml;
using namespace std;

void get_tree(const std::string& file, xml_document<> &doc);

unordered_map<string, double> get_bounds(xml_document<> &doc);

void get_ways(xml_document<> &doc, vector<xml_node<>*> &ways);

void get_nodes(xml_document<> &doc, unordered_map<string, xml_node<>*> &nodes);

void get_points(vector<xml_node<>*> &ways, unordered_map<string, xml_node<>*> &nodes, vector<unordered_map<string, vector<unordered_map<string, double>>>> &points);

#endif //OSM_PARSER_H

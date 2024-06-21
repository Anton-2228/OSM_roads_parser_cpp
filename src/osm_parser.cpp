#include <../include/osm_parser.h>

unordered_set<string> way_types {"service", "residential", "tertiary", "motorway",
             "trunk", "primary", "secondary", "tertiary",
             "motorway_link", "trunk_link", "primary_link", "secondary_link",
             "tertiary_link", "footway"};

void get_tree(const std::string& file_name, xml_document<> &doc) {

    std::ifstream file(file_name,  std::ios::in | std::ios::binary | std::ios::ate);
    std::streampos size = file.tellg();
    char* fileContent = new char[static_cast<std::size_t>(size) + 1];
    file.seekg(0, std::ios::beg);
    file.read(fileContent, size);
    file.close();
    fileContent[size] = '\0';

    doc.parse<0>(fileContent);    // 0 means default parse flags
}

unordered_map<string, double> get_bounds(xml_document<> &doc) {
    xml_node<> *element_bounds = doc.first_node("osm") -> first_node("bounds");
    unordered_map<string, double> bounds;
    bounds["minlat"] = strtod(element_bounds -> first_attribute("minlat")->value(), NULL);
    bounds["maxlat"] = strtod(element_bounds -> first_attribute("maxlat")->value(), NULL);
    bounds["minlon"] = strtod(element_bounds -> first_attribute("minlon")->value(), NULL);
    bounds["maxlon"] = strtod(element_bounds -> first_attribute("maxlon")->value(), NULL);
    bounds["delt_lat"] = bounds["maxlat"] - bounds["minlat"];
    bounds["delt_lon"] = bounds["maxlon"] - bounds["minlon"];

    return bounds;
}

void get_ways(xml_document<> &doc, vector<xml_node<>*> &ways) {
    xml_node<> *element_way = doc.first_node("osm") -> first_node("bounds");
    while (element_way) {
        xml_node<> *element_tag = element_way -> first_node("tag");
        while (element_tag) {
            if (strcmp(element_tag -> first_attribute("k")->value(), "highway")==0 &&
                way_types.count(element_tag -> first_attribute("v")->value())) {
                ways.push_back(element_way);
                break;
            } else if (strcmp(element_tag -> first_attribute("k")->value(), "railway")==0) {
                ways.push_back(element_way);
                break;
            }
            element_tag = element_tag -> next_sibling("tag");
        }
        element_way = element_way -> next_sibling("way");
    }
}

void get_nodes(xml_document<> &doc, unordered_map<string, xml_node<>*> &nodes) {
    xml_node<> *element_nodes = doc.first_node("osm") -> first_node("node");
    while (element_nodes) {
        string id = element_nodes->first_attribute("id")->value();
        nodes[id] = element_nodes;
        element_nodes = element_nodes -> next_sibling("node");
    }
}

void get_points(vector<xml_node<>*> &ways, unordered_map<string, xml_node<>*> &nodes, vector<unordered_map<string, vector<unordered_map<string, double>>>> &points) {
    for (auto way : ways) {
        xml_node<> *element_nd = way -> first_node("nd");
        unordered_map<string, vector<unordered_map<string, double>>> el;
        while (element_nd) {
            string ref = element_nd->first_attribute("ref")->value();
            xml_node<>* node = nodes[ref];
            double lat = strtod(node->first_attribute("lat")->value(), NULL);
            double lon = strtod(node->first_attribute("lon")->value(), NULL);
            unordered_map<string, double> cord;
            cord["lat"] = lat;
            cord["lon"] = lon;
            el["nodes"].push_back(cord);
            element_nd = element_nd -> next_sibling("nd");
        }
        points.push_back(el);
    }
}
#include "runAllGraphs.hpp"
#include "graphs/graphListAdj.hpp"
#include "graphs/weightedgraphDefs.hpp"

#include <iostream>
#include <dirent.h>
#include "utils.hpp"
#include "path.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

#include "hill_climb/hill_climb.hpp"
#include "gradient/gradient.hpp"
#include "criteria/degree.hpp"
#include "criteria/connexeGraphSize.hpp"

struct Path_Size {
    string path;
    int size;
};

void getPathGraphs(const char* pathInstance , vector<Path_Size>& pathGraph){
    DIR* dir = opendir(pathInstance);
    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if(entry->d_name != string(".") && entry->d_name != string("..")){
            string new_path = string(pathInstance) + string("/") + entry->d_name;
            if(entry->d_type == DT_REG){
                Path_Size p;
                p.path = new_path.substr(sizeof(path_instance),new_path.length());
                GraphHeavy g(p.path);
                p.size = g.nb_vertices() * 1000 + g.nb_edges();

                pathGraph.push_back(p);
            }else{
                getPathGraphs(new_path.c_str(),pathGraph);
            }
        }
    }
    closedir(dir);

}

struct comparator
{
    inline bool operator() (const Path_Size & key1,const Path_Size & key2){
        return key1.size < key2.size;
    }
};


void runGradient(const string& path) {
    string p = path;
    GraphHeavy g(p);
    cout << path << endl;

    vector<vertex> sub = vector<vertex>();
    weight score = gradient(g,getVertexWeight_mod, sub);
    cout << score <<endl;
    
    ofstream file;
    file.open("../run/gradient.txt", ios_base::app | ios_base::out);
    file << path << " ";
    file << score << "\n";
    file.close();
}
void runHC(neighborhood::Neighborhood* n, const string& save_path, const string& path) {
    string p = path;
    GraphHeavy g(p);
    cout << path << endl;

    vector<vertex> sub = vector<vertex>();
    weight score = hill_climb(g, n, sub);
    cout << score <<endl;
    
    ofstream file;
    file.open("../run/" + save_path, ios_base::app | ios_base::out);
    file << path << " ";
    file << score << "\n";
    file.close();
}
void runAllGraphs(function<void(const string&)> runner, int nb_graphs){
    vector<Path_Size> pathGraph = vector<Path_Size>();
    getPathGraphs(path_instance, pathGraph);

    std::sort(pathGraph.begin(), pathGraph.end(),comparator());

    for(Path_Size path : pathGraph){
        if (nb_graphs-- <= 0) return;
        runner(path.path);
    }
}
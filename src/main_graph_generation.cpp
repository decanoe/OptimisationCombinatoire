
#include "graphs/graphListAdj.hpp"
#include "graphs/graphAdjMatrix.hpp"
#include "graphs/weightedgraphDefs.hpp"

#include <iostream>
#include <unistd.h>
#include "utils.hpp"
#include "runAllGraphs.hpp"

#include "hill_climb/hill_climb.hpp"
#include "criteria/degree.hpp"
#include "criteria/connexeGraphSize.hpp"
#include "neighborhood/nn.hpp"


inline bool exists(const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}

int main(int argc , char* argv [])
{
    int nb_graphs = 10;

    // NN weighted
    for (neighborhood::NN::Choice c : {neighborhood::NN::Choice::Best, neighborhood::NN::Choice::First, neighborhood::NN::Choice::Worst})
    for (int i = 1; i <= 3; i++)
    {
        string choice = "Best";
        if (c == neighborhood::NN::Choice::First) choice = "First";
        if (c == neighborhood::NN::Choice::Worst) choice = "Worst";

        string run_path = "NN" + std::to_string(i) + "_Degree_" + choice + "_Weighted.txt";
        if (!exists("../run/" + run_path)) {
            neighborhood::Neighborhood* neigh = new neighborhood::NN(i, c, new criteria::Degree(), &getVertexWeight_mod);
            std::cout << endl << "==========" << run_path << "============================" << endl;
            runAllGraphs([neigh, run_path](const string& path)
            {
                runHC(neigh, run_path, path);
            }, nb_graphs);
            delete neigh;
        }
        
        run_path = "NN" + std::to_string(i) + "_ConnexeGraphSize_" + choice + "_Weighted.txt";
        if (!exists("../run/" + run_path)) {
            neighborhood::Neighborhood* neigh = new neighborhood::NN(i, c, new criteria::ConnexeGraphSize(), &getVertexWeight_mod);
            std::cout << endl << "==========" << run_path << "============================" << endl;
            runAllGraphs([neigh, run_path](const string& path)
            {
                runHC(neigh, run_path, path);
            }, nb_graphs);
            delete neigh;
        }
    }

    // NN no weight
    for (neighborhood::NN::Choice c : {neighborhood::NN::Choice::Best, neighborhood::NN::Choice::First, neighborhood::NN::Choice::Worst})
    for (int i = 1; i <= 3; i++)
    {
        string choice = "Best";
        if (c == neighborhood::NN::Choice::First) choice = "First";
        if (c == neighborhood::NN::Choice::Worst) choice = "Worst";

        string run_path = "NN" + std::to_string(i) + "_Degree_" + choice + ".txt";
        if (!exists("../run/" + run_path)) {
            neighborhood::Neighborhood* neigh = new neighborhood::NN(i, c, new criteria::Degree(), &getVertexWeight_1);
            std::cout << endl << "==========" << run_path << "============================" << endl;
            runAllGraphs([neigh, run_path](const string& path)
            {
                runHC(neigh, run_path, path);
            }, nb_graphs);
            delete neigh;
        }
            
        run_path = "NN" + std::to_string(i) + "_ConnexeGraphSize_" + choice + ".txt";
        if (!exists("../run/" + run_path)) {
            neighborhood::Neighborhood* neigh = new neighborhood::NN(i, c, new criteria::ConnexeGraphSize(), &getVertexWeight_1);
            std::cout << endl << "==========" << run_path << "============================" << endl;
            runAllGraphs([neigh, run_path](const string& path)
            {
                runHC(neigh, run_path, path);
            }, nb_graphs);
            delete neigh;
        }
    }

    // runAllGraphs([](const string& path)
    // {
    //     runGradient("gradient.txt", &getVertexWeight_1, path);
    // }, nb_graphs);
    // runAllGraphs([](const string& path)
    // {
    //     runGradient("gradient_Weighted.txt", &getVertexWeight_mod, path);
    // }, nb_graphs);
}

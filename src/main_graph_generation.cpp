
#include "graphs/graphListAdj.hpp"
#include "graphs/graphAdjMatrix.hpp"
#include "graphs/weightedgraphDefs.hpp"

#include <iostream>
#include "utils.hpp"
#include "runAllGraphs.hpp"

#include "hill_climb/hill_climb.hpp"
#include "criteria/degree.hpp"
#include "criteria/connexeGraphSize.hpp"
#include "neighborhood/nn.hpp"

int main(int argc , char* argv [])
{
    int nb_graphs = 30;

    // NN weighted
    for (neighborhood::NN::Choice c : {neighborhood::NN::Choice::Best, neighborhood::NN::Choice::First, neighborhood::NN::Choice::Worst})
    for (int i = 1; i <= 4; i++)
    {
        string choice = "Best";
        if (c == neighborhood::NN::Choice::First) choice = "First";
        if (c == neighborhood::NN::Choice::Worst) choice = "Worst";
        neighborhood::Neighborhood* neigh = new neighborhood::NN(1, c, new criteria::Degree(), &getVertexWeight_mod);
        runAllGraphs([neigh, i, choice](const string& path)
        {
            runHC(neigh, "NN" + std::to_string(i) + "_Degree_" + choice + "_Weighted.txt", path);
        }, nb_graphs);

        neigh = new neighborhood::NN(1, c, new criteria::ConnexeGraphSize, &getVertexWeight_mod);
        runAllGraphs([neigh, i, choice](const string& path)
        {
            runHC(neigh, "NN" + std::to_string(i) + "_ConnexeGraphSize_" + choice + "_Weighted.txt", path);
        }, nb_graphs);
    }

    // NN no weight
    for (neighborhood::NN::Choice c : {neighborhood::NN::Choice::Best, neighborhood::NN::Choice::First, neighborhood::NN::Choice::Worst})
    for (int i = 1; i <= 4; i++)
    {
        string choice = "Best";
        if (c == neighborhood::NN::Choice::First) choice = "First";
        if (c == neighborhood::NN::Choice::Worst) choice = "Worst";
        neighborhood::Neighborhood* neigh = new neighborhood::NN(1, c, new criteria::Degree(), &getVertexWeight_1);
        runAllGraphs([neigh, i, choice](const string& path)
        {
            runHC(neigh, "NN" + std::to_string(i) + "_Degree_" + choice + ".txt", path);
        }, nb_graphs);

        neigh = new neighborhood::NN(1, c, new criteria::ConnexeGraphSize, &getVertexWeight_1);
        runAllGraphs([neigh, i, choice](const string& path)
        {
            runHC(neigh, "NN" + std::to_string(i) + "_ConnexeGraphSize_" + choice + ".txt", path);
        }, nb_graphs);
    }

    runAllGraphs([](const string& path)
    {
        runGradient("gradient.txt", &getVertexWeight_1, path);
    }, nb_graphs);
    runAllGraphs([](const string& path)
    {
        runGradient("gradient_Weighted.txt", &getVertexWeight_mod, path);
    }, nb_graphs);
}

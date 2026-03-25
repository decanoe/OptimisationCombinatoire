#pragma once
#include "neighborhood/neighborhood.hpp"
#include <functional>

void runGradient(const string& path);
void runHC(neighborhood::Neighborhood* n, const string& save_path, const string& path);

void runAllGraphs(function<void(const string&)> runner, int nb_graphs);
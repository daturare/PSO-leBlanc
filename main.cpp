#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include <stack>
#include <map>
#include <cmath>

#include <stdlib.h>
#include <time.h>

#include "data.h"
#include "dijkstra.h"
#include "particle.h"
#include "swarm.h"
#include "optimization.h"

int main(){
    optimize(particles_amount, vertex_amount, iterations_amount, graph, d, t0, lower_bound, upper_bound, e, precision, c1, c2);
    GetFlowVector(graph, vertex_amount, d);
}

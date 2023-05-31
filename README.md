# PSO-leBlanc
swarm-and-evolutionary-algorithms-for-bilevel-optimization-problem

A lot of optimization problems and decision-making processes faced by public and private organizations are hierarchical in sense that decisions at the top level are influenced by lower-level actors. Decision makers at the top level are usually fully aware of the issues at the bottom, while those at lower levels oversee the leaders' decisions and optimize their own strategies.

Bilevel optimization problems are a class of complex optimization problems in which one problem contains the other as a constraint. Their structure suggests that the optimal solution to the lower level problem is a suitable candidate for the upper level optimization problem.

Approbation of swarm intelligence tools for solving bilevel optimization problems on test examples was carried out. The obtained results are compared with evolutionary procedures for solving bilevel optimization problems on test examples (BLEAQ and BPSOQ algorithms). The most efficient algorithm is adapted for solving problems of bilevel optimization on transport networks (PSODP–LeBlanc algorithm with dynamic inertia coefficient). Efficient procedures for solving the problem of transport network topology optimization using the constructed heuristics are implemented.

PSO interia factor.ipynb

is devoted to the analysis of parameter changes in the calculation of the particle velocity vector for various test functions.

PSO for transport routing problem.ipynb

is devoted to the implementation of the traveling salesman problem solution by the PSO-algorithm.

task1.pdf and task2.pdf

describe the mathematical formulation of the problemon which the implemented algorithms were tested on.

##BLEAQ_for_task1.nb and PSO_for_task1.nb swarm and evolutionary approaches that were used to solve problem 1. They allow you to vary the number of variables in the problem.

BPSOQ.nb

This algorithm solves task2. Approaches to optimization of the upper and lower levels of the considered problem are different. At the upper level, it is proposed to find the optimal value of the function using swarm intelligence with selected adaptations, at the lower level, optimization is implemented by the LeBlanc algorithm.

data.xlxs

The Sioux-Falls network was chosen to test the algorithm BPSOQ. It can be represented as a directed weighted graph consisting of 24 nodes and 74 arcs. Visualization of the test network is shown in below.

image

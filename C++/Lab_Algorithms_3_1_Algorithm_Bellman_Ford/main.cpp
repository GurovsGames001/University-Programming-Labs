#include <iostream>
#include <vector>
#include <list>
#include "AlgorithmBellmanFord.h"

void runProgram(std::istream& inStream, std::ostream& outStream);

int main()
{
	try
	{
		runProgram(std::cin, std::cout);
	}

	catch (const std::string& error)
	{
		std::cout << std::endl << error << std::endl;
		return -1;
	}

	return 0;
}

void runProgram(std::istream& inStream, std::ostream& outStream)
{
	unsigned int nVertex = 0;
	inStream >> nVertex;

	DirectedGraph graph(nVertex);

	int currentVertex = 0;
	int adjacentVertex = 0;
	double weightEdge = 0.0;
	for (unsigned int i = 0; i < nVertex; i++)
	{
		inStream >> currentVertex;

		inStream >> adjacentVertex;
		while (adjacentVertex != -1)
		{
			inStream >> weightEdge;
			graph.addEdge(currentVertex, adjacentVertex, weightEdge);
			inStream >> adjacentVertex;
		}
	}

	int sourceVertexGraph = 0;
	inStream >> sourceVertexGraph;

	AlgorithmBellmanFord algorithmBellmanFord;
	algorithmBellmanFord(graph, sourceVertexGraph);
}
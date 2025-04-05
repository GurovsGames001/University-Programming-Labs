#include <iostream>
#include <vector>
#include <list>
#include "BuilderMetagraph.h"

void runProgram(std::istream& inStream, std::ostream& outStream);

int main()
{
	runProgram(std::cin, std::cout);

	return 0;
}

void runProgram(std::istream& inStream, std::ostream& outStream)
{
	int nVertex = 0;
	inStream >> nVertex;

	std::vector<std::list<int>> adjOther(nVertex);
	int currentVertex = 0;
	int adjacentVertex = 0;
	for (int i = 0; i < nVertex; i++)
	{
		inStream >> currentVertex;

		inStream >> adjacentVertex;
		while (adjacentVertex != -1)
		{
			adjOther[currentVertex].push_back(adjacentVertex);
			inStream >> adjacentVertex;
		}
	}

	DirectedGraph graph(adjOther);

	BuilderMetagraph builderMetagraph;
	builderMetagraph.buildMetagraph(graph);
	builderMetagraph.printSCC();
	builderMetagraph.printMetagraph();
}
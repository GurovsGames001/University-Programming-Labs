#include "BuilderMetagraph.h"
#include <iostream>

static int curSCC = -1; // ����� ��� �������

// ��������� ������� ��� ������ �-�� getPostValue
	// ����: 1) ����� ����� vertex (����� ������� �������), 
	//				����� ��� 0 <= vertex <= nVertex - 1;
	//		 2) ������ post[0..nVertex - 1] �� ����������� ����� 
	//				(������ ������ � ������� �������� �� post-��������), 
	//				��� nVertex - ��� ���������� ������ �������.
	// �����: � ����� ������� post ����������� ������� �� ���������, 
	//			������ ����� vertex.
void getPostValue(const int vertex, std::vector<int>& post)
{
	post.push_back(vertex);
}

// ��������� ������ ���
	// ����: 1) ����� ����� vertex (����� ������� �������), 
	//				����� ��� 0 <= vertex <= nVertex - 1;
	//		 2) ������ numSCC[0..nVertex - 1] �� ����������� ����� 
	//				(������ ��� �������), ��� nVertex - 
	//				- ��� ���������� ������ �������.
	// �����: numSCC[vertex] ���������� ������ ����� curSCC.
void getNumberSCC(const int vertex, std::vector<int>& numSCC)
{
	numSCC[vertex] = curSCC;
}

// ���������� ��������� �������
	// ����: ������ graph.
	// �����: ������ graphReverse, ���������� ���������� ������� graph.
void BuilderMetagraph::buildGraphReverse(const DirectedGraph& graph)
{
	unsigned int nVertex = graph.adj.size();

	graphReverse.adj.resize(nVertex);

	for (unsigned int i = 0; i < nVertex; i++)
	{
		for (std::list<int>::const_iterator it = graph.adj[i].begin(); 
				it != graph.adj[i].end(); it++)
		{
			graphReverse.adj[*it].push_back(i);
		}
	}
}

// ��������� ��� �������
	// ����: ������ graph.
	// �����: 1) ������ numSCC[0..nVertex - 1] �� ����������� �����, �����, 
	//				��� numSCC[v] �������� ������� ���, ���������� ������� v ������� graph;
	//		  2) ������ arraySCC[0..nSCC - 1] �� ������� � ������������ ������� 
	//				(nSCC - ��� ���������� ��� �������), �����, ��� arrayForPrintSCC[i] 
	//				�������� ������� ���� ������ i-� ��� ������� graph.
void BuilderMetagraph::getSCC(const DirectedGraph& graph)
{
	// ���������� ��������� �������
	this->buildGraphReverse(graph);

	// ������������� ������� ��� ������ ������� � �������
	unsigned int nVertex = graph.adj.size();
	std::vector<bool> visited(nVertex);

	// ������������� ������� ��� ���������� ������ ������� 
	//		� ������� �������� �� post-��������
	std::vector<int> post;

	// ����� ��������� ������� � ������� � ����� ��������� ������� post 
	//		���� ������ � ������� �������� �� post - ��������
	for (unsigned int i = 0; i < nVertex; i++)
	{
		if (!visited[i])
		{
			visit(i, graphReverse.adj, visited, post, getPostValue);
		}
	}

	// ����� �������� � ������� ��� ������ ������� � �������
	// � ��������� ������ ��� ������� � �������� ��� �������
	curSCC = -1;
	std::fill(visited.begin(), visited.end(), false);
	numSCC.resize(nVertex);

	// ����� ������� � ������� � ����� ��������� ������� ��� ��� ������ �������
	for (std::vector<int>::reverse_iterator it = post.rbegin(); 
			it != post.rend(); it++)
	{
		if (!visited[*it])
		{
			curSCC++;
			visit(*it, graph, visited, numSCC, getNumberSCC);
		}
	}

	// ���������� ������� �� ��� ��� ������
	arrayForPrintSCC.resize(curSCC + 1);
	for (unsigned int i = 0; i < nVertex; i++)
	{
		arrayForPrintSCC[numSCC[i]].push_back(i);
	}
}

// ����� ������� � �������
	// �����������: 1) vertex - ������� �������;
	//				2) visited[z] = false ��� ������ z, ���������� �� vertex.
	// �����������: 1) visited[z] = true ��� ������ z, ���������� �� vertex;
	//				2) visited[u] ������� ��� �� ��� ���� u, �� ���������� �� vertex.
void BuilderMetagraph::visit(const int vertex, const DirectedGraph& graph,
	std::vector<bool>& visited, std::vector<int>& arrayForPostVisit,
	void (*postVisit)(const int vertex, std::vector<int>& arrayForPostVisit))
{
	visited[vertex] = true;

	for (std::list<int>::const_iterator it = graph.adj[vertex].begin(); 
			it != graph.adj[vertex].end(); it++)
	{
		if (!visited[*it])
		{
			visit(*it, graph, visited, arrayForPostVisit, postVisit);
		}
	}
	postVisit(vertex, arrayForPostVisit);
}

// ���������� ��������� �������
	// ����: ������ graph.
	// �����: ������ metagraph, ���������� ���������� ������� graph.
void BuilderMetagraph::buildMetagraph(const DirectedGraph& graph)
{
	// ��������� ��� �������
	this->getSCC(graph);

	metagraph.adj.resize(curSCC + 1);
	unsigned int nVertex = numSCC.size();
	unsigned int numberCurrentSCC = 0;
	unsigned int numberOtherSCC = 0;

	// ������� ��������� ��� ����, ����� ��������� ������������ ���� 
	// � ������� metagraph
	std::vector<std::vector<bool>> matrixAddedSCC(curSCC + 1, 
			std::vector<bool>(curSCC + 1));

	for (unsigned int i = 0; i < nVertex; i++)
	{
		numberCurrentSCC = numSCC[i];
		for (std::list<int>::const_iterator it = graph.adj[i].begin(); 
				it != graph.adj[i].end(); it++)
		{
			numberOtherSCC = numSCC[*it];
			if ((numberCurrentSCC != numberOtherSCC) &&
				(!matrixAddedSCC[numberCurrentSCC][numberOtherSCC]))
			{
				metagraph.adj[numberCurrentSCC].push_back(numberOtherSCC);
				matrixAddedSCC[numberCurrentSCC][numberOtherSCC] = true;
			}
		}
	}
}

// ����� ��� �������
void const BuilderMetagraph::printSCC()
{
	unsigned int nSCC = arrayForPrintSCC.size();

	for (unsigned int i = 0; i < nSCC; i++)
	{
		std::cout << "SCC " << i << ":   ";
		for (std::list<int>::const_iterator it = arrayForPrintSCC[i].begin(); 
				it != arrayForPrintSCC[i].end(); it++)
		{
			std::cout << *it << ' ';
		}
		std::cout << std::endl;
	}
}

// ����� ��������� �������
void const BuilderMetagraph::printMetagraph()
{
	std::cout << "Meta-graph:\n";
	unsigned int nVertex = metagraph.adj.size();

	for (unsigned int i = 0; i < nVertex; i++)
	{
		std::cout << i << "   ";
		for (std::list<int>::const_iterator it = metagraph.adj[i].begin(); 
				it != metagraph.adj[i].end(); it++)
		{
			std::cout << *it << ' ';
		}
		std::cout << "  -1\n";
	}
}
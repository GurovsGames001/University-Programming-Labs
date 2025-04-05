#ifndef DIRECTED_GRAPH_AND_BUILDER_METAGRAPH_H
#define DIRECTED_GRAPH_AND_BUILDER_METAGRAPH_H

#include <vector>
#include <list>

class BuilderMetagraph;

class DirectedGraph
{
public:
	DirectedGraph() {};
	DirectedGraph(const std::vector<std::list<int>>& adjOther)
	{
		adj = adjOther;
	};
	DirectedGraph(const DirectedGraph& otherGraph)
	{
		adj = otherGraph.adj;
	};

	~DirectedGraph() {};

	friend BuilderMetagraph;

private:
	std::vector<std::list<int>> adj; // ������ ��������� �������

};


class BuilderMetagraph
{
public:
	BuilderMetagraph() {};
	BuilderMetagraph(const BuilderMetagraph& otherObject) = delete;
	BuilderMetagraph(BuilderMetagraph&& otherObject) = delete;

	~BuilderMetagraph() {};
	
	void buildMetagraph(const DirectedGraph& graph); // ���������� ��������� �������
	void const printSCC(); // ����� ��� �������
	void const printMetagraph(); // ����� ��������� �������

private:
	void buildGraphReverse(const DirectedGraph& graph); // ���������� ��������� �������
	void getSCC(const DirectedGraph& graph); // ��������� ��� �������
	void visit(const int vertex, const DirectedGraph& graph,
		std::vector<bool>& visited, std::vector<int>& arrayForPostVisit,
		void (*postVisit)(const int vertex, std::vector<int>& arrayForPostVisit));

	DirectedGraph graphReverse; // ��������� �������
	std::vector<int> numSCC; // ������ � �������� ��� �������
	std::vector<std::list<int>> arrayForPrintSCC; // ������ � ��� �������
	DirectedGraph metagraph; // �������� �������

};

#endif
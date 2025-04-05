#ifndef DIRECTED_GRAPH_AND_CHECKER_ARRAY_FOR_CHANGES
#define DIRECTED_GRAPH_AND_CHECKER_ARRAY_FOR_CHANGES

#include <vector>
#include <list>

class CheckerArrayForChanges;

class DirectedGraph
{
public:
	DirectedGraph() {};
	DirectedGraph(const unsigned int nVertex)
	{
		adj.resize(nVertex);
	};
	DirectedGraph(const DirectedGraph& otherGraph)
	{
		adj = otherGraph.adj;
	};

	~DirectedGraph() {};

	// ���������� � ������ ����� (sourceVertex, destinationVertex) � ����� weigth
	void addEdge(const unsigned int sourceVertex,
		const unsigned int destinationVertex, const double weigth);

	// ��������� ���� ����� (sourceVertex, destinationVertex)
	double getWeightEdge(const unsigned int sourceVertex,
		const unsigned int destinationVertex) const;

	// ��������� ���������� ������ �������
	unsigned int getNumberVertex() const;

	friend CheckerArrayForChanges;

private:
	// ������ ��������� �������, �. �. � ������ adj[i] ��������� ����
	// (j, w), ��� w - ��� ����� (i, j)
	std::vector<std::list<std::pair<unsigned int, double>>> adj;

};

class CheckerArrayForChanges
{
public:
	CheckerArrayForChanges() {};
	CheckerArrayForChanges(const CheckerArrayForChanges& otherObject) = delete;
	CheckerArrayForChanges(CheckerArrayForChanges&& otherObject) = delete;

	~CheckerArrayForChanges() {};

	// �������� ������� a[1..|V|] �� ��������� (����� ���������� ��������)
	void checkArrayForChanges(const DirectedGraph& graph, 
		const std::vector<double>& a, const int sourceVertex) const;

private:
	// �������� ������� a[1..|V|] �� ��������� (���� ��������)
	bool isNoChangeInArray(const DirectedGraph& graph, 
		const std::vector<double>& a, const int sourceVertex) const;

	// �������� ����������� ���� �� ������������
	bool isCorrectShortestPath(const unsigned int currentVertex,
		const unsigned int nextVertex, const double weigth, 
		const std::vector<double>& a) const;

};

#endif
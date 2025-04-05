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

	// Добавление в орграф ребра (sourceVertex, destinationVertex) с весом weigth
	void addEdge(const unsigned int sourceVertex,
		const unsigned int destinationVertex, const double weigth);

	// Получение веса ребра (sourceVertex, destinationVertex)
	double getWeightEdge(const unsigned int sourceVertex,
		const unsigned int destinationVertex) const;

	// Получение количества вершин орграфа
	unsigned int getNumberVertex() const;

	friend CheckerArrayForChanges;

private:
	// Списки смежности орграфа, т. ч. в списке adj[i] находятся пары
	// (j, w), где w - вес ребра (i, j)
	std::vector<std::list<std::pair<unsigned int, double>>> adj;

};

class CheckerArrayForChanges
{
public:
	CheckerArrayForChanges() {};
	CheckerArrayForChanges(const CheckerArrayForChanges& otherObject) = delete;
	CheckerArrayForChanges(CheckerArrayForChanges&& otherObject) = delete;

	~CheckerArrayForChanges() {};

	// Проверка массива a[1..|V|] на изменения (вывод результата проверки)
	void checkArrayForChanges(const DirectedGraph& graph, 
		const std::vector<double>& a, const int sourceVertex) const;

private:
	// Проверка массива a[1..|V|] на изменения (сама проверка)
	bool isNoChangeInArray(const DirectedGraph& graph, 
		const std::vector<double>& a, const int sourceVertex) const;

	// Проверка кратчайшего пути на правильность
	bool isCorrectShortestPath(const unsigned int currentVertex,
		const unsigned int nextVertex, const double weigth, 
		const std::vector<double>& a) const;

};

#endif
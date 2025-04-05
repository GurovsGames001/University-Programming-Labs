#ifndef DIRECTED_GRAPH_AND_ALGORITHM_BELLMAN_FORD
#define DIRECTED_GRAPH_AND_ALGORITHM_BELLMAN_FORD

#include <vector>
#include <list>

class AlgorithmBellmanFord;

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

	friend AlgorithmBellmanFord;

private:
	// Списки смежности орграфа, т. ч. в списке adj[i] находятся пары
	// (j, w), где w - вес ребра (i, j)
	std::vector<std::list<std::pair<unsigned int, double>>> adj;

};

class AlgorithmBellmanFord
{
public:
	AlgorithmBellmanFord() 
	{ 
		isNegativeWeightCycle = false;
		sourceVertex = 0;
	};
	AlgorithmBellmanFord(const AlgorithmBellmanFord& otherObject) = delete;
	AlgorithmBellmanFord(AlgorithmBellmanFord&& otherObject) = delete;

	void operator()(const DirectedGraph& graph, unsigned int sourceVertexGraph);

	~AlgorithmBellmanFord() {};

private:
	// Получение кратчайших путей и дерева кратчайших путей
	void searchShortestPaths(const DirectedGraph& graph);

	// Построение дерева кратчайших путей
	void buildShortestPathsTree(const DirectedGraph& graph);

	// Вывод весов кратчайших путей орграфа
	void printWeightsShortestPaths() const;

	// Вывод дерева кратчайших путей орграфа
	void printShortestPathsTree(const DirectedGraph& graph) const;

	// Релаксация ребра (currentVertex, nextVertex)
	void update(const unsigned int currentVertex, const unsigned int nextVertex, 
		const double weigth, bool& flagNoChanges);

	// Проверка на наличие в графе достижимого из начальной 
	// вершины цикла отрицательного веса
	void checkNegativeWeightCycle(const unsigned int currentVertex, 
		const unsigned int nextVertex, const double weigth);

	// Обход орграфа в глубину с целью вывода дерева кратчайших путей орграфа
	void visitForPrintTree(const int vertex, 
		unsigned int nSpace) const;


	// Начальная вершина (d[sourceVertex] = 0)
	unsigned int sourceVertex;

	// массив d, т. ч. d[v] = δ(s, v) для всех v ∈ V;
	std::vector<double> d;

	// массив arrayPredecessors, т. ч. орграф, построенный на основе этого массива
	// — дерево кратчайших путей с корнем sourceVertex.
	std::vector<int> arrayPredecessors;

	// Орграф, являющийся деревом кратчайших путей с корнем sourceVertex
	DirectedGraph shortestPathsTree;

	// Индикатор наличия в графе достижимого из начальной 
	// вершины цикла отрицательного веса
	bool isNegativeWeightCycle;

};

#endif
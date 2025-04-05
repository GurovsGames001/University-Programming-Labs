#include "AlgorithmBellmanFord.h"
#include <iostream>
#include <iomanip>

static const std::string ERROR_EDGE_DOES_NOT_EXIST = "ERROR: This edge doesn't exist";

/////////////////////////////////////////////////////////////////////////////////////
// Методы класса DirectedGraph

// Добавление в орграф ребра (vertex, adjacentVertex) с весом weigth
// Вход: 1) вершина vertex;
//		 2) вершина adjacentVertex, т. ч. (vertex, adjacentVertex) 
//			является ребром исходного орграфа;
//		 3) вес weigth ребра (vertex, adjacentVertex).
// Выход: в список adj[vertex] добавляется вершина adjacentVertex с весом weigth.
void DirectedGraph::addEdge(const unsigned int vertex,
		const unsigned int adjacentVertex, const double weigth)
{
	adj[vertex].push_back({ adjacentVertex, weigth });
}

// Получение веса ребра (sourceVertex, destinationVertex)
// Вход: 1) вершина sourceVertex;
//		 2) вершина destinationVertex, т. ч. (vertex, adjacentVertex) 
//			является ребром исходного орграфа.
// Выход: либо вес ребра (sourceVertex, destinationVertex),
//		  либо исключение ERROR_EDGE_DOES_NOT_EXIST, если данного ребра 
//			   не существует в исходном орграфе
double DirectedGraph::getWeightEdge(const unsigned int sourceVertex,
		const unsigned int destinationVertex) const
{
	for (const std::pair<unsigned int, double>& nextVertex : adj[sourceVertex])
	{
		if (nextVertex.first == destinationVertex)
		{
			return nextVertex.second;
		}
	}
	throw ERROR_EDGE_DOES_NOT_EXIST;
}

// Получение количества вершин орграфа
unsigned int DirectedGraph::getNumberVertex() const
{
	return adj.size();
}

/////////////////////////////////////////////////////////////////////////////////////
// Методы класса AlgorithmBellmanFord

void AlgorithmBellmanFord::operator()(const DirectedGraph& graph,
		unsigned int sourceVertexGraph)
{
	isNegativeWeightCycle = false;
	sourceVertex = sourceVertexGraph;

	searchShortestPaths(graph);
	printWeightsShortestPaths();
	printShortestPathsTree(graph);
}

// Получение кратчайших путей и дерева кратчайших путей
// Вход: орграф graph.
// Выход: либо сообщение "A negative-weight cycle is reachable from the source vertex"
//		  либо 1) d[v] = δ(s, v) для всех v ∈ V;
//			   2) массив arrayPredecessors, т. ч. граф, 
//				  построенный на основе этого массива
//				  — дерево кратчайших путей с корнем s.
void AlgorithmBellmanFord::searchShortestPaths(const DirectedGraph& graph)
{
	const unsigned int nVertex = graph.getNumberVertex();
	d.resize(nVertex);
	arrayPredecessors.resize(nVertex);

	// Инициализация массивов d и arrayPredecessors
	for (unsigned int i = 0; i < nVertex; i++)
	{
		d[i] = (INFINITY);
		arrayPredecessors[i] = -1;
	}

	// Значение кратчайшего пути для начальной вершины
	d[sourceVertex] = 0;

	bool flagNoChanges = true;
	// Получение кратчайших путей и предшественников для всех вершин
	for (unsigned int i = 0; i < nVertex - 1; i++)
	{
		flagNoChanges = true;

		for (unsigned int j = 0; j < nVertex; j++)
		{
			for (const std::pair<unsigned int, double>& nextVertex : graph.adj[j])
			{
				update(j, nextVertex.first, nextVertex.second, flagNoChanges);
			}
		}

		if (flagNoChanges)
		{
			break;
		}
	}

	// Проверка на наличие в графе достижимого из начальной 
	// вершины цикла отрицательного веса
	if (!flagNoChanges)
	{
		for (unsigned int i = 0; i < nVertex; i++)
		{
			for (const std::pair<unsigned int, double>& nextVertex : graph.adj[i])
			{
				checkNegativeWeightCycle(i, nextVertex.first, nextVertex.second);
			}

			if (isNegativeWeightCycle)
			{
				std::cout << "\nA negative-weight cycle is reachable from the source vertex\n";
				break;
			}
		}
	}

	// Создание дерева кратчайших путей - орграфа на основе массива arrayPredecessors
	buildShortestPathsTree(graph);
}

// Построение дерева кратчайших путей
void AlgorithmBellmanFord::buildShortestPathsTree(const DirectedGraph& graph)
{
	const unsigned int nVertex = graph.getNumberVertex();
	DirectedGraph tempShortestPathsTree(nVertex);
	for (unsigned int i = 0; i < nVertex; i++)
	{
		if (arrayPredecessors[i] != -1)
		{
			tempShortestPathsTree.addEdge(arrayPredecessors[i], i,
				graph.getWeightEdge(arrayPredecessors[i], i));
		}
	}

	shortestPathsTree = tempShortestPathsTree;
}

// Релаксация ребра (currentVertex, nextVertex)
// Вход: 1) вершина currentVertex;
//		 2) вершина nextVertex, т. ч. (currentVertex, nextVertex) 
//			является ребром исходного орграфа;
//		 3) вес weigth ребра (currentVertex, nextVertex);
//		 4) булевская переменная flagNoChanges - флаг отсутствия изменений 
//			в массивах d и arrayPredecessors.
// Выход: если d[nextVertex] > d[currentVertex] + weigth, то 
//		  d[nextVertex] = d[currentVertex] + weigth,
//		  arrayPredecessors[nextVertex] = currentVertex.
void AlgorithmBellmanFord::update(const unsigned int currentVertex, 
		const unsigned int nextVertex, const double weigth, bool& flagNoChanges)
{
	if (d[nextVertex] > d[currentVertex] + weigth)
	{
		d[nextVertex] = d[currentVertex] + weigth;
		arrayPredecessors[nextVertex] = currentVertex;

		flagNoChanges = false;
	}
}

// Проверка на наличие в графе достижимого из начальной 
// вершины цикла отрицательного веса
// Вход: 1) вершина currentVertex;
//		 2) вершина nextVertex, т. ч. (currentVertex, nextVertex) 
//			является ребром исходного орграфа;
//		 3) вес weigth ребра (currentVertex, nextVertex).
// Выход: если d[nextVertex] > d[currentVertex] + weigth, то 
//		  isNegativeWeightCycle = true.
void AlgorithmBellmanFord::checkNegativeWeightCycle(const unsigned int currentVertex,
		const unsigned int nextVertex, const double weigth)
{
	if (d[nextVertex] > d[currentVertex] + weigth)
	{
		isNegativeWeightCycle = true;
	}
}

// Вывод кратчайших путей орграфа
void AlgorithmBellmanFord::printWeightsShortestPaths() const
{
	if (!isNegativeWeightCycle)
	{
		const unsigned int nVertex = d.size();

		std::cout << "\nThe weight of a shortest path from vertex " 
				<< sourceVertex << " to vertex\n";
		for (unsigned int i = 0; i < nVertex; i++)
		{
			std::cout << i << " is " << d[i] << std::endl;
		}
	}
}

// Вывод дерева кратчайших путей орграфа
void AlgorithmBellmanFord::printShortestPathsTree(const DirectedGraph& graph) const
{
	if (!isNegativeWeightCycle)
	{
		unsigned int nSpace = -2;

		std::cout << "\nA shortest-paths tree:\n";
		visitForPrintTree(sourceVertex, nSpace);
		std::cout << std::endl;
	}
}

// Обход дерева кратчайших путей в глубину с целью его вывода
void AlgorithmBellmanFord::visitForPrintTree(const int sourceVertex, 
		unsigned int nSpace) const
{
	nSpace += 2;
	std::cout << std::setw(nSpace) << sourceVertex << std::endl;
	for (const std::pair<unsigned int, double>& nextVertex : 
			shortestPathsTree.adj[sourceVertex])
	{
		visitForPrintTree(nextVertex.first, nSpace);
	}
}
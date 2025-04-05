//#include <iostream>
//#include <vector>
//#include <list>
//#include <iomanip>
//
//class AlgorithmBellmanFord;
//
//class DirectedGraph
//{
//public:
//	DirectedGraph() {};
//	DirectedGraph(const unsigned int nVertex)
//	{
//		adj.resize(nVertex);
//	};
//	DirectedGraph(const DirectedGraph& otherGraph)
//	{
//		adj = otherGraph.adj;
//	};
//
//	~DirectedGraph() {};
//
//	// Добавление в орграф ребра (sourceVertex, destinationVertex) с весом weigth
//	void addEdge(const unsigned int sourceVertex,
//		const unsigned int destinationVertex, const double weigth);
//
//	// Получение веса ребра (sourceVertex, destinationVertex)
//	double getWeightEdge(const unsigned int sourceVertex,
//		const unsigned int destinationVertex) const;
//
//	// Получение количества вершин орграфа
//	unsigned int getNumberVertex() const;
//
//	friend AlgorithmBellmanFord;
//
//private:
//	// Списки смежности орграфа, т. ч. в списке adj[i] находятся пары
//	// (j, w), где w - вес ребра (i, j)
//	std::vector<std::list<std::pair<unsigned int, double>>> adj;
//
//};
//
//class AlgorithmBellmanFord
//{
//public:
//	AlgorithmBellmanFord()
//	{
//		isNegativeWeightCycle = false;
//		sourceVertex = 0;
//	};
//	AlgorithmBellmanFord(const AlgorithmBellmanFord& otherObject) = delete;
//	AlgorithmBellmanFord(AlgorithmBellmanFord&& otherObject) = delete;
//
//	void operator()(const DirectedGraph& graph, unsigned int sourceVertexGraph);
//
//	~AlgorithmBellmanFord() {};
//
//private:
//	// Получение кратчайших путей и дерева кратчайших путей
//	void searchShortestPaths(const DirectedGraph& graph);
//
//	// Построение дерева кратчайших путей
//	void buildShortestPathsTree(const DirectedGraph& graph);
//
//	// Вывод весов кратчайших путей орграфа
//	void printWeightsShortestPaths() const;
//
//	// Вывод дерева кратчайших путей орграфа
//	void printShortestPathsTree(const DirectedGraph& graph) const;
//
//	// Релаксация ребра (currentVertex, nextVertex)
//	void update(const unsigned int currentVertex, const unsigned int nextVertex,
//		const double weigth, bool& flagNoChanges);
//
//	// Проверка на наличие в графе достижимого из начальной 
//	// вершины цикла отрицательного веса
//	void checkNegativeWeightCycle(const unsigned int currentVertex,
//		const unsigned int nextVertex, const double weigth);
//
//	// Обход орграфа в глубину с целью вывода дерева кратчайших путей орграфа
//	void visitForPrintTree(const int vertex,
//		unsigned int nSpace) const;
//
//
//	// Начальная вершина (d[sourceVertex] = 0)
//	unsigned int sourceVertex;
//
//	// массив d, т. ч. d[v] = δ(s, v) для всех v ∈ V;
//	std::vector<double> d;
//
//	// массив arrayPredecessors, т. ч. орграф, построенный на основе этого массива
//	// — дерево кратчайших путей с корнем sourceVertex.
//	std::vector<int> arrayPredecessors;
//
//	// Орграф, являющийся деревом кратчайших путей с корнем sourceVertex
//	DirectedGraph shortestPathsTree;
//
//	// Индикатор наличия в графе достижимого из начальной 
//	// вершины цикла отрицательного веса
//	bool isNegativeWeightCycle;
//
//};
//
//static const std::string ERROR_EDGE_DOES_NOT_EXIST = "ERROR: This edge doesn't exist";
//
///////////////////////////////////////////////////////////////////////////////////////
//// Методы класса DirectedGraph
//
//// Добавление в орграф ребра (vertex, adjacentVertex) с весом weigth
//// Вход: 1) вершина vertex;
////		 2) вершина adjacentVertex, т. ч. (vertex, adjacentVertex) 
////			является ребром исходного орграфа;
////		 3) вес weigth ребра (vertex, adjacentVertex).
//// Выход: в список adj[vertex] добавляется вершина adjacentVertex с весом weigth.
//void DirectedGraph::addEdge(const unsigned int vertex,
//		const unsigned int adjacentVertex, const double weigth)
//{
//	adj[vertex].push_back({ adjacentVertex, weigth });
//}
//
//// Получение веса ребра (sourceVertex, destinationVertex)
//// Вход: 1) вершина sourceVertex;
////		 2) вершина destinationVertex, т. ч. (vertex, adjacentVertex) 
////			является ребром исходного орграфа.
//// Выход: либо вес ребра (sourceVertex, destinationVertex),
////		  либо исключение ERROR_EDGE_DOES_NOT_EXIST, если данного ребра 
////			   не существует в исходном орграфе
//double DirectedGraph::getWeightEdge(const unsigned int sourceVertex,
//		const unsigned int destinationVertex) const
//{
//	for (const std::pair<unsigned int, double>& nextVertex : adj[sourceVertex])
//	{
//		if (nextVertex.first == destinationVertex)
//		{
//			return nextVertex.second;
//		}
//	}
//	throw ERROR_EDGE_DOES_NOT_EXIST;
//}
//
//// Получение количества вершин орграфа
//unsigned int DirectedGraph::getNumberVertex() const
//{
//	return adj.size();
//}
//
///////////////////////////////////////////////////////////////////////////////////////
//// Методы класса AlgorithmBellmanFord
//
//void AlgorithmBellmanFord::operator()(const DirectedGraph& graph,
//		unsigned int sourceVertexGraph)
//{
//	isNegativeWeightCycle = false;
//	sourceVertex = sourceVertexGraph;
//
//	searchShortestPaths(graph);
//	printWeightsShortestPaths();
//	printShortestPathsTree(graph);
//}
//
//// Получение кратчайших путей и дерева кратчайших путей
//// Вход: орграф graph.
//// Выход: либо сообщение "A negative-weight cycle is reachable from the source vertex"
////		  либо 1) d[v] = δ(s, v) для всех v ∈ V;
////			   2) массив arrayPredecessors, т. ч. граф, 
////				  построенный на основе этого массива
////				  — дерево кратчайших путей с корнем s.
//void AlgorithmBellmanFord::searchShortestPaths(const DirectedGraph& graph)
//{
//	const unsigned int nVertex = graph.getNumberVertex();
//	d.resize(nVertex);
//	arrayPredecessors.resize(nVertex);
//
//	// Инициализация массивов d и arrayPredecessors
//	for (unsigned int i = 0; i < nVertex; i++)
//	{
//		d[i] = (INFINITY);
//		arrayPredecessors[i] = -1;
//	}
//
//	// Значение кратчайшего пути для начальной вершины
//	d[sourceVertex] = 0;
//
//	bool flagNoChanges = true;
//	// Получение кратчайших путей и предшественников для всех вершин
//	for (unsigned int i = 0; i < nVertex - 1; i++)
//	{
//		flagNoChanges = true;
//
//		for (unsigned int j = 0; j < nVertex; j++)
//		{
//			for (const std::pair<unsigned int, double>& nextVertex : graph.adj[j])
//			{
//				update(j, nextVertex.first, nextVertex.second, flagNoChanges);
//			}
//		}
//
//		if (flagNoChanges)
//		{
//			break;
//		}
//	}
//
//	// Проверка на наличие в графе достижимого из начальной 
//	// вершины цикла отрицательного веса
//	if (!flagNoChanges)
//	{
//		for (unsigned int i = 0; i < nVertex; i++)
//		{
//			for (const std::pair<unsigned int, double>& nextVertex : graph.adj[i])
//			{
//				checkNegativeWeightCycle(i, nextVertex.first, nextVertex.second);
//			}
//
//			if (isNegativeWeightCycle)
//			{
//				std::cout << "\nA negative-weight cycle is reachable from the source vertex\n";
//				break;
//			}
//		}
//	}
//
//	// Создание дерева кратчайших путей - орграфа на основе массива arrayPredecessors
//	buildShortestPathsTree(graph);
//}
//
//// Построение дерева кратчайших путей
//void AlgorithmBellmanFord::buildShortestPathsTree(const DirectedGraph& graph)
//{
//	const unsigned int nVertex = graph.getNumberVertex();
//	DirectedGraph tempShortestPathsTree(nVertex);
//	for (unsigned int i = 0; i < nVertex; i++)
//	{
//		if (arrayPredecessors[i] != -1)
//		{
//			tempShortestPathsTree.addEdge(arrayPredecessors[i], i,
//					graph.getWeightEdge(arrayPredecessors[i], i));
//		}
//	}
//
//	shortestPathsTree = tempShortestPathsTree;
//}
//
//// Релаксация ребра (currentVertex, nextVertex)
//// Вход: 1) вершина currentVertex;
////		 2) вершина nextVertex, т. ч. (currentVertex, nextVertex) 
////			является ребром исходного орграфа;
////		 3) вес weigth ребра (currentVertex, nextVertex);
////		 4) булевская переменная flagNoChanges - флаг отсутствия изменений 
////			в массивах d и arrayPredecessors.
//// Выход: если d[nextVertex] > d[currentVertex] + weigth, то 
////		  d[nextVertex] = d[currentVertex] + weigth,
////		  arrayPredecessors[nextVertex] = currentVertex.
//void AlgorithmBellmanFord::update(const unsigned int currentVertex,
//		const unsigned int nextVertex, const double weigth, bool& flagNoChanges)
//{
//	if (d[nextVertex] > d[currentVertex] + weigth)
//	{
//		d[nextVertex] = d[currentVertex] + weigth;
//		arrayPredecessors[nextVertex] = currentVertex;
//
//		flagNoChanges = false;
//	}
//}
//
//// Проверка на наличие в графе достижимого из начальной 
//// вершины цикла отрицательного веса
//// Вход: 1) вершина currentVertex;
////		 2) вершина nextVertex, т. ч. (currentVertex, nextVertex) 
////			является ребром исходного орграфа;
////		 3) вес weigth ребра (currentVertex, nextVertex).
//// Выход: если d[nextVertex] > d[currentVertex] + weigth, то 
////		  isNegativeWeightCycle = true.
//void AlgorithmBellmanFord::checkNegativeWeightCycle(const unsigned int currentVertex,
//		const unsigned int nextVertex, const double weigth)
//{
//	if (d[nextVertex] > d[currentVertex] + weigth)
//	{
//		isNegativeWeightCycle = true;
//	}
//}
//
//// Вывод кратчайших путей орграфа
//void AlgorithmBellmanFord::printWeightsShortestPaths() const
//{
//	if (!isNegativeWeightCycle)
//	{
//		const unsigned int nVertex = d.size();
//
//		std::cout << "\nThe weight of a shortest path from vertex "
//				<< sourceVertex << " to vertex\n";
//		for (unsigned int i = 0; i < nVertex; i++)
//		{
//			std::cout << i << " is " << d[i] << std::endl;
//		}
//	}
//}
//
//// Вывод дерева кратчайших путей орграфа
//void AlgorithmBellmanFord::printShortestPathsTree(const DirectedGraph& graph) const
//{
//	if (!isNegativeWeightCycle)
//	{
//		unsigned int nSpace = -2;
//
//		std::cout << "\nA shortest-paths tree:\n";
//		visitForPrintTree(sourceVertex, nSpace);
//		std::cout << std::endl;
//	}
//}
//
//// Обход дерева кратчайших путей в глубину с целью его вывода
//void AlgorithmBellmanFord::visitForPrintTree(const int sourceVertex,
//	unsigned int nSpace) const
//{
//	nSpace += 2;
//	std::cout << std::setw(nSpace) << sourceVertex << std::endl;
//	for (const std::pair<unsigned int, double>& nextVertex :
//			shortestPathsTree.adj[sourceVertex])
//	{
//		visitForPrintTree(nextVertex.first, nSpace);
//	}
//}
//
//void runProgram(std::istream& inStream, std::ostream& outStream);
//
//int main()
//{
//	try
//	{
//		runProgram(std::cin, std::cout);
//	}
//
//	catch (const std::string& error)
//	{
//		std::cout << std::endl << error << std::endl;
//		return -1;
//	}
//
//	return 0;
//}
//
//void runProgram(std::istream& inStream, std::ostream& outStream)
//{
//	unsigned int nVertex = 0;
//	inStream >> nVertex;
//
//	DirectedGraph graph(nVertex);
//
//	int currentVertex = 0;
//	int adjacentVertex = 0;
//	double weightEdge = 0.0;
//	for (unsigned int i = 0; i < nVertex; i++)
//	{
//		inStream >> currentVertex;
//
//		inStream >> adjacentVertex;
//		while (adjacentVertex != -1)
//		{
//			inStream >> weightEdge;
//			graph.addEdge(currentVertex, adjacentVertex, weightEdge);
//			inStream >> adjacentVertex;
//		}
//	}
//
//	int sourceVertexGraph = 0;
//	inStream >> sourceVertexGraph;
//
//	AlgorithmBellmanFord algorithmBellmanFord;
//	algorithmBellmanFord(graph, sourceVertexGraph);
//}
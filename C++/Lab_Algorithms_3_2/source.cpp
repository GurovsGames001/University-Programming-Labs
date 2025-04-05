//#include <iostream>
//#include <vector>
//#include <list>
//
//class CheckerArrayForChanges;
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
//	friend CheckerArrayForChanges;
//
//private:
//	// Списки смежности орграфа, т. ч. в списке adj[i] находятся пары
//	// (j, w), где w - вес ребра (i, j)
//	std::vector<std::list<std::pair<unsigned int, double>>> adj;
//
//};
//
//class CheckerArrayForChanges
//{
//public:
//	CheckerArrayForChanges() {};
//	CheckerArrayForChanges(const CheckerArrayForChanges& otherObject) = delete;
//	CheckerArrayForChanges(CheckerArrayForChanges&& otherObject) = delete;
//
//	~CheckerArrayForChanges() {};
//
//	// Проверка массива a[1..|V|] на изменения (вывод результата проверки)
//	void checkArrayForChanges(const DirectedGraph& graph,
//		const std::vector<double>& a, const int sourceVertex) const;
//
//private:
//	// Проверка массива a[1..|V|] на изменения (сама проверка)
//	bool isNoChangeInArray(const DirectedGraph& graph,
//		const std::vector<double>& a, const int sourceVertex) const;
//
//	// Проверка кратчайшего пути на правильность
//	bool isCorrectShortestPath(const unsigned int currentVertex,
//		const unsigned int nextVertex, const double weigth,
//		const std::vector<double>& a) const;
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
//	const unsigned int adjacentVertex, const double weigth)
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
//	const unsigned int destinationVertex) const
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
//// Проверка массива a[1..|V|] на изменения (вывод результата проверки)
//// Вход: 1) орграф graph без достижимых из начальной вершины циклов 
////			отрицательного веса;
////		 2) массив a[1..|V|], т. ч. для всех v ∈ V выполняется a[v] ≥ δ(s, v);
////		 3) начальная вершина sourceVertex.
//// Выход: сообщение «Array a[1..|V|] has not been changed», если 
////		  для всех вершин v орграфа graph выполняется a[v] = δ(s, v); или
////	      сообщение «Array a[1..|V|] has been changed», если есть хотя бы одна 
////		  вершина v орграфа graph, т. ч. a[v] > δ(s, v).
//void CheckerArrayForChanges::checkArrayForChanges(const DirectedGraph& graph,
//	const std::vector<double>& a, const int sourceVertex)  const
//{
//	if (isNoChangeInArray(graph, a, sourceVertex))
//	{
//		std::cout << "\nArray a[1..|V|] has not been changed\n";
//	}
//	else
//	{
//		std::cout << "\nArray a[1..|V|] has been changed\n";
//	}
//}
//
//// Проверка массива a[1..|V|] на изменения (сама проверка)
//// Вход: 1) орграф graph без достижимых из начальной вершины циклов 
////			отрицательного веса;
////		 2) массив a[1..|V|], т. ч. для всех v ∈ V выполняется a[v] ≥ δ(s, v);
//// 		 3) начальная вершина sourceVertex.
//// Выход: true, если для всех вершин v орграфа graph выполняется 
////		  a[v] = δ(s, v); или
////	      false, если есть хотя бы одна вершина v орграфа graph, 
////		  т. ч. a[v] > δ(s, v).
//bool CheckerArrayForChanges::isNoChangeInArray(const DirectedGraph& graph,
//	const std::vector<double>& a, const int sourceVertex)  const
//{
//	if (a[sourceVertex] > 0)
//	{
//		return false;
//	}
//	else
//	{
//		unsigned int nVertex = graph.adj.size();
//
//		for (int i = 0; i < nVertex; i++)
//		{
//			for (std::list<std::pair<unsigned int, double>>::const_iterator
//				it = graph.adj[i].begin(); it != graph.adj[i].end(); it++)
//			{
//				if (!isCorrectShortestPath(i, it->first, it->second, a))
//				{
//					return false;
//				}
//			}
//		}
//	}
//
//	return true;
//}
//
//// Проверка кратчайшего пути на правильность
//// Вход: 1) вершина currentVertex;
////	     2) вершина nextVertex, т. ч. (currentVertex, nextVertex) 
////			является ребром исходного орграфа;
////		 3) вес weigth ребра (currentVertex, nextVertex);
////		 4) массив a[1..|V|], т. ч. для всех v ∈ V выполняется a[v] ≥ δ(s, v).
//// Выход: true, если a[nextVertex] ≤ a[currentVertex] + weigth; или
////	      false, если a[nextVertex] > a[currentVertex] + weigth.
//bool CheckerArrayForChanges::isCorrectShortestPath(const unsigned int currentVertex,
//	const unsigned int nextVertex, const double weigth, const std::vector<double>& a) const
//{
//	if (a[nextVertex] > a[currentVertex] + weigth)
//	{
//		return false;
//	}
//
//	return true;
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
//	int nVertex = 0;
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
//	// Ввод массива a
//	std::vector<double> a(nVertex);
//	for (int i = 0; i < nVertex; i++)
//	{
//		inStream >> a[i];
//	}
//
//	CheckerArrayForChanges checkerArrayForChanges;
//
//	checkerArrayForChanges.checkArrayForChanges(graph, a, sourceVertexGraph);
//}
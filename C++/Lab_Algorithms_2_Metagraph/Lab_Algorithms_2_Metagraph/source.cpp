//#include <iostream>
//#include <vector>
//#include <list>
//
//class BuilderMetagraph;
//
//class DirectedGraph
//{
//public:
//	DirectedGraph() {};
//	DirectedGraph(const std::vector<std::list<int>>& adjOther)
//	{
//		adj = adjOther;
//	};
//	DirectedGraph(const DirectedGraph& otherGraph)
//	{
//		adj = otherGraph.adj;
//	};
//
//	~DirectedGraph() {};
//
//	friend BuilderMetagraph;
//
//private:
//	std::vector<std::list<int>> adj; // Списки смежности орграфа
//
//};
//
//
//class BuilderMetagraph
//{
//public:
//	BuilderMetagraph() {};
//	BuilderMetagraph(const BuilderMetagraph& otherObject) = delete;
//	BuilderMetagraph(BuilderMetagraph&& otherObject) = delete;
//
//	~BuilderMetagraph() {};
//
//	void buildMetagraph(const DirectedGraph& graph); // Построение метаграфа орграфа
//	void const printSCC(); // Вывод ССК орграфа
//	void const printMetagraph(); // Вывод метаграфа орграфа
//
//private:
//	void buildGraphReverse(const DirectedGraph& graph); // Построение обращения орграфа
//	void getSCC(const DirectedGraph& graph); // Получение ССК орграфа
//	void visit(const int vertex, const DirectedGraph& graph,
//		std::vector<bool>& visited, std::vector<int>& arrayForPostVisit,
//		void (*postVisit)(const int vertex, std::vector<int>& arrayForPostVisit));
//
//	DirectedGraph graphReverse; // Обращение орграфа
//	std::vector<int> numSCC; // Массив с номерами ССК орграфа
//	std::vector<std::list<int>> arrayForPrintSCC; // Массив с ССК орграфа
//	DirectedGraph metagraph; // Метаграф орграфа
//
//};
//
//static int curSCC = -1; // Номер ССК орграфа
//
//// Получение времени при вызове ф-ии getPostValue
//	// Вход: 1) целое число vertex (номер вершины орграфа), 
//	//				такое что 0 <= vertex <= nVertex - 1;
//	//		 2) массив post[0..nVertex - 1] из натуральных чисел 
//	//				(номера вершин в порядке убывания их post-значений), 
//	//				где nVertex - это количество вершин орграфа.
//	// Выход: в конец массива post добавляется элемент со значением, 
//	//			равным числу vertex.
//void getPostValue(const int vertex, std::vector<int>& post)
//{
//	post.push_back(vertex);
//}
//
//// Получение номера ССК
//	// Вход: 1) целое число vertex (номер вершины орграфа), 
//	//				такое что 0 <= vertex <= nVertex - 1;
//	//		 2) массив numSCC[0..nVertex - 1] из натуральных чисел 
//	//				(номера ССК орграфа), где nVertex - 
//	//				- это количество вершин орграфа.
//	// Выход: numSCC[vertex] становится равным числу curSCC.
//void getNumberSCC(const int vertex, std::vector<int>& numSCC)
//{
//	numSCC[vertex] = curSCC;
//}
//
//// Построение обращения орграфа
//	// Вход: орграф graph.
//	// Выход: орграф graphReverse, являющийся обращением орграфа graph.
//void BuilderMetagraph::buildGraphReverse(const DirectedGraph& graph)
//{
//	unsigned int nVertex = graph.adj.size();
//
//	graphReverse.adj.resize(nVertex);
//
//	for (unsigned int i = 0; i < nVertex; i++)
//	{
//		for (std::list<int>::const_iterator it = graph.adj[i].begin();
//			it != graph.adj[i].end(); it++)
//		{
//			graphReverse.adj[*it].push_back(i);
//		}
//	}
//}
//
//// Получение ССК орграфа
//	// Вход: орграф graph.
//	// Выход: 1) массив numSCC[0..nVertex - 1] из натуральных чисел, такой, 
//	//				что numSCC[v] является номером ССК, содержащей вершину v орграфа graph;
//	//		  2) массив arraySCC[0..nSCC - 1] из списков с натуральными числами 
//	//				(nSCC - это количество ССК орграфа), такой, что arrayForPrintSCC[i] 
//	//				является списком всех вершин i-й ССК орграфа graph.
//void BuilderMetagraph::getSCC(const DirectedGraph& graph)
//{
//	// Построение обращения орграфа
//	this->buildGraphReverse(graph);
//
//	// Инициализация вектора для обхода орграфа в глубину
//	unsigned int nVertex = graph.adj.size();
//	std::vector<bool> visited(nVertex);
//
//	// Инициализация вектора для сохранения вершин орграфа 
//	//		в порядке убывания их post-значений
//	std::vector<int> post;
//
//	// Обход обращения орграфа в глубину с целью получения массива post 
//	//		всех вершин в порядке убывания их post - значений
//	for (unsigned int i = 0; i < nVertex; i++)
//	{
//		if (!visited[i])
//		{
//			visit(i, graphReverse.adj, visited, post, getPostValue);
//		}
//	}
//
//	// Сброс значений в векторе для обхода орграфа в глубину
//	// и выделение памяти для вектора с номерами ССК орграфа
//	curSCC = -1;
//	std::fill(visited.begin(), visited.end(), false);
//	numSCC.resize(nVertex);
//
//	// Обход орграфа в глубину с целью получения номеров ССК для каждой вершины
//	for (std::vector<int>::reverse_iterator it = post.rbegin();
//		it != post.rend(); it++)
//	{
//		if (!visited[*it])
//		{
//			curSCC++;
//			visit(*it, graph, visited, numSCC, getNumberSCC);
//		}
//	}
//
//	// Построение массива из ССК для вывода
//	arrayForPrintSCC.resize(curSCC + 1);
//	for (unsigned int i = 0; i < nVertex; i++)
//	{
//		arrayForPrintSCC[numSCC[i]].push_back(i);
//	}
//}
//
//// Обход орграфа в глубину
//	// Предусловие: 1) vertex - вершина орграфа;
//	//				2) visited[z] = false для каждой z, достижимой из vertex.
//	// Постусловие: 1) visited[z] = true для каждой z, достижимой из vertex;
//	//				2) visited[u] остаётся тем же для всех u, не достижимых из vertex.
//void BuilderMetagraph::visit(const int vertex, const DirectedGraph& graph,
//	std::vector<bool>& visited, std::vector<int>& arrayForPostVisit,
//	void (*postVisit)(const int vertex, std::vector<int>& arrayForPostVisit))
//{
//	visited[vertex] = true;
//
//	for (std::list<int>::const_iterator it = graph.adj[vertex].begin();
//		it != graph.adj[vertex].end(); it++)
//	{
//		if (!visited[*it])
//		{
//			visit(*it, graph, visited, arrayForPostVisit, postVisit);
//		}
//	}
//	postVisit(vertex, arrayForPostVisit);
//}
//
//// Построение метаграфа орграфа
//	// Вход: орграф graph.
//	// Выход: орграф metagraph, являющийся метаграфом орграфа graph.
//void BuilderMetagraph::buildMetagraph(const DirectedGraph& graph)
//{
//	// Получение ССК орграфа
//	this->getSCC(graph);
//
//	metagraph.adj.resize(curSCC + 1);
//	unsigned int nVertex = numSCC.size();
//	unsigned int numberCurrentSCC = 0;
//	unsigned int numberOtherSCC = 0;
//
//	// Матрица смежности для того, чтобы исключить дублирование рёбер 
//	// в орграфе metagraph
//	std::vector<std::vector<bool>> matrixAddedSCC(curSCC + 1,
//		std::vector<bool>(curSCC + 1));
//
//	for (unsigned int i = 0; i < nVertex; i++)
//	{
//		numberCurrentSCC = numSCC[i];
//		for (std::list<int>::const_iterator it = graph.adj[i].begin();
//			it != graph.adj[i].end(); it++)
//		{
//			numberOtherSCC = numSCC[*it];
//			if ((numberCurrentSCC != numberOtherSCC) &&
//				(!matrixAddedSCC[numberCurrentSCC][numberOtherSCC]))
//			{
//				metagraph.adj[numberCurrentSCC].push_back(numberOtherSCC);
//				matrixAddedSCC[numberCurrentSCC][numberOtherSCC] = true;
//			}
//		}
//	}
//}
//
//// Вывод ССК орграфа
//void const BuilderMetagraph::printSCC()
//{
//	unsigned int nSCC = arrayForPrintSCC.size();
//
//	for (unsigned int i = 0; i < nSCC; i++)
//	{
//		std::cout << "SCC " << i << ":   ";
//		for (std::list<int>::const_iterator it = arrayForPrintSCC[i].begin();
//			it != arrayForPrintSCC[i].end(); it++)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << std::endl;
//	}
//}
//
//// Вывод метаграфа орграфа
//void const BuilderMetagraph::printMetagraph()
//{
//	std::cout << "Meta-graph:\n";
//	unsigned int nVertex = metagraph.adj.size();
//
//	for (unsigned int i = 0; i < nVertex; i++)
//	{
//		std::cout << i << "   ";
//		for (std::list<int>::const_iterator it = metagraph.adj[i].begin();
//			it != metagraph.adj[i].end(); it++)
//		{
//			std::cout << *it << ' ';
//		}
//		std::cout << "  -1\n";
//	}
//}
//
//void runProgram(std::istream& inStream, std::ostream& outStream);
//
//int main()
//{
//	runProgram(std::cin, std::cout);
//
//	return 0;
//}
//
//void runProgram(std::istream& inStream, std::ostream& outStream)
//{
//	int nVertex = 0;
//	inStream >> nVertex;
//
//	std::vector<std::list<int>> adjOther(nVertex);
//	int currentVertex = 0;
//	int adjacentVertex = 0;
//	for (int i = 0; i < nVertex; i++)
//	{
//		inStream >> currentVertex;
//
//		inStream >> adjacentVertex;
//		while (adjacentVertex != -1)
//		{
//			adjOther[currentVertex].push_back(adjacentVertex);
//			inStream >> adjacentVertex;
//		}
//	}
//
//	DirectedGraph graph(adjOther);
//
//	BuilderMetagraph builderMetagraph;
//	builderMetagraph.buildMetagraph(graph);
//	builderMetagraph.printSCC();
//	builderMetagraph.printMetagraph();
//}
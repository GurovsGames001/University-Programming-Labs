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
	std::vector<std::list<int>> adj; // Списки смежности орграфа

};


class BuilderMetagraph
{
public:
	BuilderMetagraph() {};
	BuilderMetagraph(const BuilderMetagraph& otherObject) = delete;
	BuilderMetagraph(BuilderMetagraph&& otherObject) = delete;

	~BuilderMetagraph() {};
	
	void buildMetagraph(const DirectedGraph& graph); // Построение метаграфа орграфа
	void const printSCC(); // Вывод ССК орграфа
	void const printMetagraph(); // Вывод метаграфа орграфа

private:
	void buildGraphReverse(const DirectedGraph& graph); // Построение обращения орграфа
	void getSCC(const DirectedGraph& graph); // Получение ССК орграфа
	void visit(const int vertex, const DirectedGraph& graph,
		std::vector<bool>& visited, std::vector<int>& arrayForPostVisit,
		void (*postVisit)(const int vertex, std::vector<int>& arrayForPostVisit));

	DirectedGraph graphReverse; // Обращение орграфа
	std::vector<int> numSCC; // Массив с номерами ССК орграфа
	std::vector<std::list<int>> arrayForPrintSCC; // Массив с ССК орграфа
	DirectedGraph metagraph; // Метаграф орграфа

};

#endif
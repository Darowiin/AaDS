#include <functional>
#include "DLinkedList.cpp"
#include "HashTable.cpp"

class Graph {
	struct Edge {
		int from;
		int to;
		double distance;
	};
	DLinkedList<int> _vertices;
	UnorderedMap<int, DLinkedList<Edge>> _edges;
public:
	bool add_vertex(int vertex) {
		auto it = std::find(_vertices.begin(), _vertices.end(), vertex);
		if (it != _vertices.end()) return false;
		_vertices.push_back(vertex);
		_edges.insert(vertex, {});
		return true;
	}
	bool delete_vertex(int vertex) {
		auto it = std::find(_vertices.begin(), _vertices.end(), vertex);
		if (it == _vertices.end()) return false;
		_vertices.erase(it);
		_edges.erase(vertex);
		for (auto& vert : _vertices) {
			auto& list_edge = _edges.search(vert);
			for (auto i = list_edge.begin(); i != list_edge.end(); ++i) {
				if ((*i).to == vertex) i = list_edge.erase(i);
			}
		}
		return true;
	}
	void add_edge(const Edge& e) {
	}
	bool remove_edge(const Edge& e);

	void dwalk(int start, std::function<void(int)> f);
	void bwalk(int start, std::function<void(int)> f);

	DLinkedList<Edge> dijkstra(int start);
	DLinkedList<Edge> bellmanford(int start);

	const DLinkedList<int> vertices() const {
		return _vertices;
	}
	const UnorderedMap<int, DLinkedList<Edge>> edges() const {
		return _edges;
	}
};
#include <deque>
#include <queue>
#include <unordered_set>

template <class Vertex, class Graph, class Visitor>
void BreadthFirstSearch(Vertex origin_vertex, const Graph &graph,
                        Visitor visitor) {
    std::unordered_set<Vertex> visited({origin_vertex});
    std::queue<Vertex> visit_queue({origin_vertex});
    visitor.DiscoverVertex(origin_vertex);
    while (!visit_queue.empty()) {
        auto current_vertex = visit_queue.front();
        visit_queue.pop();
        visitor.ExamineVertex(current_vertex);
        for (const auto& edge : OutgoingEdges(graph, current_vertex)) {
            visitor.ExamineEdge(edge);
            auto target_vertex = GetTarget(graph, edge);
            if (visited.find(target_vertex) == visited.end()) {
                visitor.DiscoverVertex(target_vertex);
                visit_queue.push(target_vertex);
                visited.insert(target_vertex);
            }
        }
    }
}

template <class Vertex, class Edge>
class BfsVisitor {
public:
    virtual void DiscoverVertex(Vertex /*vertex*/) {}
    virtual void ExamineEdge(const Edge & /*edge*/) {}
    virtual void ExamineVertex(Vertex /*vertex*/) {}
    virtual ~BfsVisitor() = default;
};

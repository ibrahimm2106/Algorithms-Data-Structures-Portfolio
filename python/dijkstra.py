"""Dijkstra shortest-path implementation for the Coursework 2 graph."""

from heapq import heappop, heappush
from math import inf
from typing import Dict, Iterable, List, Mapping, Optional, Tuple

Graph = Mapping[str, Iterable[Tuple[str, int]]]

# Adjacency list documented in the submitted Coursework 2 report.
COURSEWORK_GRAPH: Dict[str, List[Tuple[str, int]]] = {
    "A": [("B", 2), ("C", 3)],
    "B": [("D", 5), ("E", 6)],
    "C": [("D", 8), ("F", 9)],
    "D": [("E", 8)],
    "E": [("F", 5)],
    "F": [("A", 5)],
}


def dijkstra(graph: Graph, start: str) -> Tuple[Dict[str, float], Dict[str, Optional[str]]]:
    if start not in graph:
        raise KeyError(f"Start node {start!r} is not present in graph")

    nodes = set(graph)
    for edges in graph.values():
        for neighbour, weight in edges:
            if weight < 0:
                raise ValueError("Dijkstra's algorithm requires non-negative edge weights")
            nodes.add(neighbour)

    distances: Dict[str, float] = {node: inf for node in nodes}
    previous: Dict[str, Optional[str]] = {node: None for node in nodes}
    distances[start] = 0

    queue: List[Tuple[float, str]] = [(0, start)]
    while queue:
        current_distance, node = heappop(queue)
        if current_distance != distances[node]:
            continue

        for neighbour, weight in graph.get(node, []):
            candidate = current_distance + weight
            if candidate < distances[neighbour]:
                distances[neighbour] = candidate
                previous[neighbour] = node
                heappush(queue, (candidate, neighbour))

    return distances, previous


def reconstruct_path(previous: Mapping[str, Optional[str]], start: str, destination: str) -> List[str]:
    path: List[str] = []
    node: Optional[str] = destination
    while node is not None:
        path.append(node)
        if node == start:
            return list(reversed(path))
        node = previous[node]
    return []


if __name__ == "__main__":
    distances, previous = dijkstra(COURSEWORK_GRAPH, "A")
    for node in sorted(distances):
        print(f"A -> {node}: distance={distances[node]:g}, path={' -> '.join(reconstruct_path(previous, 'A', node))}")

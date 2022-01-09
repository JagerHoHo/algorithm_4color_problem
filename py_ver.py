class n_color_solution:

    def __init__(self, adjacent: list, colors: list):
        self._adjacent = adjacent
        self._colors = colors
        self._coloring = [None] * len(adjacent)
        self._colored = set()

    def _clash(self, color: int, node: int) -> bool:
        return any(self._coloring[neighbor] == color for neighbor in self._adjacent[node])

    def solvable(self, node: int = 0, curr_color: int = 0) -> bool:
        if node in self._colored or self._clash(curr_color, node):
            return False
        self._colored.add(node)
        self._coloring[node] = curr_color
        if len(self._colored) == len(self._adjacent):
            for i, _ in enumerate(self._adjacent):
                print(f"Node{i + 1}: {self._colors[self._coloring[i]]}")
            return True
        for neighbor in self._adjacent[node]:
            for color in range(len(self._colors)):
                if self.solvable(neighbor, color):
                    return True
        return False


def main():
    if input("Do you wanna use the default case of the question in class (Y/N)? ").upper() != "Y":
        n_nodes = input("Enter number of nodes: ")
        n_colors = input("Enter number of colors: ")
        adj = []
        for i in range(int(n_nodes)):
            adj.append([])
            while (node := input(f"Enter neighbor of node {i + 1}(input end to stop entering):")) != "end":
                adj[i].append(int(node) - 1)
        colors = [input(f"Enter name of color {i + 1}:") for i in range(int(n_colors))]
    else:
        adj = [
            [1, 2],  # 1
            [0, 2, 3, 4, 5],  # 2
            [0, 1, 3, 7, 8],  # 3
            [1, 2, 4, 6, 8, 9],  # 4
            [1, 3, 5, 6],  # 5
            [1, 4],  # 6
            [3, 4, 8, 9],  # 7
            [2, 8],  # 8
            [2, 3, 6, 7, 9],  # 9
            [3, 6, 8]  # 10
        ]
        colors = ["RED", "GREEN", "BLUE", "YELLOW"]
    solution = n_color_solution(adj, colors)
    print(solution.solvable())


if __name__ == '__main__':
    main()
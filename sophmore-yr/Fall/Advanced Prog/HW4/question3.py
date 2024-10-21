"""
UMass ECE 241 - Advanced Programming
Homework #4     Fall 2023
question3.py - Tree Traversal
"""


class Question3:
    @staticmethod
    def example():
        """
        Find the minimum element in a binary search tree
        """
        return "DFS"
    
    @staticmethod
    def question1():
        """
        Given a node n, find its nearest neighbor
        """
        return "BFS"
    
    @staticmethod
    def question2():
        """
        Find the shortest path between 2 vertices(nodes) in a graph.
        """
        return "BFS"
    
    @staticmethod
    def question3():
        """
        Find the shortest cycle in a directed graph.
        """
        return "DFS"
    
    @staticmethod
    def question4():
        """
        Find the longest cycle in a directed graph.
        """
        return "DFS"
    
    @staticmethod
    def question5():
        """
        Which tree traversal scheme uses more memory
        """
        return "BFS"
    
    
if __name__ == "__main__":
    print("Find the minimum element in a binary search tree: ", Question3.example())
    print("Given a node n, find its nearest neighbor: ", Question3.question1())
    print("Find the shortest path between 2 vertices(nodes) in a graph: ", Question3.question2())
    print("Find the shortest cycle in a directed graph: ", Question3.question3())
    print("Find the longest cycle in a directed graph: ", Question3.question4())
    print("Which tree traversal scheme uses more memory: ", Question3.question5())
    

    
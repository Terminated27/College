"""
UMass ECE 241 - Advanced Programming
Homework #4     Fall 2023
question1.py - BFS and DFS
"""


class Question1:
    @staticmethod
    def example():
        """
        This is an example: if the node traversed are A, B, C, D, E, F
        then the function should return the following list
        """
        return ['A', 'B', 'C', 'D', 'E', 'F']
        
    @staticmethod
    def DFSA():
        """
        Returns a list of nodes in the order they are 
        visited during a DFS starting from node A.
        """
        return ['A', 'B', 'D', 'G', 'C', 'F', 'H', 'E']
    
    @staticmethod
    def DFSG():
        """
        Returns a list of nodes in the order they are 
        visited during a DFS starting from node G.
        """
        return ['G', 'C', 'A', 'B', 'D', 'E', 'F', 'H']
    
    @staticmethod
    def BFSF():
        """
        Returns a list of nodes in the order they are 
        visited during a BFS starting from node F.
        """
        return ['F', 'C', 'G', 'H', 'A', 'D', 'E', 'B']
    
    @staticmethod
    def BFSB():
        """
        Returns a list of nodes in the order they are 
        visited during a DFS starting from node B.
        """
        return ['B', 'A', 'D', 'E', 'C', 'G', 'F', 'H']
    
    @staticmethod
    def BFSH():
        """
        Returns a list of nodes in the order they are 
        visited during a DFS starting from node H.
        """
        return ['H', 'F', 'C', 'G', 'A', 'D', 'E', 'B']
        
        
        
if __name__ == "__main__":
    print("Depth First Search from A: ",   "->".join(Question1.DFSA()), sep="\t")
    print("Depth First Search from G: ",   "->".join(Question1.DFSG()), sep="\t")
    print("Breadth First Search from F: ", "->".join(Question1.BFSF()), sep="\t")
    print("Breadth First Search from B: ", "->".join(Question1.BFSB()), sep="\t")
    print("Breadth First Search from H: ", "->".join(Question1.BFSH()), sep="\t")
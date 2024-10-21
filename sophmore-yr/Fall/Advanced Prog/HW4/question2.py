"""
UMass ECE 241 - Advanced Programming
Homework #4     Fall 2023
question2.py - AVL Trees
"""


class Question2:
    @staticmethod
    def balancedTrees():
        """
        Return the list of trees that are balanced.
        
        Choose all that applies from "a", "b", "c", and "d"
        
        For example, if you think a, c are balanced and b, d
        are unbalanced, you should return ["a", "c"]
        """
        
        return ["b", "c", "d"]
    
    @staticmethod
    def balanceFactors():
        """
        Return the balance factor of each tree (at root).
        """
        
        return {
            "a": 2,     # balance factor for root node for tree (a)
            "b": 1,     # balance factor for root node for tree (b)
            "c": 1,     # balance factor for root node for tree (c)
            "d": 1,      # balance factor for root node for tree (d)
        }
        
    @staticmethod
    def insertion():
        """
        Fill in the AVL tree list after inserting
        10, 20, 15, 25, 30, 16, 18, 19
        according to the question.
        First two steps is done for you. 
        """
        AVL_tree_lists = [
            [10],
            [10, 
            None, 20],
            [15, 
            10, 20],
            [15,
            10, 20,
            None, None, None, 25],
            [20,
            15, 25, 
            10, None, None, 30],
            [20, 
            15, 25, 
            10, 16, None, 30],
            [16, 
            15, 20, 
            10, 18, 25, 30],
            [16, 
            15, 20,
            10, 18, 25, 30,
            None, None, None, 19, None, None, None, None],
            

        ]
        
        """
        Fill in the balance factor lists 
        for each steps of the AVL_tree_lists above.
        First two steps is done for you.
        """
        balance_factors = [
            [0],
            [-1, 
            None, 0],
            [0,
            0, 0],
            [-1,
            0, -1,
            None, None, None, 0],
            [0,
            1, -1, 
            0, None, None, 0],
            [0, 
            0, -1, 
            0, 0, None, 0],
            [0, 
            0, 0, 
            0, 0, 0, 0],
            [1, 
            -1, 0,
            0, -1, 0, 0,
            None, None, None, 0, None, None, None, None],
        ]
        
        return {
            "AVL_tree_lists": AVL_tree_lists,
            "balance_factors": balance_factors
        }


if __name__ == "__main__":
    pass
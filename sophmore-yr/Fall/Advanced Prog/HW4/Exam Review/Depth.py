# Define the Node and Tree classes
class Node:
    def __init__(self, k, v, l=None, r=None):
        self.key = k
        self.value = v
        self.leftChild = l
        self.rightChild = r

class Tree:
    def __init__(self, r=None):
        self.root = r

# Define the treeHeight function
def treeHeight(node):
    if node.leftChild is None and node.rightChild is None:
        # Leaf node
        return 0
    if node.leftChild is not None:
        left_height = treeHeight(node.leftChild)
    else:
        left_height = 0
    if node.rightChild is not None:
        right_height = treeHeight(node.rightChild)
    else:
        right_height = 0
    return max(left_height, right_height) + 1

# Test the Node, Tree, and treeHeight function
if __name__ == "__main__":
    # Create a sample binary tree
    #      10
    #     /  \
    #    5   20
    #   / \
    #  3   7
    root = Node(10, "Root")
    root.leftChild = Node(5, "Left Child")
    root.rightChild = Node(20, "Right Child")
    root.leftChild.leftChild = Node(3, "Left-Left Child")
    root.leftChild.rightChild = Node(7, "Left-Right Child")
    
    # Create a Tree instance with the root node
    tree = Tree(root)
    
    # Calculate and print the height of the tree
    height = treeHeight(tree.root)
    print("Height of the tree:", height)

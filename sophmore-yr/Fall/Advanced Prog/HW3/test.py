import pytest
from question2 import Node

class TestFindPath:
    @pytest.fixture
    def binary_tree(self):
        # Create a binary tree for testing
        root = Node(10)
        root.leftChild = Node(5)
        root.rightChild = Node(15)
        root.leftChild.parent = root
        root.rightChild.parent = root
        root.leftChild.leftChild = Node(3)
        root.leftChild.rightChild = Node(7)
        root.leftChild.leftChild.parent = root.leftChild
        root.leftChild.rightChild.parent = root.leftChild
        root.rightChild.leftChild = Node(12)
        root.rightChild.rightChild = Node(17)
        root.rightChild.leftChild.parent = root.rightChild
        root.rightChild.rightChild.parent = root.rightChild
        return root

    @pytest.mark.parametrize(
        "element_1, element_2, nature, expected_path, expected_steps",
        [
            (Node(3), Node(7), 0, [3, 5, 7], 3),
            (Node(7), Node(3), 0, [3, 5, 7], 3),
            (Node(3), Node(7), 1, [7, 5, 3], 3),
            (Node(7), Node(3), 1, [7, 5, 3], 3),
            (Node(3), Node(12), 0, [3, 5, 10, 15, 12], 5),
            (Node(12), Node(3), 0, [3, 5, 10, 15, 12], 5),
            (Node(3), Node(12), 1, [12, 15, 10, 5, 3], 5),
            (Node(12), Node(3), 1, [12, 15, 10, 5, 3], 5),
            (Node(3), Node(17), 0, [3, 5, 10, 15, 17], 5),
            (Node(17), Node(3), 0, [3, 5, 10, 15, 17], 5),
            (Node(3), Node(17), 1, [17, 15, 10, 5, 3], 5),
            (Node(17), Node(3), 1, [17, 15, 10, 5, 3], 5),
            (Node(5), Node(5), 0, [5], 1),
            (Node(5), Node(5), 1, [5], 1),
            (Node(100), Node(200), 0, None, None),
            (Node(100), Node(200), 1, None, None),
        ],
        ids=[
            "Path from 3 to 7 (nature=0)",
            "Path from 7 to 3 (nature=0)",
            "Path from 3 to 7 (nature=1)",
            "Path from 7 to 3 (nature=1)",
            "Path from 3 to 12 (nature=0)",
            "Path from 12 to 3 (nature=0)",
            "Path from 3 to 12 (nature=1)",
            "Path from 12 to 3 (nature=1)",
            "Path from 3 to 17 (nature=0)",
            "Path from 17 to 3 (nature=0)",
            "Path from 3 to 17 (nature=1)",
            "Path from 17 to 3 (nature=1)",
            "Path from 5 to 5 (nature=0)",
            "Path from 5 to 5 (nature=1)",
            "Path from 100 to 200 (nature=0)",
            "Path from 100 to 200 (nature=1)",
        ],
    )
    def test_find_path(
        self, binary_tree, element_1, element_2, nature, expected_path, expected_steps
    ):
        # Arrange
        node = binary_tree

        # Act
        path, steps = node._find_path(element_1, element_2, nature)

        # Assert
        assert path == expected_path
        assert steps == expected_steps

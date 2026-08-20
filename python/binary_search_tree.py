"""Binary search tree for unique letters from a name."""

from dataclasses import dataclass
from typing import List, Optional


@dataclass
class Node:
    value: str
    left: Optional["Node"] = None
    right: Optional["Node"] = None


class BinarySearchTree:
    """BST that ignores duplicate letters, as permitted by the coursework brief."""

    def __init__(self) -> None:
        self.root: Optional[Node] = None

    def insert(self, value: str) -> None:
        if len(value) != 1:
            raise ValueError("BST values must be single characters")
        value = value.lower()

        if self.root is None:
            self.root = Node(value)
            return

        current = self.root
        while True:
            if value == current.value:
                return
            if value < current.value:
                if current.left is None:
                    current.left = Node(value)
                    return
                current = current.left
            else:
                if current.right is None:
                    current.right = Node(value)
                    return
                current = current.right

    def add_text(self, text: str) -> None:
        for character in text.lower():
            if "a" <= character <= "z":
                self.insert(character)

    def contains(self, value: str) -> bool:
        value = value.lower()
        current = self.root
        while current:
            if value == current.value:
                return True
            current = current.left if value < current.value else current.right
        return False

    def inorder(self) -> List[str]:
        output: List[str] = []

        def visit(node: Optional[Node]) -> None:
            if node is None:
                return
            visit(node.left)
            output.append(node.value)
            visit(node.right)

        visit(self.root)
        return output


if __name__ == "__main__":
    tree = BinarySearchTree()
    tree.add_text("Mohamed Ibrahim")
    print("In-order traversal:", tree.inorder())

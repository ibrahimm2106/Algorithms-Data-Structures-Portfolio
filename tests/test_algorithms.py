import unittest
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "python"))

from binary_search_tree import BinarySearchTree
from dijkstra import COURSEWORK_GRAPH, dijkstra, reconstruct_path
from hash_table import AlphabetHashTable
from sorting_algorithms import COURSEWORK_ARRAY, insertion_sort, merge_sort, quick_sort
from string_processor import COURSEWORK_CASES, StringProcessor


class StringProcessorTests(unittest.TestCase):
    def test_all_coursework_cases(self):
        processor = StringProcessor()
        for tokens, expected in COURSEWORK_CASES:
            with self.subTest(tokens=tokens):
                self.assertEqual(processor.process(tokens), expected)

    def test_invalid_operator(self):
        with self.assertRaises(ValueError):
            StringProcessor().process(["a", "*", "b"])


class SortingTests(unittest.TestCase):
    def test_all_sorts_match_python_sorted(self):
        expected = sorted(COURSEWORK_ARRAY)
        self.assertEqual(merge_sort(COURSEWORK_ARRAY), expected)
        self.assertEqual(quick_sort(COURSEWORK_ARRAY), expected)
        self.assertEqual(insertion_sort(COURSEWORK_ARRAY), expected)


class DijkstraTests(unittest.TestCase):
    def test_shortest_distances_from_a(self):
        distances, previous = dijkstra(COURSEWORK_GRAPH, "A")
        self.assertEqual(distances, {"A": 0, "B": 2, "C": 3, "D": 7, "E": 8, "F": 12})
        self.assertEqual(reconstruct_path(previous, "A", "F"), ["A", "C", "F"])


class DataStructureTests(unittest.TestCase):
    def test_hash_table_chaining(self):
        table = AlphabetHashTable()
        table.add_text("Mohamed Ibrahim")
        self.assertEqual(table.occurrences("m"), 3)
        self.assertEqual(table.occurrences("h"), 2)
        self.assertTrue(table.contains("o"))
        self.assertFalse(table.contains("z"))

    def test_bst_inorder_is_sorted_unique_letters(self):
        tree = BinarySearchTree()
        tree.add_text("Mohamed Ibrahim")
        letters = [c for c in "mohamedibrahim" if c.isalpha()]
        self.assertEqual(tree.inorder(), sorted(set(letters)))
        self.assertTrue(tree.contains("r"))
        self.assertFalse(tree.contains("z"))


if __name__ == "__main__":
    unittest.main()

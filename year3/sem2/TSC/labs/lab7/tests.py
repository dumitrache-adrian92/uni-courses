import unittest
from tree import Tree

class TestFind(unittest.TestCase):
    def setUp(self):
        self.tree = Tree()
        self.tree.add(1)
        self.tree.add(2)
        self.tree.add(3)
        self.tree.add(4)
        self.tree.add(5)

    def test_find1(self):
        self.assertEqual(self.tree.find(1).data, 1)

    def test_find2(self):
        self.assertEqual(self.tree.find(7), None)

if __name__ == '__main__':
    unittest.main()
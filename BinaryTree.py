class BinaryTree:
    def __init__(self, nodeData, left=None, right=None):
        self.nodeData = nodeData
        self.left = left
        self.right = right

    def __str__(self):
        return str(self.nodeData)


tree = BinaryTree('Root')


BranchA = BinaryTree('Branch A')

BranchB = BinaryTree('Branch B')


tree.left = BranchA

tree.right = BranchB


LeafC = BinaryTree('Leaf C')

LeafD = BinaryTree('Leaf D')

LeafE = BinaryTree('Leaf E')

LeafF = BinaryTree('Leaf F')


BranchA.left = LeafC

BranchA.right = LeafD

BranchB.left = LeafE

BranchB.right = LeafF

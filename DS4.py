from collections import deque
import copy

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    # Insert
    def insert(self, node, data):
        if node is None:
            return Node(data)
        if data < node.data:
            node.left = self.insert(node.left, data)
        elif data > node.data:
            node.right = self.insert(node.right, data)
        else:
            print("Duplicate Entry Not Allowed")
        return node

    # Search
    def search(self, node, key):
        if node is None:
            return False
        if node.data == key:
            return True
        if key < node.data:
            return self.search(node.left, key)
        return self.search(node.right, key)

    # Find Minimum
    def minimum(self, node):
        while node.left:
            node = node.left
        return node

    # Delete
    def delete(self, node, key):
        if node is None:
            return node
        if key < node.data:
            node.left = self.delete(node.left, key)
        elif key > node.data:
            node.right = self.delete(node.right, key)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            temp = self.minimum(node.right)
            node.data = temp.data
            node.right = self.delete(node.right, temp.data)
        return node

    # Traversals
    def inorder(self, node):
        if node:
            self.inorder(node.left)
            print(node.data, end=" ")
            self.inorder(node.right)

    def preorder(self, node):
        if node:
            print(node.data, end=" ")
            self.preorder(node.left)
            self.preorder(node.right)

    def postorder(self, node):
        if node:
            self.postorder(node.left)
            self.postorder(node.right)
            print(node.data, end=" ")

    # Depth
    def depth(self, node):
        if node is None:
            return 0
        return max(self.depth(node.left), self.depth(node.right)) + 1

    # Mirror
    def mirror(self, node):
        if node:
            node.left, node.right = node.right, node.left
            self.mirror(node.left)
            self.mirror(node.right)

    # Parent Child
    def parentChild(self, node):
        if node:
            print("Parent:", node.data, end=" -> ")
            if node.left:
                print("Left:", node.left.data, end=" ")
            if node.right:
                print("Right:", node.right.data, end=" ")
            print()
            self.parentChild(node.left)
            self.parentChild(node.right)

    # Leaf Nodes
    def leafNodes(self, node):
        if node:
            if node.left is None and node.right is None:
                print(node.data, end=" ")
            self.leafNodes(node.left)
            self.leafNodes(node.right)
# --- Driver Code to Test Implementation ---
if __name__ == "__main__":
    bst = BST()
    
    # 1. Test Insertion
    # Creating a sample tree:
    #        50
    #       /  \
    #     30    70
    #    /  \  /  \
    #   20  40 60  80
    keys = [50, 30, 70, 20, 40, 60, 80]
    for key in keys:
        bst.root = bst.insert(bst.root, key)

    print("--- Traversals ---")
    print("Inorder traversal:")
    bst.inorder(bst.root)  # Expected: 20 30 40 50 60 70 80
    print("\n\nPreorder traversal:")
    bst.preorder(bst.root) # Expected: 50 30 20 40 70 60 80
    print("\n\nPostorder traversal:")
    bst.postorder(bst.root) # Expected: 20 40 30 60 80 70 50
    print("\n")

    print("--- Properties ---")
    print("Tree Depth:", bst.depth(bst.root)) # Expected: 3
    
    print("Leaf Nodes:")
    bst.leafNodes(bst.root) # Expected: 20 40 60 80
    print("\n")

    print("--- Search Test ---")
    print("Search 40:", bst.search(bst.root, 40)) # Expected: True
    print("Search 90:", bst.search(bst.root, 90)) # Expected: False
    print()

    print("--- Parent-Child Relationships ---")
    bst.parentChild(bst.root)
    print()

    print("--- Deletion Test ---")
    print("Deleting leaf node 20...")
    bst.root = bst.delete(bst.root, 20)
    print("Inorder after deletion:")
    bst.inorder(bst.root) # Expected: 30 40 50 60 70 80
    print("\n")

    print("--- Mirror Copy Test ---")
    # Make a deep copy to keep original tree intact before mirroring
    mirrored_root = copy.deepcopy(bst.root)
    bst.mirror(mirrored_root)
    print("Inorder of Mirrored Tree (should be descending):")
    bst.inorder(mirrored_root) # Expected: 80 70 60 50 40 30
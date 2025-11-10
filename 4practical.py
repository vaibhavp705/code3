class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None


class BST:
    def __init__(self):
        self.root = None

    def insert(self, root, key):
        if root is None:
            return Node(key)
        if key < root.key:
            root.left = self.insert(root.left, key)
        elif key > root.key:
            root.right = self.insert(root.right, key)
        else:
            print(f"Duplicate entry '{key}' ignored.")
        return root

    def search(self, root, key):
        if root is None:
            return None
        if root.key == key:
            return root
        if key < root.key:
            return self.search(root.left, key)
        return self.search(root.right, key)

    def inorder(self, root):
        if root:
            self.inorder(root.left)
            print(root.key, end=" ")
            self.inorder(root.right)

    def preorder(self, root):
        if root:
            print(root.key, end=" ")
            self.preorder(root.left)
            self.preorder(root.right)

    def postorder(self, root):
        if root:
            self.postorder(root.left)
            self.postorder(root.right)
            print(root.key, end=" ")

    def delete(self, root, key):
        if root is None:
            print(f"Value {key} not found in tree!")
            return root
        if key < root.key:
            root.left = self.delete(root.left, key)
        elif key > root.key:
            root.right = self.delete(root.right, key)
        else:
            if root.left is None:
                return root.right
            elif root.right is None:
                return root.left
            temp = self.min_value_node(root.right)
            root.key = temp.key
            root.right = self.delete(root.right, temp.key)
        return root

    def min_value_node(self, node):
        current = node
        while current.left:
            current = current.left
        return current


def menu():
    bst = BST()
    while True:
        print("\n------- MENU -------")
        print("1. Insert")
        print("2. Search")
        print("3. Delete")
        print("4. Inorder Traversal")
        print("5. Preorder Traversal")
        print("6. Postorder Traversal")
        print("7. Exit")

        choice = input("Enter your choice: ")

        if choice == "1":
            key = int(input("Enter value to insert: "))
            bst.root = bst.insert(bst.root, key)

        elif choice == "2":
            key = int(input("Enter value to search: "))
            found = bst.search(bst.root, key)
            print("Found!" if found else "Not found.")

        elif choice == "3":
            key = int(input("Enter value to delete: "))
            bst.root = bst.delete(bst.root, key)

        elif choice == "4":
            print("Inorder Traversal: ", end="")
            bst.inorder(bst.root)
            print()

        elif choice == "5":
            print("Preorder Traversal: ", end="")
            bst.preorder(bst.root)
            print()

        elif choice == "6":
            print("Postorder Traversal: ", end="")
            bst.postorder(bst.root)
            print()

        elif choice == "7":
            print("Exiting program.")
            break

        else:
            print("Invalid choice.")


if __name__ == "__main__":
    menu()


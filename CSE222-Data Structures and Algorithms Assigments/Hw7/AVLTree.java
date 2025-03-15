/**
 * AVLTree represents a self-balancing binary search tree with stock data.
 * It supports insertion, deletion, and searching of stocks while maintaining balance.
 */
public class AVLTree{

    /**
     * Node represents a node in the AVL tree.
     */
    private class Node {
        Stock stock;
        int height;
        Node left, right;

        /**
         * Constructs a new node with the specified stock.
         * The height of a new node is initialized to 1.
         * @param stock the stock to be stored in this node
         */
        Node(Stock stock) {
            this.stock = stock;
            this.height = 1;
        }
    }

    private Node root;

    /**
     * Inserts a new stock into the AVL tree.
     * @param stock the stock to be inserted
     * @return the root node of the AVL tree after insertion
     */
    public Node insert(Stock stock){
        root = insert(root, stock);
        return root;
    }

    /**
     * Helper method to insert a stock into the subtree rooted at the given node.
     * @param node the root of the subtree
     * @param stock the stock to be inserted
     * @return the new root of the subtree after insertion
     */
    private Node insert(Node node, Stock stock){
        // The base case,when the node is null that means correct position is found.
        if(node == null){
            return new Node(stock);
        }

        // By comparing the stock with the current node's stock the correct way will be found and recursive call are made.
        int compare = stock.getSymbol().compareTo(node.stock.getSymbol());
        if(compare < 0){
            node.left = insert(node.left, stock);
        }else if(compare > 0){
            node.right = insert(node.right, stock);
        }else{
            return node; // Duplicate keys are not allowed in AVL tree
        }

        //The height of processed nodes are updated.
        node.height = 1 + Math.max(height(node.left), height(node.right));
        
        // To balance the after insertion, find the correct rotation to implement
        int balance = getBalance(node);

        // For left left case,rotate the node on right.
        if(balance > 1 && stock.getSymbol().compareTo(node.left.stock.getSymbol()) < 0){
            return rightRotate(node);
        }

        // For right right case,rotate the node on left.
        if(balance < -1 && stock.getSymbol().compareTo(node.right.stock.getSymbol()) > 0){
            return leftRotate(node);
        }

        // For left right case,rotate the left child on the left and rotate the current node on right.
        if(balance > 1 && stock.getSymbol().compareTo(node.left.stock.getSymbol()) > 0){
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        // For right left case,rotate the right child on the right and rotate the current node on left.
        if(balance < -1 && stock.getSymbol().compareTo(node.right.stock.getSymbol()) < 0){
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }

        return node;
    }

    /**
     * Deletes a stock with the specified symbol from the AVL tree.
     * @param symbol the symbol of the stock to be deleted
     * @return the root node of the AVL tree after deletion
     */
    public Node delete(String symbol){
        root = delete(root, symbol);
        return root;
    }

    /**
     * Helper method to delete a stock from the subtree rooted at the given node.
     * @param node the root of the subtree
     * @param symbol the symbol of the stock to be deleted
     * @return the new root of the subtree after deletion
     */
    private Node delete(Node node, String symbol){
        // The base case,when the node is null that means the searched node isnt found.
        if(node == null){
            return node;
        }

        // By comparing the stock with the current node's stock the correct way will be found and recursive call are made.
        int compare = symbol.compareTo(node.stock.getSymbol());
        if(compare < 0){
            node.left = delete(node.left, symbol);
        }else if(compare > 0){
            node.right = delete(node.right, symbol);
        }else{
            //To find the successor of the deleted node,the possible cases will be found.
            if(node.left == null || node.right == null){
                //If the left or right child is null,then the other child must be successor, if both of them is null
                //then there shouldnt be a successor
                Node temp = (node.left != null) ? node.left : node.right;

                if(temp == null){
                    temp = node;
                    node = null;
                }else{
                    node = temp;
                }
            }else{
                // By using findSuccessor method,the smallest of right subtree will be found as the next successor of deleted node.
                Node temp = findSuccessor(node.right);
                node.stock = temp.stock;
                node.right = delete(node.right, temp.stock.getSymbol());
            }
        }

        //After delete,if node is empty then this means tree is empty. 
        if(node == null){
            return node;
        }

        //The height of processed nodes are updated.
        node.height = 1 + Math.max(height(node.left), height(node.right));
        // To balance the after deletion, find the correct rotation to implement
        int balance = getBalance(node);

        // For left left case,rotate the node on right.
        if(balance > 1 && getBalance(node.left) >= 0){
            return rightRotate(node);
        }

        // For right right case,rotate the node on left.
        if(balance < -1 && getBalance(node.right) <= 0){
            return leftRotate(node);
        }

        // For left right case,rotate the left child on the left and rotate the current node on right.
        if(balance > 1 && getBalance(node.left) < 0){
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        // For right left case,rotate the right child on the right and rotate the current node on left.
        if(balance < -1 && getBalance(node.right) > 0){
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }

        return node;
    }

    /**
     * Finds the node with the smallest value in the given subtree.
     * @param node the root of the subtree
     * @return the node with the smallest value
     */
    private Node findSuccessor(Node node){
        Node current = node;
        while(current.left != null){
            current = current.left;
        }
        return current;
    }

    /**
     * Searches for a stock with the specified symbol in the AVL tree.
     * @param symbol the symbol of the stock to be searched for
     * @return the stock with the specified symbol, or null if not found
     */
    public Stock search(String symbol){
        Node result = search(root, symbol);
        return (result != null) ? result.stock : null;
    }

    /**
     * Helper method to search for a stock in the subtree rooted at the given node.
     * @param node the root of the subtree
     * @param symbol the symbol of the stock to be searched for
     * @return the node containing the stock, or null if not found
     */
    private Node search(Node node, String symbol){
        //If the searched node isnt found or it is found, return the node.
        if(node == null || node.stock.getSymbol().equals(symbol)){
            return node;
        }

        //By comparing stock,the searched node will be found.
        int compare = symbol.compareTo(node.stock.getSymbol());
        if(compare < 0){
            return search(node.left, symbol);
        }else{
            return search(node.right, symbol);
        }
    }

    /**
     * Computes the balance factor of the given node.
     * @param node the node to compute the balance factor for
     * @return the balance factor of the node
     */
    private int getBalance(Node node){
        if(node == null){
            return 0;
        }
        return height(node.left) - height(node.right);
    }

    /**
     * Computes the height of the given node.
     * @param node the node to compute the height for
     * @return the height of the node
     */
    private int height(Node node){
        if(node == null){
            return 0;
        }
        return node.height;
    }

    /**
     * Performs a right rotation on the given node.
     * @param node the node to be rotated
     * @return the new root of the subtree after rotation
     */
    private Node rightRotate(Node node){
        Node leftChild = node.left;
        Node leftChildRight = leftChild.right;

        leftChild.right = node;
        node.left = leftChildRight;

        node.height = Math.max(height(node.left), height(node.right)) + 1;
        leftChild.height = Math.max(height(leftChild.left), height(leftChild.right)) + 1;

        return leftChild;
    }

    /**
     * Performs a left rotation on the given node.
     * @param node the node to be rotated
     * @return the new root of the subtree after rotation
     */
    private Node leftRotate(Node node){
        Node rightChild = node.right;
        Node rightChildLeft = rightChild.left;

        rightChild.left = node;
        node.right = rightChildLeft;

        node.height = Math.max(height(node.left), height(node.right)) + 1;
        rightChild.height = Math.max(height(rightChild.left), height(rightChild.right)) + 1;

        return rightChild;
    }

    /**
     * Performs a pre-order traversal of the AVL tree, starting from the given node.
     * @param node the starting node for the traversal
     */
    private void preOrder(Node node){
        if(node != null){
            System.out.print(node.stock.getSymbol() + " ");
            preOrder(node.left);
            preOrder(node.right);
        }
    }

    /**
     * Performs an in-order traversal of the AVL tree, starting from the given node.
     * @param node the starting node for the traversal
     */
    private void inOrder(Node node){
        if(node != null){
            inOrder(node.left);
            System.out.print(node.stock.getSymbol() + " ");
            inOrder(node.right);
        }
    }

    /**
     * Performs a post-order traversal of the AVL tree, starting from the given node.
     * @param node the starting node for the traversal
     */
    private void postOrder(Node node){
        if(node != null){
            postOrder(node.left);
            postOrder(node.right);
            System.out.print(node.stock.getSymbol() + " ");
        }
    }
}

package reshi.ppt.algorytmy.BST;


import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.function.Consumer;

/**
 * @author Marcin Regulski on 25.04.2016.
 */
@SuppressWarnings("WeakerAccess")
public class BST<K extends Comparable<K>, V> implements Iterable<BSTNode<K, V>> {
    private BSTNode<K, V> root;
    private int size;

    /**
     * Create new empty BST.
     */
    public BST() {
        this.root = null;
        this.size = 0;
    }

    /**
     * Check if tree contains no elements.
     * @return true if the tree contains no elements.
     */
    public boolean isEmpty() {
        return this.root == null;
    }

    public BSTNode<K, V> getRoot() {
        return this.root;
    }

    public int getSize() {
        return size;
    }

    /**
     * Create and insert a new node into the tree.
     * @param key key of the node. This is used for all comparisons within this tree.
     * @param value value associated with the key.
     */
    public void insert (K key, V value) {
        BSTNode<K, V> node = new BSTNode<>(key, value);
        size++;
        if(isEmpty()) {
            this.root = node;
        }
        else {
            insert(node, this.root);
        }
    }

    /**
     * Insert a node into the specified subtree.
     * @param node node to be inserted
     * @param subtree root of a subtree to insert the node into.
     */
    private void insert(BSTNode<K, V> node, BSTNode<K, V> subtree) {
        if(node.getKey().compareTo(subtree.getKey()) > 0) {
            if(subtree.right == null) {
                subtree.right = node;
                node.parent = subtree;
            }
            else {
                insert(node, subtree.right);
            }
        }
        else if (node.getKey().compareTo(subtree.getKey()) < 0) {
            if(subtree.left == null) {
                subtree.left = node;
                node.parent = subtree;
            }
            else {
                insert(node, subtree.left);
            }
        }
        else {
            throw new IllegalArgumentException("Tree cannot contain duplicate keys");
        }

    }

    /**
     * Remove a specific node from the tree.
     * @param node node to be removed
     */
    public void delete(BSTNode<K, V> node) {
        if(node == null) {
            return;
        }
        // node has no children: only remove node.
        // y <- node, x <- null

        // node has 1 child: bind it's child to parent's appropriate side
        // y <- node, x = child, x.parent <- node.parent

        // 2 children:
        // y <-succ(node)

        BSTNode<K, V> x, y;
        y = (node.left == null || node.right == null) ? node : successor(node);
        x = (y.left != null) ? y.left : y.right;
        if (x != null) {
            x.parent = y.parent;
        }
        if(y.parent == null) {  //
            root = x;
        }
        else if (y == y.parent.left) {
            y.parent.left = x;
        }
        else {
            y.parent.right = x;
        }
        if (y != node) {
            node.setKey(y.getKey());
            node.setValue(y.getValue());
        }
        this.size--;
        //y = null;
    }

    /**
     * Find element in the tree by key.
     * @param key key to look for
     * @return node with the specified key, null if such node cannot be found.
     */
    public BSTNode<K, V> search(K key) {
        return searchInSubtree(key, this.root);
    }

    /**
     * Find element by key under a specified node.
     * @param key - key to find
     * @param subtree - where to look
     * @return node matching the key or null if such node cannot be found
     */
    public BSTNode<K, V> searchInSubtree(K key, BSTNode<K, V> subtree) {
        if(this.isEmpty()) {
            return null;
        }

        if (subtree == null || subtree.getKey().equals(key)) {
            return subtree;
        }
        if(subtree.getKey().compareTo(key) < 0) {
            return searchInSubtree(key, subtree.right);
        }
        else {
            return searchInSubtree(key, subtree.left);
        }
    }

    /**
     * @return - minimal node of this tree.
     */
    public BSTNode<K, V> minimum() {
        return minimum(this.root);
    }

    /**
     * Find minimal element in a subtree.
     * @param node root of a subtree to searched through.
     * @return minimal element of a subtree rooted in node.
     */
    public BSTNode<K, V> minimum(BSTNode<K, V> node) {
        BSTNode<K, V> current = node;
        while(current.left != null) {
            current = current.left;
        }
        return current;
    }

    /**
     * @return - maximal node of this tree.
     */
    public BSTNode<K, V> maximum() {
        return maximum(this.root);
    }

    /**
     * Find maximal node in a subtree.
     * @param node root of a subtree to search through.
     * @return maximal element of a subtree rooted in node.
     */
    public BSTNode<K, V> maximum(BSTNode<K, V> node) {
        BSTNode<K, V> current = node;
        while(current.right != null) {
            current = current.right;
        }
        return current;
    }

    /**
     * Return first element in the tree that is greater than the specified node.
     * @param node node whose successor is to be found
     * @return node's successor or null if node is the maximal element of the tree.
     */
    public BSTNode<K,V> successor(BSTNode<K, V> node) {
        if(node.right != null) {
            return minimum(node.right);
        }
        BSTNode<K, V> cur = node.parent;
        while(cur != null && node == cur.right) {
            node = cur;
            cur = cur.parent;
        }
        return cur;
    }

    /**
     *
     * @param node starting element
     * @return node's predecessor or null if node is the minimal element of the tree.
     */
    public BSTNode<K, V> predecessor(BSTNode<K, V> node) {
        if(node.left != null) {
            return maximum(node.left);
        }
        BSTNode<K, V> cur = node.parent;
        while(cur != null && node == cur.left) {
            node = cur;
            cur = cur.parent;
        }
        return cur;
    }

    /**
     * Perform pre-order traversal of the whole tree, and apply a function at each node.
     * @param function function to call on each node.
     */
    public void preOrder(Consumer<BSTNode<K, V>> function) {
        preOrder(function, this.root);
    }

    /**
     * Perform pre-order traversal of a subtree rooted in the specified node, and call a function at each node.
     * @param function - function to call on each node
     * @param node - root of a subtree to traverse
     */
    private void preOrder(Consumer<BSTNode<K, V>> function, BSTNode<K, V> node) {
        if(node != null) {
            function.accept(node);
            preOrder(function, node.left);
            preOrder(function, node.right);
        }
    }

    public void inOrder(Consumer<BSTNode<K, V>> function) {
        inOrder(function, this.root);
    }

    private void inOrder(Consumer<BSTNode<K, V>> function, BSTNode<K, V> node) {
        if(node != null) {
            inOrder(function, node.left);
            function.accept(node);
            inOrder(function, node.right);
        }
    }

    /**
     * Perform post-order traversal of the whole tree, and apply a function at each node.
     * @param function function to call on each node.
     */
    public void postOrder(Consumer<BSTNode<K, V>> function) {
        postOrder(function, this.root);
    }

    /**
     * Perform post-order traversal of a subtree rooted in the specified node, and call a function at each node.
     * @param function - function to call on each node
     * @param node - root of a subtree to traverse
     */
    private void postOrder(Consumer<BSTNode<K, V>> function, BSTNode<K, V> node) {
        if(node != null) {
            postOrder(function, node.left);
            postOrder(function, node.right);
            function.accept(node);
        }
    }

    /**
     * @return list of tree nodes, sorted by keys
     */
    public List<BSTNode<K,V>> toList() {
        List<BSTNode<K, V>> list = new ArrayList<>(size);
        for(BSTNode<K, V> node : this) {
            list.add(node);
        }
        return list;

    }

    /**
     * Print a nicely formatted tree.
     */
    public void prettyPrint() {
        if(!isEmpty()) {
            root.prettyPrint();
        }
    }



    /**
     * Default iterator, used by {@link Iterable} interface.
     * @return an iterator that performs in-order traversal of the tree.
     */
    @Override
    public Iterator<BSTNode<K, V>> iterator() {
        return new Iterator<BSTNode<K, V>>() {
            private BSTNode<K, V> currentNode;
            private int index = 0;  // to avoid looking for successor in each hasNext() call
            @Override
            public boolean hasNext() {
                return index < size;
            }

            @Override
            public BSTNode<K, V> next() {
                index++;
                if(currentNode == null) {
                    currentNode = minimum();
                }
                else {
                    currentNode = successor(currentNode);
                }
                return currentNode;
            }
        };
    }

}

package reshi.ppt.algorytmy.BST;


import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.function.Consumer;

/**
 * @author Marcin Regulski on 25.04.2016.
 */
public class BST<K extends Comparable<K>, V> implements Iterable<BSTNode<K, V>> {
    private BSTNode<K, V> root;
    private int size;

    public BST() {
        this.root = null;
        this.size = 0;
    }

    public boolean isEmpty() {
        return this.root == null;
    }

    public BSTNode getRoot() {
        return this.root;
    }

    public int getSize() {
        return size;
    }

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
        else {
            if(subtree.left == null) {
                subtree.left = node;
                node.parent = subtree;
            }
            else {
                insert(node, subtree.left);
            }
        }
    }

    public void delete(BSTNode<K, V> node) {

    }

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

        if (subtree.getKey().equals(key)) {
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
     * Find minimal element of a subtree rooted in node, according to the ordering on K type.
     * @param node - root of a subtree to be searched.
     * @return - minimal node in the considered subtree.
     */
    public BSTNode<K, V> minimum(BSTNode<K, V> node) {
        BSTNode<K, V> current = node;
        while(current.left != null) {
            current = current.left;
        }
        return current;
    }

    /**
     * @return - minimal node of this tree.
     */
    public BSTNode<K, V> maximum() {
        return maximum(this.root);
    }

    public BSTNode<K, V> maximum(BSTNode<K, V> node) {
        BSTNode<K, V> current = node;
        while(current.right != null) {
            current = current.right;
        }
        return current;
    }

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
     * Perform pre-order traversal of the tree, starting at root, and apply a function at each node.
     * @param function - function: BSTNode -> void that will be applied on each element.
     */
    public void preOrder(Consumer<BSTNode<K, V>> function) {
        preOrder(function, this.root);
    }

    /**
     * Perform pre-order traversal of the tree, treating node as root, and call a function at each node.
     * @param function - function to call on each node
     * @param node - root of subtree to traverse
     */
    private void preOrder(Consumer<BSTNode<K, V>> function, BSTNode<K, V> node) {
        if(node != null) {
            function.accept(node);
            preOrder(function, node.left);
            preOrder(function, node.right);
        }
    }

    public void postOrder(Consumer<BSTNode<K, V>> function) {
        postOrder(function, this.root);
    }

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

    public void prettyPrint() {
        root.prettyPrint();
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

package reshi.ppt.algorytmy;

import reshi.ppt.algorytmy.BST.BST;
import reshi.ppt.algorytmy.BST.BSTNode;

public class Main {

    public static void main(String[] args) {
        BST<Integer, String> tree = new BST<>();
        tree.insert(4, "first");
        tree.insert(9, "second");
        tree.insert(7, "third");
        tree.insert(2, "fourth");
        tree.insert(3, "fifth");
        tree.insert(1, "sixth");
        tree.insert(6, "seventh");
        tree.insert(5, "eighth");
        tree.insert(14, "ninth");
        tree.insert(16, "tenth");
        tree.insert(8, "eleventh");
        tree.insert(10, "twelfth");
        tree.forEach(System.out::print);
        System.out.println();
        BSTNode<Integer, String> node = tree.search(6);
        System.out.println("search(6): " + node);
        System.out.println("succ(6): " + tree.successor(node));
        tree.forEach(System.out::print);
        System.out.println();
        System.out.println("max: " + tree.maximum());
        System.out.println("min: " + tree.minimum());
        System.out.println("listed: " + tree.toList());
        tree.prettyPrint();
    }
}

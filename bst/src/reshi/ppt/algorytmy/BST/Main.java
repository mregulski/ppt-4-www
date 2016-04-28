package reshi.ppt.algorytmy.BST;

import java.io.IOException;


public class Main {

    public static void main(String[] args) {
        SimpleFileTreeGenerator gen;
        System.out.println(System.getProperty("user.dir"));
        try {
            gen = new SimpleFileTreeGenerator("input.txt");
            gen.generate();
        }
        catch(IOException ioe) {
            System.out.println("error opening input.txt");
        }
//        BST<Integer, String> tree = new BST<>();
//        tree.insert(8, "first");
//        tree.insert(7, "third");
//        tree.insert(2, "fourth");
//        tree.insert(3, "fifth");
//        tree.insert(1, "sixth");
//        tree.insert(6, "seventh");
//        tree.insert(5, "eighth");
//        tree.insert(10, "twelfth");
//        tree.insert(14, "ninth");
//
//        tree.insert(9, "second");
//        tree.insert(16, "tenth");
//        tree.insert(12, "eleventh");
//        tree.insert(13, "eleventh");
//
//        tree.prettyPrint();
//        log("\nremoving 6");
//        tree.delete(tree.search(6));
//        tree.prettyPrint();
//        log("\nremoving 2");
//        tree.delete(tree.search(2));
//        tree.prettyPrint();
//        log("\nremoving root");
//        tree.delete(tree.getRoot());
//        tree.prettyPrint();
//        tree.forEach(System.out::print);
//        System.out.println();
//        BSTNode<Integer, String> node = tree.search(6);
//        System.out.println("search(6): " + node);
//        System.out.println("succ(6): " + tree.successor(node));
//        System.out.println("pre(6): " + tree.predecessor(node));
//        node = tree.maximum();
//        System.out.println("succ(max): " + tree.successor(node));
//        tree.forEach(System.out::print);
//        System.out.println();
//        System.out.println("max: " + tree.maximum());
//        System.out.println("min: " + tree.minimum());
//        System.out.println("listed: " + tree.toList());

//        BST<Integer, Integer> largeTree = new BST<>();
//        Random r = new Random();
//        for (int i = 0; i < 1000; i++) {
//            int num = r.nextInt(100000);
//            largeTree.insert(num,num);
//        }
//        largeTree.prettyPrint();
    }

    static void log(String m) {
        System.out.println(m);
    }
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mcjes
 */
public class BinaryTree<T> {

    private T data;
    private BinaryTree<T> parent;
    private BinaryTree<T> left;
    private BinaryTree<T> right;

    public BinaryTree() {
        parent = left = right = null;
        data = null;
    }

    public void makeRoot(T data) {
        if (!isEmpty()) {
            System.out.println("Can't make root. Already exists");
        } else {
            this.data = data;
        }
    }

    public void setData(T data) {
        this.data = data;
    }

    public void setLeft(BinaryTree<T> tree) {
        left = tree;
    }

    public void setRight(BinaryTree<T> tree) {
        right = tree;
    }

    public void setParent(BinaryTree<T> tree) {
        parent = tree;
    }

    public T getData() {
        return data;
    }

    public BinaryTree<T> getParent() {
        return parent;
    }

    public BinaryTree<T> getLeft() {
        return left;
    }

    public BinaryTree<T> getRight() {
        return right;
    }

    public void attachLeft(BinaryTree<T> tree) {
        if (tree == null) {
            return;
        } else if (left != null || tree.getParent() != null) {
            System.out.println("Can't attach");
            return;
        } else {

            tree.setParent(this);
            this.setLeft(tree);
        }
    }

    public void attachRight(BinaryTree<T> tree) {
        if (tree == null) {
            return;
        } else if (right != null || tree.getParent() != null) {
            if (right != null) {
                System.out.println("Right null");//debug
            } else if (tree.getParent() != null) {
                System.out.println("getParent is null");//debug
            }
            System.out.println("Can't attach");
            return;
        } else {

            tree.setParent(this);
            this.setRight(tree);
        }
    }

    public BinaryTree<T> detachLeft() {
        if (this.isEmpty()) {
            return null;
        }
        BinaryTree<T> retLeft = left;
        left = null;
        if (retLeft != null) {
            retLeft.setParent(null);
        }
        return retLeft;
    }

    public BinaryTree<T> detachRight() {
        if (this.isEmpty()) {
            return null;
        }
        BinaryTree<T> retRight = right;
        right = null;
        if (retRight != null) {
            retRight.setParent(null);
        }
        return retRight;
    }

    public boolean isEmpty() {
        if (data == null) {
            return true;
        } else {
            return false;
        }
    }

    public void clear() {
        left = right = parent = null;
        data = null;
    }

    public BinaryTree<T> root() {
        if (parent == null) {
            return this;
        } else {
            BinaryTree<T> next = parent;
            while (next.getParent() != null) {
                next = next.getParent();
            }
            return next;
        }
    }
    public void print(){
        System.out.println(getData());
    }

    public static <T> void preorder(BinaryTree<T> t) {
        if (t != null) {
            System.out.print(t.getData() + "\t");
            preorder(t.getLeft());
            preorder(t.getRight());
        }
    }

    public static <T> void inorder(BinaryTree<T> t) {
        if (t != null) {
            inorder(t.getLeft());
            System.out.print(t.getData() + "\t");
            inorder(t.getRight());
        }
    }

    public static <T> void postorder(BinaryTree<T> t) {
        if (t != null) {
            postorder(t.getLeft());
            postorder(t.getRight());
            System.out.print(t.getData() + "\t");
        }
    }

    //A simple demo program
    public static void main(String[] args) {
        BinaryTree<String> tree = new BinaryTree<String>();
        BinaryTree<String> A = new BinaryTree<String>();
        BinaryTree<String> B = new BinaryTree<String>();
        BinaryTree<String> C = new BinaryTree<String>();
        BinaryTree<String> D = new BinaryTree<String>();
        A.makeRoot("A");
        B.makeRoot("B");
        C.makeRoot("C");
        D.makeRoot("D");
        A.attachLeft(B);
        B.attachLeft(C);
        A.attachRight(D);
        System.out.print("Preorder:\t");
        preorder(A);
        System.out.println();
        System.out.print("Inorder:\t");
        inorder(A);
        System.out.println();
        System.out.print("Postorder:\t");
        postorder(A);
        System.out.println();
    }
}

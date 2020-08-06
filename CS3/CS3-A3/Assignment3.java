
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.StringTokenizer;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mcjes
 */
public class Assignment3 {
    public static void main(String[] args) throws FileNotFoundException, IOException{
        File file = new File("Assignment3Input.txt");
        Scanner inputFile = new Scanner(file);
        String letter;
        char holder;
        ArrayList<Character> letters = new ArrayList<>();
        ArrayList<Double> letterCount = new ArrayList<>();
        ArrayList<Pair> pairs=new ArrayList<>();
        
        /*Iterates over the text file and creates 2 arrayLists, "letters" holding the 
        different chars and letterCount holding the # of times they appear in the
        text file. The loop is set so that the index of the letter in letters
        is the same index as its count in letterCount
        Fully functional :)
        */
        
        while (inputFile.hasNext()) {
            String s = inputFile.next();
            StringTokenizer token = new StringTokenizer(s, "\t");
            letter = token.nextElement().toString();
            char[] word = letter.toCharArray();
            for (int i=0;i<word.length;i++){
                holder=word[i];
                if(!letters.contains(holder)){
                    letters.add(holder);
                    letterCount.add(1.0);
                }
                else{
                    int index=letters.indexOf(holder);
                    double value=letterCount.get(index);
                    letterCount.set(index,value+1);
                }
            }
        }
        System.out.println("Total number of unique characters: "+letterCount.size());
        /*Determines the total amount of characters in the text file*/
        double totalChar=0;
        for(double x: letterCount){
            totalChar=totalChar+x;
        }
        
        System.out.println("The total number of chars: "+totalChar);
        
        //Fills the pairs arrayList with the pairs made up of the corresponding
        //character and its probability
        for(int i=0;i<letters.size();i++){
            pairs.add(new Pair(letters.get(i),(letterCount.get(i)/totalChar)));
        }
        
        //Prints the list of pairs and their probability as well as the total prob.
        double probability=0;
        for (Pair pair : pairs) {
            System.out.println(pair);
            probability=probability+pair.getProb();
        }
        ArrayList<Pair> finalPairs=pairs;
        System.out.println("Total probability: "+probability);
        
        //Creating the huffman tree
        
        ArrayList<BinaryTree<Pair>> queueS=new ArrayList<>();
        
        //Compares all elements of the pairs arrayList and enqueus them in
        //increasing order to the queueS
        while(!pairs.isEmpty()){
        Pair compare=pairs.get(0);
        for(Pair pair: pairs){
           if(pair.getProb()<compare.getProb())
               compare=pair;
        }
        BinaryTree<Pair> n=new BinaryTree<>();
        n.makeRoot(compare);
        queueS.add(n);
        pairs.remove(compare);
        }
        System.out.println("Completed Comparison");
        System.out.println("This is an oredred list of the values and their probabilities: ");
        
        //Prints the queue to determine if we didn't mess up
        for(BinaryTree<Pair> x: queueS){
            x.print();
        }
        System.out.print("\n");
        
        //Generates the HuffmanTree from our orderedList of BinaryTree Nodes
        BinaryTree<Pair> huffman=generateHuffman(queueS);
        //Prints a preorder Traversal of the Huffman tree to make sure we didn't
        //mess up, again :)
        System.out.println("This is the preorder traversel of the Huffman Tree: ");
        BinaryTree.preorder(huffman);  
        //Prints the huffman Values:
        System.out.println("These are the huffman encoded values printed in the array: ");
        System.out.println(Arrays.toString(findEncoding(huffman)));
        String[] codes = findEncoding(huffman);
        ArrayList<Pair> encoded=new ArrayList<>();
        int j=0;
        for(int i=0;i<codes.length;i++){
            if(codes[i]!=null){
                encoded.add(new Pair(codes[i],i));
                j++;
            }
        }
        for(int i=0;i<encoded.size();i++){
            System.out.println(encoded.get(i));
        }
        System.out.println(j);
        
        
    }
    
    public static void findEncoding(BinaryTree<Pair> t, String[] a, String prefix) {
        if (t.getLeft() == null && t.getRight() == null) {
            a[(byte) (t.getData().getValue())] = prefix;
        } else {
            findEncoding(t.getLeft(), a, prefix + "0");
            findEncoding(t.getRight(), a, prefix + "1");
        }
    }

    public static String[] findEncoding(BinaryTree<Pair> t) {
        String[] result = new String[256];
        findEncoding(t, result, "");
        return result;
    }
    //Generates the Huffman Tree from the ArrayList of BinaryTree Nodes
    public static BinaryTree<Pair> generateHuffman(ArrayList<BinaryTree<Pair>> queue){
        while(queue.size()>1){
        BinaryTree<Pair> compare1=queue.get(0);
        BinaryTree<Pair> compare2=queue.get(0);
        BinaryTree<Pair> joined=new BinaryTree<Pair>();
        for(BinaryTree<Pair> x: queue){
           if(x.getData().getProb()<compare1.getData().getProb())
               compare1=x;
        }
        queue.remove(compare1);
        for(BinaryTree<Pair> x: queue){
           if(x.getData().getProb()<compare2.getData().getProb())
               compare2=x;
        }
        queue.remove(compare2);
        compare1.setParent(joined);
        compare2.setParent(joined);
        Pair root=new Pair('o',compare1.getData().getProb()+compare2.getData().getProb());
        joined.makeRoot(root);
        joined.setLeft(compare1);
        joined.setRight(compare2);
        queue.add(0,joined);
        }
        return queue.get(0); 
        }
        
    }
      
        
    


    


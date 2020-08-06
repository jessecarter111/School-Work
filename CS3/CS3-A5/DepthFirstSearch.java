
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mcjes
 */
public class DepthFirstSearch {
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        //Uses a stack to perform the DFS
        Stack hold=new Stack();
        System.out.print("Enter a file name: ");
        String filename = scan.nextLine();
        File file = new File(filename);
        Scanner inputFile = new Scanner(file);
        //Assumes the input file is formatted as specified by the question,
        //reads the first int as the size of the adjancency matrix
        int size=inputFile.nextInt();
        System.out.println(size);
        int[][] adjMatrix=new int[size][size];
        int[] visited=new int[size];
        //Sets array to track visited nodes, sets all null entries to 0
        for(int i=0;i<size;i++){
            visited[i]=0;
        }
        //While there is a next element 
        while (inputFile.hasNext()) {
            String edge=inputFile.next();
            //Conversion of vertexs to numerical value 
            int asciiA=(int)edge.charAt(0)-65;
            edge=inputFile.next();
            int asciiB=(int)edge.charAt(0)-65;
            System.out.println(asciiB+" "+asciiA);
            //Sets the index to 1 if there is an edge there
            adjMatrix[asciiA][asciiB]=1;
            adjMatrix[asciiB][asciiA]=1;
        }
        System.out.println("File Completed");
        //Set all null values to 0
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                if(adjMatrix[i][j]!=1)
                    adjMatrix[i][j]=0;
            }
        }
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                System.out.print(adjMatrix[i][j]);
            }
            System.out.print("\n");
        }
        //DepthFirstSearch
        System.out.println("Please enter the vertex to begin the search from: ");
        String temp=scan.next();
        int vertex=(temp.charAt(0)-65);
        hold.push(vertex);
        
        while(!hold.isEmpty()){
            int a=(int)hold.pop();
            visited[a]=1;
            System.out.println((char)(a+65)+" visited\n");
            for(int i=0;i<size;i++){
                if(adjMatrix[a][i]!=0 && visited[i]!=1){
                    hold.push(i);
                    visited[i]=1;
                }
            }
        }
        System.out.println("Reachable from "+vertex+": ");
        for(int i=0;i<size;i++){
            if(visited[i]==1 && i!=vertex)
                System.out.print((char)(i+65));
        }
        System.out.print("\n");
        
    }
}

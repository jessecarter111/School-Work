/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mcjes
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import java.util.StringTokenizer;

public class NHLListDemo {

    public static void main(String[] args) throws FileNotFoundException {
        //Reading in the file
        File file = new File("HockeyInput.txt");
        Scanner inputFile = new Scanner(file);
        String Name, Position, Team;
        int GP, G, A, PIM, SOG, GWG;

        NHLStats newStats = new NHLStats();
        PlayerRecord pr = null;

        while (inputFile.hasNextLine()) {
            String s = inputFile.nextLine();
            StringTokenizer token = new StringTokenizer(s, "\t");
            Name = token.nextElement().toString();
            Position = token.nextElement().toString();
            Team = token.nextElement().toString();
            GP = Integer.parseInt(token.nextElement().toString());
            G = Integer.parseInt(token.nextElement().toString());
            A = Integer.parseInt(token.nextElement().toString());
            PIM = Integer.parseInt(token.nextElement().toString());
            SOG = Integer.parseInt(token.nextElement().toString());
            GWG = Integer.parseInt(token.nextElement().toString());
            pr = new PlayerRecord(Name, Position, Team, GP, G, A, PIM, SOG, GWG);
            newStats.addPlayerRecord(pr);
        }

        inputFile.close();
        newStats.highestPoints();
        newStats.mvp();
        newStats.mostAggresive();
        newStats.mostPromising();
        newStats.teamLeastGWG();
        newStats.teamGWG();
        newStats.teamPen();
    }
}

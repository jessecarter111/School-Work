/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mcjes
 */
import java.text.DecimalFormat;
public class PlayerRecord {

    private String name, position, team;
    private int gamesPlayed, goals, assists, pim, sog, gwg, p, pg, pct;
    private static final DecimalFormat dec=new DecimalFormat("0.##");

    public PlayerRecord(String name, String position, String team, int gamesPlayed, int goals, int assists, int pim, int sog, int gwg) {
        this.name = name;
        this.position = position;
        this.team = team;
        this.gamesPlayed = gamesPlayed;
        this.goals = goals;
        this.assists = assists;
        this.pim = pim;
        this.sog = sog;
        this.gwg = gwg;
        calcP();
        calcPG();
        calcPCT();
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPosition() {
        return position;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public String getTeam() {
        return team;
    }

    public void setTeam(String team) {
        this.team = team;
    }

    public int getGamesPlayed() {
        return gamesPlayed;
    }

    public void setGamesPlayed(int gamesPlayed) {
        this.gamesPlayed = gamesPlayed;
    }

    public int getGoals() {
        return goals;
    }

    public void setGoals(int goals) {
        this.goals = goals;
    }

    public int getAssists() {
        return assists;
    }

    public void setAssists(int assists) {
        this.assists = assists;
    }

    public int getPim() {
        return pim;
    }

    public void setPim(int pim) {
        this.pim = pim;
    }

    public int getSog() {
        return sog;
    }

    public void setSog(int sog) {
        this.sog = sog;
    }

    public int getGwg() {
        return gwg;
    }

    public void setGwg(int gwg) {
        this.gwg = gwg;
    }

    public void calcP() {
        this.p = goals + assists;
    }

    public void calcPG() {
        this.pg = Integer.parseInt(dec.format((goals + assists)/gamesPlayed));
    }

    public void calcPCT() {
        this.pct = Integer.parseInt(dec.format((goals/sog)*100));
    }

    public int getP() {
        return p;
    }

    public void setP(int p) {
        this.p = p;
    }

    public int getPG() {
        return pg;
    }

    public void setPG(int pg) {
        this.pg = pg;
    }

    public int getPCT() {
        return pct;
    }

    public void setPCT(int pct) {
        this.pct = pct;
    }
    public static void main(String[] args){
        PlayerRecord poop=new PlayerRecord("Jenna","isa","bitch",4,5,6,7,8,8);
        PlayerRecord poop1=new PlayerRecord("Jesse","dog","asd",1,2,3,4,5,6);
        System.out.println(poop.getP());
        System.out.println(poop1.getP());
    }

}

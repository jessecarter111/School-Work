
import java.util.ArrayList;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mcjes
 */
public class NHLStats {
    private List<PlayerRecord> playerlist;
    
    public NHLStats(){
        playerlist=new List<>();
    }
    
    public void addPlayerRecord(PlayerRecord x){
        playerlist.add(x);
    }
    public Boolean isEmpty(){
       return playerlist.isEmpty();
    }
    public PlayerRecord getFirst(){
        return playerlist.first();
    }
    public PlayerRecord getNext(){
        return playerlist.next();
    }
    public void enumerate(){
        playerlist.enumerate();
    }
    public void highestPoints(){
        PlayerRecord j=playerlist.first();
        PlayerRecord best=null;
        int points =0;
        int max=0;
        ArrayList<PlayerRecord> plyrs = new ArrayList<PlayerRecord>();
        while (j != null){
            points= j.getP();
            if(points > max){
                best =j;
                max=points;
            }
            j=playerlist.next();
        }
        j=playerlist.first();
        plyrs.add(best);
        while(j != null){
            if (j.getP()==best.getP()){
                if(!plyrs.contains(j))
                    plyrs.add(j);
            }
            j=playerlist.next();
        }
        for (int i=0;i<plyrs.size();i++){
            System.out.println("Player with the Most Points: "+plyrs.get(i).getName());
            System.out.println("Team: "+plyrs.get(i).getTeam());
            System.out.println("Points: "+plyrs.get(i).getP()+"\n");
        }
        
    }
    public void mostAggresive(){
        PlayerRecord j=playerlist.first();
        PlayerRecord best=null;
        int pim =0;
        int max=0;
        ArrayList<PlayerRecord> plyrs = new ArrayList<PlayerRecord>();
        while (j != null){
            pim= j.getPim();
            if(pim > max){
                best =j;
                max=pim;
            }
            j=playerlist.next();
        }
        j=playerlist.first();
        plyrs.add(best);
        while(j != null){
            if (j.getPim()==best.getPim()){
                if(!plyrs.contains(j))
                    plyrs.add(j);
            }
            j=playerlist.next();
        }
        for (int i=0;i<plyrs.size();i++){
            System.out.println("Most Aggresive Player: "+plyrs.get(i).getName());
            System.out.println("Team: "+plyrs.get(i).getTeam());
            System.out.println("Position: "+plyrs.get(i).getPosition());
            System.out.println("Penalties in Minutes: "+plyrs.get(i).getPim()+"\n");
        }
    }
    public void mvp(){
        PlayerRecord j=playerlist.first();
        PlayerRecord best=null;
        int gwg =0;
        int max=0;
        ArrayList<PlayerRecord> plyrs = new ArrayList<PlayerRecord>();
        while (j != null){
            gwg= j.getGwg();
            if(gwg > max){
                best =j;
                max=gwg;
            }
            j=playerlist.next();
        }
        j=playerlist.first();
        plyrs.add(best);
        while(j != null){
            if (j.getGwg()==best.getGwg()){
                if(!plyrs.contains(j))
                    plyrs.add(j);
            }
            j=playerlist.next();
        }
        for (int i=0;i<plyrs.size();i++){
            System.out.println("MVP: "+plyrs.get(i).getName());
            System.out.println("Team: "+plyrs.get(i).getTeam());
            System.out.println("Game Winning Goals: "+plyrs.get(i).getGwg()+"\n");
        }
    }
    public void mostPromising(){
        PlayerRecord j=playerlist.first();
        PlayerRecord best=null;
        int sog =0;
        int max=0;
        ArrayList<PlayerRecord> plyrs = new ArrayList<PlayerRecord>();
        while (j != null){
            sog= j.getSog();
            if(sog > max){
                best =j;
                max=sog;
            }
            j=playerlist.next();
        }
        j=playerlist.first();
        plyrs.add(best);
        while(j != null){
            if (j.getSog()==best.getSog()){
                if(!plyrs.contains(j))
                    plyrs.add(j);
            }
            j=playerlist.next();
        }
        for (int i=0;i<plyrs.size();i++){
            System.out.println("Most promising player: "+plyrs.get(i).getName());
            System.out.println("Team: "+plyrs.get(i).getTeam());
            System.out.println("Position: "+plyrs.get(i).getPosition());
            System.out.println("Shots on Goal: "+plyrs.get(i).getSog()+"\n");
        }
    }
    public void teamPen(){
        PlayerRecord j=playerlist.first();
        ArrayList<String> teams= new ArrayList<String>();
        ArrayList<Integer> penalties=new ArrayList<>();
        ArrayList<String> teamNames=new ArrayList<>();
        
        int pos=0;
        int q =0;
        int max=0;
        while(j != null){
            if(!teams.contains(j.getTeam())){
                teams.add(j.getTeam());
                penalties.add(j.getPim());
            }
            else{
                pos=teams.indexOf(j.getTeam());
                q=penalties.get(pos);
                penalties.set(pos,(q+j.getPim()));
            }
         j=playerlist.next();   
        }
        for(int k=0; k<penalties.size(); k++){
            if(penalties.get(k)>max){
                max=penalties.get(k);
            }
        }
        for(int i=0;i<penalties.size();i++){
            if(penalties.get(i)==max){
                teamNames.add(teams.get(i));
            }
        }
        for(int i=0;i<teamNames.size();i++){
            System.out.println("Team with most penalties: "+teamNames.get(i));
            System.out.println("Penalty minutes: "+max+"\n");
        }
    }
    public void teamGWG(){
        PlayerRecord j=playerlist.first();
        ArrayList<String> teams= new ArrayList<String>();
        ArrayList<Integer> gwg=new ArrayList<>();
        ArrayList<String> teamNames=new ArrayList<>();
        
        int pos=0;
        int q =0;
        int max=0;
        while(j != null){
            if(!teams.contains(j.getTeam())){
                teams.add(j.getTeam());
                gwg.add(j.getGwg());
            }
            else if(teams.contains(j.getTeam())){
                pos=teams.indexOf(j.getTeam());
                q=gwg.get(pos);
                gwg.set(pos, (q+j.getGwg()));
            }
         j=playerlist.next();   
        }
        for(int k=0; k<gwg.size(); k++){
            if(gwg.get(k)>max){
                max=gwg.get(k);
            }
        }
        for(int i=0;i<gwg.size();i++){
            if(gwg.get(i)==max){
                teamNames.add(teams.get(i));
            }
        }
        for(int i=0;i<teamNames.size();i++){
            System.out.println("GWG team: "+teamNames.get(i));
            System.out.println("Most game winning goals scored: "+max+"\n");
        }
    }
    public void teamLeastGWG(){
        PlayerRecord j=playerlist.first();
        ArrayList<String> teams= new ArrayList<String>();
        ArrayList<Integer> gwg=new ArrayList<>();
        ArrayList<String> teamNames=new ArrayList<>();
        
        int pos=0;
        int q =0;
        int min=999999;
        while(j != null){
            if(!teams.contains(j.getTeam())){
                teams.add(j.getTeam());
                gwg.add(j.getGwg());
            }
            else if(teams.contains(j.getTeam())){
                pos=teams.indexOf(j.getTeam());
                q=gwg.get(pos);
                gwg.set(pos, (q+j.getGwg()));
            }
         j=playerlist.next();   
        }
        for(int k=0; k<gwg.size(); k++){
            if(gwg.get(k)<min){
                min=gwg.get(k);
            }
        }
        for(int i=0;i<gwg.size();i++){
            if(gwg.get(i)==min){
                teamNames.add(teams.get(i));
            }
        }
        for(int i=0;i<teamNames.size();i++){
            System.out.println("Least GWG team: "+teamNames.get(i));
            System.out.println("Least Game winning goals scored: "+min+"\n");
        }
        }
        public static void main(String[] args){
    }
    
    
}

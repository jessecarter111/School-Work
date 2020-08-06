
public class XO {
	private String name="";
	private static int turn=1;
	
	public XO(){
	if(turn==1){
		name="X";
		turn--;
		}
	else if(turn==0){
		name="O";
		turn++;
		}
	}
	public void setName(String n){
		this.name=n;
	}
	public String getName(){
		return name; 
	}
	public void setTurn(int t){
		this.turn=t;
	}
	public int getTurn(){
		return turn;
	}
	public String toString(){
		return name;
	}
	public boolean equals(XO other){
		if(name==other.getName())
			return true;
		else
			return false; 
	}
	
}
	


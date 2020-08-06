
public class Board {
	private int rows=4;
	private int columns=4; 
	
	public Board(int x, int y){
		rows=x;
		columns=y;
	}
	public void setRows(int x){
		this.rows=x;
	}
	public int getRows(){
		return rows; 
	}
	public void setColumns(int x){
		this.columns=x;
	}
	public int getColumns(){
		return columns;
	}
}

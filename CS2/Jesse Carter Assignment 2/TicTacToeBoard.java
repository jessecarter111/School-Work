
public class TicTacToeBoard extends Board {
	//2d Array 
	private XO[][] board;
	private int turnCnt;
	private String s;
	
	public TicTacToeBoard(int x, int y){
		//the superclass constructor 
		super(x,y);
		board=new XO[x][y];
		//For loops populate the array with XO's 
		for(int i=0;i<x;i++){
			for(int j=0;y<j;j++){
				board[i][j]=new XO();
			}
		}
		turnCnt=0;
	}
	//Get and set methods 
	public void setBoard(XO[][] y){
		this.board=y;
	}
	public XO[][] getBoard(){
		return board;
	}
	public void setTurnCnt(int x){
		turnCnt=x;
	}
	public int getTurnCnt(){
		return turnCnt;
	}
	//Add method 
	public boolean add(int x,int y){
		//Determines if the move is within the boundary 
		if(x<getRows()&&y<getColumns()){
			//Determines if the space is occupied or not 
			if(board[x][y]==null){
			//populates it with a XO
			board[x][y]=new XO();
			//Return true 
			return true; 
			}
		}
		return false;
		
	}
	//toString method 
	public String toString(){
	//Double for loops to set the s var to the board
	for(int i=0;i<3;i++){  
		for(int j=0;j<3;j++){   
		//Creates a null pointer error but i cannot understand why because s is a private variable 
		s+=(board[i][j].getName()+"\t"+"\n");
			}
		}
	return s; 
		
	}
	//To check if there is a winner 
	public boolean checkWin(XO c1,XO c2,XO c3){
	//Checks if all 3 pieces match 
	return ((c1.getName()=="X"||c1.getName()=="O")&&(c2==c1)&&(c3==c2));
	}
	
	public boolean checkRows(){
	for(int i=0; i<3; i++){
		//Checks if all the rows are the same using the checkWin method 
		if(checkWin(board[1][i],board[2][i],board[3][i])==true)
			return true;
		}
		return false; 
	}
	//Sane as above but for columns 
	public Boolean checkColumns(){
	for(int i=0; i<3; i++){
		if(checkWin(board[i][1],board[i][2],board[i][3])==true)
			return true;
		}
		return false;
	}
	//Same as above but for diagonals 
	public Boolean checkDiagonal(){
	for(int i=0; i<3; i++){
		if(checkWin(board[0][0],board[1][1],board[2][2]))
			return true;
		}
		return false;
	}
	//Uses all 3 of the above methods to determine if there is a winner 
	public Boolean checkWinner(){
		if(checkRows()||checkColumns()||checkDiagonal())
			return true;
		return false;
	}
	//I was recieving null pointer errors and could not figure it out for the life of me, i have pointed them out for you viewing pleasure!
	
	
	
}


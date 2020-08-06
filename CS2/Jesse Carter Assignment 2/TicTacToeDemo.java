import java.util.Scanner;

public class TicTacToeDemo {
	public static void main (String[] args){
		Scanner scan= new Scanner (System.in);
		//The program only works for a 3x3 board (which is a 4x4 2d Array to allow
		//indicators for rows and columns)
		TicTacToeBoard board1=new TicTacToeBoard(4,4);
		System.out.println("Please enter the name of player 1:");
		String player1=scan.nextLine();
		System.out.println("Please enter the name of player 2:");
		String player2=scan.nextLine();
		System.out.println(player1+" you are X's and you go first.");
		//Invokes the toString method resulting in a null pointer error 
		System.out.println(board1.toString());
		System.out.println("Please input a row# between 1-3 and column# between 1-3: ");
		board1.add(scan.nextInt(), scan.nextInt());
		for(;;){
		System.out.println(player2+" Please input a row# between 1-3 and column# between 1-3: ");
		if(board1.add(scan.nextInt(), scan.nextInt()));
		else{
		System.out.println("That move is not allowed. Please try another one: ");
		board1.add(scan.nextInt(),scan.nextInt());
		}
		if(board1.checkWinner()){
		System.out.println("Congragulations "+player1+" you have won!");
		break;
		}
		System.out.println(player1+" Please input a row# between 1-3 and column# between 1-3: ");
		if(board1.add(scan.nextInt(), scan.nextInt()));
		else{
		System.out.println("That move is not allowed. Please try another one: ");
		board1.add(scan.nextInt(),scan.nextInt());
		}
		if(board1.checkWinner()){
		System.out.println("Congragulations "+player2+" you have won!");
		break;
		
		
			}
		}
	}
}
 
package contacteditor;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mcjes
 */
public class Key {
    private String key;
	
	public Key(String i){
		key=i.toUpperCase();
	}
        public Key(){
            
        }
	
	public void setUnlock(String i){
            if(i==null){
               i=" ";
               return;
            }
            key=i;
	}
	public String getUnlock(){
		return key;
	}
    
}

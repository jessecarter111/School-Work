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
public class DecodedMessage {
    private EncodedMessage encodedMessage=new EncodedMessage();
    private String plainText=" ";
    private Key key=new Key();
    
    public DecodedMessage(){
        
    }
    public DecodedMessage(EncodedMessage encodedMessage){
        this.encodedMessage=encodedMessage;
        key=encodedMessage.getUnlock();
        
    }
    public String decrypt(){
         String key=this.key.getUnlock();
        //StringBuilder for same reason as above 
        StringBuilder decodedMsg=new StringBuilder();
        //No need to check for capital letters because the encrypt method and 
        //performShift method perfrom the checks necessary 
        for(int i=0;i<encodedMessage.encrypt().length();i++){
            char decrypted=encodedMessage.encrypt().charAt(i)-encodedMessage.performShift(i,key)<65?(char)(encodedMessage.encrypt().charAt(i)-encodedMessage.performShift(i,key)+26)
           :(char)(encodedMessage.encrypt().charAt(i)-encodedMessage.performShift(i,key));
            decodedMsg.append(decrypted);
        }
        return decodedMsg.toString();
    }
    
}

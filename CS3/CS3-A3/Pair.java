
import java.text.DecimalFormat;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author mcjes
 */
public class Pair<T> {
    private char value;
    private String encodedValue;
    private double prob;
    private static final DecimalFormat dec=new DecimalFormat("0.####");
    
    public Pair(char value,double prob){
        this.value=value;
        this.prob=Double.parseDouble(dec.format(prob));
    }
    public Pair(String x,double prob){
        encodedValue=x;
        this.prob=Double.parseDouble(dec.format(prob));
    }

    public char getValue() {
        return value;
    }
    
    public void setValue(char value) {
        this.value = value;
    }

    public double getProb() {
        return prob;
    }

    public void setProb(double prob) {
        this.prob = prob;
    }
    @Override
    public String toString(){
        if(encodedValue==null)
        return value+": "+prob;
        else
        return encodedValue+": Index: "+prob;
    }
}

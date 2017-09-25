
/**
 * Write a description of class Vetement here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Vetement
{
    // instance variables - replace the example below with your own
    protected String id;
    protected int temp;
    protected boolean imprime;

    /**
     * Constructor for objects of class Vetement
     */
    public Vetement(String id, int temp, boolean imprime)
    {
        this.id = id;
        this.temp = temp;
        this. imprime = imprime;
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public String toString()
    {
        return "identifiant : " + id + " temperature : " + temp + " imprime : " + imprime;
    }
    public int gettemp()
    {
        return temp;
    }
    public boolean getimprime()
    {
        return imprime;
    }
}

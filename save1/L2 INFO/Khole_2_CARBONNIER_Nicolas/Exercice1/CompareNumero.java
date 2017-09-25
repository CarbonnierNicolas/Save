import java.util.Comparator;
/**
 * Write a description of class CompareNumero here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class CompareNumero implements Comparator<Candidat>
{
    // instance variables - replace the example below with your own
    private int x;

    /**
     * Constructor for objects of class CompareNumero
     */
    public CompareNumero()
    {
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public int compare(Candidat c1, Candidat c2)
    {
        return c1.getnumero_anonyme().compareTo(c2.getnumero_anonyme());
    }
}

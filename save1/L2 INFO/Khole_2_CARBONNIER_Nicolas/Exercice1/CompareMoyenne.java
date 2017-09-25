import java.util.Comparator;
/**
 * Write a description of class CompareCandidat here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class CompareMoyenne implements Comparator<Candidat>
{
    /**
     * Constructor for objects of class CompareCandidat
     */
    public CompareMoyenne()
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
        return c1.getmoyenne().compareTo(c2.getmoyenne());
    }
}

import java.util.*;
/**
 * Write a description of class ListeCandidats here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ListeCandidats
{
    // instance variables - replace the example below with your own
    private List<Candidat>liste;

    /**
     * Constructor for objects of class ListeCandidats
     */
    public ListeCandidats()
    {
        liste = new ArrayList<Candidat>();
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public void AjouterCandidat(Candidat c)
    {
        liste.add(c);
    }
    public void RetirerCandidat(Candidat c)
    {
        liste.remove(c);
    }
    public void AfficheMoyennne()
    {
        Comparator<Candidat> cmp = new CompareMoyenne();
        Collections.sort(liste,cmp);
        for(Candidat c:liste)
        {
            System.out.println("Candidat : " + c.getnom()+ " " + c.getprenom() + " " + c.getmoyenne());
        }
    }
    public void AfficheNumero()
    {
        Comparator<Candidat> cmp = new CompareNumero();
        Collections.sort(liste, cmp);
        for(Candidat c:liste)
        {
            System.out.println("Candidat : " + c.getnom() + " " + c.getprenom() + " " + c.getnumero_anonyme());
        }
    }
}

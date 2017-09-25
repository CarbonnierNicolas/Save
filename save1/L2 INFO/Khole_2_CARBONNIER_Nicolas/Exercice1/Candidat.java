import java.util.*;
/**
 * Write a description of class Candidat here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Candidat
{
    // instance variables - replace the example below with your own
    private String numero_anonyme;
    private String nom;
    private String prenom;
    private String moyenne;

    /**
     * Constructor for objects of class Candidat
     */
    public Candidat(String numero_anonyme, String nom, String prenom, String moyenne)
    {
        this.numero_anonyme = numero_anonyme;
        this.nom = nom;
        this.prenom = prenom;
        this.moyenne = moyenne;
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public String getnumero_anonyme()
    {
        return numero_anonyme;
    }
    public String getnom()
    {
        return nom;
    }
    public String getprenom()
    {
        return prenom;
    }
    public String getmoyenne()
    {
        return moyenne;
    }
}

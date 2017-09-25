
/**
 * Write a description of class Employé here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Employé
{
    // instance variables - replace the example below with your own
    private String nom;
    private String prenom;
    private String phone;

    /**
     * Constructor for objects of class Employé
     */
    public Employé(String nom, String prenom)
    {
        // initialise instance variables
        this.nom = nom;
        this.prenom = prenom;
    }
    
    public Employé(String nom, String prenom, String phone)
    {
        this.nom = nom;
        this.prenom = prenom;
        this.phone = phone;
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public String setPhone(String phone)
    {
        // put your code here
        this.phone = phone;
        return phone;
    }
    
    public boolean addFormation(Formation formation)
    {
        if(formation.nombre < 15)
        {
            return true ;
        }
        else
        {
            return false;
        }
    }
}

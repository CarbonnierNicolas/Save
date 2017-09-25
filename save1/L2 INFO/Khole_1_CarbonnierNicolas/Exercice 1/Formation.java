
/**
 * Write a description of class Formation here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Formation
{
    // instance variables - replace the example below with your own
    private String intitule;
    private String date;
    public int nombre;

    /**
     * Constructor for objects of class Formation
     */
    public Formation(String intitule, String date)
    {
        // initialise instance variables
        this.intitule = intitule;
        this.date = date;
        this.nombre = 0;
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public String getDate()
    {
        // put your code here
        return date;
    }
    
    public boolean addEmployé(Employé employé)
    {
        if(this.nombre <= 15)
        {
            this.nombre = nombre--;
            return true;
        }
        else
        {
            return false;
        }
    }
}

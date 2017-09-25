import java.util.*;
/**
 * Write a description of class Dressing here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Dressing
{
    // instance variables - replace the example below with your own
    private List<Vetement>dressing ;

    /**
     * Constructor for objects of class Dressing
     */
    public Dressing()
    {
        dressing = new ArrayList<Vetement>();
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public void AjouterVetement(Vetement v)
    {
        int i;
        boolean a = true;
        for(i=0;i<dressing.size();i++)
        {
            if((dressing.get(i).id).equals(v.id))
            {
                a = false;
                System.out.println("Vetement deja dans le dressing");
            }
        }
        if(a)
        {
            dressing.add(v);
            System.out.println("Vetement ajouter");
        }
    }
    public boolean repasser(int temp)
        throws TemptropeleveException, ImprimeException
    {
        int i;
        for(i=0;i<dressing.size();i++)
        {
            if((dressing.get(i).temp)<temp)
            {
                throw new TemptropeleveException();
            }
            if((dressing.get(i).imprime))
            {
                throw new ImprimeException();
            }
        }
        for(i=0;i<dressing.size();i++)
        {
            dressing.remove(i);
        }
        return true;
    }
    public void Afficher()
    {
        int i;
        for(i=0;i<dressing.size();i++)
        {
            System.out.println("identifiant : " +dressing.get(i).id + " temperature : "+ dressing.get(i).temp + " imprime : "+ dressing.get(i).imprime);
        }
        System.out.println();
    }
}

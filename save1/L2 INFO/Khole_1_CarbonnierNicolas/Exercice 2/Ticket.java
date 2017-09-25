import java.util.ArrayList;
import java.util.List;
/**
 * Write a description of class Ticket here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Ticket
{
    // instance variables - replace the example below with your own
    private List<ArticleAlimentaire> list_Alimentaire;
    private List <ArticleNonAlimentaire> list_NonAlimentaire;

    /**
     * Constructor for objects of class Ticket
     */
    public Ticket()
    {
        // initialise instance variables
        list_Alimentaire = new ArrayList<ArticleAlimentaire>();
        list_NonAlimentaire = new ArrayList<ArticleNonAlimentaire>();
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public void AjoutArticleAlimentaire(ArticleAlimentaire article)
    {
        // put your code here
        list_Alimentaire.add(article);
    }
    
    public void AjoutArticleNonAlimentaire(ArticleNonAlimentaire article)
    {
        // put your code here
        list_NonAlimentaire.add(article);
    }
    
    public double CalculPrixGlobal()
    {
        double prixglobal;
        double prixAlimentaire = 0;
        double prixNonAlimentaire = 0;
        int i,j;
        
        for(i=0; i<list_Alimentaire.size(); i++)
        {
            prixAlimentaire = prixAlimentaire + list_Alimentaire.get(i).CalculPrixAlimentaire();
        }
        
        for(j=0; j<list_Alimentaire.size(); j++)
        {
            prixNonAlimentaire = prixNonAlimentaire + list_NonAlimentaire.get(j).CalculPrixNonAlimentaire();
        }
        
        prixglobal = prixNonAlimentaire + prixAlimentaire;
        return prixglobal;
    }
}


/**
 * Write a description of class ArticleNonAlimentaire here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ArticleNonAlimentaire
{
    // instance variables - replace the example below with your own
    private String codebarre;
    private double prixhorstaxe;

    /**
     * Constructor for objects of class ArticleNonAlimentaire
     */
    public ArticleNonAlimentaire(String codebarre, int prixhorstaxe)
    {
        // initialise instance variables
        this.codebarre = codebarre;
        this.prixhorstaxe = prixhorstaxe;
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public double CalculPrixNonAlimentaire()
    {
        // put your code here
        double prix;
        double TVA = this.prixhorstaxe*(20/100);
        prix = this.prixhorstaxe + (this.prixhorstaxe*TVA);
        return prix;
    }
}

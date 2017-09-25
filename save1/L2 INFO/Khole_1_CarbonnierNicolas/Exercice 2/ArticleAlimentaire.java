
/**
 * Write a description of class ArticleAlimentaire here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ArticleAlimentaire
{
    // instance variables - replace the example below with your own
    private String codebarre;
    private double prixhorstaxe;
    private String dateperemption;

    /**
     * Constructor for objects of class ArticleAlimentaire
     */
    public ArticleAlimentaire(String codebarre, int prixhorstaxe, String dateperemption )
    {
        // initialise instance variables
        this.codebarre = codebarre;
        this.prixhorstaxe = prixhorstaxe;
        this.dateperemption = dateperemption;
    }

    /**
     * An example of a method - replace this comment with your own
     * 
     * @param  y   a sample parameter for a method
     * @return     the sum of x and y 
     */
    public double CalculPrixAlimentaire()
    {
        // put your code here
        double prix;
        double TVA = this.prixhorstaxe*(5.5/100);
        prix = this.prixhorstaxe + (this.prixhorstaxe*TVA);
        return prix;
    }
}

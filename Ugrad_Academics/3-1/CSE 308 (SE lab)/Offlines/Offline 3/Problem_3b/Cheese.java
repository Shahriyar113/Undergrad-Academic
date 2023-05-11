package Problem_3b;

interface Burger_Excessories
{
    String get_item();

    double get_Price();

}


public class Cheese implements Burger_Excessories {

    public String get_item()
    {
        return "Cheese";
    }

    public double get_Price()
    {
        return 25.0;
    }


}

package Problem_3b;

public interface Appetizer {

    String get_Appetizer();
    double get_Price();

}

class Frence_Fry implements Appetizer
{
    public String get_Appetizer()
    {
        return "Frence Fry";
    }

    public double get_Price()
    {
        return 30.0;
    }
}

class Onion_Rings implements Appetizer
{
    public String get_Appetizer()
    {
        return "Onion Rings";
    }
    public double get_Price()
    {
        return 40.0;
    }
}

package Problem_3b;

public interface Drinks {

    String get_Drinks();
    double get_Price();
}

class Coke implements Drinks
{
    public String get_Drinks()
    {
        return "Coke";
    }

    public double get_Price()
    {
        return 30.0;
    }
}

class Coffee implements Drinks
{
    public String get_Drinks()
    {
        return "Coffee";
    }

    public double get_Price()
    {
        return 45.0;
    }
}

class Water implements Drinks
{
    public String get_Drinks()
    {
        return "Water";
    }

    public double get_Price()
    {
        return 15.0;
    }
}

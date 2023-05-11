package Problem_3b;

public interface Burger {

    String get_Food_Items();
    double get_Price();
    void set_Appetizer(String appetizer_name);
    void add_Drinks(String drinks);
}

class Veggi_Burger implements Burger
{

    public String get_Food_Items()
    {
        return "Veggi Burger";
    }

    public double get_Price()
    {
        return 50.0;
    }

    public void set_Appetizer(String appetizer_name)
    {
        ;
    }

    public void add_Drinks(String drinks)
    {
        ;
    }
}

class Chicken_Burger implements Burger
{
    public String get_Food_Items()
    {
        return "Chicken Burger";
    }

    public double get_Price()
    {
        return 75.0;
    }
    public void set_Appetizer(String appetizer_name)
    {
        ;
    }

    public void add_Drinks(String drinks)
    {
        ;
    }
}

class Beef_Burger implements Burger
{
    public String get_Food_Items()
    {
        return "Beef Burger";
    }

    public double get_Price()
    {
        return 100.0;
    }
    public void set_Appetizer(String appetizer_name)
    {
        ;
    }

    public void add_Drinks(String drinks)
    {
        ;
    }
}

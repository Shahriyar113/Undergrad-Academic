package Problem_3b;

import java.util.ArrayList;
import java.util.List;

public abstract class Burger_Decorator implements Burger {
    Burger new_burger;

    Burger_Decorator (Burger burger)
    {
        new_burger = burger;
    }


    public String get_Food_Items()
    {
        return new_burger.get_Food_Items();
    }

    public double get_Price()
    {
        return new_burger.get_Price();
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


class Burger_With_Cheese extends Burger_Decorator
{
    Cheese cheese;
    Burger_With_Cheese(Burger burger)
    {
        super(burger);
        cheese = new Cheese();
    }

    @Override
    public String get_Food_Items()
    {
        return super.get_Food_Items()+ " With "+cheese.get_item() ;
    }

    @Override
    public double get_Price()
    {
        return super.get_Price() + cheese.get_Price();
    }


}


class Burger_With_Appetizer extends Burger_Decorator
{
    Appetizer appetizer;
    Burger_With_Appetizer(Burger burger)
    {
        super(burger);
    }


    public void set_Appetizer(String appetizer_name)
    {
        if(appetizer_name.equalsIgnoreCase("Frence Fry"))
        {
            appetizer = new Frence_Fry();

        }

        else if(appetizer_name.equalsIgnoreCase("Onion Rings"))
        {
            appetizer = new Onion_Rings();

        }
    }

    @Override
    public String get_Food_Items()
    {
        return super.get_Food_Items()+ " With "+appetizer.get_Appetizer() ;
    }

    @Override
    public double get_Price()
    {
        return super.get_Price() + appetizer.get_Price();
    }


}


class Burger_With_Drinks extends Burger_Decorator
{
    List<Drinks> drinksList;

    Burger_With_Drinks(Burger burger)
    {
        super(burger);
        drinksList = new ArrayList<>();

    }

    public void add_Drinks(String drinks)
    {
        if(drinks.equalsIgnoreCase("Coke"))
        {
            drinksList.add(new Coke());

        }

        else if(drinks.equalsIgnoreCase("Coffee"))
        {
            drinksList.add(new Coffee());

        }
        else if(drinks.equalsIgnoreCase("Water"))
        {
            drinksList.add(new Water());
        }

    }

    @Override
    public String get_Food_Items()
    {
        String drinks="";
        for (Drinks d : drinksList)
        {
            drinks = drinks+d.get_Drinks()+" ";
        }
        return super.get_Food_Items()+ " With "+drinks;
    }

    @Override
    public double get_Price()
    {
        double drinks_price = 0.0;

        for (Drinks d : drinksList)
        {
            drinks_price = drinks_price+ d.get_Price();
        }



        return super.get_Price() + drinks_price;
    }


}

class Burger_With_Appetizer_And_Cheese extends Burger_With_Appetizer
{
    Cheese cheese ;

    Burger_With_Appetizer_And_Cheese(Burger burger)
    {
        super(burger);
        cheese = new Cheese();
    }

    @Override
    public String get_Food_Items()
    {
        return super.get_Food_Items()+ " With "+cheese.get_item() ;
    }

    @Override
    public double get_Price()
    {
        return super.get_Price() + cheese.get_Price();
    }


}


class Burger_With_Appetizer_And_Drinks extends Burger_With_Drinks
{
    Appetizer appetizer;


    Burger_With_Appetizer_And_Drinks(Burger burger)
    {
        super(burger);
    }

    public void set_Appetizer(String appetizer_name)
    {
        if(appetizer_name.equalsIgnoreCase("Frence Fry"))
        {
            appetizer = new Frence_Fry();

        }

        else if(appetizer_name.equalsIgnoreCase("Onion Rings"))
        {
            appetizer = new Onion_Rings();

        }
    }




    @Override
    public String get_Food_Items()
    {
        return super.get_Food_Items()+ " With "+appetizer.get_Appetizer() ;
    }

    @Override
    public double get_Price()
    {
        return super.get_Price() + appetizer.get_Price();
    }


}


class Burger_With_Cheese_And_Drinks extends Burger_With_Drinks
{

    Cheese cheese;

    Burger_With_Cheese_And_Drinks(Burger burger)
    {
        super(burger);
        cheese = new Cheese();
    }



    @Override
    public String get_Food_Items()
    {
        return super.get_Food_Items()+ " With "+cheese.get_item() ;
    }

    @Override
    public double get_Price()
    {
        return super.get_Price() + cheese.get_Price();
    }


}

class Burger_With_Cheese_Appetizer_And_Drinks extends Burger_With_Drinks
{
    Appetizer appetizer;
    Cheese cheese;


    Burger_With_Cheese_Appetizer_And_Drinks(Burger burger)
    {
        super(burger);
        cheese = new Cheese();
    }

    public void set_Appetizer(String appetizer_name)
    {
        if(appetizer_name.equalsIgnoreCase("Frence Fry"))
        {
            appetizer = new Frence_Fry();

        }

        else if(appetizer_name.equalsIgnoreCase("Onion Rings"))
        {
            appetizer = new Onion_Rings();

        }
    }



    @Override
    public String get_Food_Items()
    {
        return super.get_Food_Items()+ " With "+cheese.get_item() +" and " +appetizer.get_Appetizer()  ;
    }

    @Override
    public double get_Price()
    {
        return super.get_Price() + cheese.get_Price() + appetizer.get_Price();
    }


}











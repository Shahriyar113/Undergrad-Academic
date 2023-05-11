package Problem_3b;

public class Decorator_Factory {

    public static Burger get_Decorator_Factory(String order)
    {
        if(order.equalsIgnoreCase("Beef Burger With Frence Fry And Cheese"))
        {
            Burger burger_with_extra = new Burger_With_Appetizer_And_Cheese(new Beef_Burger());
            burger_with_extra.set_Appetizer("Frence Fry");
            return burger_with_extra;
        }

        else if(order.equalsIgnoreCase("Veggi Buger with Onion Rings and Water"))
            {
                Burger burger_with_extra = new Burger_With_Appetizer_And_Drinks(new Veggi_Burger());
                burger_with_extra.set_Appetizer("Onion Rings");
                burger_with_extra.add_Drinks("Water");

                return burger_with_extra;
            }

        else if(order.equalsIgnoreCase("Veggi Burger With Frence Fry and Coke"))
            {
                Burger burger_with_extra = new Burger_With_Appetizer_And_Drinks(new Veggi_Burger());
                burger_with_extra.set_Appetizer("Frence Fry");
                burger_with_extra.add_Drinks("Coke");

                return burger_with_extra;
            }

        else if (order.equalsIgnoreCase("Veggi Burger With Onion Rings With Coffee and Water"))
            {
                Burger burger_with_extra = new Burger_With_Appetizer_And_Drinks(new Veggi_Burger());
                burger_with_extra.set_Appetizer("Onion Rings");
                burger_with_extra.add_Drinks("Coke");
                burger_with_extra.add_Drinks("Water");


                return burger_with_extra;
            }

        else if(order.equalsIgnoreCase("Beef Burger Only"))
            {
                Burger burger = new Beef_Burger();

                return burger;
            }

        return null;



    }


}

package Problem_3b;

public class Main {

    public static void main(String[] args) {

        Burger burger1 = Decorator_Factory.get_Decorator_Factory
                ("Beef Burger With Frence Fry And Cheese");

        System.out.println("Order: "+burger1.get_Food_Items());
        System.out.println("Total price: "+burger1.get_Price());

        System.out.println();

        Burger burger2 = Decorator_Factory.get_Decorator_Factory
                ("Veggi Buger with Onion Rings and Water");

        System.out.println("Order: "+burger2.get_Food_Items());
        System.out.println("Total price: "+burger2.get_Price());

        System.out.println();

        Burger burger3 = Decorator_Factory.get_Decorator_Factory
                ("Veggi Burger With Frence Fry and Coke");

        System.out.println("Order: "+burger3.get_Food_Items());
        System.out.println("Total price: "+burger3.get_Price());

        System.out.println();


        Burger burger4 = Decorator_Factory.get_Decorator_Factory
                ("Veggi Burger With Onion Rings With Coffee and Water");

        System.out.println("Order: "+burger4.get_Food_Items());
        System.out.println("Total price: "+burger4.get_Price());

        System.out.println();

        Burger burger5 = Decorator_Factory.get_Decorator_Factory
                ("Beef Burger Only");

        System.out.println("Order: "+burger5.get_Food_Items());
        System.out.println("Total price: "+burger5.get_Price());

        System.out.println();




    }
}

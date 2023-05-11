package Problem_1;


import java.util.ArrayList;
import java.util.List;


public class Product {

    private List<Component> components;


    public Product()
    {
        components = new ArrayList<Component>();
    }

    public void add(Component comp)
    {
        components.add(comp);
    }

    public void show()
    {
        for(Component c:components)
        {
            System.out.print(c.getClass().getSimpleName()+"-> " +c.getName()+": "+c.getPrice()+"$");
            System.out.println();
        }
    }

    public double getTotalCost()
    {
        double total_cost = 0;

        for(Component c:components)
        {
            total_cost = total_cost + c.getPrice();
        }
        return total_cost;
    }






}

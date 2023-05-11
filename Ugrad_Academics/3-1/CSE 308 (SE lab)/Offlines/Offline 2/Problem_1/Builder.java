package Problem_1;


interface Builder
{
    void Add_Display_Unit();
    void Add_Communication_Channel();
    void Add_Controller();
    Product getProducts();


}


class Delux implements Builder
{
    Product products;

    int total_display_unit;
    Component communication_module;


    Delux()
    {
        products = new Product();
        communication_module = null;

    }

    Delux(String Communication_module_type,int total_display_unit)
    {
        products = new Product();
        communication_module = Communication_System.get_Communication_Module(Communication_module_type);
        this.total_display_unit = total_display_unit;
    }



    public void Add_Display_Unit()
    {
        for(int i=0;i<total_display_unit;i++)
        {
            products.add(new Processor("Raspberry Pi", 3500));
            products.add(new Display_System("LCD Panel", 2200));
        }
    }


    public void Add_Communication_Channel()
    {
       products.add(communication_module);

    }



    public void Add_Controller()
    {
        products.add(new Web_base_Controller("PQR",4000));

    }

    public Product getProducts()
    {
        return products;
    }


}



class Optimal implements Builder
{
    Product products;

    int total_display_unit;
    Component communication_module;


    Optimal()
    {
        products = new Product();
        communication_module = null;

    }

    Optimal(String Communication_module_type,int total_display_unit)
    {
        products = new Product();
        communication_module = Communication_System.get_Communication_Module(Communication_module_type);
        this.total_display_unit = total_display_unit;
    }



    public void Add_Display_Unit()
    {
        for(int i=0;i<total_display_unit;i++)
        {
            products.add(new Processor("Arduino Mega", 2500));
            products.add(new Display_System("LED Matrix", 2000));
        }
    }


    public void Add_Communication_Channel()
    {
        products.add(communication_module);

    }

    public void Add_Controller()
    {
        products.add(new Web_base_Controller("PQR",4000));

    }

    public Product getProducts()
    {
        return products;
    }


}




class Poor implements Builder
{
    Product products;

    int total_display_unit;
    Component communication_module;


    Poor()
    {
        products = new Product();
        communication_module = null;

    }

    Poor(String Communication_module_type,int total_display_unit)
    {
        products = new Product();
        communication_module = Communication_System.get_Communication_Module(Communication_module_type);
        this.total_display_unit = total_display_unit;
    }



    public void Add_Display_Unit()
    {
        for(int i=0;i<total_display_unit;i++)
        {
            products.add(new Processor("ATMega32", 2000));
            products.add(new Display_System("LED Matrix", 1500));
        }
    }


    public void Add_Communication_Channel()
    {
        products.add(communication_module);

    }


    public void Add_Controller()
    {
        products.add(new Web_base_Controller("PQR",4000));

    }



    public Product getProducts()
    {
        return products;
    }




}





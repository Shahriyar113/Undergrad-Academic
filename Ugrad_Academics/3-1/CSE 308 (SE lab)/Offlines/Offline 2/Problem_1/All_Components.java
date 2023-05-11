package Problem_1;

abstract class Component
{
    String name;
    double price;

    public Component(String name, double price) {
        this.name = name;
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }
}



class Processor extends Component
{
    public Processor(String name, double price) {
        super(name,price);
    }
}

class Display_System extends Component
{
    public Display_System(String name, double price) {
        super(name,price);
    }
}

class Display_Unit
{
    Processor processor;
    Display_System display_system;

    public Display_Unit(Processor processor, Display_System display_system) {
        this.processor = processor;
        this.display_system = display_system;
    }

    public Processor getProcessor() {
        return processor;
    }

    public void setProcessor(Processor processor) {
        this.processor = processor;
    }

    public Display_System getDisplay_system() {
        return display_system;
    }

    public void setDisplay_system(Display_System display_system) {
        this.display_system = display_system;
    }
}


class BroadBand extends Component
{
    public BroadBand(String name, double price) {
        super(name,price);
    }
}

class Mobile_Data extends Component
{
    public Mobile_Data(String name, double price) {
        super(name,price);
    }
}




class Communication_System
{
    public static Component get_Communication_Module(String module_name)
    {
        if(module_name == null)
        {
            return null;
        }
        else if(module_name .equalsIgnoreCase("WIFI"))
        {
            return new BroadBand("ABC",2000);
        }

        else if(module_name.equalsIgnoreCase("MOBILE DATA"))
        {
            return new Mobile_Data("XYZ",1500);
        }

        return null;
    }

}


class Web_base_Controller extends Component
{
    public Web_base_Controller(String name, double price) {
        super(name,price);
    }
}




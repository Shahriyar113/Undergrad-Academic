package Problem_2;

public class Environment_Factory {

    public static Environment getEnviornmentFactory(String OS_Name)
    {
        if(OS_Name == null)
        {
            return null;
        }

        else if(OS_Name.equalsIgnoreCase("Windows"))
        {
            return new Windows();
        }
        else if(OS_Name.equalsIgnoreCase("Linux"))
        {
            return new Linux();
        }

        return null;
    }
}

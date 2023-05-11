package Banking_System;

public class Employee_Factory
{
    public Employee getEmployee(String Employee_type,String name)
    {
        if(Employee_type == null)
        {
            return null;
        }
        else if(Employee_type.equalsIgnoreCase("CASHIER"))
        {
            return new Cashier(name);
        }
        else if(Employee_type.equalsIgnoreCase("OFFICER"))
        {
            return new Officer(name);
        }
        else if(Employee_type.equalsIgnoreCase("MANAGING DIRECTOR"))
        {
            return new Managing_Director(name);
        }
        return null;
    }
}

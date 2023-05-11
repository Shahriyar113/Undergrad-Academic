package Banking_System;

import java.util.ArrayList;
import java.util.List;

class Bank {

    String Bank_Name;
    List<Account> accounts;
    List<Employee> employees;
    List<Account> pending_loan_request ;
    double Internal_Fund;


    Bank(String name,double initial_fund)
    {

       Internal_Fund = initial_fund;
       Bank_Name=name;



       accounts = new ArrayList<Account>();
       employees = new ArrayList<Employee>();
       pending_loan_request = new ArrayList<Account>();

       Employee_Factory employee_factory=new Employee_Factory();
       employees.add(employee_factory.getEmployee("Managing Director","MD"));
       employees.add(employee_factory.getEmployee("Officer","S1"));
       employees.add(employee_factory.getEmployee("Officer","S2"));
       employees.add(employee_factory.getEmployee("Cashier","C1"));
       employees.add(employee_factory.getEmployee("Cashier","C2"));
       employees.add(employee_factory.getEmployee("Cashier","C3"));
       employees.add(employee_factory.getEmployee("Cashier","C4"));
       employees.add(employee_factory.getEmployee("Cashier","C5"));



       System.out.println("Bank Created; MD,S1,S2,C1,C2,C3,C4,C5 created");


    }

    public Account open_Account(String Acc_name)
    {

        for (Account acc : accounts )
        {
            if(acc.getUserName().equals(Acc_name))
            {
                System.out.println("Welcome Back, "+acc.getUserName());
                return acc;
            }
        }
        return null;
    }

    public Employee open_Employee(String Emp_name)
    {
        for (Employee emp:employees)
        {
            if(emp.getUserName().equals(Emp_name))
            {
                System.out.print(emp.getUserName() + " active");
                if(pending_loan_request.size() != 0)
                {
                    System.out.println(", there are loan approvals pending");
                }
                else
                {
                    System.out.println(", there is no loan approval pending");
                }

                return emp;
            }


        }
        return null;
    }

    public void Year_Increment_All()
    {
        for (Account acc:accounts)
        {
            acc.Year_Increment();
        }

    }

    public void setInternal_Fund(double fund)
    {
        Internal_Fund = fund;
    }

    public double getInternal_Fund()
    {
        return Internal_Fund;
    }

}

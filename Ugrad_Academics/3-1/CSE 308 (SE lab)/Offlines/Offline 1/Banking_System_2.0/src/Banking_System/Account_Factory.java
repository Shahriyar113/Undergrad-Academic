package Banking_System;

public class Account_Factory {

    public Account getAccount(String Account_type,String username,double initial_deposit,Bank bank)
    {
        if(Account_type == null)
        {
            return null;
        }
        else if(Account_type.equalsIgnoreCase("SAVINGS"))
        {
            return new Savings_Account(username,initial_deposit,bank);
        }
        else if(Account_type.equalsIgnoreCase("STUDENT"))
        {
            return new Student_Account(username,initial_deposit,bank);
        }
        else if(Account_type.equalsIgnoreCase("FIXED DEPOSIT"))
        {
            return new Fixed_Deposit_Account(username,initial_deposit,bank);
        }

        else if(Account_type.equalsIgnoreCase("LOAN"))
        {
            return new Loan_Account(username,initial_deposit,bank);
        }

        return null;



    }


}

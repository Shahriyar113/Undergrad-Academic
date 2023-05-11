package Banking_System;

import java.util.List;

class Employee {

    protected String UserName;

    Employee(String userName)
    {
        UserName = userName;
    }

    public void Lookup(String account_name, Bank bank)
    {

        for (Account acc : bank.accounts)
        {

            if(acc.getUserName().equals(account_name))
            {
                if(!acc.getClass().getSimpleName().equals("Loan_Account"))
                    System.out.println(acc.getUserName()+"'s Current Balance: " +acc.get_Current_Balance());

                else
                    System.out.println(acc.getUserName()+"'s Current Loan: " +acc.getLoan_amount());

                return;
            }
        }

        System.out.println("No account exists with this name");
    }

    public void Approve_loan(Account acc)
    {
        //for Officers and Managing Directors

    }

    public void Approve_All_pending(Bank bank)
    {
        System.out.println("You dont have permission for this operation");
    }

    public void change_interest_rate(String Account_type,double new_rate,Bank bank)
    {
        //for Managing Director

        System.out.println("You dont have permission for this operation");


    }

    public void See_internal_Funds(Bank bank)
    {
        //for Managing Director
        System.out.println("You dont have permission for this operation");

    }


    public String getUserName()
    {
        return UserName;
    }



}


class Cashier extends Employee
{
    Cashier(String Username)
    {
        super(Username);
    }
}


class Officer extends Employee
{
    Officer(String UserName)
    {
        super(UserName);
    }

    public void Approve_loan(Account acc)
    {

       // if(acc.getRequested_Loan() < )

        if(!acc.getClass().getSimpleName().equals("Loan_Account"))
        {
            double curr_balance = acc.current_balance + acc.getRequested_Loan();
            double curr_loan_amount = acc.loan_amount + acc.getRequested_Loan();


            acc.setCurrent_balance(curr_balance);
            acc.setLoan_amount(curr_loan_amount);

            System.out.println("Loan for " + acc.getUserName() + " approved");
        }
        else
        {
            double curr_loan_amount = acc.loan_amount + acc.getRequested_Loan();
            acc.setLoan_amount(curr_loan_amount);

            System.out.println("Loan for " + acc.getUserName() + " approved");

        }

    }


    public void Approve_All_pending(Bank bank)
    {
        for (Account acc : bank.pending_loan_request)
        {
            this.Approve_loan(acc);
        }

        //removing all the account in "pending_loan_request" as all the loans are approved

        int size = bank.pending_loan_request.size();
        for(int i=0;i<size;i++)
        {
            bank.pending_loan_request.remove(i);
        }

    }
}


class Managing_Director extends Officer
{
    Managing_Director(String UserName)
    {
        super(UserName);
    }

    public void change_interest_rate(String Account_type,double new_rate,Bank bank)
    {
        //extra work
        if(Account_type.equalsIgnoreCase("STUDENT"))
        {
            Account_type = "Student_Account";
        }

        else if(Account_type.equalsIgnoreCase("SAVINGS"))
        {
            Account_type = "Savings_Account";
        }
        else if(Account_type.equalsIgnoreCase("FIXED DEPOSIT"))
        {
            Account_type = "Fixed_Deposit_Account";
        }
        else if(Account_type.equalsIgnoreCase("LOAN"))
        {
            System.out.println("There is no interest for loan");
            return;
        }

        //for Managing Director

            for (Account acc : bank.accounts) {
                if (acc.getClass().getSimpleName().equals(Account_type)) {
                    acc.change_interest_rate(new_rate);
                }
                System.out.println(UserName + " changed interest rate to " + new_rate + " for " + Account_type);

            }



    }

    public void See_internal_Funds(Bank bank)
    {
        System.out.println("The Internal Fund of the bank: "+ bank.getInternal_Fund() );

    }




}

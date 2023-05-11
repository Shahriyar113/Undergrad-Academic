package Banking_System;

abstract class Account
{
    protected String UserName;
    protected double current_balance;
    protected double loan_amount;
    protected int Account_Age;
    protected double Requested_Loan; //last requested loan
    protected double interest_rate;
    protected final double Yearly_Service_charge = 500;
    protected final double Yearly_interest_on_loan = 0.1;

    Account(String userName)
    {
        UserName = userName;
        Account_Age = 0;
        loan_amount = 0;
        interest_rate = 0;
    }

    public abstract void deposit(double amount,Bank bank);
    public abstract void withdraw(double amount,Bank bank);
    public void request_loan(double amount,Bank bank)
    {
        //loan request for other 3 type
    }

    public void request_loan(Bank bank)
    {
        //loan request for loan account
    }
    public abstract void query();


    public void Year_Increment()
    {
        Account_Age++;
        current_balance = current_balance + current_balance*(interest_rate/100) -
                loan_amount*Yearly_interest_on_loan - Yearly_Service_charge;
    }

    public void change_interest_rate(double changed_rate)
    {
        interest_rate = changed_rate;
    }


    //achieving run time polymorphism
    public double get_Current_Balance()
    {
        return current_balance;
    }

    public String getUserName()
    {
        return UserName;
    }

    public void setLoan_amount(double amount)
    {
        loan_amount = amount;
    }

    public double getLoan_amount()
    {
        return loan_amount;
    }

    public double getCurrent_Interest_rate()
    {
        return interest_rate;
    }

    public void setRequested_Loan(double amount)
    {
        Requested_Loan = amount;
    }
    public double getRequested_Loan()
    {
        return Requested_Loan;
    }

    public void setCurrent_balance(double balance)
    {
        current_balance = balance;
    }

    public double getCurrent_balance()
    {
        return current_balance;
    }







}


class Savings_Account extends Account
{

    Savings_Account(String name,double initial_deposit,Bank bank)
    {
        super(name);
        current_balance = current_balance + initial_deposit;
        super.interest_rate = 10;
        System.out.println("Savings Account For "+name+" Created. Initial Balance: "+current_balance+"$");

        double curr_bank_internal_fund = bank.getInternal_Fund() + initial_deposit;
        bank.setInternal_Fund(curr_bank_internal_fund);

        bank.accounts.add(this);


    }

    public void deposit(double amount,Bank bank)
    {
        current_balance = current_balance + amount;
        System.out.print(amount+"$ deposited! ");
        System.out.print("Current Balance: "+current_balance);
        System.out.println();

        //increasing internal Fund
        double curr_bank_internal_fund = bank.getInternal_Fund() + amount;
        bank.setInternal_Fund(curr_bank_internal_fund);

    }

    public void withdraw(double amount,Bank bank)
    {
        if(current_balance - amount < 1000 || amount > current_balance)
        {
            System.out.print("Invalid transaction! ");
            System.out.print("Current Balance: "+current_balance);
            System.out.println();
        }
        else
        {
            current_balance = current_balance - amount;
            System.out.print(amount+"$ withdrawn! ");
            System.out.print("Current Balance: "+current_balance);
            System.out.println();

            double curr_bank_internal_fund = bank.getInternal_Fund() - amount;
            bank.setInternal_Fund(curr_bank_internal_fund);
        }
    }

    public void request_loan(double amount,Bank bank)
    {
        if(amount > 10000)
        {
            System.out.println("Invalid Loan Requested");
        }
        else
        {
            super.setRequested_Loan(amount);
            bank.pending_loan_request.add(this);
            System.out.println("Loan request Successful.Sent For approval");
        }

    }

    public void query()
    {
        if(super.loan_amount > 0)
        {
            System.out.println("Current Balance: "+current_balance+"$. loan: "+super.loan_amount+"$ ");
        }
        else
        {
            System.out.println("Current Balance: "+current_balance+"$ ");
        }
    }


}


class Student_Account extends Account
{

    Student_Account(String name,double initial_deposit,Bank bank)
    {
        super(name);
        current_balance = current_balance + initial_deposit;
        super.interest_rate = 5;
        System.out.println("Student Account For "+name+" Created. Initial Balance: "+current_balance+"$");

        double curr_bank_internal_fund = bank.getInternal_Fund() + initial_deposit;
        bank.setInternal_Fund(curr_bank_internal_fund);

        bank.accounts.add(this);

    }

    public void deposit(double amount,Bank bank)
    {

        current_balance = current_balance + amount;
        System.out.print(amount+"$ deposited! ");
        System.out.print("Current Balance: "+current_balance);
        System.out.println();

        double curr_bank_internal_fund = bank.getInternal_Fund() + amount;
        bank.setInternal_Fund(curr_bank_internal_fund);

    }

    public void withdraw(double amount,Bank bank)
    {
        if(amount > 10000 || amount > current_balance)
        {
            System.out.print("Invalid transaction! ");
            System.out.print("Current Balance: "+current_balance);
            System.out.println();
        }
        else
        {
            current_balance = current_balance - amount;
            System.out.print(amount+"$ withdrawn! ");
            System.out.print("Current Balance: "+current_balance);
            System.out.println();

            double curr_bank_internal_fund = bank.getInternal_Fund() - amount;
            bank.setInternal_Fund(curr_bank_internal_fund);
        }
    }

    public void request_loan(double amount,Bank bank)
    {
        if(amount > 1000)
        {
            System.out.println("Invalid Loan Requested");
        }
        else
        {
            super.setRequested_Loan(amount);
            bank.pending_loan_request.add(this);
            System.out.println("Loan request Successful.Sent For approval");

        }

    }

    public void query()
    {
        if(super.loan_amount > 0)
        {
            System.out.println("Current Balance: "+current_balance+"$. loan: "+super.loan_amount+"$ ");
        }
        else
        {
            System.out.println("Current Balance: "+current_balance+"$ ");
        }
    }


}


class Fixed_Deposit_Account extends Account
{

    Fixed_Deposit_Account(String name,double initial_deposit,Bank bank)
    {
        super(name);
        if(initial_deposit < 100000)
        {
            System.out.println("Invalid initial deposit.");
        }
        else
        {

            current_balance = current_balance + initial_deposit;
            super.interest_rate = 15;
            System.out.println("Fixed Deposit Account For "+name+" Created. Initial Balance: "+current_balance+"$");

            double curr_bank_internal_fund = bank.getInternal_Fund() + initial_deposit;
            bank.setInternal_Fund(curr_bank_internal_fund);

            bank.accounts.add(this);



        }

    }

    public void deposit(double amount,Bank bank)
    {
        if(amount <= 50000)
        System.out.println("This Deposit is invalid for Fixed Deposit Account");

        else
        {
            current_balance = current_balance + amount;
            System.out.print(amount+"$ deposited! ");
            System.out.print("Current Balance: "+current_balance);
            System.out.println();

            double curr_bank_internal_fund = bank.getInternal_Fund() + amount;
            bank.setInternal_Fund(curr_bank_internal_fund);
        }

    }

    public void withdraw(double amount,Bank bank)
    {
        if(super.Account_Age < 1 || amount > current_balance)
        {
            System.out.print("Invalid transaction! ");
            System.out.print("Current Balance: "+current_balance);
            System.out.println();
        }
        else
        {
            current_balance = current_balance - amount;
            System.out.print(amount+"$ withdrawn! ");
            System.out.print("Current Balance: "+current_balance);
            System.out.println();

            double curr_bank_internal_fund = bank.getInternal_Fund() - amount;
            bank.setInternal_Fund(curr_bank_internal_fund);


        }
    }

    public void request_loan(double amount,Bank bank)
    {
        if(amount > 100000)
        {
            System.out.println("Invalid Loan Requested");
        }
        else
        {

            super.setRequested_Loan(amount);
            bank.pending_loan_request.add(this);
            System.out.println("Loan request Successful.Sent For approval");
        }

    }

    public void query()
    {
        if(super.loan_amount > 0)
        {
            System.out.println("Current Balance: "+current_balance+"$. loan: "+super.loan_amount+"$ ");
        }
        else
        {
            System.out.println("Current Balance: "+current_balance+"$ ");
        }
    }


}


class Loan_Account extends Account
{

    Loan_Account(String name,double initial_loan_amount,Bank bank)
    {
        super(name);
        super.loan_amount = super.loan_amount + initial_loan_amount;
        interest_rate = 0;
        System.out.println("Loan Account For "+name+" Created. Initial loan: "+super.loan_amount+"$");

        double curr_bank_internal_fund = bank.getInternal_Fund() - initial_loan_amount;
        bank.setInternal_Fund(curr_bank_internal_fund);

        bank.accounts.add(this);


    }

    public void deposit(double amount,Bank bank)
    {
        if(amount > loan_amount)
        {
            System.out.println("Invalid deposit for loan");
            return;
        }

        super.loan_amount = super.loan_amount - amount;
        System.out.print(amount+"$ deposited! ");
        System.out.print("Current loan: "+super.loan_amount);
        System.out.println();

        double curr_bank_internal_fund = bank.getInternal_Fund() + amount;
        bank.setInternal_Fund(curr_bank_internal_fund);

    }

    public void withdraw(double amount,Bank bank)
    {
        System.out.println("Can not withdraw from a loan account");
    }

    //function overloading
    public void request_loan(Bank bank)
    {
        super.setRequested_Loan(loan_amount*0.05);
        bank.pending_loan_request.add(this);
        System.out.println("Loan request Successful.Sent For approval");
    }

    public void request_loan(double amount,Bank bank)
    {
        request_loan(bank);
    }

    public void Year_Increment()
    {
        Account_Age++;
        loan_amount = loan_amount + loan_amount*0.1;
    }

    public void query()
    {
        System.out.println("Current loan: "+super.loan_amount+"$ ");
    }

    public void change_interest_rate(double changed_rate)
    {
        interest_rate = 0;
    }



}


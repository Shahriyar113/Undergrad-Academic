package Banking_System;

import java.io.File;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {


        Bank bank = new Bank("ABC",1000000);

        Account_Factory account_factory=new Account_Factory();

        //keeping the referance of currently logged account / employee
        Account Curr_logged_Account=null;
        Employee Currently_Active_employee = null;

        //Create Alice Student 1000

        try {
            File file=new File("Input.txt");

            Scanner input = new Scanner(file);


            while(true)
            {
                String line = input.nextLine();
                if(line == null)
                {
                    break;
                }
                String[] inputs = line.split(" ");

                //System.out.println(inputs[0]);

            if(inputs[0].equalsIgnoreCase("CREATE"))
            {
                Account std_acc = account_factory.getAccount(inputs[2],inputs[1],
                        Double.parseDouble(inputs[3]),bank);

                Curr_logged_Account = std_acc;
                //bank.accounts.add(std_acc);
            }

            else if(inputs[0].equalsIgnoreCase("DEPOSIT"))
            {
                Curr_logged_Account.deposit(Double.parseDouble(inputs[1]),bank);
            }

            else if(inputs[0].equalsIgnoreCase("WITHDRAW"))
            {
                Curr_logged_Account.withdraw(Double.parseDouble(inputs[1]),bank);
            }
            else if(inputs[0].equalsIgnoreCase("QUERY"))
            {
                Curr_logged_Account.query();
            }

            else if(inputs[0].equalsIgnoreCase("REQUEST"))
            {
                Curr_logged_Account.request_loan(Double.parseDouble(inputs[1]),bank);

            }
            else if(inputs[0].equalsIgnoreCase("CLOSE"))
            {
                if(Curr_logged_Account != null)
                {
                    System.out.println("Transaction for "+Curr_logged_Account.getUserName()+" Closed");
                    Curr_logged_Account = null;
                }

                else if(Currently_Active_employee != null)
                {
                    System.out.println("Operation for "+Currently_Active_employee.getUserName()+" Closed");
                    Currently_Active_employee = null;
                }
            }

            else if((inputs[0].equalsIgnoreCase("OPEN")))
            {
                Currently_Active_employee = bank.open_Employee(inputs[1]);
                if(Currently_Active_employee != null)
                {
                    continue;
                }

                Curr_logged_Account = bank.open_Account(inputs[1]);
                {
                    if(Curr_logged_Account != null)
                    {
                        continue;
                    }
                }
                System.out.println("No stuff of this name");

            }

            else if((inputs[0].equalsIgnoreCase("APPROVE")))
            {
                Currently_Active_employee.Approve_All_pending(bank);

            }

            else if((inputs[0].equalsIgnoreCase("CHANGE")))
            {

                Currently_Active_employee.change_interest_rate(inputs[1],Double.
                        parseDouble(inputs[2]),bank);

            }
            else if((inputs[0].equalsIgnoreCase("LOOKUP")))
            {
                Currently_Active_employee.Lookup(inputs[1],bank);
            }
            else if((inputs[0].equalsIgnoreCase("SEE")))
            {
                Currently_Active_employee.See_internal_Funds(bank);

            }

            else if((inputs[0].equalsIgnoreCase("INC")))
            {
                System.out.println("1 Year Passed");
                bank.Year_Increment_All();

            }

            }


        } catch (Exception e)
        {
            ;
        }


        //Open Alice



        //Query

        //Close
        //INC


        //Open Alice



//        Bank bank = new Bank("ABC",1000000);
//
//        //keeping the referance of currently logged account / employee
//        Account Curr_logged_Account=null;
//        Employee Currently_Active_employee = null;
//
//        //Create Alice Student 1000
//        Account std_acc = new Student_Account("Alice",1000,bank);
//        Curr_logged_Account = std_acc;
//        bank.accounts.add(std_acc);
//
//
//        //Deposit 20000
//        Curr_logged_Account.deposit(20000,bank);
//
//        //withdraw 12000
//        Curr_logged_Account.withdraw(12000,bank);
//
//        //Query
//        Curr_logged_Account.query();
//
//        //Request 500
//        Curr_logged_Account.request_loan(500);
//
//        bank.pending_loan_request.add(Curr_logged_Account);
//
//        //close
//
//        if(Curr_logged_Account != null)
//        {
//            System.out.println("Transaction for "+Curr_logged_Account.getUserName()+" Closed");
//            Curr_logged_Account = null;
//        }
//
//        else if(Currently_Active_employee != null)
//        {
//            System.out.println("Operation for "+Currently_Active_employee.getUserName()+" Closed");
//            Currently_Active_employee = null;
//        }
//
//
//        //Open MD
//        //searching the active employee referance
//        for (Employee emp:bank.employees)
//        {
//            if(emp.getUserName().equals("MD"))
//            {
//                Currently_Active_employee = emp;
//                break;
//            }
//
//        }
//
//        if(Currently_Active_employee == null)
//        {
//            System.out.println("This employee does not exist");
//        }
//
//
//        System.out.print(Currently_Active_employee.getUserName() + " active");
//
//        if(bank.pending_loan_request.size() != 0)
//        {
//            System.out.println(", there are loan approvals pending");
//        }
//        else
//        {
//            System.out.println("There is no loan approval pending");
//        }
//
//        //Approve loan(Approving all pending loans)
//
//        if(Currently_Active_employee.getClass().getSimpleName().equals("Officer") ||
//
//                Currently_Active_employee.getClass().getSimpleName().equals("Managing_Director"))
//        {
//            //System.out.println(bank.pending_loan_request.get(0).getUserName());
//            for (Account acc : bank.pending_loan_request)
//            {
//                Currently_Active_employee.Approve_loan(acc);
//            }
//
//            //removing all the account in "pending_loan_request" as all the loans are approved
//
//            int size = bank.pending_loan_request.size();
//            for(int i=0;i<size;i++)
//            {
//                bank.pending_loan_request.remove(i);
//            }
//
//        }
//
//        else
//        {
//            System.out.println("You dont have permission for this operation");
//        }
//
//
//        //Change Student 7.50
//
//        if(Currently_Active_employee.getClass().getSimpleName().equals("Managing_Director"))
//        {
//            Currently_Active_employee.change_interest_rate("Student_Account",7.5,bank.accounts);
//        }
//
//        else
//        {
//            System.out.println("You dont have permission for this operation");
//
//        }
//
//        //Lookup Alice
//
//        for (Account acc : bank.accounts)
//        {
//            if(acc.getUserName().equals("Alice"))
//            {
//                System.out.println(acc.getUserName()+"'s current balance "+acc.getCurrent_balance());
//                break;
//            }
//        }
//
//        //See
//        if(Currently_Active_employee.getClass().getSimpleName().equals("Managing_Director"))
//        {
//            Currently_Active_employee.See_internal_Funds(bank);
//        }
//
//        else
//        {
//            System.out.println("You dont have permission for this operation");
//
//        }
//
//        //Close
//        if(Curr_logged_Account != null)
//        {
//            System.out.println("Transaction for "+Curr_logged_Account.getUserName()+" Closed");
//            Curr_logged_Account = null;
//        }
//
//        else if(Currently_Active_employee != null)
//        {
//            System.out.println("Operation for "+Currently_Active_employee.getUserName()+" Closed");
//            Currently_Active_employee = null;
//        }
//
//        //Open Alice
//
//        for (Account acc : bank.accounts )
//        {
//            if(acc.getUserName().equals("Alice"))
//            {
//                Curr_logged_Account = acc;
//                System.out.println("Welcome Back, "+acc.getUserName());
//                break;
//            }
//        }
//
//        //Query
//        Curr_logged_Account.query();
//
//        //Close
//
//        if(Curr_logged_Account != null)
//        {
//            System.out.println("Transaction for "+Curr_logged_Account.getUserName()+" Closed");
//            Curr_logged_Account = null;
//        }
//
//        else if(Currently_Active_employee != null)
//        {
//            System.out.println("Operation for "+Currently_Active_employee.getUserName()+" Closed");
//            Currently_Active_employee = null;
//        }
//
//        //INC
//        System.out.println("1 Year Passed");
//        for (Account acc:bank.accounts)
//        {
//            acc.Year_Increment();
//        }
//
//
//        //Open Alice
//
//        for (Account acc : bank.accounts )
//        {
//            if(acc.getUserName().equals("Alice"))
//            {
//                Curr_logged_Account = acc;
//                System.out.println("Welcome Back, "+acc.getUserName());
//                break;
//            }
//        }
//
//        //Query
//        Curr_logged_Account.query();
//
//        //Close
//
//        if(Curr_logged_Account != null)
//        {
//            System.out.println("Transaction for "+Curr_logged_Account.getUserName()+" Closed");
//            Curr_logged_Account = null;
//        }
//
//        else if(Currently_Active_employee != null)
//        {
//            System.out.println("Operation for "+Currently_Active_employee.getUserName()+" Closed");
//            Currently_Active_employee = null;
//        }
//
//

    }
}

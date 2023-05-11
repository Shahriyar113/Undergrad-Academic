package Offline3_1;

import java.util.Scanner;

import static java.lang.System.exit;

public class Main {

    CustomStack<Double> value_stack;
    CustomStack<Character> op_stack;
    String anotherValueString;
    String valueString; // for storing value from String expression

    Main()
    {
        valueString="";
        anotherValueString="";
        value_stack=new CustomStack<>();
        op_stack=new CustomStack<>();
    }

    public int precedence(char op)
    {
        if(op == '*' || op == '/')
            return 2;
        else if(op == '+' || op == '-')
            return 1;
        else
        {
            return 0; //for invalid operator(e.g. '(' )
        }

    }


    //best case complexity = O(n) ,n ==> the size of input string
    //worst case complexity= O(n) ,
    public double Evaluate(String str)
    {
        try {


            int L_parenthesis_count = 0;
            int R_parenthesis_count = 0;

            //checking validity

            for (int i = 0; i < str.length(); i++) {
                if (str.charAt(i) == '(') {
                    L_parenthesis_count++;
                    continue;
                }
                if (str.charAt(i) == ')') {
                    R_parenthesis_count++;
                    continue;
                }
            }
//
//            System.out.println(L_parenthesis_count);
//            System.out.println(R_parenthesis_count);

            if (L_parenthesis_count != R_parenthesis_count) {
                System.out.println("Not Valid!");
                exit(0);
            } else {


                //it counts the number of left parenthesis in the operator stack currently
                int L_parenthesis_count_in_op_stack=0;

                for (int i = 0; i < str.length(); i++) {

                    if (str.charAt(i) == '(') {
                       // System.out.println(value_stack);
                        //System.out.println(op_stack);

                        //this is done to convert seperate the double value from inputed string expression
                        if (!valueString.equalsIgnoreCase("")) {
                            value_stack.push(Double.parseDouble(valueString));

                            //System.out.print(Double.parseDouble(valueString));
                            valueString = "";
                        }
                        //System.out.print(str.charAt(i));
                        L_parenthesis_count_in_op_stack++;
                        op_stack.push(str.charAt(i));

                    }

                    //if operator
                    else if (str.charAt(i) == '+' || str.charAt(i) == '-' || str.charAt(i) == '*' || str.charAt(i) == '/') {

                        //System.out.println(value_stack);
                        //System.out.println(op_stack);

                        //this is done to convert seperate the double value from inputed string expression
                        if (!valueString.equalsIgnoreCase("")) {
                            value_stack.push(Double.parseDouble(valueString));
                            // System.out.print(Double.parseDouble(valueString));
                            valueString = "";
                        }
                        char op = str.charAt(i);


                         //System.out.print(str.charAt(i));

                        //operators are inserting to the stack according to their precedence


                        //this while loop is for handling the precision
                        //while the op_stack is non empty and the precedence of new incoming operator
                        //is less than or equal the top most operator of the stack, then the algebric operation
                        //of the higher precedence operator will evaluate and then the new operator will be inserted
                        //but if the precedence of new incoming operator is less than the top most operator of the stack
                        //then the higher precedence incoming operator will directly push to the op_stack


                        while (!op_stack.isEmpty() && (this.precedence(op_stack.peek()) >= this.precedence(op))) {
                           // System.out.println(value_stack);
                            //System.out.println(op_stack);


                            char operator = op_stack.pop();
                            double value2 = value_stack.pop();
                            double value1 = value_stack.pop();

                            if (operator == '+') {
                                value_stack.push(value1 + value2);
                            } else if (operator == '-') {
                                value_stack.push(value1 - value2);
                            } else if (operator == '*') {
                                value_stack.push(value1 * value2);
                            } else {
                                if(value2 == 0) // something divided by 0 is undefined
                                {
                                    throw new ArithmeticException();
                                }
                                value_stack.push(value1 / value2);
                            }
                        }

                        //finally pushing the new coming operator to stack
                        op_stack.push(op);
                      //  System.out.println(value_stack);
                        //System.out.println(op_stack);

                    }


                    //if right parrenthesis
                    else if (str.charAt(i) == ')') {

                        //this is done to convert seperate the double value from inputed string expression
                        if (!valueString.equalsIgnoreCase("")) {
                            value_stack.push(Double.parseDouble(valueString));
                             //System.out.print(Double.parseDouble(valueString));
                            valueString = "";
                        }

                      //  System.out.println(value_stack);
                        //System.out.println(op_stack);

                        //when right parenthesis is found,
                        //this loop evaluates the expression with the order of precision and
                        //eleminate the left parenthesis from stack
                        //this loop helps to evaluate 12/(2+4)*5 type expression

                        while(!op_stack.isEmpty() && op_stack.peek() != '(')
                        {
                            // unary operator evaluation
                            if (op_stack.getSize()-L_parenthesis_count_in_op_stack == value_stack.getSize()) {
                                char op = op_stack.pop();

                                //if there is a unary operator in the expresion then it must be
                                //closed fully by pair for parenthesis
                                //e.g. (-4) is allowed but -4 is not allowed
                                //that's why after satisfiying the above if we have to check one more
                                //condition to ensure that it is going to be an unary operation

                                //the condition is : when we get reach a right parenthesis , and above if condition is
                                //true then the operation will be unary if there is a left parenthesis exists
                                //before the double value just added into the stack

                                //e.g (-456) or (456) ,here reading character by character  when we reach ')' ,then we should check
                                //before 456 or before -456 we have left parenthesis or not...here 456 is the last added double
                                //value to stack..that's why we stored 456 in "anotherValueString" to get the length...so if it is
                                //a valid unary opeartor, and the index of ')' in string expression is i..then we will find
                                //a '(' in "i-anotherValueString.length()-1"th index (for '+' unary) or in
                                // "i-anotherValueString.length()-2"th index (for '-' unary)

                                if(str.charAt(i-anotherValueString.length()-1) != '(' && str.charAt(i-anotherValueString.length()-2) != '('){
                                    throw new ArithmeticException();
                                }
                                double value = value_stack.pop();

                                if (op == '-') {
                                    value_stack.push(value * (-1));
                                } else if (op == '+') {
                                    value_stack.push(value);
                                } else
                                    System.out.println("Invalid operation for unary");

                              //  System.out.println(value_stack);
                               // System.out.println(op_stack);


                            }
                            //for binary operator

                            else {

                                char op = op_stack.pop();
                                double value2 = value_stack.pop();
                                double value1 = value_stack.pop();

                                if (op == '+') {
                                    value_stack.push(value1 + value2);
                                } else if (op == '-') {
                                    value_stack.push(value1 - value2);
                                } else if (op == '*') {
                                    value_stack.push(value1 * value2);
                                } else {
                                    if(value2 == 0) // something divided by 0 is undefined
                                    {
                                        throw new ArithmeticException();
                                    }
                                    value_stack.push(value1 / value2);
                                }
                            }
                        }

                        //popping left parenthesis
                        if(!op_stack.isEmpty())
                        {
                            op_stack.pop();
                            L_parenthesis_count_in_op_stack--;
                        }
                         //System.out.print(str.charAt(i));

                    }

                    //if value
                    else {

                        //converting an character to its equivalent double value;
                        valueString = valueString + String.valueOf(str.charAt(i));
                        anotherValueString=valueString;

                    }

                }




                //this is done to convert seperate the double value from inputed string expression
                if (!valueString.equalsIgnoreCase("")) {

                    value_stack.push(Double.parseDouble(valueString));
                  //  System.out.print(Double.parseDouble(valueString));
                    valueString = "";
                }

             //  System.out.println(value_stack);
               // System.out.println(op_stack);

                //sometimes the value and operator stack don't become fully empty
                //after terminating the upper while loop
                //that's why some work still to be done
                //that's why the below while loop will do the remaining algebric work

                while (!op_stack.isEmpty()) {
                    char operator = op_stack.pop();
                    if(operator =='(')
                    {
                        continue;
                    }
                    double value2 = value_stack.pop();
                    double value1 = value_stack.pop();

                    if (operator == '+') {
                        value_stack.push(value1 + value2);
                    } else if (operator == '-') {
                        value_stack.push(value1 - value2);
                    } else if (operator == '*') {
                        value_stack.push(value1 * value2);
                    } else {
                        if(value2 == 0) // something divided by 0 is undefined
                        {
                            throw new ArithmeticException();
                        }
                        value_stack.push(value1 / value2);
                    }
                }
            }

            //when a double value successfully return means the expression is valid
            System.out.println("Valid Expression!");
            return value_stack.pop();

        }catch (Exception e)
        {
            System.out.println("Not Valid");
           // e.printStackTrace();
            exit(0);
        }

        return 0.0;


    }



    public static void main(String[] args) {


        Main main=new Main();

        Scanner input=new Scanner(System.in);
        String str=input.nextLine();

        double result=main.Evaluate(str);
        System.out.println("Result: "+result);




    }
}

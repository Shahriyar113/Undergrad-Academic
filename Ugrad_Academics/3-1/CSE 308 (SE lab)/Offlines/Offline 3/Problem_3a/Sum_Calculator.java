package Problem_3a;

import java.io.File;
import java.io.PrintWriter;
import java.util.NoSuchElementException;
import java.util.Scanner;

//Adaptee
public class Sum_Calculator {

    String file_name;


    int calculate_sum(String filename)
    {
        file_name = filename ;
        String Numbers_String="";
        int sum = 0;



        //reading from file
        try {
            File file = new File(file_name);
            Scanner input = new Scanner(file);

            String line = "";

            //reading from files
            while (input.hasNextLine()) {
                line = input.nextLine();

                Numbers_String = Numbers_String + line;




            }


        }catch (Exception e)
        {
            if(e instanceof NoSuchElementException)
            {
                ;
            }
        }

        String[] numbers = Numbers_String.split(" ");

        //calculating sum

        for (String number_str : numbers)
        {
            int number = Integer.parseInt(number_str);
            sum = sum + number;
        }

        // String[] numbers =
        return sum;
    }



}

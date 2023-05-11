package Problem_3a;

import java.io.File;
import java.io.PrintWriter;
import java.util.NoSuchElementException;
import java.util.Scanner;

//The adapter only can use adaptee class
public class Sum_Calculator_Adapter implements Calculate_Sum {

    Sum_Calculator sum_calculator;

    public int calculteSum(String file_name){

      sum_calculator = new Sum_Calculator();


      convert_tilde_to_space(file_name);

      return sum_calculator.calculate_sum("SS_Numbers.txt");


    }


    public void convert_tilde_to_space(String filename)
    {

        String Numbers_String="";


        //reading from file
        try {
            File file = new File(filename);
            Scanner input = new Scanner(file);

            String line = "";

            //reading from files
            while (input.hasNextLine()) {
                line = input.nextLine();

                Numbers_String = Numbers_String + line;


            }

            String[] numbers = Numbers_String.split("~");



            File file2 = new File("SS_Numbers.txt");
            PrintWriter pw = new PrintWriter(file2);

            for(int i=0;i<numbers.length;i++)
            {
                if(i != numbers.length -1)
                    pw.print(numbers[i]+" ");
                else
                    pw.print(numbers[i]);
            }

            pw.flush();
            pw.close();






        }catch (Exception e)
        {
            if(e instanceof NoSuchElementException)
            {
                ;
            }
        }






    }




}

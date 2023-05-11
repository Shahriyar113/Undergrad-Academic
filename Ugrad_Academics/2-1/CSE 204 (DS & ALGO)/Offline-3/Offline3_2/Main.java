package Offline3_2;

import java.util.ArrayList;
import java.util.Queue;
import java.util.Scanner;

public class Main {

    int[] Frequency_Array;
    //CustomQueue<Character> String_New_queue;
    CustomQueue<Character> Stream_queue;
    int String_New_Length;
    int String_New_index;
    //this is the output String character array
    char[] String_New_array;

    char[] getString_New()
    {
        return String_New_array;
    }


    Main(int String_New_Length)
    {
        this.String_New_Length=String_New_Length;
        String_New_array=new char[this.String_New_Length];
        Frequency_Array=new int[26];
        //String_New_queue=new CustomQueue<>();
        Stream_queue=new CustomQueue<>();
    }


//finding 1st non repeating character during each insertion
//the frequency of every character is stored in Frequency_Array according to key value pair concept

    //best case complexity O(1) ,when all the element of char array are different
    //worst case complexity(O(n)),when all the element of char array are same
  public void insert(char ch)
  {
      Stream_queue.enqueue(ch);

      //storing the frequency of every character
      Frequency_Array[ch-'a']++;

      //after every insertion,checking the front of the Stream_queue..if the frequency of front char is 1, then it
      //is the 1st non repeating character
      //if the frequency is greater than 1 ,then dequeue that element from queue and try for next one
   try {


    while (!Stream_queue.isEmpty()) {

        if (Frequency_Array[Stream_queue.peek() - 'a'] == 1) {
            //inserting the 1st non repeating character for each insertion in String_New
            String_New_array[String_New_index++] = Stream_queue.peek();
            return;
        } else {

            Stream_queue.dequeue();

        }
    }

    //Successfully terminating this loop normally means every individual character is repeated..that means
    //there is no 1st_non_repeating char...that's why so inserting '#'
    String_New_array[String_New_index++] = '#';

  }
   catch (Exception e)
  {
      System.out.println(e);
  }

  }


    public static void main(String[] args) {
        Scanner input=new Scanner(System.in);


            String String_old = input.nextLine();

            Main main = new Main(String_old.length());

            //inserting each character one by one

        //Compexity of this loop
        //for best case (considering 6 character string where every char are unique)
        //time=1+1+1+1+1
        //so for best case comlexity O(n)

        //for worst case (considering 6 character string where every char are same)
        //time=1+2+3+4+5
        //so for best case comlexity O(n*n)



            for (int i = 0; i < String_old.length(); i++) {
                main.insert(String_old.charAt(i));
            }

            char[] str = main.getString_New();

            //converting the character array to String
            String String_new = new String(str);
            System.out.println(String_new);


    }
}

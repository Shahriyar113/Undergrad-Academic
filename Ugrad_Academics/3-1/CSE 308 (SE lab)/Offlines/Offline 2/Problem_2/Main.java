package Problem_2;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {


        Scanner input = new Scanner(System.in);

        String file_name = input.next();

        Editor e = new Editor();

        System.out.println("Parser Name: "+e.getParser(file_name));
        System.out.println("Font Name: "+e.getFont(file_name));
        System.out.println("Environment: "+e.getEnvironment(file_name));



    }
}

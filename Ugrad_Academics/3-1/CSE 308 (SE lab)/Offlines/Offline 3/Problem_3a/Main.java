package Problem_3a;

//Client
//Client can only use targer interface and adapter  class
public class Main {
    public static void main(String[] args) {

        Calculate_Sum calculate_sum = new Sum_Calculator_Adapter();

        System.out.println("Sum: "+calculate_sum.calculteSum("Numbers.txt"));

    }
}

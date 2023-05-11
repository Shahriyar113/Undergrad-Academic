package Offline_10;

import java.io.BufferedReader;
import java.io.FileReader;

//O(n*s*s) Complexity

public class DP {
    public static long mod= 1000000007;

    public static long Total_No_Of_Ways(int n,int s,int[] faces)
    {
        long[][] DP_table = new long [n+1][s+1]; //rows are for number of dices and columns are for target sum

        DP_table[0][0]=0;

        //populating 1 no row as it is almost same type in all the case
        for (int j=1; j<=faces[0] && j<=s ; j++ )
        {
            DP_table[1][j] = 1;
        }

        for(int i=2;i<=n;i++)
        {
            for(int j=1;j<=s;j++)
            {
                for(int k=1;k<=faces[i-1] && k<j ;k++ )
                {
                    DP_table[i][j] = (DP_table[i][j] + DP_table[i-1][j-k]) % mod  ;
                }
            }
        }


//        for(int i=0;i<=n;i++)
//        {
//            for(int j=0;j<=s;j++)
//            {
//                System.out.print(DP_table[i][j]+" ");
//            }
//            System.out.println();
//        }

        return DP_table[n][s];


    }

    public static void main(String[] args) {

        int n=0; //number of dices
        int s=0; //target sum
        int[] faces=null ; //no of faces of ith dice

        try
        {
            BufferedReader br = new BufferedReader(new FileReader("Input.txt"));
            String line="";

            line=br.readLine();
            String[] N_and_S = line.split(" ");
            n=Integer.parseInt(N_and_S[0]);
            s=Integer.parseInt(N_and_S[1]);

            faces = new int[n];

            line=br.readLine();

            String[] Str_faces=line.split(" ");

            for (int i=0;i<n;i++)
            {
                faces[i] = Integer.parseInt(Str_faces[i]);
            }

            br.close();

        }catch (Exception e)
        {
            e.printStackTrace();
        }




        System.out.println("Total number of ways: "+Total_No_Of_Ways(n,s,faces));





    }
}

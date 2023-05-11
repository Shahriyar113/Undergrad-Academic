package Offline2;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args) {

//        PlayerLinkedList players=new PlayerLinkedList();
//        players.addLast("1",4);
//        players.addLast("2",5);
//        players.addLast("3",2);
//
//        players.showAllPlayers();
//
//        players.insertBefore("1","4",1);
//        players.showAllPlayers();
//        players.remove("4");
//        players.showAllPlayers();
//        players.reverse();
//        players.showAllPlayers();


        int N; //total player number
        ArrayList<Integer> reflexTimes=new ArrayList<>(); //reflextimes of all the players
        int time;
        String command; //  M/F/P/I/R
        int reflexTime; //reflextime of new player

        Scanner input=new Scanner(System.in);

        //this while loop is for getting the correct input for N
        while (true)
        {
            try{
                N=input.nextInt();
                break;
            }
            catch (InputMismatchException e)
            {
                System.out.println("Invalid Input! Total number of players should be integer!Try again");
                input.nextLine(); //to eliminate the enter buffer

                continue;
            }
        }

        //this while loop is for getting the correct input for reflex times
        while(true)
        {

            try{

                int x=input.nextInt();
                reflexTimes.add(x);
                if(reflexTimes.size()==N)
                    break;

            }
            catch (InputMismatchException e)
            {
                System.out.println("Invalid Input! Reflex time should be integer!Try again");
                input.nextLine(); //to eliminate the enter buffer
                continue;
            }

        }

        //Creating the Circular Linked list of players with their reflex time

        PlayerLinkedList players=new PlayerLinkedList();
        int playerCounts=0; //after joining a new player playerCounts will be updated

        for(Integer rtime:reflexTimes)
        {
            playerCounts++;
            players.addLast(Integer.toString(playerCounts),rtime);

        }

        input.nextLine(); // removing the enter buffer before entering the infinite input loop


       // players.show_All_Players_Name_And_Reflextime();
        players.GameStarts();



        //infinite loop for taking time and command until command "F" or a winner is found
        while (true)
        {

            //System.out.print("Give time and command: ");
            String events=input.nextLine();
            String[] allevents=events.split(" ");

            if(allevents.length==2)
            {
                try {

                    time=Integer.parseInt(allevents[0]);

                }catch (Exception e)
                {
                    System.out.println("Invalid input!Time should be integer! Try again");
                    continue;
                }

                try {

                    if(allevents[1].equalsIgnoreCase("M") || allevents[1].equalsIgnoreCase("R")
                            || allevents[1].equalsIgnoreCase("P") || allevents[1].equalsIgnoreCase("F"))
                    {
                        command=allevents[1];
                    }
                    else
                    {
                        throw new InvalidCommandException();
                    }



                }catch (InvalidCommandException e)
                {
                    System.out.println(e);
                    continue;
                }

                //processing

                // printing the player holding pillow
                if(command.equalsIgnoreCase("P"))
                {
                    System.out.println("Player " +players.get_the_player_holding_pillow(time) + " is holding the pillow at t="+time);
                    continue; //after every time and command input,loop will start again
                }
                if(command.equalsIgnoreCase("M"))
                {
                    players.Eliminating_A_Player(time);
                    continue; //after every time and command input,loop will start again
                }

                if(command.equalsIgnoreCase("R"))
                {
                    players.get_the_player_holding_pillow(time); //it is called to update the info of the current pillow holder
                    players.reverse();
                    continue; //after every time and command input,loop will start again
                }

                if(command.equalsIgnoreCase("F"))
                {
                    players.get_the_player_holding_pillow(time); //it is called to update the info of the current pillow holder
                    players.Show_Players_Sequentially(time);
                    break;

                }


            }
            else if(allevents.length==3)
            {
                try {

                    time=Integer.parseInt(allevents[0]);

                }catch (Exception e)
                {
                    System.out.println("Invalid input!Time should be integer! Try again");
                    continue;
                }

                try {

                    if(allevents[1].equalsIgnoreCase("I"))
                    {
                        command=allevents[1];
                    }
                    else
                    {
                        throw new InvalidCommandException();
                    }



                }catch (InvalidCommandException e)
                {
                    System.out.println(e);
                    continue;
                }

                try {
                    reflexTime=Integer.parseInt(allevents[2]);

                }catch (InputMismatchException e)
                {
                    System.out.println("Invalid input! ReflexTime should be integer! Try again");
                    continue;
                }

                //processing
                //ai line porjonto asha mane command "I" deya hoyeche

                playerCounts++; //new player is joining
                String pillowHolder = players.get_the_player_holding_pillow(time);
                players.insertBefore(pillowHolder,Integer.toString(playerCounts),reflexTime);









            }

            else
            {
                System.out.println("Invalid input for events!Try again");
                continue;
            }



        }






    }
}


package Offline2;

import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

import static java.lang.System.exit;

public class PlayerLinkedList {

    private Player head;
    private int playerCount; //total number of player in the list
    private Player the_player_holding_Pillow;  //storing the player node who is currently holding the pillow
    private int updated_time; //the time when a player is eliminated or a player is added.this will store
                              //that time

    private int timetracking=0; //this variable is used to track the time to find the player holding the pillow


    PlayerLinkedList()
    {
        head=null;
        playerCount=0;
        updated_time=0;

    }

    PlayerLinkedList(Player head)
    {
        this.head=head;
    }

    void setHead(Player head)
    {
        this.head=head;
    }


    Player getHead()
    {
        return head;
    }

    int getPlayerCount()
    {
        return playerCount;
    }


    //inner node class
    class Player
    {
         String name;
         int reflex_time;
         Player next;
         Player previous;
         Player(String name,int reflex_time)
         {
             this.name=name;
             this.reflex_time=reflex_time;
         }


    }



    //for circular linked list always, lastnode.next=head and head.previous=lastnode

    //here addLast means adding an playernode after last added node
    void addLast(String name,int reflexTime)
    {
        Player p=new Player(name,reflexTime);
        playerCount++;

        if(head==null)
        {
            head=p;

            //circular list of one element
            head.next=head;
            head.previous=head;

            return;
        }
        Player currentPlayer=head;
        while(currentPlayer.next!=head)
        {
            currentPlayer=currentPlayer.next;

        }
        currentPlayer.next=p;
        currentPlayer.next.previous=currentPlayer;
        currentPlayer.next.next=head;
        head.previous=p;


    }

    //String "before" means the player before whom i want to insert

    void insertBefore(String before,String name,int reflexTime)
    {
        Player p=new Player(name,reflexTime);
        playerCount++;

        Player currentPlayer=head;
        while(true)
        {
            if(currentPlayer.name.equalsIgnoreCase(before))
            {
                break;
            }
            currentPlayer=currentPlayer.next;
        }
        p.next=currentPlayer;
        p.previous=currentPlayer.previous;
        currentPlayer.previous.next=p;
        currentPlayer.previous=p;

        System.out.println("Previous neighbour: "+currentPlayer.previous.name);
        System.out.println("Next Neighbour: "+currentPlayer.next.name);


    }

    void remove(String removeName)
    {
//
//        if(head.name.equalsIgnoreCase(removeName))
//        {
//            head.previous.next=head.next;
//            head.next.previous=head.previous;
//            head=head.next;
//            return;
//        }

        //for other nodes except head
        playerCount--;
        Player currentPlayer=head;
        while(true)
        {
            if(currentPlayer.name.equalsIgnoreCase(removeName))
            {
                break;
            }
            currentPlayer=currentPlayer.next;
        }

        currentPlayer.previous.next=currentPlayer.next;
        currentPlayer.next.previous=currentPlayer.previous;

        //if the head node is removed then the head should be the next node
        if(currentPlayer==head)
        {
            head=head.next;
        }



    }


  //if we want to reverse the circular list than we just have to swap the "next" and "previous"
  //of each node

    void reverse()
    {

        //if the list is empty or has only one element than no need to reverse
        if(head==null || head.next==head)
        {
            return;
        }

        Player currentPlayer=head;
        Player nextPlayer=head.next;
        Player temp;

        while(true)
        {

            //Swapping next and previous of each node
            temp=currentPlayer.next;
            currentPlayer.next=currentPlayer.previous;
            currentPlayer.previous=temp;
            currentPlayer=nextPlayer;

            if(currentPlayer==head)
            {
                break;
            }
            nextPlayer=currentPlayer.next;

        }

    }

    void show_All_Players_Name_And_Reflextime()
    {
        //if the list is empty
        if(head==null)
        {
            System.out.println("There is no player in the list");
            return;
        }
        Player currentPlayer=head;

       //if the list is nonempty
        while(true)
        {
            System.out.println("Player "+currentPlayer.name + " ==> "+"ReflexTime: "+currentPlayer.reflex_time);
            currentPlayer=currentPlayer.next;
            if(currentPlayer==head)
            {
                break;
            }
        }

        if(the_player_holding_Pillow!=null)
        System.out.println("Player "+the_player_holding_Pillow.name+" is holding the pillow now");
        //System.out.println();
    }

    String get_the_player_holding_pillow(int time)
    {
        //the "updatetime" store the time when a player just eleminated
        //the time will always starts when new music is on after eliminating one
        time=time-updated_time;
        Player currentPlayer=the_player_holding_Pillow;

        while(timetracking+currentPlayer.reflex_time<time)
        {
            timetracking=timetracking+currentPlayer.reflex_time;
            currentPlayer=currentPlayer.next;

//            if(timetracking<time)
//            {
//
//                //timetracking=timetracking+currentPlayer.reflex_time;
//            }

        }

        the_player_holding_Pillow=currentPlayer;
        //updated_time=time;

        return the_player_holding_Pillow.name;

    }

    void Eliminating_A_Player(int time)
    {

        //at first we have to find the name of the player who is holding pillow
        String eliminated_player=get_the_player_holding_pillow(time);
        //now remove the player
        remove(eliminated_player);
        System.out.println("Player " +eliminated_player + " has been eliminated at t="+time);

        //after eliminating the pillow will be passed to the next person
        the_player_holding_Pillow=the_player_holding_Pillow.next;

        updated_time=time;
        timetracking=0;

        //if onlu one player remains then he/she will be winner
        if(playerCount==1)
        {
            System.out.println("Game Over! Player "+the_player_holding_Pillow.name+" wins");
            exit(0);
        }

    }

    //at the start of the game 1st player will hold the pillow
    void GameStarts()
    {
        the_player_holding_Pillow=head;
//        System.out.println();
//        System.out.println("Game Starts!");
//        System.out.println("Player "+the_player_holding_Pillow.name+" is holding the pillow now");
//        System.out.println();
    }

    void Show_Players_Sequentially(int time)
    {
        boolean comma_flag=false; //this commaflag is for removing an extra comma

        System.out.println("Game over : Player "+the_player_holding_Pillow.name+" is holding the pillow at t="+time);
        System.out.print("Pillow Passing Sequence = Player ");
        Player currentPlayer = the_player_holding_Pillow;

        while (true)
        {
            if(comma_flag==false)
            {
                System.out.print(currentPlayer.name);
                comma_flag=true;
            }
            else
            {
                System.out.print(", "+currentPlayer.name);
            }
            currentPlayer=currentPlayer.next;
            if(currentPlayer==the_player_holding_Pillow)
            {
                break;
            }
        }
        System.out.println();



    }


}



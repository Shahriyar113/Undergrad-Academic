package N_Puzzle;


import java.io.File;
import java.util.*;

public class Main {


    public static int[][] move_blank_tile_to_right(int[][] old_grid,int k, int blank_tile_row_index,int blank_tile_column_index)
    {
        int[][] updated_grid = new int[k+1][k+1];
        //copying element of old grid to updated grid

        for(int i=1;i<k+1;i++)
        {
            for (int j = 1; j < k + 1; j++)
            {
                updated_grid[i][j]=old_grid[i][j];

            }
        }

        //now moving the tile to right
        int temp=updated_grid[blank_tile_row_index][blank_tile_column_index];
        updated_grid[blank_tile_row_index][blank_tile_column_index] =
                updated_grid[blank_tile_row_index][blank_tile_column_index + 1];
        updated_grid[blank_tile_row_index][blank_tile_column_index + 1]=temp;

        return updated_grid;


    }

    public static int[][] move_blank_tile_to_left(int[][] old_grid,int k,
                                                  int blank_tile_row_index,int blank_tile_column_index)
    {
        int[][] updated_grid = new int[k+1][k+1];


        //copying element of old grid to updated grid

        for(int i=1;i<k+1;i++)
        {
            for (int j = 1; j < k + 1; j++)
            {
                updated_grid[i][j]=old_grid[i][j];

            }
        }

        //now moving the tile to right
        int temp=updated_grid[blank_tile_row_index][blank_tile_column_index];
        updated_grid[blank_tile_row_index][blank_tile_column_index] =
                updated_grid[blank_tile_row_index][blank_tile_column_index - 1];
        updated_grid[blank_tile_row_index][blank_tile_column_index - 1]=temp;

        return updated_grid;


    }


    public static int[][] move_blank_tile_to_up(int[][] old_grid,int k,
                                                int blank_tile_row_index,int blank_tile_column_index)
    {

        int[][] updated_grid = new int[k+1][k+1];

        //copying element of old grid to updated grid

        for(int i=1;i<k+1;i++)
        {
            for (int j = 1; j < k + 1; j++)
            {
                updated_grid[i][j]=old_grid[i][j];

            }
        }

        //now moving the tile to right
        int temp=updated_grid[blank_tile_row_index][blank_tile_column_index];
        updated_grid[blank_tile_row_index][blank_tile_column_index] =
                updated_grid[blank_tile_row_index - 1][blank_tile_column_index];
        updated_grid[blank_tile_row_index - 1][blank_tile_column_index]=temp;

        return updated_grid;


    }

    public static int[][] move_blank_tile_to_down (int[][] old_grid,int k,int blank_tile_row_index,int blank_tile_column_index)
    {

        int[][] updated_grid = new int[k+1][k+1];


        //copying element of old grid to updated grid

        for(int i=1;i<k+1;i++)
        {
            for (int j = 1; j < k + 1; j++)
            {
                updated_grid[i][j]=old_grid[i][j];

            }
        }

        //now moving the tile to right
        int temp=updated_grid[blank_tile_row_index][blank_tile_column_index];
        updated_grid[blank_tile_row_index][blank_tile_column_index] =
                updated_grid[blank_tile_row_index + 1][blank_tile_column_index];
        updated_grid[blank_tile_row_index + 1][blank_tile_column_index]=temp;

        return updated_grid;


    }

    //for each state there is a unique key value which will be used to identify that state uniquely
    public static int key_value(int[][] grid,int k)
    {
        int sum = 1 ;
        for(int i=1;i<k+1;i++)
        {
            for (int j = 1; j < k + 1; j++)
            {
                if(grid[i][j] == 0)
                {
                   sum = sum + i*k+j;
                }
                else
                sum = sum + grid[i][j] * grid[i][j] * (i*i*(k+1) * j*j);
            }
        }

        return sum;
    }




    public static int calculate_Manhattan_distance(int[][] grid,int k)
    {
        int Manhattan_distance = 0;

        for(int i=1;i<k+1;i++)
        {
            int correct_column_index=0;
            int correct_row_index=0;
            for (int j = 1; j < k + 1; j++)
            {

                if(grid[i][j] == 0) //ignoring blank tile
                {
                    continue;
                }

                //calculating correct_column_index and correct_row_index
                if(grid[i][j] % k == 0)
                {
                    correct_column_index = 3;
                    correct_row_index = grid[i][j] / k;
                }
                else {

                    correct_column_index = grid[i][j] % k;
                    correct_row_index = (grid[i][j] / k) + 1;

                }



                int Manhattan_distance_of_current_element = Math.abs(correct_column_index-j) + Math.abs(correct_row_index - i);
                Manhattan_distance = Manhattan_distance + Manhattan_distance_of_current_element;


            }
        }

        return Manhattan_distance;
    }

    public static int calculate_Hamming_distance(int[][] grid,int k)
    {
        //"array_of_elements" is the row major order array of the grid elements
        int[] array_of_elements = new int[k*k+1]; //start indexing from 1
        int index = 1;
        //populating the array
        for(int i=1;i<k+1;i++)
        {
            for(int j=1;j<k+1;j++)
            {
                array_of_elements[index] = grid[i][j];
                index++;
            }

        }

        //finding hamming distance
        int hamming_distance=0;
        for(int i=1;i<array_of_elements.length;i++)
        {
            if(array_of_elements[i]==0) //ignoring blank tile
            {
                continue;
            }
            else
            {
                if(array_of_elements[i] != i)
                {
                    hamming_distance++;
                }
            }
        }

        return hamming_distance;

    }


    public static void print_grid(int[][] grid,int k)
    {

        for(int i=1;i<k+1;i++)
        {
            for(int j=1;j<k+1;j++)
            {
                if(grid[i][j]==0)
                    System.out.print("*"+" ");
                else
                    System.out.print(grid[i][j]+" ");
            }
            System.out.println();
        }
    }

    public static void Solve_by_Hamming_distance(int[][] initial_grid,int k)
    {
        int expanded_node_count = 0;
        int explored_node_count = 0;

        PriorityQueue<Node> priorityQueue_for_hamming = new PriorityQueue<Node>();

        //inserting initial_node
        priorityQueue_for_hamming.add(new Node (initial_grid,k,0,calculate_Hamming_distance(initial_grid,k),null,""));


        Node final_state = null;

        while (true) {


            Node current_node = priorityQueue_for_hamming.poll();

           // System.out.println("expanding");
          //  System.out.println(state_hashset_for_hamming);
            //System.out.println(current_node.getH_value());
            //print_grid(current_node.getGrid(),k);
            //System.out.println(key_value(current_node.getGrid(),k));
            //System.out.println();


            if(current_node.getH_value() == 0)
            {
                final_state = current_node;
                break;
            }

            expanded_node_count++;


            int[][] current_grid = current_node.getGrid();

            //finding blank tile position

            int blank_tile_row_index = 0;
            int blank_tile_column_index = 0;

            for (int i = 1; i < k + 1; i++) {
                for (int j = 1; j < k + 1; j++) {
                    if (current_grid[i][j] == 0) {
                        blank_tile_row_index = i;
                        blank_tile_column_index = j;
                        break;
                    }
                }
            }

            //if the tile is movable to left
            if (blank_tile_column_index - 1 >= 1) {

                int[][] new_grid = move_blank_tile_to_left(current_grid, k, blank_tile_row_index, blank_tile_column_index);
                Node new_node = new Node(new_grid, current_node.get_K(),
                        current_node.getG_value() + 1,
                        calculate_Hamming_distance(new_grid, current_node.get_K()),current_node,"moving left");

                boolean Valid_move = true;
                Node curr_node = new_node.getParent();
                while (curr_node != null)
                {
                   if(new_node.is_Identical(curr_node.getGrid()))
                   {
                       Valid_move = false;
                       break;
                   }
                   curr_node = curr_node.getParent();
                }


                //checking if the same state is repeating or not
                //if same state repeats than ignore that state
                if(Valid_move)
                {

                    priorityQueue_for_hamming.add(new_node);

                    explored_node_count++;

                }



            }

            //if the tile is movable to right
            if (blank_tile_column_index + 1 <= k) {
                int[][] new_grid = move_blank_tile_to_right(current_grid, k, blank_tile_row_index, blank_tile_column_index);
                Node new_node = new Node(new_grid, current_node.get_K(),
                        current_node.getG_value() + 1,
                        calculate_Hamming_distance(new_grid, current_node.get_K()),current_node,"moving right");

                boolean Valid_move = true;
                Node curr_node = new_node.getParent();
                while (curr_node != null)
                {
                    if(new_node.is_Identical(curr_node.getGrid()))
                    {
                        Valid_move = false;
                        break;
                    }
                    curr_node = curr_node.getParent();
                }


                //checking if the same state is repeating or not
                //if same state repeats than ignore that state
                if(Valid_move)
                {

                    priorityQueue_for_hamming.add(new_node);

                    explored_node_count++;

                }



            }

            //if the tile is movable to up
            if (blank_tile_row_index - 1 >= 1) {
                int[][] new_grid = move_blank_tile_to_up(current_grid, k, blank_tile_row_index, blank_tile_column_index);
                Node new_node = new Node(new_grid, current_node.get_K(),
                        current_node.getG_value() + 1,
                        calculate_Hamming_distance(new_grid, current_node.get_K()),current_node,"moving up");

                boolean Valid_move = true;
                Node curr_node = new_node.getParent();
                while (curr_node != null)
                {
                    if(new_node.is_Identical(curr_node.getGrid()))
                    {
                        Valid_move = false;
                        break;
                    }
                    curr_node = curr_node.getParent();
                }


                //checking if the same state is repeating or not
                //if same state repeats than ignore that state
                if(Valid_move)
                {

                    priorityQueue_for_hamming.add(new_node);

                    explored_node_count++;

                }



            }

            //if the tile is movable to down
            if (blank_tile_row_index + 1 <= k) {
                int[][] new_grid = move_blank_tile_to_down(current_grid, k, blank_tile_row_index, blank_tile_column_index);
                Node new_node = new Node(new_grid, current_node.get_K(),
                        current_node.getG_value() + 1,
                        calculate_Hamming_distance(new_grid, current_node.get_K()),current_node,"moving down");

                boolean Valid_move = true;
                Node curr_node = new_node.getParent();
                while (curr_node != null)
                {
                    if(new_node.is_Identical(curr_node.getGrid()))
                    {
                        Valid_move = false;
                        break;
                    }
                    curr_node = curr_node.getParent();
                }


                //checking if the same state is repeating or not
                //if same state repeats than ignore that state
                if(Valid_move)
                {

                    priorityQueue_for_hamming.add(new_node);
                    explored_node_count++;

                }


            }


        }

        //showing output
        //backtracking from final to initial state
        LinkedList<Node> state_list = new LinkedList<>();
        Node curr_node = final_state;
        while(curr_node != null)
        {
            state_list.addFirst(curr_node);
            curr_node=curr_node.getParent();
        }

        System.out.println("Solving Steps");
        System.out.println("---------------");
        System.out.println();


        for (Node node:state_list)
        {
            System.out.println(node.getMoving_info());
            print_grid(node.getGrid(),node.get_K());
            System.out.println();
        }



        System.out.println("Path cost: "+ final_state.getG_value());
        System.out.println("Expanded Node Count: " +expanded_node_count);
        System.out.println("Explored Node Count: " +explored_node_count);


    }


    public static void Solve_by_Manhattan_distance(int[][] initial_grid,int k)
    {
        int expanded_node_count = 0;
        int explored_node_count = 0;

        PriorityQueue<Node> priorityQueue_for_hamming = new PriorityQueue<Node>();

        //inserting initial_node
        priorityQueue_for_hamming.add(new Node (initial_grid,k,0,calculate_Manhattan_distance(initial_grid,k),null,""));





        Node final_state = null;

        while (true) {


            Node current_node = priorityQueue_for_hamming.poll();

            // System.out.println("expanding");
            //  System.out.println(state_hashset_for_hamming);
            //System.out.println(current_node.getH_value());
            //print_grid(current_node.getGrid(),k);
            //System.out.println(key_value(current_node.getGrid(),k));
            //System.out.println();


            if(current_node.getH_value() == 0)
            {
                final_state = current_node;
                break;
            }

            expanded_node_count++;


            int[][] current_grid = current_node.getGrid();

            //finding blank tile position

            int blank_tile_row_index = 0;
            int blank_tile_column_index = 0;

            for (int i = 1; i < k + 1; i++) {
                for (int j = 1; j < k + 1; j++) {
                    if (current_grid[i][j] == 0) {
                        blank_tile_row_index = i;
                        blank_tile_column_index = j;
                        break;
                    }
                }
            }

            //if the tile is movable to left
            if (blank_tile_column_index - 1 >= 1) {

                int[][] new_grid = move_blank_tile_to_left(current_grid, k, blank_tile_row_index, blank_tile_column_index);
                Node new_node = new Node(new_grid, current_node.get_K(),
                        current_node.getG_value() + 1,
                        calculate_Manhattan_distance(new_grid, current_node.get_K()),current_node,"moving left");

                boolean Valid_move = true;
                Node curr_node = new_node.getParent();
                while (curr_node != null)
                {
                    if(new_node.is_Identical(curr_node.getGrid()))
                    {
                        Valid_move = false;
                        break;
                    }
                    curr_node = curr_node.getParent();
                }


                //checking if the same state is repeating or not
                //if same state repeats than ignore that state
                if(Valid_move)
                {

                    priorityQueue_for_hamming.add(new_node);

                    explored_node_count++;

                }



            }

            //if the tile is movable to right
            if (blank_tile_column_index + 1 <= k) {
                int[][] new_grid = move_blank_tile_to_right(current_grid, k, blank_tile_row_index, blank_tile_column_index);
                Node new_node = new Node(new_grid, current_node.get_K(),
                        current_node.getG_value() + 1,
                        calculate_Manhattan_distance(new_grid, current_node.get_K()),current_node,"moving right");

                boolean Valid_move = true;
                Node curr_node = new_node.getParent();
                while (curr_node != null)
                {
                    if(new_node.is_Identical(curr_node.getGrid()))
                    {
                        Valid_move = false;
                        break;
                    }
                    curr_node = curr_node.getParent();
                }


                //checking if the same state is repeating or not
                //if same state repeats than ignore that state
                if(Valid_move)
                {

                    priorityQueue_for_hamming.add(new_node);

                    explored_node_count++;

                }



            }

            //if the tile is movable to up
            if (blank_tile_row_index - 1 >= 1) {
                int[][] new_grid = move_blank_tile_to_up(current_grid, k, blank_tile_row_index, blank_tile_column_index);
                Node new_node = new Node(new_grid, current_node.get_K(),
                        current_node.getG_value() + 1,
                        calculate_Manhattan_distance(new_grid, current_node.get_K()),current_node,"moving up");

                boolean Valid_move = true;
                Node curr_node = new_node.getParent();
                while (curr_node != null)
                {
                    if(new_node.is_Identical(curr_node.getGrid()))
                    {
                        Valid_move = false;
                        break;
                    }
                    curr_node = curr_node.getParent();
                }


                //checking if the same state is repeating or not
                //if same state repeats than ignore that state
                if(Valid_move)
                {

                    priorityQueue_for_hamming.add(new_node);

                    explored_node_count++;

                }



            }

            //if the tile is movable to down
            if (blank_tile_row_index + 1 <= k) {
                int[][] new_grid = move_blank_tile_to_down(current_grid, k, blank_tile_row_index, blank_tile_column_index);
                Node new_node = new Node(new_grid, current_node.get_K(),
                        current_node.getG_value() + 1,
                        calculate_Manhattan_distance(new_grid, current_node.get_K()),current_node,"moving down");

                boolean Valid_move = true;
                Node curr_node = new_node.getParent();
                while (curr_node != null)
                {
                    if(new_node.is_Identical(curr_node.getGrid()))
                    {
                        Valid_move = false;
                        break;
                    }
                    curr_node = curr_node.getParent();
                }


                //checking if the same state is repeating or not
                //if same state repeats than ignore that state
                if(Valid_move)
                {

                    priorityQueue_for_hamming.add(new_node);
                    explored_node_count++;

                }


            }


        }

        //showing output
        //backtracking from final to initial state
        LinkedList<Node> state_list = new LinkedList<>();
        Node curr_node = final_state;
        while(curr_node != null)
        {
            state_list.addFirst(curr_node);
            curr_node=curr_node.getParent();
        }

        System.out.println("Solving Steps");
        System.out.println("---------------");
        System.out.println();


        for (Node node:state_list)
        {
            System.out.println(node.getMoving_info());
            print_grid(node.getGrid(),node.get_K());
            System.out.println();
        }



        System.out.println("Path cost: "+ final_state.getG_value());
        System.out.println("Expanded Node Count: " +expanded_node_count);
        System.out.println("Explored Node Count: " +explored_node_count);


    }




    public static void main(String[] args) {

        try {
            File file = new File("input.txt");
            Scanner input = new Scanner(file);

            //taking input "k"
            int k = input.nextInt();
            int n = (int)Math.pow(2.0,k);

            //start array indexing from 1;
            int[][] grid = new int[k+1][k+1];

            //taking input for "start state"
            for(int i=1;i<k+1;i++)
            {
                for(int j=1;j<k+1;j++)
                {
                    try {
                        grid[i][j] = input.nextInt();
                    }catch (Exception e)
                    {
                        if (e instanceof InputMismatchException) {
                            input.next();
                            grid[i][j] = 0; // "0" means blank
                        }else
                        {
                            e.printStackTrace();
                        }


                    }

                }
            }

            //calculating inversion to determine whether the puzzle is solvable or not

            //"array_of_elements" is the row major order array of the grid elements
            int[] array_of_elements = new int[k*k+1]; //start indexing from 1
            int index = 1;
            //populating the array
            for(int i=1;i<k+1;i++)
            {
                for(int j=1;j<k+1;j++)
                {
                    array_of_elements[index] = grid[i][j];
                    index++;
                }

            }

            //calculating inversion
            int inversion_count=0;

            for (int i=1;i<array_of_elements.length;i++)
            {
               if(array_of_elements[i] == 0) //if the tile is blank.
               {
                   continue;
               }
               else
               {
                   for(int j=i+1;j<array_of_elements.length;j++)
                   {
                       if(array_of_elements[j] == 0) //if the tile is blank.
                       {
                           continue;
                       }

                       else if(array_of_elements[i] > array_of_elements[j])
                       {
                          inversion_count++;
                       }
                   }
               }

            }
            //System.out.println(calculate_Hamming_distance(grid,k));
            //System.out.println(calculate_Manhattan_distance(grid,k));

          //  System.out.println(inversion_count);
            //determining the puzzle is solvable or not
            if(k % 2 != 0) //if k is odd
            {
                if (inversion_count % 2 == 0) {
                    System.out.println("The puzzle is solvable");
                } else {
                    System.out.println("The puzzle is not solvable");
                    return;
                }
            }

            else //if k is even
            {
                int row_count_from_bottom_for_blank = 0;
                //finding the row number of blank from bottom
                for(int i=1;i<k+1;i++)
                {
                    for (int j = 1; j < k + 1; j++)
                    {
                        if(grid[i][j] == 0)
                        {
                            row_count_from_bottom_for_blank = k-i+1;
                            break;
                        }
                    }
                }

                if(row_count_from_bottom_for_blank % 2 == 0 && inversion_count % 2 != 0)
                {
                    System.out.println("The puzzle is solvable");
                }
                else if(row_count_from_bottom_for_blank % 2 != 0 && inversion_count % 2 == 0)
                {
                    System.out.println("The puzzle is solvable");
                }
                else
                {
                    System.out.println("The puzzle is not solvable");
                    return;
                }

            }

           //the puzzle is solvable..so execution continues followings



            //solving using Hamming Distance
          //  Solve_by_Hamming_distance(grid,k);

           Solve_by_Manhattan_distance(grid,k);



        }catch (Exception e)
        {
            e.printStackTrace();
        }







    }

}

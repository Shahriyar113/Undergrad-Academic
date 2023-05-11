package Local_Search;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Try {

    public static void main(String[] args) {
        Queue<Integer> list = new LinkedList<>();

        list.add(5);
        list.add(8);
        list.add(7);

        System.out.println(list);
        list.remove();
        list.add(9);
        System.out.println(list);



    }

}

package MST;

import java.util.ArrayList;
import java.util.Comparator;

class Edges_And_Weights {

        int node1;
        int node2;
        double weight;

    Edges_And_Weights(int n1, int n2, double w)
        {
            node1 = n1;
            node2 = n2;
            weight = w;

        }

    @Override
    public String toString() {
        return "("+node1+","+node2+","+weight+")";
    }

}


class Kruskal_Sorting implements Comparator<Edges_And_Weights> {
    ArrayList<Edges_And_Weights> list;

    Kruskal_Sorting()
    {
        list=new ArrayList<Edges_And_Weights>();
    }

    @Override
    public int compare(Edges_And_Weights e1, Edges_And_Weights e2) {
        Double d1=e1.weight;
        Double d2=e2.weight;

        return d1.compareTo(d2);
    }


}
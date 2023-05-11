//storing the augmented path edges
public class AP_Edge {
    int node1_id;
    int node2_id;
    double capacity;

    AP_Edge(int n1, int n2, double c)
    {
        node1_id=n1;
        node2_id=n2;
        capacity=c;
    }

    @Override
    public String toString() {
        return "AP_Edge{" +
                "node1_id=" + node1_id +
                ", node2_id=" + node2_id +
                ", capacity=" + capacity +
                '}';
    }
}

package MST;

    class MST_Edge {
    int node1;
    int node2;
    double weight;

    MST_Edge(int n1,int n2,double w)
    {
        node1=n1;
        node2=n2;
        weight=w;

    }

    @Override
    public String toString() {
        return "("+node1+","+node2+")";
    }
}

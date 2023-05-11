package All_Pairs;

    class BF_Edge {
    Graph.Node u; //parent node
    Graph.Node v; //child node
    double weight;

    BF_Edge(Graph.Node n1, Graph.Node n2, double w)
    {
        u=n1;
        v=n2;
        weight=w;

    }

}

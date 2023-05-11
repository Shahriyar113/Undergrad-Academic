package Local_Search;

//this node will be just used to create kempe chain
public class Node {

    private int node_no;
    private int parent;

    public Node(int node_no) {
        this.node_no = node_no;
    }

    public int getNode_no() {
        return node_no;
    }

    public void setNode_no(int node_no) {
        this.node_no = node_no;
    }

    public int getParent() {
        return parent;
    }

    public void setParent(int parent) {
        this.parent = parent;
    }
}

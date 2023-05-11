package CSP;

public class Value_Contraint implements Comparable<Value_Contraint> {

    private int value;
    private int constraint;

    public Value_Contraint(int value, int constraint) {
        this.value = value;
        this.constraint = constraint;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public int getConstraint() {
        return constraint;
    }

    public void setConstraint(int constraint) {
        this.constraint = constraint;
    }

    @Override
    public int compareTo(Value_Contraint value_contraint) {
        if(this.constraint < value_contraint.getConstraint())
            return 1;
        else
            return -1;
    }

    @Override
    public String toString() {
        return "Value_Contraint{" +
                "value=" + value +
                ", constraint=" + constraint +
                '}';
    }
}

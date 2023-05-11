package Problem_1;

public class Director {

    Builder builder;

    public void Construct(Builder builder)
    {
        this.builder = builder;
        builder.Add_Display_Unit();
        builder.Add_Communication_Channel();
        builder.Add_Controller();
    }
}

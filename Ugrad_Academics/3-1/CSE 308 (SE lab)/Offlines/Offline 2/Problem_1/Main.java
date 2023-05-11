package Problem_1;

public class Main {

    public static void main(String[] args) {

        //input

        String QMS_Name = "Poor";
        String Communication_Module = "Mobile Data";
        int total_display_unit = 3;


        Builder_Factory builder_factory = new Builder_Factory();
        Director director = new Director();

        Builder builder = builder_factory.getBuilder(QMS_Name,Communication_Module,total_display_unit);
        director.Construct(builder);

        Product all_products = builder.getProducts();


        System.out.println("The components are:");
        System.out.println();

        all_products.show();

        //total price calculation

        System.out.println();
        System.out.println("Total cost: "+all_products.getTotalCost()+"$");













    }
}

package Problem_1;

public class Builder_Factory {

    public Builder getBuilder(String QMS_name,String communication_module,int total_display_unit)
    {
        if(QMS_name == null)
        {
            return null;
        }

        else if (QMS_name.equalsIgnoreCase("DELUX"))
        {
            return new Delux(communication_module,total_display_unit);
        }

        else if (QMS_name.equalsIgnoreCase("OPTIMAL"))
        {
            return new Optimal(communication_module,total_display_unit);
        }

        else if (QMS_name.equalsIgnoreCase("POOR"))
        {
            return new Poor(communication_module,total_display_unit);
        }

        return null;
    }


}

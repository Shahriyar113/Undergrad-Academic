package Problem_2;

public class Parser_Factory {

    public static Parser getParserFactory(String file_name)
    {


        if(file_name == null)
        {
            return null;
        }
        else if(file_name.charAt(file_name.length()-1) == 'c')
        {
            return new C_Parser();
        }
        else if(file_name.charAt(file_name.length()-3) == 'c')
        {
            return new Cpp_Parser();
        }
        else if(file_name.charAt(file_name.length()-2) == 'p')
        {
            return new Python_Parser();
        }
       return null;
    }
}

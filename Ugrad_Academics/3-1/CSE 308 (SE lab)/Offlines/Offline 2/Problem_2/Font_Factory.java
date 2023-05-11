package Problem_2;

public class Font_Factory {

    public static Font getFontFactory(String file_name)
    {

        if(file_name == null)
        {
            return null;
        }
        else if(file_name.charAt(file_name.length()-1) == 'c')
        {
            return new C_Font();
        }
        else if(file_name.charAt(file_name.length()-3) == 'c')
        {
            return new Cpp_Font();
        }
        else if(file_name.charAt(file_name.length()-2) == 'p')
        {
            return new Python_Font();
        }
        return null;
    }

}

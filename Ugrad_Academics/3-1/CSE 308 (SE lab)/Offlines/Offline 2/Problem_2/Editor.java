package Problem_2;

public class Editor {

    Parser p;
    Font f;
    Environment e;


    Editor()
    {
        p=null;
        f=null;
        e=null;
    }

    Editor(Parser p,Font f,Environment e)
    {
        this.p = p;
        this.f = f;
        this.e = e;
    }
    public String getParser(String file_name)
    {
        p = Parser_Factory.getParserFactory(file_name);
        return p.getParserName();
    }

    public String getFont(String file_name)
    {
        f = Font_Factory.getFontFactory(file_name);
        return f.getFontName();
    }

    public String getEnvironment(String file_name)
    {
        e = Environment_Factory.getEnviornmentFactory("Windows");
        return e.getEnvironment();
    }







}

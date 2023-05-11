package Problem_2;

interface Parser {
    String getParserName();
}

class C_Parser implements Parser
{
    public String getParserName()
    {
       return "Parser For C Language" ;
    }
}

class Cpp_Parser implements Parser
{
    public String getParserName()
    {
        return "Parser For C++ Language" ;
    }
}

class Python_Parser implements Parser
{
    public String getParserName()
    {
        return "Parser For Python Language" ;
    }
}

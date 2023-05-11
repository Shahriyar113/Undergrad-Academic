package Problem_2;

interface Font {

    String getFontName();
}

class C_Font implements Font
{
    public String getFontName()
    {
        return "Courier New";
    }
}


class Cpp_Font implements Font
{
    public String getFontName()
    {
        return "Monaco";
    }
}


class Python_Font implements Font
{
    public String getFontName()
    {
        return "Consolas";
    }
}
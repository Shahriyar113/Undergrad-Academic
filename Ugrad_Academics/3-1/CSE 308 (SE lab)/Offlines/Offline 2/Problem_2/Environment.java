package Problem_2;

interface Environment {
    String getEnvironment();
}

class Windows implements Environment
{
    public  String getEnvironment()
    {
        return "Windows";
    }
}

class Linux implements Environment
{
    public  String getEnvironment()
    {
        return "Linux";
    }
}
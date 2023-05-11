public class Team {

    private int team_id;
    private  String team_name;

    Team()
    {
        ;
    }

    Team(int id, String name)
    {
        team_id=id;
        team_name=name;
    }

    public void setTeam_id(int id)
    {
        team_id=id;
    }

    public void setTeam_name(String team_name) {
        this.team_name = team_name;
    }

    public int getTeam_id()
    {
        return team_id;
    }
    public String getTeam_name()
    {
        return team_name;
    }

    @Override
    public String toString() {
        return team_name;
    }
}

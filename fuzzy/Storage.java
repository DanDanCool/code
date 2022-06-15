import java.util.*;

// TODO: rename this to Context
public class Storage
{
	public String[] Input;
	public String[] Files;
	public String[] Tokens;
	private Hashtable<String, Integer> m_Scores;

	public Storage()
	{
		m_Scores = new Hashtable<String, Integer>();
	}

	public void Add(String token, int score)
	{
		m_Scores.put(token, score);
	}

	public int Get(String token)
	{
		return m_Scores.get(token);
	}
}

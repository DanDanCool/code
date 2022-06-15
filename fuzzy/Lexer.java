import java.util.*;

public class Lexer
{
	private HashSet<String> m_Set;
	private final String REGEX = "[/.]";

	public Lexer()
	{
		m_Set = new HashSet<String>();
	}

	public String[] Tokenize(String s)
	{
		String[] tokens = s.split(REGEX);
		for (int i = 0; i < tokens.length; i++)
			tokens[i] = tokens[i].toLowerCase();

		return tokens;
	}

	public void Parse(Storage storage)
	{
		for (int i = 0; i < storage.Files.length; i++)
		{
			String[] tokens = Tokenize(storage.Files[i]);
			for (int j = 0; j < tokens.length; j++)
				m_Set.add(tokens[j]);
		}
	}

	public void Get(Storage storage)
	{
		String[] tokens = new String[m_Set.size()];
		int i = 0;
		for (String s : m_Set)
		{
			tokens[i] = s;
			i++;
		}

		storage.Tokens = tokens;
	}
}

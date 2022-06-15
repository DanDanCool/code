import java.util.*;

public class Parser
{
	private Hashtable<String, Double> m_Tokens;
	private double m_FuzzyWeight;
	private final String REGEX = "[/.]";

	public Parser()
	{
		m_Tokens = new Hashtable<String, Double>();
		m_FuzzyWeight = 10.0;
	}

	private double Fuzzy(String s1, String s2)
	{
		if (s1.length() == 0)
			return 0.0;

		if (s2.length() == 0)
			return 0.0;

		int[] edits = new int[s2.length() + 1];
		for (int i = 0; i < s2.length() + 1; i++)
			edits[i] = i;

		for (int i = 0; i < s1.length(); i++)
		{
			int corner = i;
			edits[0] = i + 1;

			for (int j = 0; j < s2.length(); j++)
			{
				int upper = edits[j + 1];
				if (s1.charAt(i) == s2.charAt(j))
				{
					edits[j + 1] = corner;
				}
				else
				{
					int min = corner > upper ? upper : corner;
					min = min > edits[j] ? edits[j] : min;
					edits[j + 1] = min + 1;
				}

				corner = upper;
			}
		}

		int max = s1.length() > s2.length() ? s1.length() : s2.length();
		double distance = edits[s2.length()] / (max + 0.0);
		return 1.0 - distance;
	}

	private double Charset(String s1, String s2)
	{
		int[] set = new int[256];
		for (int i = 0; i < s2.length(); i++)
			set[(int)s2.charAt(i)]++;

		for (int i = 0; i < s1.length(); i++)
			set[(int)s1.charAt(i)]--;

		int total = 0;
		for (int i = 0; i < 256; i++)
			total += set[i];

		return 1 - total / s2.length();
	}

	public double Score(String[] tokens, String s2)
	{
		double best = 0.0;
		for (int i = 0; i < tokens.length; i++)
		{
			double score = Fuzzy(tokens[i], s2);
			best = best > score ? best : score;
		}

		return best * m_FuzzyWeight;
	}

	public void Parse(Storage storage)
	{
		for (int i = 0; i < storage.Tokens.length; i++)
		{
			String str = storage.Tokens[i];
			double score = Score(storage.Input, str);
			m_Tokens.put(str, score);
		}
	}

	// rebuild scores for each path by combining tokens
	public void Get(Storage storage)
	{
		for (int i = 0; i < storage.Files.length; i++)
		{
			String s = storage.Files[i];
			String[] tokens = s.split(REGEX);
			Double score = 0.0;
			for (int j = 0; j < tokens.length; j++)
				score += m_Tokens.get(tokens[j].toLowerCase());

			storage.Add(s, score.intValue());
		}
	}
}

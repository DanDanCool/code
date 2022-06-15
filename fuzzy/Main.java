public class Main
{
	public static void main(String[] args)
	{
		// argv: string input
		// DirReader reads all files from a given directory, results stored in Storage
		// Lexer tokenizes the file names and stores unique results in Storage
		// Parser goes through the lexer results and uses a scoring strategy to evaluate likeness
		// Parser goes through list of file names and rebuilds the score based off the tokenized scores
		// Results printed to stdout sorted by score

		String INPUT = args.length == 0 ? "" : args[0];

		Storage storage = new Storage();

		DirReader reader = new DirReader(".");
		reader.Parse();
		reader.Get(storage);
		//printdir(storage);

		Lexer lexer = new Lexer();
		lexer.Parse(storage);
		lexer.Get(storage);
		//printtok(storage);

		storage.Input = lexer.Tokenize(INPUT);

		Parser parser = new Parser();
		parser.Parse(storage);
		parser.Get(storage);
		printscores(storage);
	}

	public static void printdir(Storage storage)
	{
		for (int i = 0; i < storage.Files.length; i++)
		{
			System.out.println(storage.Files[i]);
		}
	}

	public static void printtok(Storage storage)
	{
		for (int i = 0; i < storage.Tokens.length; i++)
		{
			System.out.println(storage.Tokens[i]);
		}
	}

	public static void printscores(Storage storage)
	{
		for (int i = 0; i < storage.Files.length; i++)
		{
			String s = storage.Files[i];
			System.out.println(s + " " + storage.Get(s));
		}
	}
}

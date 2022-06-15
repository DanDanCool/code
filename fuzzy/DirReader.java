import java.util.*;
import java.io.*;

public class DirReader
{
	public String Root;
	private String[] m_Files;

	public DirReader(String dir)
	{
		Root = dir;

		File root = new File(dir);
		if (!root.isDirectory())
			System.out.println("PATH IS NOT DIRECTORY");
	}

	public void Parse()
	{
		Vector<String> files = new Vector<String>();
		Stack<File> stack = new Stack<File>();
		stack.push(new File(Root));

		// don't want to use recursion to read directories
		while (!stack.empty())
		{
			File root = stack.pop();
			File[] dir = root.listFiles();

			for (int i = 0; i < dir.length; i++)
			{
				File f = dir[i];

				if (f.isDirectory())
					stack.push(f);

				if (f.isFile())
					files.addElement(f.getPath());
			}
		}

		m_Files = new String[files.size()];
		m_Files = files.toArray(m_Files);
	}

	public void Get(Storage storage)
	{
		storage.Files = m_Files;
	}
}

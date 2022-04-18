import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.ArrayList;

public class EmployeeSystem
{
	private HashTable m_Table;

	public EmployeeSystem()
	{
		m_Table = new HashTable();
	}

	public void AddEmployee(EmployeeInfo e)
	{
		m_Table.Set(e);
	}

	public EmployeeInfo GetEmployee(int id)
	{
		return m_Table.Get(id);
	}

	private byte[] SerializeEmployee(EmployeeInfo e)
	{
		String buf = "" + e.GetID() + " " + e.GetFirstName() + " " + e.GetLastName() + " " + e.GetDeductRate();

		if (e.IsFTE())
		{
			FTE fte = (FTE)e;
			buf = buf + " 1 " + fte.GetSalary() + "\n";
		}

		if (e.IsPTE())
		{
			buf = buf + " 0 " + e.HourlyWage() + " " + e.HoursPerWeek() + " " + e.WeeksPerYear() + "\n";
		}

		return buf.getBytes();
	}

	public void Serialize(String fname)
	{
		try
		{
			java.io.FileOutputStream o = new java.io.FileOutputStream(fname);
			String header = "# employee file format: ID(int), First Name (String), Last Name (String), Deduct Rate (double), Full Time (boolean), Wages\n";
			o.write(header.getBytes());

			for (int i = 0; i < m_Table.Size(); i++)
			{
				EmployeeInfo e = m_Table.Get(i);
				if (e == null)
					continue;

				o.write(SerializeEmployee(e));
			}

			o.close();
		}
		catch (java.io.FileNotFoundException ex)
		{
			// wow I hate try catch statements
		}
		catch (java.io.IOException ex)
		{

		}
	}

	public void Deserialize(String fname)
	{
		try
		{
			java.io.FileInputStream in = new java.io.FileInputStream(fname);
			byte[] header = new byte[22];
			in.read(header);

			in.close();
		}
		catch (java.io.FileNotFoundException ex)
		{

		}
		catch (java.io.IOException ex)
		{

		}
	}

	public void Status()
	{
		for (int i = 0; i < m_Table.Size(); i++)
		{
			EmployeeInfo e = m_Table.Get(i);
			if (e != null)
				System.out.println(i + " " + e.GetFirstName());
		}
	}
}

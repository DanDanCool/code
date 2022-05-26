import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.file.Files;
import java.io.File;

public class EmployeeSystem
{
	private HashTable m_Table;

	public EmployeeSystem()
	{
		m_Table = new HashTable();
	}

	public void Clear()
	{
		m_Table.Clear();
	}

	public void AddEmployee(EmployeeInfo e)
	{
		m_Table.Add(e);
	}

	public int Hash(EmployeeInfo e)
	{
		return m_Table.Hash(e.GetID());
	}

	public EmployeeInfo AddEmptyEmployee()
	{
		FTE e = new FTE(m_Table.NextID(), "null", "null");
		m_Table.Add(e);
		return (EmployeeInfo)e;
	}

	public void RemoveEmployee(EmployeeInfo e)
	{
		m_Table.Remove(e);
	}

	public EmployeeInfo GetEmployee(int id)
	{
		return m_Table.Get(id);
	}

	public EmployeeInfo[] GetEmployees()
	{
		return m_Table.GetEmployees();
	}

	public int GetSize()
	{
		return m_Table.Size();
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

	private void DeserializeEmployee(String l)
	{
		String[] data = l.split(" ");
		int id = Integer.parseInt(data[0]);
		double deductrate = Double.parseDouble(data[3]);
		int fulltime = Integer.parseInt(data[4]);

		EmployeeInfo e;
		if (fulltime == 1)
		{
			double salary = Double.parseDouble(data[5]);
			FTE fte = new FTE(id, data[1], data[2]);
			fte.SetSalary(salary);
			e = fte;
		}
		else
		{
			double wage = Double.parseDouble(data[5]);
			double hours = Double.parseDouble(data[6]);
			double weeks = Double.parseDouble(data[7]);
			PTE pte = new PTE(id, data[1], data[2]);
			pte.SetHourlyWage(wage);
			pte.SetHoursPerWeek(hours);
			pte.SetWeeksPerYear(weeks);
			e = pte;
		}

		e.SetDeductRate(deductrate);
		AddEmployee(e);
	}

	public void Serialize(String fname)
	{
		try
		{
			java.io.FileOutputStream o = new java.io.FileOutputStream(fname);
			String header = "# employee file format: ID(int), First Name (String), Last Name (String), Deduct Rate (double), Full Time (boolean), Wages\n";
			o.write(header.getBytes());

			EmployeeInfo[] employees = m_Table.GetEmployees();
			for (int i = 0; i < m_Table.Size(); i++)
				o.write(SerializeEmployee(employees[i]));

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
			java.io.File f = new java.io.File(fname);
			java.util.List<String> lines = java.nio.file.Files.readAllLines(f.toPath());
			java.util.ListIterator<String> it = lines.listIterator();

			String l = it.next();
			String header = "# employee file format: ID(int), First Name (String), Last Name (String), Deduct Rate (double), Full Time (boolean), Wages";
			if (l.compareTo(header) != 0)
			{
				System.out.println(fname + " contains invalid employee data");
				return;
			}

			Clear();
			for (int i = 1; i < lines.size(); i++)
			{
				l = it.next();
				DeserializeEmployee(l);
			}
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

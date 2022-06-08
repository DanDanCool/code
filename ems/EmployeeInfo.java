public class EmployeeInfo
{
	protected String m_FirstName;
	protected String m_LastName;
	protected double m_DeductRate;
	protected int m_ID;

	protected EmployeeInfo()
	{
		m_ID = -1;
	}

	protected EmployeeInfo(int id, String fname, String lname)
	{
		m_ID = id;

		String[] fdata = fname.split(" ");
		m_FirstName = fdata[0];

		String[] ldata = lname.split(" ");
		m_LastName = ldata[0];
	}

	public double NetAnnualIncome()
	{
		return 0;
	}

	public double HourlyWage()
	{
		return 0;
	}

	public double HoursPerWeek()
	{
		return 0;
	}

	public double WeeksPerYear()
	{
		return 0;
	}

	public void SetDeductRate(double dr)
	{
		m_DeductRate = dr;
	}

	public double GetDeductRate()
	{
		return m_DeductRate;
	}

	public void SetFirstName(String name)
	{
		String[] fdata = name.split(" ");
		m_FirstName = fdata[0];
	}

	public String GetFirstName()
	{
		return m_FirstName;
	}

	public void SetLastName(String name)
	{
		String[] ldata = name.split(" ");
		m_LastName = ldata[0];
	}

	public String GetLastName()
	{
		return m_LastName;
	}

	public void SetID(int id)
	{
		m_ID = id;
	}

	public int GetID()
	{
		return m_ID;
	}

	// should probably be merged into one function that returns some employee type enum
	public boolean IsFTE()
	{
		return false;
	}

	public boolean IsPTE()
	{
		return false;
	}
}

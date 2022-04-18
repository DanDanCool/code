public class FTE extends EmployeeInfo
{
	private double m_Salary;

	public FTE()
	{
		super();
	}

	public FTE(int id, String fname, String lname)
	{
		super(id, fname, lname);
	}

	public double NetAnnualIncome()
	{
		return m_Salary - m_DeductRate;
	}

	public void SetSalary(double s)
	{
		m_Salary = s;
	}

	public double GetSalary()
	{
		return m_Salary;
	}

	public boolean IsFTE()
	{
		return true;
	}
}

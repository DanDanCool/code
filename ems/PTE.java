public class PTE extends EmployeeInfo
{
	private double m_HourlyWage;
	private double m_HoursPerWeek;
	private double m_WeeksPerYear;

	public PTE()
	{
		super();
	}

	public PTE(int id, String fname, String lname)
	{
		super(id, fname, lname);
	}

	public double NetAnnualIncome()
	{
		return m_HourlyWage * m_HoursPerWeek * m_WeeksPerYear - m_DeductRate;
	}

	public double HourlyWage()
	{
		return m_HourlyWage;
	}

	public void SetHourlyWage(double wage)
	{
		m_HourlyWage = wage;
	}

	public double HoursPerWeek()
	{
		return m_HoursPerWeek;
	}

	public void SetHoursPerWeek(double hours)
	{
		m_HoursPerWeek = hours;
	}

	public double WeeksPerYear()
	{
		return m_WeeksPerYear;
	}

	public void SetWeeksPerYear(double weeks)
	{
		m_WeeksPerYear = weeks;
	}

	public boolean IsPTE()
	{
		return true;
	}
}

public class HashTable
{
	private EmployeeInfo[] m_Data;
	private final int MAX_EMPLOYEES = 1000000;

	public HashTable()
	{
		m_Data = new EmployeeInfo[MAX_EMPLOYEES];
	}

	private int Hash(int id)
	{
		return id;
	}

	public EmployeeInfo Get(int id)
	{
		return m_Data[Hash(id)];
	}

	public void Set(EmployeeInfo e)
	{
		m_Data[Hash(e.GetID())] = e;
	}

	public int Size()
	{
		return MAX_EMPLOYEES;
	}
}

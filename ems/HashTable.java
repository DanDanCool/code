public class HashTable
{
	private int[] m_Sparse;
	private EmployeeInfo[] m_Data;
	private int m_Size;
	private final int MAX_EMPLOYEES = 1000000;

	public HashTable()
	{
		m_Sparse = new int[MAX_EMPLOYEES];
		m_Data = new EmployeeInfo[MAX_EMPLOYEES];

		for (int i = 0; i < MAX_EMPLOYEES; i++)
			m_Sparse[i] = Integer.MAX_VALUE;
	}

	private int Hash(int id)
	{
		return m_Sparse[id];
	}

	public EmployeeInfo Get(int id)
	{
		return m_Data[Hash(id)];
	}

	public void Add(EmployeeInfo e)
	{
		if (Hash(e.GetID()) != Integer.MAX_VALUE)
		{
			m_Data[Hash(e.GetID())] = e;
			return;
		}

		m_Sparse[e.GetID()] = m_Size;
		m_Data[m_Size] = e;
		m_Size++;
	}

	public void Remove(EmployeeInfo e)
	{
		if (Hash(e.GetID()) == Integer.MAX_VALUE)
			return;

		m_Size--;
		m_Data[Hash(e.GetID())] = m_Data[m_Size];
		m_Sparse[m_Data[m_Size].GetID()] = Hash(e.GetID());
		m_Sparse[e.GetID()] = Integer.MAX_VALUE;
	}

	public EmployeeInfo[] GetEmployees()
	{
		return m_Data;
	}

	public int Size()
	{
		return m_Size;
	}
}

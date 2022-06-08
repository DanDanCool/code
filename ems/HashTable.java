// uses a sparse table implementation, which uses a layer of redirection
// employee id accesses an element in the "sparse" array, which contains the index of the desired data found in the "dense" array
// the advantage of such a scheme is that individual access is quite fast while also vastly improving sequential access speeds
// with a hashtable or a flat array, whether a key exists or not is unknown, so every key must be iterated through, which
// results in a lot of "null" data being loaded, which decreases iteration speeds
public class HashTable
{
	// m_Data could be dynamically resized as more elements are added to save space
	// m_Sparse could also use a hashtable implementation instead to save space
	// given the current employee adding strategy, we could get away with making it a resizing array as well
	private int[] m_Sparse;
	private EmployeeInfo[] m_Data;
	private int m_Size;
	private int m_NextID;
	private final int MAX_EMPLOYEES = 1000000;

	public HashTable()
	{
		m_Sparse = new int[MAX_EMPLOYEES];
		m_Data = new EmployeeInfo[MAX_EMPLOYEES];

		for (int i = 0; i < MAX_EMPLOYEES; i++)
			m_Sparse[i] = Integer.MAX_VALUE;
	}

	public void Clear()
	{
		m_Size = 0;
		m_NextID = 0;

		for (int i = 0; i <	MAX_EMPLOYEES; i++)
		{
			m_Sparse[i] = Integer.MAX_VALUE;
			m_Data[i] = null;
		}
	}

	// note: no array bounds checking occurs, responsibility lies on the caller to make sure ids are correct
	public int Hash(int id)
	{
		return m_Sparse[id];
	}

	public int NextID()
	{
		while (m_Sparse[m_NextID] != Integer.MAX_VALUE && m_Size < MAX_EMPLOYEES)
			m_NextID = (m_NextID + 1) % MAX_EMPLOYEES;

		return m_Size < MAX_EMPLOYEES ? m_NextID : -1;
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

	public int MaxSize()
	{
		return MAX_EMPLOYEES;
	}
}

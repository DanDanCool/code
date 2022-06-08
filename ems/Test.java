// alternate main file that runs some tests
import java.lang.Math;

public class Test
{
	// test EmployeeInfo functionality
	// no special data or setup required, runs automatically without user input
	// random employee info is generated to test if net annual income is calculated correctly
	public static void TestEmployees()
	{
		System.out.println("testing invalid name inputs");
		// note: spaces are intentionally not allowed in names, and so this should be cropped to "Mary"
		String name = "Mary Sue";
		EmployeeInfo e = new FTE(1, name, name);
		System.out.println("name: " + name);
		System.out.println("employee name: " + e.GetFirstName());
		name = "1234567890qwertyuiopasdfghjklzxcvbnm`~!@#$#%&^*()+_=-|][{/?.,<><<<>>>><<<<<<<<<<<<<>>>>>>><<}])";
		System.out.println("name: " + name);
		e.SetFirstName(name);
		System.out.println("employee name: " + e.GetFirstName());

		System.out.println("testing last names");
		System.out.println("employee name: " + e.GetLastName());
		System.out.println("setting last name to " + name);
		e.SetLastName(name);
		System.out.println("employee name: " + e.GetLastName());

		System.out.println("\ntesting fulltime employee net income calculations");
		final int TEST_CASE_COUNT = 20;
		for (int i = 0; i < TEST_CASE_COUNT; i++)
		{
			double dr = Math.random();
			double salary = Math.random() * 7777777;
			double net = salary * (1 - dr);
			System.out.println("salary: " + salary + ", deduct rate: " + dr + ", expected output: " + net);

			FTE fte = new FTE(1, name, name);
			fte.SetSalary(salary);
			fte.SetDeductRate(dr);

			boolean pass = fte.NetAnnualIncome() == net;
			System.out.println("fte.NetAnnualIncome() = " + fte.NetAnnualIncome() + ", correct = " + pass);
		}

		System.out.println("\ntesting part time employee net income calculations");
		for (int i = 0; i < TEST_CASE_COUNT; i++)
		{
			double wage = Math.random() * 17;
			double hours = Math.random() * 47;
			double weeks = Math.random() * 47;
			double dr = Math.random();
			double net = wage * hours * weeks * (1 - dr);
			System.out.println("wage: " + wage + ", hours: " + hours + ", weeks: " + weeks + ", deduct rate: " + dr + ", expected output: " + net);
			PTE pte = new PTE(1, name, name);
			pte.SetHourlyWage(wage);
			pte.SetHoursPerWeek(hours);
			pte.SetWeeksPerYear(weeks);
			pte.SetDeductRate(dr);

			boolean pass = pte.NetAnnualIncome() == net;
			System.out.println("pte.NetAnnualIncome() = " + pte.NetAnnualIncome() + ", corret = " + pass);
		}
	}

	// test the storage for the employee data
	// no special data or setup required, recommended that the memory capacity is at least 500 mb
	// user interaction not required, tests run automatically
	// tests if the table correctly inserts employee data, and in the right order as well
	// output should match the randomly generated array of employees perfectly
	public static void TestHashTable()
	{
		HashTable table = new HashTable();

		System.out.println("filling hashtable");
		for (int i = 0; i < table.MaxSize(); i++)
		{
			FTE fte = new FTE(i, "null", "null");
			table.Add(fte);
		}
		System.out.println("finished filling hashtable, size: " + table.Size());

		EmployeeInfo[] employees = table.GetEmployees();
		for (int i = 0; i < table.Size(); i++)
		{
			//System.out.println(employees[i]);
		}

		table.Clear();

		final int TEST_ARRAY_SIZE = 20;
		EmployeeInfo[] test = new EmployeeInfo[TEST_ARRAY_SIZE];
		for (int i = 0; i < TEST_ARRAY_SIZE; i++)
		{
			double id = Math.random() * table.MaxSize();
			String fname = "" + Math.random();
			String lname = "" + Math.random();
			test[i] = new FTE((int)Math.round(id), fname, lname);
		}

		System.out.println("random employee array");
		for (int i = 0; i < TEST_ARRAY_SIZE; i++)
		{
			EmployeeInfo e = test[i];
			System.out.println("id: " + e.GetID() + ", fname: " + e.GetFirstName() + ", lname: " + e.GetLastName());
			table.Add(e);
		}

		employees = table.GetEmployees();
		System.out.println("table results");
		for (int i = 0; i < table.Size(); i++)
		{
			EmployeeInfo e = employees[i];
			System.out.println("id: " + e.GetID() + ", fname: " + e.GetFirstName() + ", lname: " + e.GetLastName());
		}
	}

	// tests serializing/deserializing
	// no special data or setup required, recommended to have at least 500 mb of memory
	// user interaction is not required, tests run automatically
	// assumes that the EmployeeInfo and HashTable classes are working as intended
	// output should be the same before any serializing/deserializing
	public static void TestSystem()
	{
		EmployeeSystem system = new EmployeeSystem();

		System.out.println("filling system with random entries");
		final int TEST_ARRAY_SIZE = 20;
		EmployeeInfo[] test = new EmployeeInfo[TEST_ARRAY_SIZE];
		for (int i = 0; i < TEST_ARRAY_SIZE; i++)
		{
			double id = Math.random() * 777777;
			String fname = "" + Math.random();
			String lname = "" + Math.random();
			if (id > (777777 / 2))
			{
				FTE fte = new FTE((int)Math.round(id), fname, lname);
				fte.SetSalary(Math.random() * 77777);
				test[i] = fte;
			}
			else
			{
				PTE pte = new PTE((int)Math.round(id), fname, lname);
				pte.SetHourlyWage(Math.random() * 17);
				pte.SetHoursPerWeek(Math.random() * 77);
				pte.SetWeeksPerYear(Math.random() * 47);
				test[i] = pte;
			}

			test[i].SetDeductRate(Math.random());
			system.AddEmployee(test[i]);
		}

		System.out.println(system.GetSize() + " entries added");
		system.Status();

		String fname = "./employees.txt";
		System.out.println("serializing into " + fname);
		system.Serialize(fname);

		System.out.println("clearing system and loading " + fname);
		system.Clear();
		system.Deserialize(fname);

		System.out.println("printing out employees...");
		system.Status();
	}

	public static void main(String[] args)
	{
		System.out.println("------------------------------------------");
		System.out.println("Testing EmployeeInfo class and derivatives");
		TestEmployees();

		System.out.println("------------------------------------------");
		System.out.println("Testing HashTable storage system");
		TestHashTable();

		System.out.println("------------------------------------------");
		System.out.println("Testing Employee System");
		TestSystem();
	}
}

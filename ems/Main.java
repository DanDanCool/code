public class Main
{
	public static void main(String[] args)
	{
		EmployeeSystem system = new EmployeeSystem();
		system.AddEmployee(new FTE(1, "a", "a"));
		system.AddEmployee(new PTE(234234, "b", "b"));
		system.Status();
		system.Serialize("employees.txt");
	}
}

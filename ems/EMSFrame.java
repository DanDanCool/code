import java.util.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;

public class EMSFrame extends JFrame
{
	private EmployeeSystem m_System;
	private EmployeeInfo m_Selected;

	private EmployeeInfoPanel m_EmployeeInfoPanel;

	public EMSFrame()
	{
		m_System = new EmployeeSystem();
		m_System.AddEmployee(new FTE(1, "a", "a"));
		m_System.AddEmployee(new PTE(234234, "b", "b"));
		// system.Deserialize("employees.txt");
		// system.Status();
		// system.Serialize("employees.txt");

		setLayout(new BorderLayout(5, 5));

		add(new EmployeePanel(), BorderLayout.CENTER);
		add(new ActionPanel(), BorderLayout.EAST);

		m_EmployeeInfoPanel = new EmployeeInfoPanel();
		add(m_EmployeeInfoPanel, BorderLayout.WEST);

		setTitle("EMS");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(1000, 800);
		setVisible(true);
	}

	public void Refresh()
	{
		m_EmployeeInfoPanel.Refresh();
	}

	// contains buttons that do various things (editing, adding, etc...)
	class ActionPanel extends JPanel
	{
		public ActionPanel()
		{
			setLayout(new GridLayout(4, 1));

			JButton addbt = new JButton("Add");
			add(addbt);

			JButton rmbt = new JButton("Remove");
			add(rmbt);

			JButton savebt = new JButton("Save");
			add(savebt);

			JButton loadbt = new JButton("Load");
			add(loadbt);
		}
	}

	class EmployeePanel extends JPanel
	{
		private JTable m_Table;

		public EmployeePanel()
		{
			m_Table = new JTable(new EmployeeTableModel());
			m_Table.setFillsViewportHeight(true);
			m_Table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			ListSelectionModel model = m_Table.getSelectionModel();
			model.addListSelectionListener(new EmployeeSelectionListener());

			JScrollPane pane = new JScrollPane(m_Table);
			add(pane);
		}

		class EmployeeTableModel extends javax.swing.table.AbstractTableModel
		{
			final String[] m_ColumnNames = { "ID", "First Name", "Last Name", "Full Time", "Part Time" };
			public int getColumnCount()
			{
				return m_ColumnNames.length;
			}

			public int getRowCount()
			{
				return m_System.GetSize();
			}

			public String getColumnName(int col)
			{
				return m_ColumnNames[col];
			}

			public Object getValueAt(int rowIndex, int columnIndex)
			{
				EmployeeInfo e = m_System.GetEmployees()[rowIndex];
				Object[] o = { e.GetID(), e.GetFirstName(), e.GetLastName(), e.IsFTE(), e.IsPTE() };
				return o[columnIndex];
			}

			public Class getColumnClass(int c)
			{
				return getValueAt(0, c).getClass();
			}
		}

		class EmployeeSelectionListener implements ListSelectionListener
		{
			public void valueChanged(ListSelectionEvent e)
			{
				int[] row = m_Table.getSelectedRows();
				m_Selected = m_System.GetEmployees()[row[0]];
				Refresh();
			}
		}
	}

	class EmployeeInfoPanel extends JPanel
	{
		JLabel m_ID;
		JTextField m_FirstName;
		JTextField m_LastName;
		JCheckBox m_IsFTE;
		JCheckBox m_IsPTE;
		JPanel m_Panel;

		public EmployeeInfoPanel()
		{
			setLayout(new GridLayout(6, 1));

			m_ID = new JLabel("ID: null");
			add(m_ID);

			m_FirstName = new JTextField();
			m_FirstName.setText("no employee selected");
			add(m_FirstName);

			m_LastName = new JTextField();
			m_LastName.setText("no employee selected");
			add(m_LastName);

			m_IsFTE = new JCheckBox("Fulltime", false);
			add(m_IsFTE);

			m_IsPTE = new JCheckBox("Parttime", false);
			add(m_IsPTE);

			m_Panel = new JPanel();
			add(m_Panel);
		}

		public void Refresh()
		{
			m_ID.setText("ID: " + m_Selected.GetID());
			m_FirstName.setText(m_Selected.GetFirstName());
			m_LastName.setText(m_Selected.GetLastName());
			m_IsFTE.setSelected(m_Selected.IsFTE());
			m_IsPTE.setSelected(m_Selected.IsPTE());

			remove(m_Panel);
			m_Panel = m_Selected.IsFTE() ? new FTEPanel() : new PTEPanel();
			add(m_Panel);

			revalidate();
			repaint();
		}

		class FTEPanel extends JPanel
		{
			public FTEPanel()
			{
				setLayout(new GridLayout(1, 2, 5, 5));

				FTE fte = (FTE)m_Selected;

				add(new JLabel("Salary"));
				JTextField salary = new JTextField("Salary");
				salary.setText("" + fte.GetSalary());
				add(salary);
			}
		}

		class PTEPanel extends JPanel
		{
			public PTEPanel()
			{
				setLayout(new GridLayout(3, 2, 5, 5));

				PTE pte = (PTE)m_Selected;

				add(new JLabel("Wage"));
				JTextField wage = new JTextField("Wage");
				wage.setText("" + pte.HourlyWage());
				add(wage);

				add(new JLabel("Hours"));
				JTextField hours = new JTextField("Hours");
				hours.setText("" + pte.HoursPerWeek());
				add(hours);

				add(new JLabel("Weeks"));
				JTextField weeks = new JTextField("Weeks");
				weeks.setText("" + pte.WeeksPerYear());
				add(weeks);
			}
		}
	}
}

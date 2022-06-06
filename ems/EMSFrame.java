import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class EMSFrame extends JFrame
{
	private EmployeeSystem m_System;
	private EmployeeInfo m_Selected; // TODO: make this a stack

	private EmployeePanel m_EmployeePanel;
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

		m_EmployeePanel = new EmployeePanel();
		add(m_EmployeePanel, BorderLayout.CENTER);
		add(new ActionPanel(), BorderLayout.EAST);

		m_EmployeeInfoPanel = new EmployeeInfoPanel();
		add(m_EmployeeInfoPanel, BorderLayout.WEST);

		setTitle("EMS");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(1000, 800);
		setVisible(true);
	}

	// update UI
	public void Refresh()
	{
		m_EmployeePanel.Update();
		m_EmployeeInfoPanel.Update();
	}

	// contains buttons that do various things (editing, adding, etc...)
	class ActionPanel extends JPanel
	{
		public ActionPanel()
		{
			setLayout(new GridLayout(4, 1));

			JButton addbt = new JButton("Add");
			addbt.addActionListener(new AddListener());
			add(addbt);

			JButton rmbt = new JButton("Remove");
			rmbt.addActionListener(new RemoveListener());
			add(rmbt);

			JButton savebt = new JButton("Save");
			savebt.addActionListener(new SaveListener());
			add(savebt);

			JButton loadbt = new JButton("Load");
			loadbt.addActionListener(new LoadListener());
			add(loadbt);
		}

		class AddListener implements ActionListener
		{
			public void actionPerformed(ActionEvent e)
			{
				m_System.AddEmptyEmployee();
				Refresh();
			}
		}

		class RemoveListener implements ActionListener
		{
			public void actionPerformed(ActionEvent e)
			{
				if (m_Selected != null)
					m_System.RemoveEmployee(m_Selected);

				m_Selected = null;
				Refresh();
			}
		}

		class SaveListener implements ActionListener
		{
			public void actionPerformed(ActionEvent e)
			{
				JFileChooser fc = new JFileChooser();
				int sel = fc.showOpenDialog(m_EmployeeInfoPanel);
				if (sel == JFileChooser.APPROVE_OPTION)
					m_System.Serialize(fc.getSelectedFile().getName());

				Refresh();
			}
		}

		class LoadListener implements ActionListener
		{
			public void actionPerformed(ActionEvent e)
			{
				JFileChooser fc = new JFileChooser();
				int sel = fc.showOpenDialog(m_EmployeeInfoPanel);
				if (sel == JFileChooser.APPROVE_OPTION)
					m_System.Deserialize(fc.getSelectedFile().getName());

				Refresh();
			}
		}
	}

	// Displays a table of employees
	class EmployeePanel extends JPanel
	{
		private JTable m_Table;
		private JScrollPane m_Viewport;

		public EmployeePanel()
		{
			setLayout(new BorderLayout(5, 5));
			m_Table = new JTable(new EmployeeTableModel());
			m_Table.setFillsViewportHeight(true);
			m_Table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			ListSelectionModel model = m_Table.getSelectionModel();
			model.addListSelectionListener(new EmployeeSelectionListener());

			m_Viewport = new JScrollPane(m_Table);
			add(m_Viewport, BorderLayout.CENTER);
		}

		public void Update()
		{
			m_Viewport.revalidate();
			m_Viewport.repaint();
			revalidate();
			repaint();
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

	// Sidebar that allows for editing of employee information
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
			m_FirstName.addActionListener(new FNameListener());
			add(m_FirstName);

			m_LastName = new JTextField();
			m_LastName.setText("no employee selected");
			m_LastName.addActionListener(new LNameListener());
			add(m_LastName);

			m_IsFTE = new JCheckBox("Fulltime", false);
			m_IsFTE.addActionListener(new FTEListener());
			add(m_IsFTE);

			m_IsPTE = new JCheckBox("Parttime", false);
			m_IsPTE.addActionListener(new PTEListener());
			add(m_IsPTE);

			m_Panel = new JPanel();
			add(m_Panel);
		}

		public void Update()
		{
			if (m_Selected == null)
				return;

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

		class FNameListener implements ActionListener
		{
			public void actionPerformed(ActionEvent e)
			{
				if (m_Selected == null)
					return;

				m_Selected.SetFirstName(m_FirstName.getText());
				Refresh();
			}
		}

		class LNameListener implements ActionListener
		{
			public void actionPerformed(ActionEvent e)
			{
				if (m_Selected == null)
					return;

				m_Selected.SetLastName(m_LastName.getText());
				Refresh();
			}
		}

		class FTEListener implements ActionListener
		{
			public void actionPerformed(ActionEvent e)
			{
				if (m_Selected == null || !m_IsFTE.isSelected())
					return;

				FTE fte = new FTE(m_Selected.GetID(), m_Selected.GetFirstName(), m_Selected.GetLastName());
				m_System.RemoveEmployee(m_Selected);
				m_System.AddEmployee(fte);
				m_Selected = fte;
				m_IsPTE.setSelected(false);
				Refresh();
			}
		}

		class PTEListener implements ActionListener
		{
			public void actionPerformed(ActionEvent e)
			{
				if (m_Selected == null || !m_IsPTE.isSelected())
					return;

				PTE pte = new PTE(m_Selected.GetID(), m_Selected.GetFirstName(), m_Selected.GetLastName());
				m_System.RemoveEmployee(m_Selected);
				m_System.AddEmployee(pte);
				m_Selected = pte;
				m_IsFTE.setSelected(false);
				Refresh();
			}
		}

		class FTEPanel extends JPanel
		{
			JTextField m_Salary;

			public FTEPanel()
			{
				setLayout(new GridLayout(1, 2, 5, 5));

				FTE fte = (FTE)m_Selected;

				add(new JLabel("Salary"));
				m_Salary = new JTextField("Salary");
				m_Salary.setText("" + fte.GetSalary());
				m_Salary.addActionListener(new SalaryListener());
				add(m_Salary);
			}

			class SalaryListener implements ActionListener
			{
				public void actionPerformed(ActionEvent e)
				{
					if (m_Selected == null)
						return;

					try
					{
						FTE fte = (FTE)m_Selected;
						double salary = Double.parseDouble(m_Salary.getText());
						fte.SetSalary(salary);
					}
					catch (NumberFormatException ex)
					{

					}
				}
			}
		}

		class PTEPanel extends JPanel
		{
			private JTextField m_Wage;
			private JTextField m_Hours;
			private JTextField m_Weeks;

			public PTEPanel()
			{
				setLayout(new GridLayout(3, 2, 5, 5));

				PTE pte = (PTE)m_Selected;

				add(new JLabel("Wage"));
				m_Wage = new JTextField("Wage");
				m_Wage.setText("" + pte.HourlyWage());
				m_Wage.addActionListener(new WageListener());
				add(m_Wage);

				add(new JLabel("Hours"));
				m_Hours = new JTextField("Hours");
				m_Hours.setText("" + pte.HoursPerWeek());
				m_Hours.addActionListener(new HoursListener());
				add(m_Hours);

				add(new JLabel("Weeks"));
				m_Weeks = new JTextField("Weeks");
				m_Weeks.setText("" + pte.WeeksPerYear());
				m_Weeks.addActionListener(new WeeksListener());
				add(m_Weeks);
			}

			class WageListener implements ActionListener
			{
				public void actionPerformed(ActionEvent e)
				{
					if (m_Selected == null)
						return;

					try
					{
						PTE pte = (PTE)m_Selected;
						double wage = Double.parseDouble(m_Wage.getText());
						pte.SetHourlyWage(wage);
					}
					catch (NumberFormatException ex)
					{
					}
				}
			}

			class HoursListener implements ActionListener
			{
				public void actionPerformed(ActionEvent e)
				{
					if (m_Selected == null)
						return;

					try
					{
						PTE pte = (PTE)m_Selected;
						double hours = Double.parseDouble(m_Hours.getText());
						pte.SetHoursPerWeek(hours);
					}
					catch (NumberFormatException ex)
					{

					}
				}
			}

			class WeeksListener implements ActionListener
			{
				public void actionPerformed(ActionEvent e)
				{
					if (m_Selected == null)
						return;

					try
					{
						PTE pte = (PTE)m_Selected;
						double weeks = Double.parseDouble(m_Weeks.getText());
						pte.SetWeeksPerYear(weeks);
					}
					catch (NumberFormatException ex)
					{

					}
				}
			}
		}
	}
}

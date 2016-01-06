import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.DefaultListModel;
import javax.swing.JScrollPane;
import java.awt.event.*;
import java.awt.*;
public class IronSafe{
  public static void OpenSafe(String path){
    int dim2 = 500;
    Snatcher s = new Snatcher();
    JFrame frame = new JFrame("IronSafe - Password Keeper");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      JPanel banner = new JPanel();
      banner.setBackground(Color.BLACK);
        JLabel ban = new JLabel("IronSafe password-keeper developed by CA1K");
        ban.setFont(new Font("Arial",Font.ITALIC,14));
        ban.setForeground(Color.WHITE);
        banner.add(ban);
      frame.add(banner,BorderLayout.PAGE_START);
      JPanel main = new JPanel(new GridLayout(1,2));
        JPanel listSide = new JPanel();
          DefaultListModel listModel = new DefaultListModel();
          listModel.addElement("Your currently saved passwords on disk:");
          s.LoadData(listModel,path);
          JList list = new JList(listModel);
          list.setLayoutOrientation(JList.VERTICAL_WRAP);
          list.setVisibleRowCount(10);
          JScrollPane listPane = new JScrollPane(list);
        listSide.add(listPane);
        listSide.setBackground(Color.DARK_GRAY);
      main.add(listSide);
        JPanel ctrlSide = new JPanel(new GridLayout(5,1));
          JLabel descA = new JLabel("   Input password label (or site)");
          descA.setFont(new Font("Arial",Font.BOLD,14));
          descA.setForeground(Color.DARK_GRAY);
        ctrlSide.add(descA);
          JTextField fieldA = new JTextField(dim2/10);
        ctrlSide.add(fieldA);
          JLabel descB = new JLabel("   Input password");
          descB.setFont(new Font("Arial",Font.BOLD,14));
          descB.setForeground(Color.DARK_GRAY);
        ctrlSide.add(descB);
          JTextField fieldB = new JTextField(dim2/10);
        ctrlSide.add(fieldB);
          JPanel btnBox = new JPanel();
            JButton add = new JButton("Add");
            add.addActionListener(new ActionListener(){
              public void actionPerformed(ActionEvent e){
                String data = listModel.size() + ") " + fieldA.getText() + " -> " + fieldB.getText();
                listModel.addElement(data);
                s.SaveData(listModel,path);
              }
            });
            JButton rem = new JButton("Remove");
            rem.addActionListener(new ActionListener(){
              public void actionPerformed(ActionEvent e){
                listModel.remove(listModel.size()-1);
                s.SaveData(listModel,path);
              }
            });
          btnBox.add(add);
          btnBox.add(rem);
        ctrlSide.add(btnBox);
      main.add(ctrlSide);
      frame.add(main, BorderLayout.CENTER);
    frame.pack();
    Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
    frame.setLocation(dim.width/2-frame.getSize().width/2, dim.height/2-frame.getSize().height/2);
    frame.setSize(dim2,dim2/2);
    frame.setVisible(true);
    frame.setResizable(false);
  }
}

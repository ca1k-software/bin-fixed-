import javax.swing.JFileChooser;
import java.io.File;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JLabel;
import java.awt.*;
import java.awt.event.*;
public class IronMain{
  public static void trigger(){
    IronSafe is = new IronSafe();
    JFileChooser j = new JFileChooser();
    j.setCurrentDirectory(new File(System.getProperty("user.home")));
    int result = j.showOpenDialog(new JFrame());
    if (result == JFileChooser.APPROVE_OPTION) {
    File selectedFile = j.getSelectedFile();
    is.OpenSafe(selectedFile.getAbsolutePath());
    }
  }
  public static void main(String[] args){
    JFrame frame = new JFrame("Welcome to IronSafe");
    Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
    frame.setLocation(dim.width/2-frame.getSize().width/2, dim.height/2-frame.getSize().height/2);
    JPanel main = new JPanel(new GridLayout(3,1));
     JPanel banner = new JPanel();
      banner.setBackground(Color.BLACK);
        JLabel ban = new JLabel("IronSafe password-keeper developed by CA1K");
        ban.setFont(new Font("Arial",Font.ITALIC,14));
        ban.setForeground(Color.WHITE);
        banner.add(ban);
      frame.add(banner,BorderLayout.PAGE_START);
     JPanel panel = new JPanel();
      JLabel intro = new JLabel("To begin, press the 'Open' button as it will help you choose a file: ");
       JButton button = new JButton("Open");
       button.addActionListener(new ActionListener(){
         public void actionPerformed(ActionEvent e){
           trigger();
           frame.dispatchEvent(new WindowEvent(frame, WindowEvent.WINDOW_CLOSING));
         }
       });
     panel.add(intro);
     panel.add(button);
     main.add(panel);
     JPanel noticePanel = new JPanel();
     JLabel notice = new JLabel("Notice: In order to move on, you must have an empty text document at the ready");
     noticePanel.add(notice);
     main.add(noticePanel);
     JPanel contactPanel = new JPanel();
     JLabel contact = new JLabel("Any questions or concerns? E-mail ca1ksoftware@gmail.com");
     contactPanel.add(contact);
     main.add(contactPanel);
    frame.add(main,BorderLayout.CENTER);
    frame.pack();
    frame.setSize(500,180);
    frame.setVisible(true);
    frame.setResizable(false);
  }
}

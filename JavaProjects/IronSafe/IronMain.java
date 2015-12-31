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
    frame.add(panel);
    frame.pack();
    frame.setSize(500,70);
    frame.setVisible(true);
    frame.setResizable(false);
  }
}

import javax.swing.DefaultListModel;
import java.io.*;
public class Snatcher{
  public void SaveData(DefaultListModel model, String path){
    File file = new File(path);
    try{
    PrintWriter p = new PrintWriter(file);
    for(int i=1;i<model.size();i++){
      p.println(model.get(i).toString());
    }
    p.close();
    }catch(IOException ex){
    System.out.printf("ERROR: ",ex);
    }
  }
  public void LoadData(DefaultListModel model, String path){
    try(BufferedReader br = new BufferedReader(new FileReader(path))) {
    for(String line; (line = br.readLine()) != null; ) {
        model.addElement(line);
      }
    // line is not visible here.
    }catch(IOException ex){
    System.out.printf("ERROR: ",ex);
    }
  }
}

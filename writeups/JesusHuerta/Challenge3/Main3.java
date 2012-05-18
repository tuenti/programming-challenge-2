package Challenge3;
import java.io.IOException;
public class Main3 {
    public static void main(String[] args) {
        UserInterface3 ui = new UserInterface3();
        try {
            ui.run();
        } catch (IOException ex) {
            System.exit(-1);
        }
    }
}
package p3;

import java.io.*;

public class writeToFile {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        FileWriter writer = new FileWriter("src/p3/out.txt");

        try {
            String input = br.readLine();
            while (input.equals("exit") != true) {
                writer.write(input);
                input = br.readLine();
            }
        }
        catch(IOException e) {
            System.out.println("IO Exception occurred");
            writer.close();
            br.close();
        }
        writer.close();
        br.close();
    }
}

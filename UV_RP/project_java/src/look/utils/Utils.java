package look.utils;

import look.telegram.Info;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Utils {

    // Muril-o: I know this can be improved but I'd rather not because of dynamic file writing!
    public static String readFile(String fileName) throws IOException {
        System.out.println("readFile - " + fileName);
        BufferedReader br = new BufferedReader(new FileReader(fileName));
        try {
            StringBuilder sb = new StringBuilder();
            String line = br.readLine();

            while (line != null) {
                sb.append(line);
                sb.append("\n");
                line = br.readLine();
            }
            return sb.toString();
        } finally {
            br.close();
        }
    }

    public static String getEnvKeyValue(String key) {
        try {
            String env = readFile("./.env");
            return env.split(key + "=")[1].split("\n")[0];
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public static String[] getDataValues() {
        try {
            String env = readFile(Info.FILE_DATA);
            return env.split("\n");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}

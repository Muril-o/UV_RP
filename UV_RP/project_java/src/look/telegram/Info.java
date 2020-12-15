package look.telegram;

import look.utils.Utils;

public class Info {

    static String BOT_TOKEN = Utils.getEnvKeyValue("BOT_TOKEN");
    static String BOT_USERNAME = Utils.getEnvKeyValue("BOT_USERNAME");
    public static String FILE_DATA = Utils.getEnvKeyValue("FILE_DATA");
    public static String FILE_LATEST = Utils.getEnvKeyValue("FILE_LATEST");
}

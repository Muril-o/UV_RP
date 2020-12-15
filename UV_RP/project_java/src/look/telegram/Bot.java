package look.telegram;

import look.graph.Graph;
import look.utils.Utils;
import org.telegram.telegrambots.bots.TelegramLongPollingBot;
import org.telegram.telegrambots.meta.api.methods.send.SendMessage;
import org.telegram.telegrambots.meta.api.methods.send.SendPhoto;
import org.telegram.telegrambots.meta.api.objects.Message;
import org.telegram.telegrambots.meta.api.objects.Update;
import org.telegram.telegrambots.meta.exceptions.TelegramApiException;

import java.io.IOException;

public class Bot extends TelegramLongPollingBot {

    public void onUpdateReceived(Update update) {
        Message message = update.getMessage();
        // Muril-o: Verbose lol
        System.out.println(message.getFrom().getFirstName() + ": " + message.getText());

        if (message.getText().startsWith("/start")) {
            SendPhoto toSend = new SendPhoto();
            String[] all_uv = Utils.getDataValues();
            int last_uv = Integer.valueOf(all_uv[all_uv.length-1]);
            toSend.setChatId(message.getChatId());
            if (last_uv <= 2) {
                toSend.setCaption("**Índice UV atual:** " + last_uv + " (Baixo)\nSem proteção necessária.");
            }
            if (last_uv > 2 && last_uv <= 5) {
                toSend.setCaption("**Índice UV atual:** " + last_uv + " (Moderado)\nUsar roupas mais longas.");
            }
            if (last_uv > 5 && last_uv <= 7) {
                toSend.setCaption("**Índice UV atual:** " + last_uv + " (Alto)\nAplicar protetor solar, usar roupas mais longas, ficar na sombra.");
            }
            if (last_uv > 7) {
                toSend.setCaption("**Índice UV atual:** " + last_uv + " (Muito alto)\nAplicar protetor solar, usar roupas mais longas, ficar na sombra.");
            }
            toSend.setParseMode("markdown");
            try {
                toSend.setPhoto(Graph.updateGraphFile());
            } catch (IOException e) {
                e.printStackTrace();
            }
            try {
                execute(toSend);
            } catch (TelegramApiException e) {
                e.printStackTrace();
            }
        }
    }

    public String getBotUsername() {
        return Info.BOT_USERNAME;
    }

    public String getBotToken() {
        return Info.BOT_TOKEN;
    }
}

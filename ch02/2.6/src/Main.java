import lexer.Lexer;
import lexer.token.Token;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        Lexer lexer = new Lexer();
        Token t = lexer.scan();
        System.out.println(t.tag);
    }
}

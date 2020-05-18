package lexer;
import lexer.token.*;

import java.io.*;
import java.util.*;

public class Lexer {
    public int line = 1;
    private char peek = ' ';
    private final Hashtable<String, Word> words = new Hashtable<>();
    private final InputStreamReader stream = new InputStreamReader(System.in);

    void reserve(Word t) {
        words.put(t.lexeme, t);
    }

    public Lexer() {
        // keywords
        reserve(new Word(Tag.TRUE, "true"));
        reserve(new Word(Tag.FALSE, "false"));
    }

    /**
     * If input is "11ss", this lexer will identify 11 as an INT type.
     */
    public Token scan() throws IOException {
        // ignore space and tab
        for (; ; peek = (char)stream.read()) {
            if (peek == '\n') line++;
            else if (peek != ' ' && peek != '\t') break;
        }
        // ignore comment
        if (peek == '/') {
            peek = (char)stream.read();
            // inline comment
            if (peek == '/') {
                do {
                    peek = (char)stream.read();
                    System.out.println("peek1: " + peek);
                } while (peek != '\n');
                line++;
            }
            if (peek == '*') {
                char previous;
                do {
                    previous = peek;
                    peek = (char)stream.read();
                    if (peek == '\n') line++;
                } while (previous != '*' || peek != '/');
            }
        }
        // relation operator
        if ("<=!>".indexOf(peek) != -1) {
            StringBuilder sb = new StringBuilder();
            sb.append(peek);
            peek = (char)stream.read();
            if (peek == '=') {
                sb.append(peek);
                peek = (char)stream.read();
            }
            return new Rel(sb.toString());
        }
        if (Character.isDigit(peek) || peek == '.') {
            double v = 0;
            if (peek != '.') {
                do {
                    v = v * 10 + Character.digit(peek, 10);
                    peek = (char)stream.read();
                } while (Character.isDigit(peek));
            }
            if (peek == '.') {
                double decimal = 0;
                int divisor = 0;
                peek = (char)stream.read();
                while (Character.isDigit(peek)) {
                    decimal = decimal * 10 + Character.digit(peek, 10);
                    divisor++;
                    peek = (char)stream.read();
                };
                if (divisor > 0) v += decimal / (10 * divisor);
            }
            return new Num(v);
        }
        if (Character.isLetter(peek)) {
            StringBuilder b = new StringBuilder();
            do {
                b.append(peek);
                peek = (char)stream.read();
            } while (Character.isLetterOrDigit(peek));
            String s = b.toString();
            Word w = words.get(s);
            if (w != null) return w;
            w = new Word(Tag.ID, s);
            words.put(s, w);
            return w;
        }
        Token t = new Token(peek);
        peek = ' ';
        return t;
    }
}

package lexer.token;

public class Rel extends Token {
    public final String opertor;
    public Rel(String s) {
        super(Tag.REL_OPR);
        opertor = s;
    }
}

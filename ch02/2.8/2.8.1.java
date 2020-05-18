/* my solution */
class For extends Stmt {
    Expr E1, E2, E3;
    Stmt S;
    
    public For(Expr E1, Expr E2, Expr E3, Stmt S) {
        this.E1 = E1;
        this.E2 = E2;
        this.E3 = E3;
        this.S = S;
    }

    public void gen() {
        Label start = new Label();
        Label end = new Label();

        E1.gen();
        emit(start + ":");
        Expr n = E2.rvalue();
        emit("ifFalse " + n + " goto " + end);
        S.gen(); E3.gen();
        emit("goto " + start);
        emit(end + ":");
    }
}
class D {
    int method() {
        return 1;
    }
}

class E extends D {
    int method() {
        return 2;
    }
}

class F extends E {
    int fun(D d) {
        return d.method();
    }
}

class Test {
    public static void main(String[] args) {
        F x = new F();

        System.out.println(x.fun(x));
    }
}
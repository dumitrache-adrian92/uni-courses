class Ra {
    Ra(Integer i) {

    }
}

class Ka extends Ra{
    Ka(int i) {
        super(i);
    }

    public static void main(String[] args) {
        new Ka(10);
    }
}
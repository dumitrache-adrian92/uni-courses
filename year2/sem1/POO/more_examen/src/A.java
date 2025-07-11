class UrMom {
    public static void main(String[] args) {
        try {
            System.out.println("1");
            try {
                String x = null;
                System.out.println(x.toString());
            } finally {
                System.out.println("urasc");
            }
        } catch (Exception e) {
            System.out.println("2");
        }
    }
}
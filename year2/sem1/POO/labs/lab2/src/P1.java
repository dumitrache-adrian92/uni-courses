public class P1 {
    public static void main(String args[]) {
        String s1 = "si";
        String s = "sir1 si cu sir2 fac un sir3";
        int current_index = s.indexOf(s1, 0);
        int result = 0;
        while (current_index != -1) {
            result++;
            current_index = s.indexOf(s1, current_index + 1);
        }
        System.out.println(result);
    }
}

public class P5 {
    public static String sus(String s, String []words) {
        boolean sus_flag = false;
        char []censored = new char[20];
        for (String x : words)
            if (s.contains(x)) {
                sus_flag = true;
                censored = x.toCharArray();
                for (int i = 1; i < censored.length - 1; i++)
                    censored[i] = '*';
                s = s.replace(x, String.valueOf(censored));
            }
        if (sus_flag)
            System.out.println("Text suspect");
        else
            System.out.println("Nimic suspect");
        System.out.println(s);
        return s;
    }

    public static void main(String []args) {
        String[] words = new String[] {"gagicar", "bomba", "terorist", "dota"};
        System.out.println(sus("Un terorist avea o bomba si o boaba", words));
    }
}

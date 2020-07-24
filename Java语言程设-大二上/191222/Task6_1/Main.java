import java.util.*;

class Computer {
    private int val;

    @Override
    public String toString() {
        return "Computer [" +
                "val=" + val +
                ']';
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        Object[] data = new Object[n];
        for (int i=0; i<n; i++) {
            String op = sc.next();
            if (op.equals("c")) {
                data[i] = new Computer();
            }
            else if (op.equals("d")) {
                data[i] = sc.nextDouble();
            }
            else if (op.equals("i")) {
                data[i] = sc.nextInt();
            }
            else if (op.equals("s")) {
                data[i] = sc.next();
            }
            else {
                data[i] = null;
            }
        }
        for (int i=n-1; i>=0; i--) {
            if (data[i] == null) {
                continue;
            }
            else if (data[i] instanceof Computer) {
                System.out.println(data[i].toString());
            }
            else {
                System.out.println(data[i]);
            }
        }
        sc.close();
    }
}

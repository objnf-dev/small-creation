import java.util.*;

abstract class Shape {
    final double PI = 3.14;
    abstract public double getPerimeter();
    abstract public double getArea();
}

class Rectangle extends Shape {
    private int width;
    private int length;

    public Rectangle(int width, int length) {
        this.width = width;
        this.length = length;
    }

    public double getPerimeter() {
        return ((2.0 * this.length) + (2.0 * this.width));
    }

    public double getArea() {
        return (this.length * this.width * 1.0);
    }

    @Override
    public String toString() {
        return "Rectangle [" +
                "width=" + width +
                ", length=" + length +
                ']';
    }
}

class Circle extends Shape {
    private int radius;

    public Circle(int radius) {
        this.radius = radius;
    }

    public double getPerimeter() {
        return 2 * this.PI * this.radius;
    }

    public double getArea() {
        return this.PI * this.radius * this.radius;
    }

    @Override
    public String toString() {
        return "Circle [" +
                "radius=" + radius +
                ']';
    }
}

public class Main {
    public static double sumPerimeter(Shape[] data) {
        double sum = 0.0;
        for (int i=0; i<data.length; i++) {
            sum += data[i].getPerimeter();
        }
        return sum;
    }

    public static double sumArea(Shape[] data) {
        double sum = 0.0;
        for (int i=0; i<data.length; i++) {
            sum += data[i].getArea();
        }
        return sum;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        input.nextLine();
        Shape[] data = new Shape[n];
        for (int i=0; i<n; i++) {
            String user_type = input.nextLine();
            if(user_type.equals("rect")) {
                data[i] = new Rectangle(input.nextInt(), input.nextInt());
                input.nextLine();
            }
            else {
                data[i] = new Circle(input.nextInt());
                input.nextLine();
            }
        }
        System.out.println(sumPerimeter(data));
        System.out.println(sumArea(data));
        System.out.println(Arrays.toString(data));
        for (int i=0; i<data.length; i++) {
            System.out.println(data[i].getClass() + "," + data[i].getClass().getSuperclass());
        }
        input.close();
    }
}

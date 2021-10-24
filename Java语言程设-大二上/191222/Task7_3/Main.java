import java.util.*;
class Rectangle {
    private int width;
    private int length;

    public Rectangle(int width, int length) {
        this.width = width;
        this.length = length;
    }

    public int getPerimeter() {
        return ((2 * this.length) + (2 * this.width));
    }

    public int getArea() {
        return (this.length * this.width);
    }

    @Override
    public String toString() {
        return "Rectangle [" +
                "width=" + width +
                ", length=" + length +
                ']';
    }
}

class Circle {
    private int radius;

    public Circle(int radius) {
        this.radius = radius;
    }

    public int getPerimeter() {
        double ret = 2 * Math.PI * this.radius;
        return (int)ret;
    }

    public int getArea() {
        double ret = Math.PI * this.radius * this.radius;
        return (int)ret;
    }

    @Override
    public String toString() {
        return "Circle [" +
                "radius=" + radius +
                ']';
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int per_sum=0, area_sum=0;
        Rectangle[] recs = new Rectangle[2];
        for(int i=0; i<2; i++) {
            recs[i] = new Rectangle(input.nextInt(), input.nextInt());
            per_sum += recs[i].getPerimeter();
            area_sum += recs[i].getArea();
        }
        Circle[] cirs = new Circle[2];
        for(int i=0; i<2; i++) {
            cirs[i] = new Circle(input.nextInt());
            per_sum += cirs[i].getPerimeter();
            area_sum += cirs[i].getArea();
        }
        System.out.println(per_sum);
        System.out.println(area_sum);
        System.out.println(Arrays.deepToString(recs));
        System.out.println(Arrays.deepToString(cirs));
        input.close();
    }
}

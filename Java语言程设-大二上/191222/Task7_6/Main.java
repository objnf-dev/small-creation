// Thanks to E99plant
import java.text.DecimalFormat;
import java.util.*;

public class Main {


    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        ArrayList<Person> personList = new ArrayList<>();
        while (input.hasNext()) {
            String op = input.next();
            if (op.equals("s")) {
                personList.add(new Student(input.next(), input.nextInt(), input.nextBoolean(), input.next(), input.next()));
            }else if(op.equals("e")){
                personList.add(new Employee(input.next(), input.nextInt(), input.nextBoolean(), input.nextDouble(), new Company(input.next())));
            }else{
                break;
            }
        }

        personList.sort(Comparator.comparing(Person::getName).thenComparingInt(Person::getAge));
        for (Person person : personList) {
            System.out.println(person.toString());
        }

        if(input.next().equals("exit")){
            return;
        }

        ArrayList<Student> stuList = new ArrayList<>();
        ArrayList<Employee> empList = new ArrayList<>();
        for (Person person : personList) {
            if (person instanceof Student) {
                if (!stuList.contains((Student) person)) {
                    stuList.add((Student) person);
                }
            }

            if (person instanceof Employee) {
                if (!empList.contains((Employee) person)) {
                    empList.add((Employee) person);
                }
            }
        }

        System.out.println("stuList");
        for (Student student : stuList) {
            System.out.println(student.toString());
        }
        System.out.println("empList");
        for (Employee employee : empList) {
            System.out.println(employee.toString());
        }
        input.close();
    }
}

abstract class Person {
    protected String name;
    protected int age;
    protected boolean gender;

    public Person(String name, int age, boolean gender) {
        this.name = name;
        this.age = age;
        this.gender = gender;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public String toString() {
        return String.format("%s-%d-%s", this.name, this.age, this.gender);
    }

    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        else if (obj instanceof Person) {
            Person p = (Person) obj;
            return p.name.equals(this.name) && p.gender == this.gender && p.age == this.age;
        }
        return false;
    }
}

class Student extends Person {
    protected String stuNo;
    protected String clazz;

    public Student(String name, int age, boolean gender, String stuNo, String clazz) {
        super(name, age, gender);
        this.stuNo = stuNo;
        this.clazz = clazz;
    }

    @Override
    public String toString() {
        return "Student:" + super.toString() + String.format("-%s-%s", this.stuNo, this.clazz);
    }

    @Override
    public boolean equals(Object obj) {
        if (!super.equals(obj)) {
            return false;
        }
        else if (obj instanceof Student) {
            Student s = (Student) obj;
            return s.clazz.equals(this.clazz) && s.stuNo.equals(this.stuNo);
        }
        return false;
    }
}

class Company {
    private String name;

    public Company(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return this.name;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        else if (obj instanceof Company) {
            Company c = (Company) obj;
            if (c.name == null) {
                return false;
            }
            return c.name.equals(this.name);
        }
        return false;
    }
}

class Employee extends Person {
    private Company company;
    private double salary;

    public Employee(String name, int age, boolean gender, double salary, Company company) {
        super(name, age, gender);
        this.salary = salary;
        this.company = company;
    }

    @Override
    public String toString() {
        return "Employee:" + super.toString() + String.format("-%s-%s", this.company, this.salary);
    }

    @Override
    public boolean equals(Object obj) {
        if (!super.equals(obj)) {
            return false;
        }
        else if (obj instanceof Employee) {
            Employee e = (Employee) obj;
            if (this.company == null || e.company == null) {
                return false;
            }
            return e.company.equals(this.company) &&
                    new DecimalFormat(String.format("%.1f", e.salary)).equals(new DecimalFormat(String.format("%.1f", this.salary)));
        }
        return false;
    }
}
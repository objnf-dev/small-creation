import java.util.*;
class PersonOverride {
    private String name;
    private int age;
    private boolean gender;

    public PersonOverride() {
        this("default", 1, true);
    }

    public PersonOverride(String name, int age, boolean gender) {
        this.name = name;
        this.age = age;
        this.gender = gender;
    }

    @Override
    public String toString() {
        return this.name + "-" + this.age + "-" + this.gender;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj instanceof PersonOverride) {
            PersonOverride tmp = (PersonOverride)obj;
            if (this.age == tmp.age && this.gender == tmp.gender && this.name.equals(tmp.name)) {
                return true;
            }
        }
        return false;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        ArrayList<PersonOverride> persons1 = new ArrayList<>();
        int n = input.nextInt();
        for (int i=0; i<n; i++) {
            persons1.add(new PersonOverride());
        }
        ArrayList<PersonOverride> persons2 = new ArrayList<>();
        n = input.nextInt();
        for (int i=0; i<n; i++) {
            PersonOverride tmp = new PersonOverride(input.next(), input.nextInt(), input.nextBoolean());
            if (!persons2.contains(tmp)) {
                persons2.add(tmp);
            }
        }
        Iterator<PersonOverride> it = persons1.iterator();
        while (it.hasNext()) {
            PersonOverride tmp = it.next();
            System.out.println(tmp.toString());
        }
        it = persons2.iterator();
        while (it.hasNext()) {
            PersonOverride tmp = it.next();
            System.out.println(tmp.toString());
        }
        System.out.println(persons2.size());
        System.out.println(Arrays.toString(PersonOverride.class.getConstructors()));
        input.close();
    }
}

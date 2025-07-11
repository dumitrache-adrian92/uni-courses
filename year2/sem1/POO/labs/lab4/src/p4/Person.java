package p4;

public class Person {
    private String name;
    private String address;

    public Person() {
        this("Unknown", "Unknown");
    }

    public Person(String name, String address) {
        this.name = name;
        this.address = address;
    }

    public String getAddress() {
        return address;
    }

    public String getName() {
        return name;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String toString() {
        return "Person{" +
                "name='" + name + '\n' +
                ", address='" + address + '\n' +
                '}';
    }
}

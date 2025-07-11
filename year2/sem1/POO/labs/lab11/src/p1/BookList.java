package p1;

import javax.swing.*;
import java.awt.*;
import java.util.Vector;

public class BookList extends JFrame {
    JList<Book> books;
    JScrollPane scroller;

    public BookList(Vector<Book> input) {
        super();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 250);

        books = new JList<>(input);

        scroller = new JScrollPane(books);
        books.setLayoutOrientation(JList.VERTICAL);

        scroller.setSize(500, 250);

        add(scroller, BorderLayout.CENTER);

        setVisible(true);
    }

    public static void main(String[] args) {
        Vector<Book> books = new Vector<>();
        books.add(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.add(new Book("Safe C", "null", ""));
        books.add(new Book("Java for Pythons", "spam", ""));
        books.add(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.add(new Book("Safe C", "null", ""));
        books.add(new Book("Java for Pythons", "spam", ""));
        books.add(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.add(new Book("Safe C", "null", ""));
        books.add(new Book("Java for Pythons", "spam", ""));
        books.add(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.add(new Book("Safe C", "null", ""));
        books.add(new Book("Java for Pythons", "spam", ""));
        books.add(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.add(new Book("Safe C", "null", ""));
        books.add(new Book("Java for Pythons", "spam", ""));
        books.add(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.add(new Book("Safe C", "null", ""));
        books.add(new Book("Java for Pythons", "spam", ""));
        books.add(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.add(new Book("Safe C", "null", ""));
        books.add(new Book("Java for Pythons", "spam", ""));
        books.add(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.add(new Book("Safe C", "null", ""));
        books.add(new Book("Java for Pythons", "spam", ""));
        books.add(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.add(new Book("Safe C", "null", ""));
        books.add(new Book("Java for Pythons", "spam", ""));
        BookList test = new BookList(books);
    }
}
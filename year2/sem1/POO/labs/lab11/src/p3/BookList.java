package p3;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class BookList extends JFrame implements ListSelectionListener, ActionListener {
    JList<Book> books;
    JScrollPane scroller;
    JLabel nameLabel, authorLabel;
    JTextField name, author;
    JButton delete;

    public BookList(DefaultListModel<Book> input) {
        super();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(500, 250);

        // setup JList scrollable
        books = new JList<>(input);
        books.setLayoutOrientation(JList.VERTICAL);

        scroller = new JScrollPane(books);
        scroller.setSize(300, 250);

        // setup field de nume
        nameLabel = new JLabel("Name:");
        name = new JTextField();
        name.setEditable(false);
        JPanel namePanel = new JPanel();
        namePanel.setLayout(new GridLayout(1, 2));
        namePanel.add(nameLabel);
        namePanel.add(name);
        name.setSize(500, 50);

        // setup field de autor
        authorLabel = new JLabel("Author:");
        author = new JTextField();
        author.setEditable(false);
        JPanel authorPanel = new JPanel();
        authorPanel.setLayout(new GridLayout(1, 2));
        authorPanel.add(authorLabel);
        authorPanel.add(author);
        author.setSize(500, 50);

        delete = new JButton("Delete");

        JPanel right = new JPanel();
        right.setLayout(new GridLayout(3, 1));
        right.add(namePanel);
        right.add(authorPanel);
        right.add(delete);
        right.setSize(200, 250);

        add(scroller, BorderLayout.WEST);
        add(right, BorderLayout.EAST);

        books.addListSelectionListener(this);
        delete.addActionListener(this);

        //pack();
        setVisible(true);
    }

    @Override
    public void valueChanged(ListSelectionEvent e) {
        if(books.isSelectionEmpty())
            return;
        else {
            author.setText(books.getSelectedValue().getAuthor());
            name.setText(books.getSelectedValue().getName());
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() instanceof JButton) {
            if(books.isSelectionEmpty())
                return;
            else {
                ((DefaultListModel) books.getModel()).remove(books.getSelectedIndex());
                books.clearSelection();
                author.setText("");
                name.setText("");
            }
        }
    }

    public static void main(String[] args) {
        DefaultListModel<Book> books = new DefaultListModel<>();
        books.addElement(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.addElement(new Book("Safe C", "Vivec", ""));
        books.addElement(new Book("Java for Pythons", "Monty Python", ""));
        books.addElement(new Book("OOP", "Oduba", ""));
        books.addElement(new Book("Operating Systems", "Xi Xor", ""));
        books.addElement(new Book("Functional Programming", "Morgan Freeman", ""));
        books.addElement(new Book("Advanced D Programming", "Dumnezeu", ""));
        books.addElement(new Book("Safe C", "Vivec", ""));
        books.addElement(new Book("Java for Pythons", "Monty Python", ""));
        books.addElement(new Book("OOP", "Oduba", ""));
        books.addElement(new Book("Operating Systems", "Xi Xor", ""));
        books.addElement(new Book("Functional Programming", "Morgan Freeman", ""));

        BookList test = new BookList(books);
    }
}
package p6;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;

public class FileViewer extends JFrame implements ActionListener {
    JLabel title;
    JTextField input;
    JButton submit;
    JScrollPane result;
    JTextArea resultText;

    public FileViewer() {
        super("Problema 2");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("File Viewer 1923");
        setMinimumSize(new Dimension(300, 200));
        //getContentPane().setLayout(new FlowLayout());

        title = new JLabel("Path");

        input = new JTextField();
        input.setEditable(true);

        submit = new JButton("Submit");
        submit.addActionListener(this);

        resultText = new JTextArea();
        resultText.setEditable(false);
        resultText.setLineWrap(true);
        resultText.setWrapStyleWord(true);
        result = new JScrollPane(resultText);
        result.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        result.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        result.setPreferredSize(new Dimension(200, 100));

        JPanel rb=new JPanel();
        rb.setLayout(new GridLayout(1,3));
        rb.add(title);
        rb.add(input);
        rb.add(submit);

        add(rb, BorderLayout.NORTH);
        add(result, BorderLayout.SOUTH);

        pack();
        show();
        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() instanceof JButton) {
            File f = new File(input.getText());

            if(f.exists() && !f.isDirectory()) {
                try {
                    resultText.setText(Files.readAllLines(f.toPath(), StandardCharsets.UTF_8).toString());
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
                resultText.setPreferredSize(new Dimension(result.getPreferredSize().width, result.getPreferredSize().width));
                show();
            }
        }
    }

    public static void main(String[] args) {
        FileViewer test = new FileViewer();
    }

}

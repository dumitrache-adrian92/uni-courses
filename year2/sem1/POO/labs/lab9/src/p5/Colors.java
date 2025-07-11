package p5;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.util.Vector;

public class Colors extends JFrame implements ActionListener {
    JButton changer;
    Vector colors;
    int currentBackgroundColor;
    int currentForegroundColor;

    public Colors() {
        super();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new FlowLayout());

        colors = new Vector<Color>();
        colors.add(Color.BLUE);
        colors.add(Color.GREEN);
        colors.add(Color.RED);
        colors.add(Color.MAGENTA);
        currentBackgroundColor = -1;
        currentForegroundColor = 0;

        changer = new JButton("Colors");
        changer.addActionListener(this);
        changer.setEnabled(true);
        changer.setMnemonic(KeyEvent.VK_C);

        add(changer, BorderLayout.CENTER);

        setSize(100, 100);
        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() instanceof JButton) {
            if (currentBackgroundColor + 1 == colors.size())
                currentBackgroundColor = 0;
            else
                currentBackgroundColor++;

            if (currentForegroundColor + 1 == colors.size())
                currentForegroundColor = 0;
            else
                currentForegroundColor++;

            ((JButton) e.getSource()).setBackground((Color) colors.get(currentBackgroundColor));
            ((JButton) e.getSource()).setForeground((Color) colors.get(currentForegroundColor));
        }
    }

    public static void main(String[] args) {
        Colors test = new Colors();
    }
}

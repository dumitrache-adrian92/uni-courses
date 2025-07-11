package p4;

import org.w3c.dom.events.Event;
import org.w3c.dom.events.EventListener;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RGB extends JFrame implements ChangeListener {
    JSlider red, green, blue;
    JTextField color;

    public RGB() {
        super();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        red = new JSlider(JSlider.HORIZONTAL, 0, 255, 0);
        green = new JSlider(JSlider.HORIZONTAL, 0, 255, 0);
        blue = new JSlider(JSlider.HORIZONTAL, 0, 255, 0);
        red.addChangeListener(this);
        green.addChangeListener(this);
        blue.addChangeListener(this);

        color = new JTextField();
        color.setEditable(false);

        JPanel rb = new JPanel();
        rb.setLayout(new GridLayout(1,3));
        rb.add(red);
        rb.add(green);
        rb.add(blue);
        add(rb, BorderLayout.CENTER);
        add(color, BorderLayout.SOUTH);

        pack();
        setVisible(true);
    }

    public void stateChanged(ChangeEvent e) {
        if (e.getSource() instanceof JSlider) {
            color.setBackground(new Color(red.getValue(), green.getValue(), blue.getValue()));
        }
    }

    public static void main(String[] args) {
        RGB test = new RGB();
    }
}

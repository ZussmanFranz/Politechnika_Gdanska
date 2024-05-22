package Abstractions;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Field extends JPanel {
    Point position;
    Dimension fieldSize;
    Point id;
    Organism member;

    public Field(Point position, Dimension fieldSize, Point id, Organism member) {
        this.position = position;
        this.fieldSize = fieldSize;
        this.id = id;
        this.member = member;

        // Set the size of the panel
        setPreferredSize(fieldSize);
        // Set the background color to black
        //setBackground(Color.BLACK);
        setFocusable(true);

        // Add mouse listener for click events
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                handleClickEvent(e);
            }
        });
    }

    private void handleClickEvent(MouseEvent e) {
        System.out.println("Field clicked at: " + id);
        // Add additional logic for click event if needed
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        drawBox(g);
    }

    public void drawBox(Graphics g) {
        g.setColor(Color.BLACK);
        g.fillRect(position.x, position.y, fieldSize.width + 10, fieldSize.height + 10);

        // Set the color based on the member type
        if (member != null) {
            switch (member.getClassType()) {
                case ANIMAL:
                    g.setColor(Color.RED);
                    break;
                case PLANT:
                    g.setColor(Color.GREEN);
                    break;
                case PLAYER:
                    g.setColor(Color.YELLOW);
                    break;
                default:
                    g.setColor(Color.WHITE);
                    break;
            }
        } else {
            g.setColor(Color.WHITE);
        }

        g.drawRect(position.x, position.y, fieldSize.width, fieldSize.height);

        // Reset color
        if (member != null) {
            g.setColor(Color.WHITE);
        }
    }

    public Organism getMember() {
        return member;
    }

    public void setMember(Organism member) {
        this.member = member;
        repaint(); // Repaint to update the field with the new member
    }

    public Point getId() {
        return id;
    }
}

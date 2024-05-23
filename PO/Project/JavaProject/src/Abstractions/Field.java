package Abstractions;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Field extends JButton {
    Point position;
    Dimension fieldSize;
    Dimension padding;
    Point id;
    Organism member;

    boolean clicked;

    public Field(Point position, Dimension fieldSize, Dimension padding, Point id, Organism member) {
        this.position = position;
        this.fieldSize = fieldSize;
        this.padding = padding;
        this.id = id;
        this.member = member;

        // Set the size of the panel
        setPreferredSize(fieldSize);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        drawBox(g);
    }

    public void drawBox(Graphics g) {
        g.setColor(Color.BLACK);
        g.fillRect(position.x, position.y, fieldSize.width + padding.width, fieldSize.height + padding.height);

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
            if (clicked) {
                g.setColor(Color.CYAN);
            }
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

    public void setClicked() {
        this.clicked = true;
    }
}

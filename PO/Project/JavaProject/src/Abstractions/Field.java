package Abstractions;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class Field {
    Point position;
    Dimension fieldSize;
    Point id;
    Organism member;

    public Field(Point position, Dimension fieldSize, Point id, Organism member) {
        this.position = position;
        this.fieldSize = fieldSize;
        this.id = id;
        this.member = member;
    }

    public void drawBox(Graphics g) {
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
                    break;
            }
        }

        g.drawRect(position.x, position.y, fieldSize.width, fieldSize.height);
        g.drawLine(position.x, position.y, position.x + fieldSize.width, position.y);
        g.drawLine(position.x, position.y, position.x, position.y + fieldSize.height);
        g.drawLine(position.x + fieldSize.width, position.y, position.x + fieldSize.width, position.y + fieldSize.height);
        g.drawLine(position.x, position.y + fieldSize.height, position.x + fieldSize.width, position.y + fieldSize.height);

        if (member != null) {
            g.setColor(Color.BLACK); // Reset color
        }
    }

    public Organism getMember() {
        return member;
    }

    public void setMember(Organism member) {
        this.member = member;
    }

    public Point getId() {
        return id;
    }
}


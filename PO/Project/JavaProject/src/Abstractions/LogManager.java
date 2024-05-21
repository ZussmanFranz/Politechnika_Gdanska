package Abstractions;

import Animals.*;
import Plants.*;

import java.awt.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import java.text.SimpleDateFormat;
import java.util.List;

public class LogManager {
    private String filepath;
    private PrintWriter logFile;
    private JTextArea logArea;

    public LogManager(String filepath, int width, int height) {
        this.filepath = filepath;
        try {
            logFile = new PrintWriter(new FileWriter(filepath, false), true);
            logFile.println("---!log started!---");
        } catch (IOException e) {
            System.err.println("Error: Unable to open log file for writing.");
        }

        logArea = new JTextArea(height, width);
        logArea.setEditable(false);

        JFrame frame = new JFrame("Log");
        frame.add(new JScrollPane(logArea), BorderLayout.CENTER);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);

        logF(LogMessageType.TECHNICAL, "---!log started!---\n\n");
    }

    public String getEntityName(Organism entity) {
        if (entity instanceof Player) return "player";
        else if (entity instanceof Wolf) return "wolf";
        else if (entity instanceof Sheep) return "sheep";
        else if (entity instanceof Fox) return "fox";
        else if (entity instanceof Turtle) return "turtle";
        else if (entity instanceof Antelope) return "antelope";
        else if (entity instanceof Grass) return "grass";
        else if (entity instanceof Mlecz) return "mlecz";
        else if (entity instanceof Guarana) return "guarana";
        else if (entity instanceof Wolfberry) return "wolfberry";
        else if (entity instanceof Hogweed) return "hogweed";
        else return "ERROR";
    }

    public void log(String prompt) {
        if (logFile == null) return;
        logFile.println(prompt);
        logF(LogMessageType.WARNING, prompt + "\n\n");
    }

    public void logF(LogMessageType type, String prompt, Object... args) {
        String formattedMessage = String.format(prompt, args);
        logArea.append(formattedMessage);
        //logFile.println(formattedMessage);
    }

    public void logTime() {
        if (logFile == null) return;
        String time = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
        logFile.println("Current time is " + time + "\n\n");
        logF(LogMessageType.WARNING, "Current time is " + time + "\n\n");
    }

    public void logCreation(Organism created) {
        if (logFile == null) return;
        String message = String.format("Created %s at y = %d and x = %d",
                getEntityName(created), created.getPosition().y, created.getPosition().x);
        logFile.println(message);
        logF(LogMessageType.SPAWN, message + "\n\n");
    }

    public void logCollision(Organism attacker, Organism prey) {
        if (logFile == null) return;
        String attackerName = getEntityName(attacker);
        String preyName = getEntityName(prey);

        String message = String.format("Fight log: %s vs %s\nLocation: y = %d, x = %d\nRound: %d\n%s strength = %d, %s strength = %d",
                attackerName, preyName, prey.getPosition().y, prey.getPosition().x,
                attacker.getWorld().getRound(), attackerName, attacker.getStrength(), preyName, prey.getStrength());
        logFile.println(message);
        logF(LogMessageType.FIGHT, "Fight: %s vs %s (%d | %d)\n",
                attackerName, preyName, attacker.getStrength(), prey.getStrength());
    }

    public void logCollisionResult(Organism winner) {
        if (logFile == null) return;
        String message = String.format("The winner is %s\n\n", getEntityName(winner));
        logFile.println(message);
    }

    public void logReproductionCollision(Organism parent1, Organism parent2) {
        if (logFile == null) return;
        String message = String.format("%s and %s now have a child!\n\n",
                getEntityName(parent1), getEntityName(parent2));
        logFile.println(message);
    }

    public void logOrder(List<Organism> members) {
        if (logFile == null) return;
        logFile.println("The New Order:");
        for (int i = 0; i < members.size(); i++) {
            logFile.println(i + ") " + getEntityName(members.get(i)));
        }
        logFile.println();
    }

    public void logStrengthIncrease(Organism luckyOne) {
        if (logFile == null) return;
        String message = String.format("Strength of the %s has been increased by 3, new strength is %d",
                getEntityName(luckyOne), luckyOne.getStrength());
        logFile.println(message);
        logF(LogMessageType.ABILITY, message + "\n\n");
    }

    public void logOverpopulation(Organism unluckyOne, int neighbours) {
        if (logFile == null) return;
        String message = String.format("%s has died because of overpopulation, it had %d neighbours\n\n",
                getEntityName(unluckyOne), neighbours);
        logFile.println(message);
    }

    public void necroLog(Organism rip) {
        if (logFile == null) return;
        String message = String.format("%s is dead :( It was %d rounds old.\n\n",
                getEntityName(rip), rip.getWorld().getRound() - rip.getBirth());
        logFile.println(message);
        logF(LogMessageType.DEATH, "%s died at (y = %d, x = %d), it was %d rounds old.\n\n",
                getEntityName(rip), rip.getPosition().y, rip.getPosition().x, rip.getWorld().getRound() - rip.getBirth());
    }

    public void close() {
        if (logFile != null) {
            logFile.println("---!log ended!---");
            logFile.close();
        }
    }

    public JTextArea getLogArea() {
        return logArea;
    }

    public enum LogMessageType {
        NORMAL(Color.BLACK),
        DEATH(Color.RED),
        SPAWN(Color.GREEN),
        FIGHT(Color.ORANGE),
        WARNING(Color.CYAN),
        ABILITY(Color.BLUE),
        TECHNICAL(Color.MAGENTA);

        private final Color color;

        LogMessageType(Color color) {
            this.color = color;
        }

        public Color getColor() {
            return color;
        }
    }
}

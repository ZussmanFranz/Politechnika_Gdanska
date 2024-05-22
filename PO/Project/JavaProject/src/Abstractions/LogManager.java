package Abstractions;

import Animals.*;
import Plants.*;

import java.awt.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.List;
import javax.swing.*;

public class LogManager extends JTextArea {
    public LogManager(int width, int height) {
        super(height, width);
        setEditable(false);
        append("---!log started!---\n\n");
        setFocusable(false);
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
        append(prompt + "\n\n");
    }

    public void logF(LogMessageType type, String prompt, Object... args) {
        String formattedMessage = String.format(prompt, args);
        append(formattedMessage);
    }

    public void logTime() {
        String time = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
        logF(LogMessageType.WARNING, "Current time is " + time + "\n\n");
    }

    public void logCreation(Organism created) {
        String message = String.format("Created %s at y = %d and x = %d",
                getEntityName(created), created.getPosition().y, created.getPosition().x);
        logF(LogMessageType.SPAWN, message + "\n\n");
    }

    public void logCollision(Organism attacker, Organism prey) {
        String attackerName = getEntityName(attacker);
        String preyName = getEntityName(prey);

        String message = String.format("Fight log: %s vs %s\nLocation: y = %d, x = %d\nRound: %d\n%s strength = %d, %s strength = %d",
                attackerName, preyName, prey.getPosition().y, prey.getPosition().x,
                attacker.getWorld().getRound(), attackerName, attacker.getStrength(), preyName, prey.getStrength());
        logF(LogMessageType.FIGHT, "Fight: %s vs %s (%d | %d)\n",
                attackerName, preyName, attacker.getStrength(), prey.getStrength());
    }

    public void logCollisionResult(Organism winner) {
        String message = String.format("The winner is %s\n\n", getEntityName(winner));
        log(message);
    }

    public void logReproductionCollision(Organism parent1, Organism parent2) {
        String message = String.format("%s and %s now have a child!\n\n",
                getEntityName(parent1), getEntityName(parent2));
        log(message);
    }

    public void logOrder(List<Organism> members) {
        log("The New Order:");
        for (int i = 0; i < members.size(); i++) {
            log(i + ") " + getEntityName(members.get(i)));
        }
        log("");
    }

    public void logStrengthIncrease(Organism luckyOne) {
        String message = String.format("Strength of the %s has been increased by 3, new strength is %d",
                getEntityName(luckyOne), luckyOne.getStrength());
        logF(LogMessageType.ABILITY, message + "\n\n");
        System.out.println(luckyOne.getStrength() + " > " + luckyOne.getStartingStrength());
    }

    public void logOverpopulation(Organism unluckyOne, int neighbours) {
        String message = String.format("%s has died because of overpopulation, it had %d neighbours\n\n",
                getEntityName(unluckyOne), neighbours);
        log(message);
    }

    public void necroLog(Organism rip) {
        String message = String.format("%s is dead :( It was %d rounds old.\n\n",
                getEntityName(rip), rip.getWorld().getRound() - rip.getBirth());
        logF(LogMessageType.DEATH, "%s died at (y = %d, x = %d), it was %d rounds old.\n\n",
                getEntityName(rip), rip.getPosition().y, rip.getPosition().x, rip.getWorld().getRound() - rip.getBirth());
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

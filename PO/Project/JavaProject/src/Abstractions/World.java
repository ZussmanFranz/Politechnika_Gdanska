package Abstractions;

import Animals.*;
import Plants.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class World extends JPanel implements ActionListener {
    private List<Organism> members;
    private Field[][] fields;
    private Dimension dimensions;
    private Dimension fieldSize;
    private Point padding;
    private int round;
    private boolean end;
    private int updateOrder;
    private LogManager logger;
    private int windowWidth;
    private int windowHeight;
    private JFrame frame;

    public World(String filepath) {
        this(12, 12);
        load(filepath);
    }

    public World(int y, int x) {
        this.dimensions = new Dimension(x, y);
        this.fieldSize = new Dimension(30, 50);
        this.padding = new Point(0, 10);
        this.members = new ArrayList<>();
        this.round = 0;
        this.end = false;
        this.updateOrder = 0;

        this.frame = new JFrame("World Simulation");
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.frame.setSize(new Dimension(800, 600));
        this.frame.add(this);
        this.frame.setVisible(true);

        this.logger = new LogManager("log.txt");
        initializeFields();
    }

    private void initializeFields() {
        this.fields = new Field[dimensions.height][dimensions.width];
        for (int i = 0; i < dimensions.height; i++) {
            for (int j = 0; j < dimensions.width; j++) {
                Point position = new Point(
                        j * (fieldSize.width + padding.x),
                        i * (fieldSize.height + padding.y)
                );
                fields[i][j] = new Field(position, fieldSize, new Point(j, i), null);
            }
        }
        generateRandomStart((dimensions.width * dimensions.height) / 12);
        sortMembers();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        draw(g);
    }

    private void draw(Graphics g) {
        drawInterface(g);
        for (Field[] row : fields) {
            for (Field field : row) {
                field.drawBox(g);
                if (field.member != null) {
                    field.member.draw(g, field.position, fieldSize);
                }
            }
        }
    }

    private void drawInterface(Graphics g) {
        g.drawString("Round: " + round, windowWidth / 2 - 50, 20);
        g.drawString("Yauheni Pyryeu 201253 project", windowWidth / 2 - 150, 40);
        g.drawString("q - quit, e - ability, w a s d - controls", 10, windowHeight - 20);
    }

    public void actionPerformed(ActionEvent e) {
        // Handle game actions here
    }

    public void update() {
        round++;
        for (int i = 0; i < members.size(); i++) {
            if (members.size() <= 1) {
                end = true;
            }
            if (end) {
                drawEndscreen();
                return;
            }
            if (updateOrder > 0 && updateOrder < members.size()) {
                i = updateOrder;
                updateOrder = 0;
            }
            members.get(i).action();
        }
        clean();
        repaint();
    }

    public void add(Organism added) {
        added.setBirth(round);
        members.add(added);
        findField(added.getPosition()).setMember(added);
        sortMembers();
        logger.logCreation(added);
    }

    public void destroy(Organism destroyed) {
        logger.necroLog(destroyed);
        findField(destroyed.getPosition()).setMember(null);
        members.remove(destroyed);
        sortMembers();
    }

    public void sortMembers() {
        members.sort(Comparator.comparingInt(Organism::getInitiative)
                .thenComparingInt(Organism::getBirth).reversed());
    }

    public void stop() {
        this.end = true;
    }

    public Dimension getDimensions()
    {
        return dimensions;
    }

    public Field findField(Point id) {
        if (id.y < dimensions.height && id.y >= 0 && id.x < dimensions.width && id.x >= 0) {
            return fields[id.y][id.x];
        } else {
            return null;
        }
    }

    public List<Field> getFieldsNear(Point position)
    {
        List<Field> near = new ArrayList<>();

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if ((i == 0) && (j == 0)) {
                    continue;
                }

                Point target_point = new Point(position.x + j, position.y + i);
                Field target = findField(target_point);

                if (target != null) {
                    near.add(target);
                }
            }
        }

        return near;
    }

    public int getRound() {
        return round;
    }

    public LogManager getLogger() {
        return logger;
    }

    public Field getRandomField() {
        List<Field> freeFields = new ArrayList<>();
        for (Field[] row : fields) {
            for (Field field : row) {
                if (field.getMember() == null) {
                    freeFields.add(field);
                }
            }
        }
        if (freeFields.isEmpty()) {
            return null;
        } else {
            return freeFields.get(ThreadLocalRandom.current().nextInt(freeFields.size()));
        }
    }

    public Field getFreeFieldNear(Point position) {
        List<Field> freeFields = new ArrayList<>();
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (i == 0 && j == 0) continue;
                Field target = findField(new Point(position.x + j, position.y + i));
                if (target != null && target.member == null) {
                    freeFields.add(target);
                }
            }
        }
        if (freeFields.isEmpty()) {
            return null;
        } else {
            return freeFields.get(ThreadLocalRandom.current().nextInt(freeFields.size()));
        }
    }

    public boolean sameType(Organism a, Organism b) {
        // Check if both references are non-null
        if (a != null && b != null) {
            // Compare the runtime types of the objects
            return a.getClass() == b.getClass();
        }
        return false;
    }

    public void generateRandomStart(int numberOfOrganisms) {
        for (int i = 0; i < numberOfOrganisms; i++) {
            generateRandomOrganism(ThreadLocalRandom.current().nextInt(1, 3), ThreadLocalRandom.current().nextInt(1, 6));
        }
    }

    public void generateRandomOrganism(int type, int subType) {
        Field randomField = getRandomField();
        if (randomField == null) {
            System.out.println("There is no free field!");
            return;
        }
        Organism organism = null;
        switch (type) {
            case 1:
                organism = switch (subType) {
                    case 1 -> new Wolf(this, randomField.id);
                    case 2 -> new Sheep(this, randomField.id);
                    case 3 -> new Fox(this, randomField.id);
                    case 4 -> new Turtle(this, randomField.id);
                    case 5 -> new Antelope(this, randomField.id);
                    default -> null;
                };
                break;
            case 2:
                organism = switch (subType) {
                    case 1 -> new Grass(randomField.id, this);
                    case 2 -> new Mlecz(randomField.id, this);
                    case 3 -> new Guarana(randomField.id, this);
                    case 4 -> new Wolfberry(randomField.id, this);
                    case 5 -> new Hogweed(randomField.id, this);
                    default -> null;
                };
                break;
        }
        if (organism != null) {
            add(organism);
        }
    }

    private void drawEndscreen() {
        JOptionPane.showMessageDialog(frame, "End of Game! Round: " + round + (getPlayer() != null ? " You have won!!" : " You have lost!"));
    }

    public Organism getPlayer() {
        for (Organism member : members) {
            if (member instanceof Player) {
                return (Player) member;
            }
        }
        return null;
    }

    public void clean() {
        for (int i = 0; i < members.size(); i++) {
            int neighbours = countNeighboursSameType(members.get(i));
            if (neighbours > 2) {
                logger.logOverpopulation(members.get(i), neighbours);
                destroy(members.get(i));
                i--;
            }
        }
    }

    public int countNeighboursSameType(Organism me) {
        int count = 0;
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (i == 0 && j == 0) continue;
                Field target = findField(new Point(me.getPosition().x + j, me.getPosition().y + i));
                if (target != null && target.member != null && target.member.getClass() == me.getClass()) {
                    count++;
                }
            }
        }
        return count;
    }

    public void save(String path) {
        try {
            FileWriter writer = new FileWriter(path);
            writer.write("{\"round\":" + round + ",\"dimensions\":{\"height\":" + dimensions.height + ",\"width\":" + dimensions.width + "},\"members\":");
            String json = new Gson().toJson(members);
            writer.write(json + "}");
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void load(String path) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            JsonObject jsonObject = new Gson().fromJson(br, JsonObject.class);
            this.round = jsonObject.get("round").getAsInt();
            JsonObject dims = jsonObject.getAsJsonObject("dimensions");
            this.dimensions = new Dimension(dims.get("width").getAsInt(), dims.get("height").getAsInt());
            initializeFields();
            JsonArray array = jsonObject.getAsJsonArray("members");
            for (JsonElement element : array) {
                JsonObject member = element.getAsJsonObject();
                Organism newMember = Organism.createFromJson(this, member);
                members.add(newMember);
                findField(newMember.getPosition()).member = newMember;
            }
            sortMembers();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

//    public static void main(String[] args) {
//        new World("path/to/your/file.json");
//    }
}
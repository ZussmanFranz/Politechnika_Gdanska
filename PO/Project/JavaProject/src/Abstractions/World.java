package Abstractions;

import Animals.*;
import Plants.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.*;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

public class World extends JPanel implements ActionListener {
    private List<Organism> members;
    private Field[][] fields;
    private Dimension dimensions;

    private Dimension window_size;
    private Dimension fieldSize;
    private Dimension padding;
    private int round;
    private boolean end;
    private int updateOrder;
    private LogManager logger;
    private int windowWidth;
    private int windowHeight;
    private JFrame frame;
    private KeyHandler keyHandler;

    private char playerDirection;

    public World(String filepath) {
        this(12, 12);
        load(filepath);
    }

    public World(int y, int x) {
        this.dimensions = new Dimension(x, y);
        this.fieldSize = new Dimension(30, 50);
        this.padding = new Dimension(10, 10);
        this.window_size = new Dimension(dimensions.width * (fieldSize.width + padding.width) + 100, dimensions.height * (fieldSize.height + padding.height) + 100);
        this.members = new ArrayList<>();
        this.round = 0;
        this.end = false;
        this.updateOrder = 0;

        this.frame = new JFrame("World Simulation");
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.frame.setSize(new Dimension(window_size.width + 480, window_size.height));
        this.frame.setLocationRelativeTo(null);
        //this.gamePanel = new GamePanel(x, y);
        //this.frame.add(gamePanel);
        //gamePanel.startGameThread();
        //this.frame.pack();

        // Set layout for the frame
        this.frame.setLayout(new BorderLayout());

        this.logger = new LogManager( 50, window_size.height / 240);
        this.frame.add(logger, BorderLayout.EAST);
        this.frame.add(new JScrollPane(logger), BorderLayout.EAST);
        this.frame.add(this, BorderLayout.CENTER);

        this.keyHandler = new KeyHandler();
        frame.addKeyListener(keyHandler);

        this.frame.setVisible(true);
        this.frame.setFocusable(true);
        this.frame.revalidate();
        this.frame.repaint();

        initializeFields();
    }


    private void initializeFields() {
        logger.log("Initialising fields...");
        this.fields = new Field[dimensions.height][dimensions.width];
        for (int i = 0; i < dimensions.height; i++) {
            for (int j = 0; j < dimensions.width; j++) {
                Point position = new Point(
                        j * (fieldSize.width + padding.width),
                        i * (fieldSize.height + padding.height)
                );
                fields[i][j] = new Field(position, fieldSize, new Point(j, i), null);
            }
        }

        logger.log("Initialised!\nAdding the player...");
        add(new Player(this, new Point(0,0)));

        logger.log("Added!\nGenerating random start...");
        generateRandomStart((dimensions.width * dimensions.height) / 12);

        logger.log("Generated!\nSorting members...");
        sortMembers();
        logger.log("Sorted!");
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        draw(g);
    }

    private void draw(Graphics g) {
        drawInterface(g); //?
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
//        g.drawString("Round: " + round, 200, 20);
//        g.drawString("Yauheni Pyryeu 201253 project", 200, 40);
//        g.drawString("q - quit, e - ability, w a s d - controls", 10, 200);
        System.out.println("Round " + (round + 1));
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

//            if (members.get(i) instanceof Player) {
//                // Wait for player's action
////                JOptionPane.showMessageDialog(null, "Player's turn!");
////                clean();
////                repaint();
//
////                try {
////                    Thread.sleep(50);
////                } catch (InterruptedException e) {
////                    e.printStackTrace();
////                }
////                playerDirection = ' ';
//                Player player = (Player) members.get(i);
//                try {
//                    player.action(keyHandler);
//                } catch (InterruptedException e) {
//                    throw new RuntimeException(e);
//                }
//            }
//            else {
                members.get(i).action();
//            }
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

    public boolean isOver() {
        return end;
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

    public List<Field> getFieldsNear(Point position){
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
    public KeyHandler getKeyHandler(){
        return keyHandler;
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
        Organism organism = switch (type) {
            case 1 -> switch (subType) {
                case 1 -> new Wolf(this, randomField.id);
                case 2 -> new Sheep(this, randomField.id);
                case 3 -> new Fox(this, randomField.id);
                case 4 -> new Turtle(this, randomField.id);
                case 5 -> new Antelope(this, randomField.id);
                default -> null;
            };
            case 2 -> switch (subType) {
                case 1 -> new Grass(this, randomField.id);
                case 2 -> new Mlecz(this, randomField.id);
                case 3 -> new Guarana(this, randomField.id);
                case 4 -> new Wolfberry(this, randomField.id);
                case 5 -> new Hogweed(this, randomField.id);
                default -> null;
            };
            default -> null;
        };
        if (organism != null) {
            add(organism);
        }
    }

    public void drawEndscreen() {
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
                char avatar = (char)(member.get("avatar").getAsInt());

                Organism entity = null;
                Point new_position = new Point();
                new_position.x = member.get("x").getAsInt(); // Assuming 'x' represents the x-coordinate of the position
                new_position.y = member.get("y").getAsInt();

                switch (avatar)
                {
                    case 'P':
                        entity = new Player(this,new_position);
                        break;
                    case 'W':
                        entity = new Wolf(this,new_position);
                        break;
                    case 'F':
                        entity = new Fox(this,new_position);
                        break;
                    case 'T':
                        entity = new Turtle(this,new_position);
                        break;
                    case 'A':
                        entity = new Antelope(this,new_position);
                        break;
                    case 'S':
                        entity = new Sheep(this,new_position);
                        break;
                    case 'g':
                        entity = new Grass(this, new_position);
                        break;
                    case 'u':
                        entity = new Guarana(this, new_position);
                        break;
                    case 'm':
                        entity = new Mlecz(this, new_position);
                        break;
                    case 'w':
                        entity = new Wolfberry(this, new_position);
                        break;
                    case 'h':
                        entity = new Hogweed(this, new_position);
                        break;
                    default:
                        break;
                }

                members.add(entity);
                findField(entity.getPosition()).setMember(entity);
            }
            sortMembers();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    public void clearWorld() {
        members.clear();
        frame.dispose();
    }

//    public static void main(String[] args) {
//        new World("path/to/your/file.json");
//    }
}
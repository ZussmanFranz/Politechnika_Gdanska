package Abstractions;

import Animals.*;
import Plants.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
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

public class World extends JPanel implements ActionListener, MouseListener {
    private List<Organism> members;
    private Field[][] fields;
    private Dimension dimensions;

    private Dimension window_size;
    private Dimension fieldSize;
    private Dimension padding;
    private int round;
    private int speed;
    private boolean end;
    private boolean loaded;
    private LogManager logger;
    private int windowWidth;
    private int windowHeight;
    private JFrame frame;
    private KeyHandler keyHandler;

    private char playerDirection;

    public World(String filepath) {
        this.dimensions = new Dimension(0, 0);
        this.fieldSize = new Dimension(48, 48);
        this.padding = new Dimension(10, 10);
        this.window_size = new Dimension(dimensions.width * (fieldSize.width + padding.width) + 100, dimensions.height * (fieldSize.height + padding.height) + 100);
        this.members = new ArrayList<>();
        this.round = 0;
        this.end = false;
        this.loaded = true;

        this.frame = new JFrame("World Simulation");
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.frame.setSize(new Dimension(window_size.width + 480, window_size.height));
        this.frame.setLocationRelativeTo(null);

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

        speed = 1;
        load(filepath);
        this.window_size = new Dimension(dimensions.width * (fieldSize.width + padding.width) + 100, dimensions.height * (fieldSize.height + padding.height) + 100);
        this.frame.setSize(new Dimension(window_size.width + 480, window_size.height));

        addMouseListener(this);
    }

    public World(int x, int y) {
        this.dimensions = new Dimension(x, y);
        this.fieldSize = new Dimension(48, 48);
        this.padding = new Dimension(10, 10);
        this.window_size = new Dimension(dimensions.width * (fieldSize.width + padding.width) + 100, dimensions.height * (fieldSize.height + padding.height) + 100);
        this.members = new ArrayList<>();
        this.round = 0;
        this.end = false;
        this.loaded = false;

        this.frame = new JFrame("World Simulation");
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.frame.setSize(new Dimension(window_size.width + 480, window_size.height));
        this.frame.setLocationRelativeTo(null);

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

        speed = 2;

        initializeFields();

        logger.log(LogManager.LogMessageType.NORMAL,"Adding the player...");
        add(new Player(this, new Point(0,0)));

        logger.log(LogManager.LogMessageType.NORMAL,"Added!\nGenerating random start...");
        generateEvenStart((dimensions.width * dimensions.height) / 12);

        logger.log(LogManager.LogMessageType.NORMAL,"Generated!\nSorting members...");
        sortMembers();
        logger.log(LogManager.LogMessageType.NORMAL,"Sorted!");

        addMouseListener(this);
    }

    public void mouseClicked(MouseEvent e) {
        // Get the coordinates of the mouse click
        int mouseX = e.getX();
        int mouseY = e.getY();

        // Calculate the clicked field based on mouse coordinates
        int fieldX = mouseX / (fieldSize.width + padding.width);
        int fieldY = mouseY / (fieldSize.height + padding.height);

        // Check if the clicked field is within the valid range
        if (fieldX >= 0 && fieldX < dimensions.width && fieldY >= 0 && fieldY < dimensions.height) {
            // Perform action based on the clicked field
            handleFieldClick(new Point(fieldX, fieldY));
            System.out.println("Clicked on {" + fieldX + ", " + fieldY + "} field");
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    private void handleFieldClick(Point clickedField) {
        // Implement your logic to handle the clicked field
        Field clickedFieldObject = fields[clickedField.y][clickedField.x];
        clickedFieldObject.setClicked();

        if (clickedFieldObject.getMember() == null) {
            JFrame addingFrame = new JFrame("add new entity!");
            addingFrame.setSize(500, 200);
            addingFrame.setLocationRelativeTo(null);

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel(new GridLayout(2, 5)); // Adjust the grid layout as needed

            // Create buttons for each type of animal and plant (excluding Player)
            JButton[] buttons = new JButton[10]; // Adjust the array size based on the number of types

            buttons[0] = new JButton("Wolf");
            buttons[1] = new JButton("Sheep");
            buttons[2] = new JButton("Fox");
            buttons[3] = new JButton("Turtle");
            buttons[4] = new JButton("Antelope");
            buttons[5] = new JButton("Grass");
            buttons[6] = new JButton("Mlecz");
            buttons[7] = new JButton("Guarana");
            buttons[8] = new JButton("Wolfberry");
            buttons[9] = new JButton("Hogweed");

            // Add action listeners to the buttons
            for (JButton button : buttons) {
                buttonPanel.add(button);
                button.addActionListener(e -> {
                    // Spawn the corresponding organism when the button is clicked
                    spawnOrganism(clickedField, button.getText());
                    addingFrame.dispose(); // Close the frame after spawning
                });
            }

            // Add the button panel to the frame
            addingFrame.add(buttonPanel);
            addingFrame.setVisible(true);
        }
    }



    private void initializeFields() {
        logger.log(LogManager.LogMessageType.NORMAL,"Initialising fields...");
        this.fields = new Field[dimensions.height][dimensions.width];
        for (int i = 0; i < dimensions.height; i++) {
            for (int j = 0; j < dimensions.width; j++) {
                Point position = new Point(
                        j * (fieldSize.width + padding.width),
                        i * (fieldSize.height + padding.height)
                );
                fields[i][j] = new Field(position, fieldSize, padding, new Point(j, i), null);
            }
        }
        logger.log(LogManager.LogMessageType.NORMAL,"Initialised!");
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        draw(g);
    }

    private void draw(Graphics g) {
        //drawInterface(g);
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
        speed = keyHandler.getSpeed();

        round++;
        for (int i = 0; i < members.size(); i++) {
            if (members.size() <= 1) {
                end = true;
            }
            if (getPlayer() == null){
                end = true;
            }
            if (end) {
                drawEndscreen();
                return;
            }
            if (loaded) {
                if (members.get(i) instanceof Player){
                    loaded = false;
                }
                else {
                    continue;
                }
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

    public void spawnOrganism(Point new_position, String entityType){
        Organism entity;

        switch (entityType)
        {
            case "Wolf":
                entity = new Wolf(this,new_position);
                break;
            case "Fox":
                entity = new Fox(this,new_position);
                break;
            case "Turtle":
                entity = new Turtle(this,new_position);
                break;
            case "Antelope":
                entity = new Antelope(this,new_position);
                break;
            case "Sheep":
                entity = new Sheep(this,new_position);
                break;
            case "Grass":
                entity = new Grass(this, new_position);
                break;
            case "Guarana":
                entity = new Guarana(this, new_position);
                break;
            case "Mlecz":
                entity = new Mlecz(this, new_position);
                break;
            case "Wolfberry":
                entity = new Wolfberry(this, new_position);
                break;
            case "Hogweed":
                entity = new Hogweed(this, new_position);
                break;
            default:
                entity = null;
                break;
        }

        if (entity != null){
            add(entity);
        }
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

    public void generateEvenStart(int numberOfOrganisms){
        int type = 1;
        int subtype = 1;
        int count = 0;

        while (count < numberOfOrganisms)
        {
            type = (type == 1) ? 2 : 1;

            if (count % 2 == 0)
            {
                subtype = (subtype >= 5) ? 1 : (subtype + 1);
            }

            generateRandomOrganism(type, subtype);
            count++;
        }

        return;
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
        String status = " You have won!!";
        if (getPlayer() == null)
        {
            status = " You have died.";
        } else if (members.size() > 1) {
            status = " Saving...";
        }
        JOptionPane.showMessageDialog(frame, "End of Game! Round: " + round + status);
    }

    public Organism getPlayer() {
        for (Organism member : members) {
            if (member instanceof Player) {
                return (Player) member;
            }
        }
        return null;
    }

    public int getSpeed(){
        return speed;
    }

    public void clean() {
        int current_type_counter = 0;
        Class<?> prev_type = null;

        for (int i = 0; i < members.size(); i++) {
            Class<?> current_type = members.get(i).getClass();
            if (current_type.equals(prev_type)) {
                current_type_counter++;
            } else {
                // If the current type is different from the previous type, reset the counter
                prev_type = current_type;
                current_type_counter = 1; // Start counting from 1 for the current type
            }

            int neighbours = countNeighboursSameType(members.get(i));
            if (neighbours > 2 || current_type_counter > 6) {
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
                if (i == 0 && j == 0) {
                    continue;
                }
                Field target = findField(new Point(me.getPosition().x + j, me.getPosition().y + i));
                if (target != null && target.member != null && target.member.getClass() == me.getClass()) {
                    count++;
                }
            }
        }
        return count;
    }

    public void save(String path) {
        System.out.println("Saving at " + path + "...");
        FileWriter writer = null;
        try {
            writer = new FileWriter(path);
            JsonObject jsonObject = new JsonObject();
            jsonObject.addProperty("round", round);
            JsonObject dimensionsObject = new JsonObject();
            dimensionsObject.addProperty("height", dimensions.height);
            dimensionsObject.addProperty("width", dimensions.width);
            jsonObject.add("dimensions", dimensionsObject);

            // Convert members to JSON
            JsonArray membersArray = new JsonArray();
            for (Organism member : members) {
                JsonObject memberObject = new JsonObject();
                memberObject.addProperty("avatar", member.getAvatar());
                JsonObject positionObject = new JsonObject();
                positionObject.addProperty("x", member.getPosition().x);
                positionObject.addProperty("y", member.getPosition().y);
                memberObject.add("position", positionObject);
                memberObject.addProperty("strength", member.getStrength());
                membersArray.add(memberObject);
            }
            jsonObject.add("members", membersArray);

            // Write JSON to file
            new Gson().toJson(jsonObject, writer);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (writer != null) {
                    writer.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void load(String path) {
        System.out.println("Loading from " + path + "...");
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            JsonObject jsonObject = new Gson().fromJson(br, JsonObject.class);
            this.round = jsonObject.get("round").getAsInt();
            //System.out.println("round: " + round);
            JsonObject dims = jsonObject.getAsJsonObject("dimensions");
            this.dimensions = new Dimension(dims.get("width").getAsInt(), dims.get("height").getAsInt());
            //System.out.println("dimensions: width = " + dimensions.width + ", height = " + dimensions.height);
            initializeFields();
            JsonArray array = jsonObject.getAsJsonArray("members");
            for (JsonElement element : array) {
                //System.out.println("New entity... " + round);
                JsonObject member = element.getAsJsonObject();
                char avatar = member.get("avatar").getAsString().charAt(0);
                //System.out.println("avatar: " + avatar);
                int new_strength = member.get("strength").getAsInt();
                //System.out.println("strength: " + new_strength);

                Organism entity = null;
                Point new_position = new Point();
                JsonObject positionObject = member.get("position").getAsJsonObject();
                new_position.x = positionObject.get("x").getAsInt(); // Assuming 'x' represents the x-coordinate of the position
                new_position.y = positionObject.get("y").getAsInt();
                //System.out.println("position: x = " + new_position.x + " y = " + new_position.y);

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

                entity.setStrength(new_strength);
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
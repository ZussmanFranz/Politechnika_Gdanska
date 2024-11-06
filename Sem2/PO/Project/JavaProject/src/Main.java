import Abstractions.*;
import Animals.*;
import Plants.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class Main {

    private static World myWorld;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> createAndShowGUI());
    }

    private static void createAndShowGUI() {
        System.out.println("Java project by Yauheni Pyryeu 201253\nw a s d - directions, q - exit, e - special ability, p - pause, 1 2 3 - speed modes\nclick on free field to spawn any organizm (except of your clone)");

        JFrame frame = new JFrame("World Simulation");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        JTextField widthField = new JTextField();
        widthField.setMaximumSize(new Dimension(Integer.MAX_VALUE, widthField.getPreferredSize().height));
        panel.add(new JLabel("Width:"));
        panel.add(widthField);

        JTextField heightField = new JTextField();
        heightField.setMaximumSize(new Dimension(Integer.MAX_VALUE, heightField.getPreferredSize().height));
        panel.add(new JLabel("Height:"));
        panel.add(heightField);

        JButton startButton = new JButton("Start");
        panel.add(startButton);

        JButton loadButton = new JButton("Load");
        panel.add(loadButton);

        frame.getContentPane().add(panel);
        frame.setVisible(true);

        startButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int width = Integer.parseInt(widthField.getText());
                int height = Integer.parseInt(heightField.getText());

                if (width < 5 || height < 5) {
                    JOptionPane.showMessageDialog(frame, "Minimum world dimensions are 5 x 5.");
                } else {
                    frame.dispose();
                    startNewGame(width, height);
                }
            }
        });

        loadButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.dispose();
                loadGame();
            }
        });
    }

    private static void loadGame() {
        myWorld = new World("save.txt");
        runGame();
    }

    private static void startNewGame(int width, int height) {
        myWorld = new World(width, height);
        runGame();
    }

    private static void runGame() {
        GameWorker gameWorker = new GameWorker(myWorld);
        gameWorker.execute();
    }

    private static void drawEndScreen() {
        JOptionPane.showMessageDialog(null, "Game Over!");
    }
}

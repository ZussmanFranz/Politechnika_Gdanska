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
                    JOptionPane.showMessageDialog(frame, "starting the new game!");
                    startNewGame(width, height);
                }
            }
        });

        loadButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
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
        while (!myWorld.isOver()) {
            myWorld.update();
            // Here you would typically have a delay or wait for user input
            // For a Swing GUI, you might use a timer or event-based updates
        }

        drawEndScreen();
    }

    private static void drawEndScreen() {
        JOptionPane.showMessageDialog(null, "Game Over!");
    }
}

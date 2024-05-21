package Abstractions;

import javax.swing.*;
import java.awt.*;

public class GamePanel extends JPanel implements Runnable{
    final int originalTileSize = 16;
    final int scale = 3;
    final int tileSize = originalTileSize * scale;
    private int screenCol;
    private int screenRow;
    private int screenWidth;
    private int screenHeight;
    Thread gameThread;

    public GamePanel(int columns, int rows)
    {
        screenCol = columns;
        screenRow = rows;
        screenWidth = tileSize * screenCol;
        screenHeight = tileSize * screenRow;
        this.setPreferredSize(new Dimension(screenWidth, screenHeight));
        this.setBackground(Color.BLACK);
        this.setDoubleBuffered(true);
    }

    public void startGameThread(){
        this.gameThread = new Thread(this);
        this.gameThread.start();
    }
    @Override
    public void run(){
        while(gameThread != null) {
            //System.out.println("the game loop is running!");
            update();
            repaint();
        }
    }
    public void update() {

    }
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D)g;
        g2.setColor(Color.WHITE);
        g2.fillRect(100, 100, tileSize, tileSize);
        g2.dispose();
    }
}

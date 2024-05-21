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
    KeyHandler keyHandler = new KeyHandler();
    Thread gameThread;

    //player's cords:
    int playerX = 0;
    int playerY = 0;
    int playerSpeed = 4;

    public GamePanel(int columns, int rows)
    {
        screenCol = columns;
        screenRow = rows;
        screenWidth = tileSize * screenCol;
        screenHeight = tileSize * screenRow;
        this.setPreferredSize(new Dimension(screenWidth, screenHeight));
        this.setBackground(Color.BLACK);
        this.setDoubleBuffered(true);
        this.addKeyListener(keyHandler);
        this.setFocusable(true);
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
        if (keyHandler.upPressed){
            playerY -= playerSpeed;
        } else if (keyHandler.downPressed) {
            playerY += playerSpeed;
        }

        if (keyHandler.rightPressed){
            playerX += playerSpeed;
        } else if (keyHandler.leftPressed) {
            playerX -= playerSpeed;
        }
    }
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D)g;
        g2.setColor(Color.WHITE);
        g2.fillRect(playerX, playerY, tileSize, tileSize);
        g2.dispose();
    }
}

package Abstractions;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class KeyHandler implements KeyListener {
    private BlockingQueue<Character> keyQueue = new LinkedBlockingQueue<>();
    public boolean upPressed, downPressed, leftPressed, rightPressed, end, ability;

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyPressed(KeyEvent e) {
        int code = e.getKeyCode();

        if (code == KeyEvent.VK_W){
            upPressed = true;
        }
        if (code == KeyEvent.VK_S){
            downPressed = true;
        }
        if (code == KeyEvent.VK_A){
            leftPressed = true;
        }
        if (code == KeyEvent.VK_D){
            rightPressed = true;
        }
        if (code == KeyEvent.VK_Q){
            end = true;
        }
        if (code == KeyEvent.VK_E){
            ability = true;
        }

//        System.out.println("pressed!");
    }

    @Override
    public void keyReleased(KeyEvent e) {
        int code = e.getKeyCode();

        if (code == KeyEvent.VK_W){
            upPressed = false;
        }
        if (code == KeyEvent.VK_S){
            downPressed = false;
        }
        if (code == KeyEvent.VK_A){
            leftPressed = false;
        }
        if (code == KeyEvent.VK_D){
            rightPressed = false;
        }
        if (code == KeyEvent.VK_E){
            ability = false;
        }

//        System.out.println("released!");
    }

    public char getPlayerInput(){
        if (end) {
            return 'q';
        }
        if (ability){
            return 'e';
        }

        if (upPressed){
            return 'w';
        } else if (downPressed) {
            return 's';
        } else if (rightPressed) {
            return 'd';
        } else if (leftPressed) {
            return 'a';
        }
        return ' ';
    }
}

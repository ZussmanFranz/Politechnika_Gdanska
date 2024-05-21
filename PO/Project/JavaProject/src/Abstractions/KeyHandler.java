package Abstractions;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class KeyHandler implements KeyListener {
    private BlockingQueue<Character> keyQueue = new LinkedBlockingQueue<>();
    public boolean upPressed, downPressed, leftPressed, rightPressed;

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyPressed(KeyEvent e) {
//        char keyChar = e.getKeyChar();
//        if (keyChar == 'w' || keyChar == 'a' || keyChar == 's' || keyChar == 'd' || keyChar == 'e' || keyChar == 'q') {
//            keyQueue.offer(keyChar);
//        }
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
    }

    public char getKey() throws InterruptedException {
        char key = keyQueue.take();
        System.out.println("key"+ key +"handled\n");
        return key;
    }
}

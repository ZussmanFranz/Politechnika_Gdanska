package Abstractions;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class KeyHandler implements KeyListener {
    private BlockingQueue<Character> keyQueue = new LinkedBlockingQueue<>();

    @Override
    public void keyTyped(KeyEvent e) {
    }

    @Override
    public void keyPressed(KeyEvent e) {
        char keyChar = e.getKeyChar();
        if (keyChar == 'w' || keyChar == 'a' || keyChar == 's' || keyChar == 'd' || keyChar == 'e' || keyChar == 'q') {
            keyQueue.offer(keyChar);
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
    }

    public char getKey() throws InterruptedException {
        char key = keyQueue.take();
        System.out.println("key"+ key +"handled\n");
        return key;
    }
}

import javax.swing.*;
import java.awt.*;

/**
 * Affiche les éléments graphiques de la page d'introduction et gère les événements liés
 * @author membmat
 */
public class IntroPanel extends JPanel {

    private static final Font TETRIS_FONT = new Font("Tetris Blocks", Font.BOLD, 24);
    private static final int BOARD_WIDTH = 400;
    private static final String MAIN_TITLE = "Tetris";

    /**
     * Gère l'aspect graphique des éléments
     * @param g Element graphique
     */
    public void paint(Graphics g) {
        FontMetrics metrics = getFontMetrics(TETRIS_FONT);

        // Ecris le titre du jeu avec la bonne police et la bonne position
        g.setFont(TETRIS_FONT);
        g.drawString("Tetris",(BOARD_WIDTH - metrics.stringWidth(MAIN_TITLE)) / 2, 80);
    }

}

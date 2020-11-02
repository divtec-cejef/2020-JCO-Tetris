import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Fenêtre d'introduction du jeu
 * @author membmat
 */
public class Intro extends JFrame {

    /**
     * Point d'entré du programme
     */
    public static void main(String[] args) {
        Intro intro = new Intro();
    }

    /**
     * Constructeur de la fenêtre d'introduction
     */
    public Intro() {

        // Configuration de la page
        setTitle("Tetris introduction");
        setSize(400, 400);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setIconImage(Toolkit.getDefaultToolkit().getImage("C:/git/2020-JCO-Tetris/img/tetrisIcon.png"));
        setResizable(false);

        IntroPanel introPanel = new IntroPanel();

        setContentPane(introPanel);
        introPanel.setLayout(null);

        // Création et ajout du bouton "solo"
        JButton BT_Solo = new JButton("Solo");
        BT_Solo.setBounds(100, 200, 80, 50);
        introPanel.add(BT_Solo);

        /**
         * Action a effectuer lors du clic sur le bouton "solo"
         */
        BT_Solo.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setTitle("rayan m'a aidé");
            }
        });

        // Création et ajout du bouton "mutli"
        JButton BT_Multi = new JButton("Multi");
        BT_Multi.setBounds(200, 200, 80, 50);
        introPanel.add(BT_Multi);

        /**
         * Action a effectuer lors du clic sur le bouton "multi"
         */
        BT_Multi.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                setTitle("Tetris introduction");
            }
        });

        setVisible(true);

    }
}

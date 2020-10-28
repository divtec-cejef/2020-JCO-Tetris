import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;

import javax.swing.JPanel;

/**
 * Affiche les diverses informations sur le jeu, comme
 * la pièce suivante, le score, le niveau actuel et les commandes.
 * @author Membrez Matteo
 */
public class SidePanel extends JPanel {

	/**
	 * l'UID de la version de série
	 */

	private static final long serialVersionUID = 2181495598854992747L;

	/**
	 * Les dimensions de chaque carreau sur l'affichage de la pièce suivante
	 */
	private static final int TILE_SIZE = BoardPanel.TILE_SIZE >> 1;

	/**
	 * La largeur des effets d'ombres sur l'affichage de la pièce suivante
	 */
	private static final int SHADE_WIDTH = BoardPanel.SHADE_WIDTH >> 1;

	/**
	 * Le nombre de lignes et de colonnes dans l'affichage de la pièce suivante
	 */
	private static final int TILE_COUNT = 5;

	/**
	 * Le centre X de la zone de prévisualisation de la prochaine pièce
	 */
	private static final int SQUARE_CENTER_X = 130;

	/**
	 * Le centre Y de la zone de prévisualisation de la porchaine pièce
	 */
	private static final int SQUARE_CENTER_Y = 65;

	/**
	 * La taille de la zone de prévisualisation de la prochaine pièce
	 */
	private static final int SQUARE_SIZE = (TILE_SIZE * TILE_COUNT >> 1);


	private static final int SMALL_INSET = 20;
	private static final int LARGE_INSET = 40;

	/**
	 * La position y des statistiques
	 */
	private static final int STATS_INSET = 175;

	/**
	 * La position y des contrôles
	 */
	private static final int CONTROLS_INSET = 300;

	/**
	 * Le nombre de pixels à décaler entre chaque chaînes
	 */
	private static final int TEXT_STRIDE = 25;

	/**
	 * La petite police
	 */
	private static final Font SMALL_FONT = new Font("Tahoma", Font.BOLD, 11);

	/**
	 * La grande police
	 */
	private static final Font LARGE_FONT = new Font("Tahoma", Font.BOLD, 13);

	/**
	 * La couleur du text
	 */
	private static final Color DRAW_COLOR = new Color(128, 192, 128);
	

	private Tetris tetris;
	
	/**
	 * Constructeur d'un SidePanel
	 * @param tetris l'instance de tetris à utiliser
	 */
	public SidePanel(Tetris tetris) {
		this.tetris = tetris;
		
		setPreferredSize(new Dimension(200, BoardPanel.PANEL_HEIGHT));
		setBackground(Color.BLACK);
	}
	
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		// Défini la couleur
		g.setColor(DRAW_COLOR);

		int offset;
		
		/*
		 * Crée l'affichage des statistiques
		 */
		g.setFont(LARGE_FONT);
		g.drawString("Stats", SMALL_INSET, offset = STATS_INSET);
		g.setFont(SMALL_FONT);
		g.drawString("Level: " + tetris.getLevel(), LARGE_INSET, offset += TEXT_STRIDE);
		g.drawString("Score: " + tetris.getScore(), LARGE_INSET, offset += TEXT_STRIDE);
		
		/*
		 * Crée l'affichage des contrôles
		 */
		g.setFont(LARGE_FONT);
		g.drawString("Controls", SMALL_INSET, offset = CONTROLS_INSET);
		g.setFont(SMALL_FONT);
		g.drawString("A - Move Left", LARGE_INSET, offset += TEXT_STRIDE);
		g.drawString("D - Move Right", LARGE_INSET, offset += TEXT_STRIDE);
		g.drawString("Q - Rotate Anticlockwise", LARGE_INSET, offset += TEXT_STRIDE);
		g.drawString("E - Rotate Clockwise", LARGE_INSET, offset += TEXT_STRIDE);
		g.drawString("S - Drop", LARGE_INSET, offset += TEXT_STRIDE);
		g.drawString("P - Pause Game", LARGE_INSET, offset += TEXT_STRIDE);
		
		/*
		 * Crée l'affichage de la prochaine pièce
		 */
		g.setFont(LARGE_FONT);
		g.drawString("Next Piece:", SMALL_INSET, 70);
		g.drawRect(SQUARE_CENTER_X - SQUARE_SIZE, SQUARE_CENTER_Y - SQUARE_SIZE, SQUARE_SIZE * 2, SQUARE_SIZE * 2);
		
		/*
		 * Génère la prochaine pièce
		 */
		TileType type = tetris.getNextPieceType();
		if(!tetris.isGameOver() && type != null) {
			/*
			 * Récupère les propriétés de la taille de la pièce actuelle
			 */
			int cols = type.getCols();
			int rows = type.getRows();
			int dimension = type.getDimension();
		
			/*
			 * Calcul le coin en haut à gauche de la pièce
			 */
			int startX = (SQUARE_CENTER_X - (cols * TILE_SIZE / 2));
			int startY = (SQUARE_CENTER_Y - (rows * TILE_SIZE / 2));

			int top = type.getTopInset(0);
			int left = type.getLeftInset(0);
		
			/*
			 * Dessine la prochaine pièce
			 */
			for(int row = 0; row < dimension; row++) {
				for(int col = 0; col < dimension; col++) {
					if(type.isTile(col, row, 0)) {
						drawTile(type, startX + ((col - left) * TILE_SIZE), startY + ((row - top) * TILE_SIZE), g);
					}
				}
			}
		}
	}
	
	/**
	 * Dessine la prochaine pièce dans la zone de prévisualisation
	 * @param type Le type de la pièce
	 * @param x la coordonnée x de la pièce
	 * @param y la coordonnée y de la pièce
	 * @param g l'objet graphique
	 */
	private void drawTile(TileType type, int x, int y, Graphics g) {
		/*
		 * Applique la couleur
		 */
		g.setColor(type.getBaseColor());
		g.fillRect(x, y, TILE_SIZE, TILE_SIZE);
		
		/*
		 * Applique les effets de lumière et d'ombre
		 */
		g.setColor(type.getDarkColor());
		g.fillRect(x, y + TILE_SIZE - SHADE_WIDTH, TILE_SIZE, SHADE_WIDTH);
		g.fillRect(x + TILE_SIZE - SHADE_WIDTH, y, SHADE_WIDTH, TILE_SIZE);
		g.setColor(type.getLightColor());
		for(int i = 0; i < SHADE_WIDTH; i++) {
			g.drawLine(x, y + i, x + TILE_SIZE - i - 1, y + i);
			g.drawLine(x + i, y, x + i, y + TILE_SIZE - i - 1);
		}
	}
	
}

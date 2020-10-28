import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;

import javax.swing.JPanel;

/**
 * Affiche la grille de jeu et gère les actions liées au plateau de jeu
 * @author Membrez Matteo
 */
public class BoardPanel extends JPanel {

	/**
	 * l'UID de la version de série
	 */
	private static final long serialVersionUID = 5055679736784226108L;

	public static final int COLOR_MIN = 35;
	public static final int COLOR_MAX = 255 - COLOR_MIN;
	
	/**
	 * Largeur de la bordure autour du plateau de jeu
	 */
	private static final int BORDER_WIDTH = 5;
	
	/**
	 * Le nombre de colonnes sur le plateu.
	 */
	public static final int COL_COUNT = 10;
		
	/**
	 * Le nombre de lignes visible sur le plateau
	 */
	private static final int VISIBLE_ROW_COUNT = 20;
	
	/**
	 * Le nombre de lignes masquées
	 */
	private static final int HIDDEN_ROW_COUNT = 2;
	
	/**
	 * Le nombre total de lignes que contient le tableau
	 */
	public static final int ROW_COUNT = VISIBLE_ROW_COUNT + HIDDEN_ROW_COUNT;
	
	/**
	 * Le nombre de pixel nécessaire pour un carreau
	 */
	public static final int TILE_SIZE = 24;
	
	/**
	 * Largeur de l'effet d'ombre sur les carreaux
	 */
	public static final int SHADE_WIDTH = 4;
	
	/**
	 * Le centre X de la BoardPanel
	 */
	private static final int CENTER_X = COL_COUNT * TILE_SIZE / 2;
	
	/**
	 * Le centre Y de la BoardPanel
	 */
	private static final int CENTER_Y = VISIBLE_ROW_COUNT * TILE_SIZE / 2;
		
	/**
	 * La largeur totale du panneau
	 */
	public static final int PANEL_WIDTH = COL_COUNT * TILE_SIZE + BORDER_WIDTH * 2;
	
	/**
	 * La hauteur totale du panneau
	 */
	public static final int PANEL_HEIGHT = VISIBLE_ROW_COUNT * TILE_SIZE + BORDER_WIDTH * 2;
	
	/**
	 * La plus grande police à afficher
	 */
	private static final Font LARGE_FONT = new Font("Tahoma", Font.BOLD, 16);

	/**
	 * La plus petite police à afficher
	 */
	private static final Font SMALL_FONT = new Font("Tahoma", Font.BOLD, 12);

	private Tetris tetris;
	
	/**
	 * Les tuiles qui composent le plateau
	 */
	private TileType[][] tiles;
		
	/**
	 * Crée un nouveau plateau de jeu
	 * @param tetris l'instance de tetris utilisé
	 */
	public BoardPanel(Tetris tetris) {
		this.tetris = tetris;
		this.tiles = new TileType[ROW_COUNT][COL_COUNT];
		
		setPreferredSize(new Dimension(PANEL_WIDTH, PANEL_HEIGHT));
		setBackground(Color.BLACK);
	}
	
	/**
	 * Réinitialise le plateau de jeu
	 */
	public void clear() {

		for(int i = 0; i < ROW_COUNT; i++) {
			for(int j = 0; j < COL_COUNT; j++) {
				tiles[i][j] = null;
			}
		}
	}
	
	/**
	 * Détermine si une pièce peut ou non être placée aux coordonnées.
	 * @param type Le type de pièce
	 * @param x La coordonnée X de la pièce
	 * @param y La coordonnée Y de la pièce
	 * @param rotation La rotation de la pièce
	 * @return Si la position est valide ou non
	 */
	public boolean isValidAndEmpty(TileType type, int x, int y, int rotation) {
				
		// Assure que la pièce est dans une colonne valide
		if(x < -type.getLeftInset(rotation) || x + type.getDimension() - type.getRightInset(rotation) >= COL_COUNT) {
			return false;
		}
		
		// Assure que la pièce est dans une ligne valide
		if(y < -type.getTopInset(rotation) || y + type.getDimension() - type.getBottomInset(rotation) >= ROW_COUNT) {
			return false;
		}
		
		/*
		 * Pacourt chaque carreau de la pièce pour vérifier qu'il ne soit pas en conflit avec
		 * un carreau existant.
		 */
		for(int col = 0; col < type.getDimension(); col++) {
			for(int row = 0; row < type.getDimension(); row++) {
				if(type.isTile(col, row, rotation) && isOccupied(x + col, y + row)) {
					return false;
				}
			}
		}
		return true;
	}
	
	/**
	 * Ajoute une pièce au plateau de jeu
	 * @param type le type de la pièce
	 * @param x la coordonnée X de la pièce
	 * @param y la coordonnée Y de la pièce
	 * @param rotation la rotation de la pièce
	 */
	public void addPiece(TileType type, int x, int y, int rotation) {

		for(int col = 0; col < type.getDimension(); col++) {
			for(int row = 0; row < type.getDimension(); row++) {
				if(type.isTile(col, row, rotation)) {
					setTile(col + x, row + y, type);
				}
			}
		}
	}
	
	/**
	 * Vérifie le tableau pour voir si des lignes ont été effacées et les supprime du jeu
	 * @return le nombre de lignes qui ont été effacées
	 */
	public int checkLines() {
		int completedLines = 0;

		for(int row = 0; row < ROW_COUNT; row++) {
			if(checkLine(row)) {
				completedLines++;
			}
		}
		return completedLines;
	}
			
	/**
	 * Vérifie si la ligne est pleine ou non
	 * @param line la ligne à vérifier
	 * @return si la ligne est plein ou non
	 */
	private boolean checkLine(int line) {
		/*
		 * Parcourt chaque colonne de cette ligne, si l'une d'elle est vide
		 * la ligne n'est pas pleine
		 */
		for(int col = 0; col < COL_COUNT; col++) {
			if(!isOccupied(col, line)) {
				return false;
			}
		}
		
		/*
		 * Puisque la ligne est remplie il faut la supprimer
		 * Pour cela il faut décaler chaque ligne au-dessus d'une unité
		 */
		for(int row = line - 1; row >= 0; row--) {
			for(int col = 0; col < COL_COUNT; col++) {
				setTile(col, row + 1, getTile(col, row));
			}
		}
		return true;
	}
	
	
	/**
	 * Vérifie si le carreau est déjà occupé
	 * @param x La coordonnée X à vérifier
	 * @param y La coordonnée Y à vérifier
	 * @return Si le carreau est occupé ou non
	 */
	private boolean isOccupied(int x, int y) {
		return tiles[y][x] != null;
	}
	
	/**
	 * Définit un carreau à la colonne et la ligne souhaitées.
	 * @param x la colonne
	 * @param y la ligne
	 * @param type le type à définir pour le carreau
	 */
	private void setTile(int  x, int y, TileType type) {
		tiles[y][x] = type;
	}
		
	/**
	 * Récupère un carreau par sa colonne et sa ligne
	 * @param x la colonne
	 * @param y la ligne
	 * @return le carreau
	 */
	private TileType getTile(int x, int y) {
		return tiles[y][x];
	}
	
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		g.translate(BORDER_WIDTH, BORDER_WIDTH);
		
		/*
		 * Dessine le plateau différement selon l'était actuel du jeu
		 */
		if(tetris.isPaused()) {
			g.setFont(LARGE_FONT);
			g.setColor(Color.WHITE);
			String msg = "PAUSED";
			g.drawString(msg, CENTER_X - g.getFontMetrics().stringWidth(msg) / 2, CENTER_Y);
		} else if(tetris.isNewGame() || tetris.isGameOver()) {
			g.setFont(LARGE_FONT);
			g.setColor(Color.WHITE);

			String msg = tetris.isNewGame() ? "TETRIS" : "GAME OVER";
			g.drawString(msg, CENTER_X - g.getFontMetrics().stringWidth(msg) / 2, 150);
			g.setFont(SMALL_FONT);
			msg = "Press Enter to Play" + (tetris.isNewGame() ? "" : " Again");
			g.drawString(msg, CENTER_X - g.getFontMetrics().stringWidth(msg) / 2, 300);
		} else {
			
			/*
			 * Dessine le carreau dans le plateau
			 */
			for(int x = 0; x < COL_COUNT; x++) {
				for(int y = HIDDEN_ROW_COUNT; y < ROW_COUNT; y++) {
					TileType tile = getTile(x, y);
					if(tile != null) {
						drawTile(tile, x * TILE_SIZE, (y - HIDDEN_ROW_COUNT) * TILE_SIZE, g);
					}
				}
			}

			TileType type = tetris.getPieceType();
			int pieceCol = tetris.getPieceCol();
			int pieceRow = tetris.getPieceRow();
			int rotation = tetris.getPieceRotation();

			for(int col = 0; col < type.getDimension(); col++) {
				for(int row = 0; row < type.getDimension(); row++) {
					if(pieceRow + row >= 2 && type.isTile(col, row, rotation)) {
						drawTile(type, (pieceCol + col) * TILE_SIZE, (pieceRow + row - HIDDEN_ROW_COUNT) * TILE_SIZE, g);
					}
				}
			}
			
			/*
			 * Dessine la pièce fantôme (la pièce transparente qui montre où la pièce va atterir)
			 */
			Color base = type.getBaseColor();
			base = new Color(base.getRed(), base.getGreen(), base.getBlue(), 20);
			for(int lowest = pieceRow; lowest < ROW_COUNT; lowest++) {
				//If no collision is detected, try the next row.
				if(isValidAndEmpty(type, pieceCol, lowest, rotation)) {					
					continue;
				}
				
				// Dessine la pièce fantôme une ligne au dessus de la collision
				lowest--;

				for(int col = 0; col < type.getDimension(); col++) {
					for(int row = 0; row < type.getDimension(); row++) {
						if(lowest + row >= 2 && type.isTile(col, row, rotation)) {
							drawTile(base, base.brighter(), base.darker(), (pieceCol + col) * TILE_SIZE, (lowest + row - HIDDEN_ROW_COUNT) * TILE_SIZE, g);
						}
					}
				}
				
				break;
			}
			
			/*
			 * Dessine la grille d'arrière-plan
			 */
			g.setColor(Color.DARK_GRAY);
			for(int x = 0; x < COL_COUNT; x++) {
				for(int y = 0; y < VISIBLE_ROW_COUNT; y++) {
					g.drawLine(0, y * TILE_SIZE, COL_COUNT * TILE_SIZE, y * TILE_SIZE);
					g.drawLine(x * TILE_SIZE, 0, x * TILE_SIZE, VISIBLE_ROW_COUNT * TILE_SIZE);
				}
			}
		}
		
		/*
		 * Dessine le contour
		 */
		g.setColor(Color.WHITE);
		g.drawRect(0, 0, TILE_SIZE * COL_COUNT, TILE_SIZE * VISIBLE_ROW_COUNT);
	}
	
	/**
	 * Dessine un carreau sur le plateau
	 * @param type le type de pièce à dessiner
	 * @param x la colonne
	 * @param y la ligne
	 * @param g l'objet graphique
	 */
	private void drawTile(TileType type, int x, int y, Graphics g) {
		drawTile(type.getBaseColor(), type.getLightColor(), type.getDarkColor(), x, y, g);
	}
	
	/**
	 * Dessine un carreau sur le plateau
	 * @param base la couleur de base de la pièce
	 * @param light l'effet de lumière de la pièce
	 * @param dark l'effet d'ombre de la pièce
	 * @param x la colonne
	 * @param y la ligne
	 * @param g l'objet graphique
	 */
	private void drawTile(Color base, Color light, Color dark, int x, int y, Graphics g) {
		
		/*
		 * Rempli le carreau entier avec la couleur de base
		 */
		g.setColor(base);
		g.fillRect(x, y, TILE_SIZE, TILE_SIZE);
		
		/*
		 * Ajoute les effets d'ombre au carreau
		 */
		g.setColor(dark);
		g.fillRect(x, y + TILE_SIZE - SHADE_WIDTH, TILE_SIZE, SHADE_WIDTH);
		g.fillRect(x + TILE_SIZE - SHADE_WIDTH, y, SHADE_WIDTH, TILE_SIZE);
		
		/*
		 * Ajoute les effets de lumière au carreau
		 */
		g.setColor(light);
		for(int i = 0; i < SHADE_WIDTH; i++) {
			g.drawLine(x, y + i, x + TILE_SIZE - i - 1, y + i);
			g.drawLine(x + i, y, x + i, y + TILE_SIZE - i - 1);
		}
	}

}

import java.awt.Color;

/**
 * Enum qui permet de définir les différents types de forme
 * @author Membrez Matteo
 *
 */
public enum TileType {

	/**
	 * Pièce de type I.
	 */
	TypeI(new Color(BoardPanel.COLOR_MIN, BoardPanel.COLOR_MAX, BoardPanel.COLOR_MAX), 4, 4, 1, new boolean[][] {
		{
			false,	false,	false,	false,
			true,	true,	true,	true,
			false,	false,	false,	false,
			false,	false,	false,	false,
		},
		{
			false,	false,	true,	false,
			false,	false,	true,	false,
			false,	false,	true,	false,
			false,	false,	true,	false,
		},
		{
			false,	false,	false,	false,
			false,	false,	false,	false,
			true,	true,	true,	true,
			false,	false,	false,	false,
		},
		{
			false,	true,	false,	false,
			false,	true,	false,	false,
			false,	true,	false,	false,
			false,	true,	false,	false,
		}
	}),
	
	/**
	 * Pièce de type J.
	 */
	TypeJ(new Color(BoardPanel.COLOR_MIN, BoardPanel.COLOR_MIN, BoardPanel.COLOR_MAX), 3, 3, 2, new boolean[][] {
		{
			true,	false,	false,
			true,	true,	true,
			false,	false,	false,
		},
		{
			false,	true,	true,
			false,	true,	false,
			false,	true,	false,
		},
		{
			false,	false,	false,
			true,	true,	true,
			false,	false,	true,
		},
		{
			false,	true,	false,
			false,	true,	false,
			true,	true,	false,
		}
	}),
	
	/**
	 * Pièce de type L.
	 */
	TypeL(new Color(BoardPanel.COLOR_MAX, 127, BoardPanel.COLOR_MIN), 3, 3, 2, new boolean[][] {
		{
			false,	false,	true,
			true,	true,	true,
			false,	false,	false,
		},
		{
			false,	true,	false,
			false,	true,	false,
			false,	true,	true,
		},
		{
			false,	false,	false,
			true,	true,	true,
			true,	false,	false,
		},
		{
			true,	true,	false,
			false,	true,	false,
			false,	true,	false,
		}
	}),
	
	/**
	 * Pièce de type O.
	 */
	TypeO(new Color(BoardPanel.COLOR_MAX, BoardPanel.COLOR_MAX, BoardPanel.COLOR_MIN), 2, 2, 2, new boolean[][] {
		{
			true,	true,
			true,	true,
		},
		{
			true,	true,
			true,	true,
		},
		{	
			true,	true,
			true,	true,
		},
		{
			true,	true,
			true,	true,
		}
	}),
	
	/**
	 * Pièce de type S.
	 */
	TypeS(new Color(BoardPanel.COLOR_MIN, BoardPanel.COLOR_MAX, BoardPanel.COLOR_MIN), 3, 3, 2, new boolean[][] {
		{
			false,	true,	true,
			true,	true,	false,
			false,	false,	false,
		},
		{
			false,	true,	false,
			false,	true,	true,
			false,	false,	true,
		},
		{
			false,	false,	false,
			false,	true,	true,
			true,	true,	false,
		},
		{
			true,	false,	false,
			true,	true,	false,
			false,	true,	false,
		}
	}),
	
	/**
	 * Pièce de type T.
	 */
	TypeT(new Color(128, BoardPanel.COLOR_MIN, 128), 3, 3, 2, new boolean[][] {
		{
			false,	true,	false,
			true,	true,	true,
			false,	false,	false,
		},
		{
			false,	true,	false,
			false,	true,	true,
			false,	true,	false,
		},
		{
			false,	false,	false,
			true,	true,	true,
			false,	true,	false,
		},
		{
			false,	true,	false,
			true,	true,	false,
			false,	true,	false,
		}
	}),
	
	/**
	 * Pièce de type Z.
	 */
	TypeZ(new Color(BoardPanel.COLOR_MAX, BoardPanel.COLOR_MIN, BoardPanel.COLOR_MIN), 3, 3, 2, new boolean[][] {
		{
			true,	true,	false,
			false,	true,	true,
			false,	false,	false,
		},
		{
			false,	false,	true,
			false,	true,	true,
			false,	true,	false,
		},
		{
			false,	false,	false,
			true,	true,	false,
			false,	true,	true,
		},
		{
			false,	true,	false,
			true,	true,	false,
			true,	false,	false,
		}
	});

	private Color baseColor;
	private Color lightColor;
	private Color darkColor;
	private int spawnCol;
	private int spawnRow;
	private int dimension;
	private int rows;
	private int cols;
	private boolean[][] tiles;
	
	/**
	 * Creation d'un nouveau type de carreau
	 * @param color la couleur de baes du carreau
	 * @param dimension Les dimensions
	 * @param cols Le nombre de colonnes
	 * @param rows Le nombre de lignes
	 * @param tiles le carreau
	 */
	TileType(Color color, int dimension, int cols, int rows, boolean[][] tiles) {
		this.baseColor = color;
		this.lightColor = color.brighter();
		this.darkColor = color.darker();
		this.dimension = dimension;
		this.tiles = tiles;
		this.cols = cols;
		this.rows = rows;
		
		this.spawnCol = 5 - (dimension >> 1);
		this.spawnRow = getTopInset(0);
	}
	
	/**
	 * Getteur de la couleur de base
	 * @return la couleur de base
	 */
	public Color getBaseColor() {
		return baseColor;
	}
	
	/**
	 * Getteur de l'effet de lumière
	 * @return l'effet de lumière
	 */
	public Color getLightColor() {
		return lightColor;
	}
	
	/**
	 * Getteur de l'effet d'ombre
	 * @return l'effet d'ombre
	 */
	public Color getDarkColor() {
		return darkColor;
	}
	
	/**
	 * Getteur des dimensions
	 * @return les dimensions
	 */
	public int getDimension() {
		return dimension;
	}
	
	/**
	 * Getteur de la colonne d'apparition
	 * @return la colonne d'apparition
	 */
	public int getSpawnColumn() {
		return spawnCol;
	}
	
	/**
	 * Getteur de la ligne d'apparition
	 * @return la ligne d'apparition
	 */
	public int getSpawnRow() {
		return spawnRow;
	}
	
	/**
	 * Getteur du nombre de lignes
	 * @return le nombre de lignes
	 */
	public int getRows() {
		return rows;
	}
	
	/**
	 * Getteur du nombre de colonnes
	 * @return le nombre de colonnes
	 */
	public int getCols() {
		return cols;
	}
	
	/**
	 * Vérifie si les coordonées données contiennent un carreau
	 * @param x La coordonnée x du carreau
	 * @param y la coordonnée y du carreau
	 * @param rotation La rotation à enregistrer
	 * @return si un carreau s'y trouve ou non
	 */
	public boolean isTile(int x, int y, int rotation) {
		return tiles[rotation][y * dimension + x];
	}
	
	/**
	 * Donne le nombre de colonnes libres sur la gauche
	 * @param rotation La rotation
	 * @return le nombre de colonnes libres sur la gauche
	 */
	public int getLeftInset(int rotation) {

		for(int x = 0; x < dimension; x++) {
			for(int y = 0; y < dimension; y++) {
				if(isTile(x, y, rotation)) {
					return x;
				}
			}
		}
		return -1;
	}
	
	/**
	 * Donne le nombre de colonnes libres sur la droite
	 * @param rotation la rotation
	 * @return le nombre de colonnes libres sur la gauche
	 */
	public int getRightInset(int rotation) {

		for(int x = dimension - 1; x >= 0; x--) {
			for(int y = 0; y < dimension; y++) {
				if(isTile(x, y, rotation)) {
					return dimension - x;
				}
			}
		}
		return -1;
	}
	
	/**
	 * Donne le nombre de lignes libres au dessus
	 * @param rotation la rotation
	 * @return le nombre de lignes libres au dessus
	 */
	public int getTopInset(int rotation) {

		for(int y = 0; y < dimension; y++) {
			for(int x = 0; x < dimension; x++) {
				if(isTile(x, y, rotation)) {
					return y;
				}
			}
		}
		return -1;
	}
	
	/**
	 * Donne le nombre de lignes libres en dessous
	 * @param rotation la rotation
	 * @return le nombre de lignes libres en dessous
	 */
	public int getBottomInset(int rotation) {

		for(int y = dimension - 1; y >= 0; y--) {
			for(int x = 0; x < dimension; x++) {
				if(isTile(x, y, rotation)) {
					return dimension - y;
				}
			}
		}
		return -1;
	}
	
}

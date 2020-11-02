import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.Random;

import javax.swing.JFrame;

/**
 * Gère une grande partie de la logique du jeu et de la lecture de l'entrée utilisateur
 * @author Membrez Matteo
 */
public class Tetris extends JFrame {
	
	/**
	 * l'UID de la version de série
	 */
	private static final long serialVersionUID = -4722429764792514382L;

	/**
	 * le nombre de millisecondes par image
	 */
	private static final long FRAME_TIME = 1000L / 50L;
	
	/**
	 * Le nombre de pièces qu'il existe
	 */
	private static final int TYPE_COUNT = TileType.values().length;
		
	/**
	 * Instance du BoardPanel
	 */
	private BoardPanel board;
	
	/**
	 * Instance du SidePanel
	 */
	private SidePanel side;
	
	/**
	 * Est-ce que le jeu est en pause ou non
	 */
	private boolean isPaused;
	
	/**
	 * Est-ce qu'une partie à déjà été jouée
	 */
	private boolean isNewGame;
	
	/**
	 * Est-ce que le jeu est fini ou non
	 */
	private boolean isGameOver;
	
	/**
	 * Le niveau actuel
	 */
	private int level;
	
	/**
	 * Le score actuel
	 */
	private int score;
	
	/**
	 * Générateur de nombre pseudo-aléatoire utilisé pour tirer au hazard la pièce suivante
	 */
	private Random random;
	
	/**
	 * Timer qui gère la mise à jour
	 */
	private Clock logicTimer;
				
	/**
	 * le type de carreau actuel
	 */
	private TileType currentType;
	
	/**
	 * le prochain type de carreau
	 */
	private TileType nextType;
		
	/**
	 * la colonne actuelle du carreau
	 */
	private int currentCol;
	
	/**
	 * la ligne actuelle du carreau
	 */
	private int currentRow;

	/**
	 * la rotation actuelle du carreau
	 */
	private int currentRotation;
		
	/**
	 * Applique un cooldown avant que l'on puisse faire tomber la pièce
	 */
	private int dropCooldown;
	
	/**
	 * la vitesse du jeu
	 */
	private float gameSpeed;
		
	/**
	 * Création d'une nouvelle instance de Tetris
	 */
	private Tetris() {
		/*
		 * Configure les propriétée de la fenêtre
		 */
		super("Tetris");
		setLayout(new BorderLayout());
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setIconImage(Toolkit.getDefaultToolkit().getImage("C:/git/2020-JCO-Tetris/img/tetrisIcon.png"));
		setResizable(false);
		
		/*
		 * Initialise les instances du BoardPanel et du SidePanel
		 */
		this.board = new BoardPanel(this);
		this.side = new SidePanel(this);
		
		/*
		 * Ajoute les instances du BoardPanel et du SidePanel à la fenêtre
		 */
		add(board, BorderLayout.CENTER);
		add(side, BorderLayout.EAST);

		addKeyListener(new KeyAdapter() {
			
			@Override
			/**
			 * Evenements effectués lors de la pression sur les différentes touches.
			 */
			public void keyPressed(KeyEvent e) {
								
				switch(e.getKeyCode()) {
				
				/*
				 * Fait tomber la pièce si le jeu n'est pas en pause
				 * et qu'il n'y a pas de cooldown.
				 */
				case KeyEvent.VK_S:
					if(!isPaused && dropCooldown == 0) {
						logicTimer.setCyclesPerSecond(25.0f);
					}
					break;
					
				/*
				 * Se déplace à gauche si le jeu n'est pas en pause
				 * et que la pièce n'est pas déjà tout à gauche
				 */
				case KeyEvent.VK_A:
					if(!isPaused && board.isValidAndEmpty(currentType, currentCol - 1, currentRow, currentRotation)) {
						currentCol--;
					}
					break;
					
				/*
				 * Se déplace à droite si le jeu n'est pas en pause
				 * et que la pièce n'est pas déjà tout à droite
				 */
				case KeyEvent.VK_D:
					if(!isPaused && board.isValidAndEmpty(currentType, currentCol + 1, currentRow, currentRotation)) {
						currentCol++;
					}
					break;
					
				/*
				 * Effectue une rotation de la pièce sur la gauche
				 */
				case KeyEvent.VK_Q:
					if(!isPaused) {
						rotatePiece((currentRotation == 0) ? 3 : currentRotation - 1);
					}
					break;
				
				/*
			     * Effectue une rotation de la pièce sur la droite
				 */
				case KeyEvent.VK_E:
					if(!isPaused) {
						rotatePiece((currentRotation == 3) ? 0 : currentRotation + 1);
					}
					break;
					
				/*
				 * Met le jeu en pause si la partie n'est pas fini et qu'elle a déjà commencé
				 */
				case KeyEvent.VK_P:
					if(!isGameOver && !isNewGame) {
						isPaused = !isPaused;
						logicTimer.setPaused(isPaused);
					}
					break;
				
				/*
				 * Lance la partie
				 */
				case KeyEvent.VK_ENTER:
					if(isGameOver || isNewGame) {
						resetGame();
					}
					break;
				
				}
			}
			
			@Override
			public void keyReleased(KeyEvent e) {

				/*
				 * Redonne la vitesse de base à la pièce lorsque la touche est relâchée
				 */
				if (e.getKeyCode() == KeyEvent.VK_S) {
					logicTimer.setCyclesPerSecond(gameSpeed);
					logicTimer.reset();
				}
				
			}
			
		});

		pack();
		setLocationRelativeTo(null);
		setVisible(true);
	}
	
	/**
	 * Début de la partie
	 */
	private void startGame() {

		this.random = new Random();
		this.isNewGame = true;
		this.gameSpeed = 1.0f;
		
		/*
		 * Configuration du timer
		 */
		this.logicTimer = new Clock(gameSpeed);
		logicTimer.setPaused(true);
		
		while(true) {
			long start = System.nanoTime();

			logicTimer.update();
			
			/*
			 * Met à jour le jeu en fonction du temps écoulé
			 */
			if(logicTimer.hasElapsedCycle()) {
				updateGame();
			}
		
			// Décrémente le cooldown si nécéssaire
			if(dropCooldown > 0) {
				dropCooldown--;
			}
			
			// Affichage
			renderGame();

			long delta = (System.nanoTime() - start) / 1000000L;
			if(delta < FRAME_TIME) {
				try {
					Thread.sleep(FRAME_TIME - delta);
				} catch(Exception e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	/**
	 * Mets à jour le jeu
	 */
	private void updateGame() {
		/*
		 * Vérifie si la pièce peut déscendre
		 */
		if(board.isValidAndEmpty(currentType, currentCol, currentRow + 1, currentRotation)) {
			currentRow++;
		} else {
			board.addPiece(currentType, currentCol, currentRow, currentRotation);
			
			/*
			 * Vérifie si l'ajout de la pièce a effacé d'autres lignes
			 * Augmente le score selon le nombre de lignes effacées en 1 coup
			 * [1 = 100pts, 2 = 200pts, 3 = 400pts, 4 = 800pts]).
			 */
			int cleared = board.checkLines();
			if(cleared > 0) {
				score += 50 << cleared;
			}
			
			/*
			 * Augmente la vitesse de la pièce suivante
			 */
			gameSpeed += 0.035f;
			logicTimer.setCyclesPerSecond(gameSpeed);
			logicTimer.reset();

			dropCooldown = 25;
			
			/*
			 * Change le niveau de difficulté
			 */
			level = (int)(gameSpeed * 1.70f);
			
			/*
			 * Création d'une nouvelle pièce
			 */
			spawnPiece();
		}		
	}

	private void renderGame() {
		board.repaint();
		side.repaint();
	}
	
	/**
	 * Réinitialise les variables du jeu à leurs valeur de base
	 */
	private void resetGame() {
		this.level = 1;
		this.score = 0;
		this.gameSpeed = 1.0f;
		this.nextType = TileType.values()[random.nextInt(TYPE_COUNT)];
		this.isNewGame = false;
		this.isGameOver = false;		
		board.clear();
		logicTimer.reset();
		logicTimer.setCyclesPerSecond(gameSpeed);
		spawnPiece();
	}
		
	/**
	 * Créér une nouvelle pièce et réinitialiser les variables
	 */
	private void spawnPiece() {

		this.currentType = nextType;
		this.currentCol = currentType.getSpawnColumn();
		this.currentRow = currentType.getSpawnRow();
		this.currentRotation = 0;
		this.nextType = TileType.values()[random.nextInt(TYPE_COUNT)];
		
		/*
		 * Si le point d'appartion n'est pas valide, met en pause et termine la partie
		 * car cela signifie que les pièces sont allées trop haut
		 */
		if(!board.isValidAndEmpty(currentType, currentCol, currentRow, currentRotation)) {
			this.isGameOver = true;
			logicTimer.setPaused(true);
		}		
	}

	/**
	 * Défini la rotation de la pièce actuelle
	 * @param newRotation la rotation de la nouvelle pièce
	 */
	private void rotatePiece(int newRotation) {

		int newColumn = currentCol;
		int newRow = currentRow;
		
		/*
		 * Mémorise le nombre de colonnes et lignes vides de chaque côté
		 */
		int left = currentType.getLeftInset(newRotation);
		int right = currentType.getRightInset(newRotation);
		int top = currentType.getTopInset(newRotation);
		int bottom = currentType.getBottomInset(newRotation);

		/*
		 * S'assure que la pièce actuelle n'est pas trop à gauche ou trop à droite
		 */
		if(currentCol < -left) {
			newColumn -= currentCol - left;
		} else if(currentCol + currentType.getDimension() - right >= BoardPanel.COL_COUNT) {
			newColumn -= (currentCol + currentType.getDimension() - right) - BoardPanel.COL_COUNT + 1;
		}
		
		/*
		 * S'assure que la pièce actuelle n'est pas trop haute ou trop basse
		 */
		if(currentRow < -top) {
			newRow -= currentRow - top;
		} else if(currentRow + currentType.getDimension() - bottom >= BoardPanel.ROW_COUNT) {
			newRow -= (currentRow + currentType.getDimension() - bottom) - BoardPanel.ROW_COUNT + 1;
		}
		
		/*
		 * Vérifie si la nouvelle position est correcte et mets à jour la rotation si c'est le cas
		 */
		if(board.isValidAndEmpty(currentType, newColumn, newRow, newRotation)) {
			currentRotation = newRotation;
			currentRow = newRow;
			currentCol = newColumn;
		}
	}
	
	/**
	 * @return Si le jeu est en pause ou non
	 */
	public boolean isPaused() {
		return isPaused;
	}
	
	/**
	 * @return Si la partie est finie ou non
	 */
	public boolean isGameOver() {
		return isGameOver;
	}
	
	/**
	 * @return Si c'est une nouvelle partie ou non
	 */
	public boolean isNewGame() {
		return isNewGame;
	}
	
	/**
	 * @return le score actuel
	 */
	public int getScore() {
		return score;
	}
	
	/**
	 * @return le niveau actuel
	 */
	public int getLevel() {
		return level;
	}
	
	/**
	 * @return le type de pièce
	 */
	public TileType getPieceType() {
		return currentType;
	}
	
	/**
	 * @return Le prochain type de pièce
	 */
	public TileType getNextPieceType() {
		return nextType;
	}
	
	/**
	 * @return la colonne de la pièce actuelle
	 */
	public int getPieceCol() {
		return currentCol;
	}
	
	/**
	 * @return la ligne de la pièce actuelle
	 */
	public int getPieceRow() {
		return currentRow;
	}
	
	/**
	 * @return la rotation de la pièce actuelle
	 */
	public int getPieceRotation() {
		return currentRotation;
	}

	/**
	 * Point d'entré du jeu
	 */
	public static void main(String[] args) {
		Tetris tetris = new Tetris();
		tetris.startGame();
	}

}

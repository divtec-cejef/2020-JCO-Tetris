/**
 * Suis le nombre de cycles qui s'écoulent au fil du temps
 * @author Membrez Matteo
 *
 */
public class Clock {
	
	/**
	 * Le nombre de millisecondes qui composent un cycle
	 */
	private float millisPerCycle;
	
	/**
	 * La dernière mise à jour de l'horloge
	 */
	private long lastUpdate;
	
	/**
	 * Le nombre de cycle qui se sont écoulés mais qui n'ont pas encore été gérés
	 */
	private int elapsedCycles;
	
	/**
	 * La quantité de temps supplémentaire vers le prochain cycle écoulé
	 */
	private float excessCycles;
	
	/**
	 * Est-ce que l'horloge est en pause ou non
	 */
	private boolean isPaused;
	
	/**
	 * Crée une nouvelle horloge et définit ses cycles par secondes
	 * @param cyclesPerSecond Le nombre de cycles par secondes
	 */
	public Clock(float cyclesPerSecond) {
		setCyclesPerSecond(cyclesPerSecond);
		reset();
	}
	
	/**
	 * Définit le nombre de cycles qui s'écoulent par seconde
	 * @param cyclesPerSecond Le nombre de cylce par secondes
	 */
	public void setCyclesPerSecond(float cyclesPerSecond) {
		this.millisPerCycle = (1.0f / cyclesPerSecond) * 1000;
	}
	
	/**
	 * Réinitialise l'horloge
	 */
	public void reset() {
		this.elapsedCycles = 0;
		this.excessCycles = 0.0f;
		this.lastUpdate = getCurrentTime();
		this.isPaused = false;
	}
	
	/**
	 * Met à jour l'horloge
	 */
	public void update() {

		long currUpdate = getCurrentTime();
		float delta = (float)(currUpdate - lastUpdate) + excessCycles;

		if(!isPaused) {
			this.elapsedCycles += (int)Math.floor(delta / millisPerCycle);
			this.excessCycles = delta % millisPerCycle;
		}

		this.lastUpdate = currUpdate;
	}
	
	/**
	 * Met en pause ou rétablit l'horloge
	 */
	public void setPaused(boolean paused) {
		this.isPaused = paused;
	}
	
	/**
	 * Vérifie si un cycle s'est écoulé
	 */
	public boolean hasElapsedCycle() {
		if(elapsedCycles > 0) {
			this.elapsedCycles--;
			return true;
		}
		return false;
	}
	
	/**
	 * Calcul l'heure actuelle en millisecondes
	 */
	private static final long getCurrentTime() {
		return (System.nanoTime() / 1000000L);
	}

}

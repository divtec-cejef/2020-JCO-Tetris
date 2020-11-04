/**
  Fichier qui contient toute la logique du jeu.
  
  @author   JCO
  @date     Février 2014
 */
#include "gamecore.h"

#include <cmath>

#include <QDebug>
#include <QSettings>

#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"
#include "utilities.h"
#include "sprite.h"

const int SCENE_WIDTH = 400;
const int SCENE_HEIGHT = 700;
const int PLAYER_SPEED = 150; // vitesse de déplacement du joueur en pixels/s
const int SHIFT_MOVEMENT = 20; // nbre de pixels qui séparent la position initial de l'objet avec sa position finale

//! Initialise le contrôleur de jeu.
//! \param pGameCanvas  GameCanvas pour lequel cet objet travaille.
//! \param pParent      Pointeur sur le parent (afin d'obtenir une destruction automatique de cet objet).
GameCore::GameCore(GameCanvas* pGameCanvas, QObject* pParent) : QObject(pParent) {
    
    // Mémorise l'accès au canvas (qui gère le tick et l'affichage d'une scène)
    m_pGameCanvas = pGameCanvas;
    
    // Créé la scène de base et indique au canvas qu'il faut l'afficher.
    m_pScene = pGameCanvas->createScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    pGameCanvas->setCurrentScene(m_pScene);
    
    // Trace un rectangle blanc tout autour des limites de la scène.
    m_pScene->addRect(m_pScene->sceneRect(), QPen(Qt::white));
    
    // Instancier et initialiser les sprite
    // Sprite de la pièce carrée
    Sprite* SpriteCarre = new Sprite(GameFramework::imagesPath() + "Tetris_carre.png");
    m_pScene->addSpriteToScene(SpriteCarre);
    m_pPieceCarre = SpriteCarre;

    // Sprite de la pièce en T
    Sprite* SpriteT = new Sprite(GameFramework::imagesPath() + "Tetris_T.png");
    m_pScene->addSpriteToScene(SpriteT);
    m_pPieceT = SpriteT;

    SpriteCarre->setPos(m_pScene->width()/2.0, 0);
    SpriteT->setPos(m_pScene->width()/2.0, 0);


    // Démarre le tick pour que les animations qui en dépendent fonctionnent correctement.
    // Attention : il est important que l'enclenchement du tick soit fait vers la fin de cette fonction,
    // sinon le temps passé jusqu'au premier tick (ElapsedTime) peut être élevé et provoquer de gros
    // déplacements, surtout si le déboggueur est démarré.
    m_pGameCanvas->startTick();
}

//! Destructeur de GameCore : efface les scènes
GameCore::~GameCore() {
    delete m_pScene;
    m_pScene = nullptr;
}

//! Traite la pression d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
//!
void GameCore::keyPressed(int key) {
    emit notifyKeyPressed(key);

    switch(key) {
    // Décale le sprite sur la gauche
    case Qt::Key_Left:
        if(m_pPieceCarre->left() > 10) {
            m_pPieceCarre->setX(m_pPieceCarre->x() - SHIFT_MOVEMENT);
        } break;

    // Décale le sprite sur la droite
    case Qt::Key_Right:
        if(m_pPieceCarre->right() < m_pScene->width()-10) {
            m_pPieceCarre->setX(m_pPieceCarre->x() + SHIFT_MOVEMENT);
        } break;

    case Qt::Key_Down:
        if(m_pPieceCarre->bottom() < m_pScene->height()-SHIFT_MOVEMENT) {
            m_pPieceCarre->setY(m_pPieceCarre->y() + SHIFT_MOVEMENT);
        }
    }

}

//! Traite le relâchement d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
void GameCore::keyReleased(int key) {
    emit notifyKeyReleased(key);

}

//! Cadence.
//! Gère le déplacement de la Terre qui tourne en cercle.
//! \param elapsedTimeInMilliseconds  Temps écoulé depuis le dernier appel.
void GameCore::tick(long long elapsedTimeInMilliseconds) {

    if(m_pPieceCarre->bottom() < m_pScene->height()) {
        m_pPieceCarre->setY(m_pPieceCarre->y() + 2);
    }

//    float distance = PLAYER_SPEED * elapsedTimeInMilliseconds / 1000.0F * m_playerDirection;

//    m_pPlayer->setX(m_pPlayer->x() + distance);

//    // Détecte si le joueur atteint un des bords de la scène
//    if (m_pPlayer->right() > m_pScene->width() || m_pPlayer->left() < 0) {
//        m_playerDirection *= -1;
//    }
}

//! La souris a été déplacée.
//! Pour que cet événement soit pris en compte, la propriété MouseTracking de GameView
//! doit être enclenchée avec GameCanvas::startMouseTracking().
void GameCore::mouseMoved(QPointF newMousePosition) {
    emit notifyMouseMoved(newMousePosition);
}

//! Traite l'appui sur un bouton de la souris.
void GameCore::mouseButtonPressed(QPointF mousePosition, Qt::MouseButtons buttons) {
    emit notifyMouseButtonPressed(mousePosition, buttons);
}

//! Traite le relâchement d'un bouton de la souris.
void GameCore::mouseButtonReleased(QPointF mousePosition, Qt::MouseButtons buttons) {
    emit notifyMouseButtonReleased(mousePosition, buttons);
}


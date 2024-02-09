#pragma once 

#include "playerShip.h"

// Section for enemy types
#include "EnemyCruiser.h"
#include "EnemyVanguard.h"

// Section for Bosses
#include "ORT.h"
#include "UFO.h"

class EnemyManager {
        static void drawEnemyBullets(EnemyShip* enemy);
        static void updateEnemyBullets(EnemyShip* enemy);
        static ofVec2f getRandomEdgePoint();

        static bool bossIsActive;
        static EnemyShip* currentBoss;

        static bool ufoSeen;
        static bool ortSeen;

    public:
        static int pointsPerUpdateCycle;
        static int getPointsScored() { return pointsPerUpdateCycle; }

        static int killSpreeTimer;
        static void decrementKillSpreeTimer();
        static int getKillSpreeTimer();
        static void resetKillSpreeTimer(int value);


        static vector<EnemyShip*> enemyList;
        static vector<Boss*> bossList; // A list to keep track of bosses
        static vector<EnemyShip*> enemiesForDeletion;
        
        static void updateEnemies(Player* player);
        static void removeEnemies();

        static void drawEnemies();

        static int enemySpawnTimer;
        static void spawnEnemy();
        static void spawnEnemy(Player* player);
        static void spawnBoss(Boss* boss);
        static void bossHasDied();
        static int whichSpawnInterval(int playerScore);

        static void activateBoss();


        static void cleanUp();
        static void deleteMarkedBullets();
};
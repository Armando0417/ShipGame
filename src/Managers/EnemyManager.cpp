#include "EnemyManager.h"

// Define static members here
    int EnemyManager::pointsPerUpdateCycle = 0;
    int EnemyManager::killSpreeTimer = 0;
    vector<EnemyShip*> EnemyManager::enemyList;
    vector<Boss*> EnemyManager::bossList;
    vector<EnemyShip*> EnemyManager::enemiesForDeletion;
    bool EnemyManager::bossIsActive = false;
    EnemyShip* EnemyManager::currentBoss = nullptr;
    bool EnemyManager::ufoSeen = false;
    bool EnemyManager::ortSeen = false;
    int EnemyManager::enemySpawnTimer = 0;


void EnemyManager::updateEnemies(Player* player){
    // At the beginning of the update method
    decrementKillSpreeTimer();
    pointsPerUpdateCycle = 0;

    //Spawning logic
    enemySpawnTimer += 1;
    spawnEnemy(player);

    //Movement and hit detection for enemies
    for(unsigned int i = 0; i < enemyList.size(); i++){
        EnemyShip* enemy = enemyList[i];
        enemy->update(player->pos);
        updateEnemyBullets(enemy);
        //Collisions for the player bullets
        for (Projectiles& p : player->bullets) {
            
            if(!p.bulletIsOutOfBounds()) {
                if(enemy->getHitBox()->isHit(p)){                
                    player->health = min(player->health + 3.0, 100.0);  // Reward the player for hitting an enemy
                    
                    enemy->takeDamage(p.getDamage());

                    if(enemy->isDead()) {   // Remove the enemy from the list
                        SoundManager::playSong("shipExplosion", false);
                        pointsPerUpdateCycle += enemy->getPoints();
                        resetKillSpreeTimer(150);
                        enemiesForDeletion.push_back(enemy);
                        
                    }
                    p.markForDeletion();                    
                }
            }

        }
        enemy->removeMarkedBullets();
    }


    //Enemy projectiles
    for(EnemyShip* enemy : enemyList){

        for(Projectiles& p : enemy->getBullets()){
            if(!p.bulletIsOutOfBounds()) {
                if(player->hitBox.isHit(p)){
                    if(player->health > 0){
                        player->health = max(player->health - 10, 0);
                    }
                }
            }
            else {
                p.markForDeletion();
            }
        }
    }

    // Update and manage bosses
        for (unsigned int i = 0; i < bossList.size(); i++) {
            Boss* boss = bossList[i];
            boss->update(player->pos);

            for (Projectiles& p : player->bullets) {
                if (boss->getHitBox()->isHit(p)) {
                    player->health = min(player->health + 5, 100); // Healing upon hitting the boss
                    boss->takeDamage(p.getDamage());

                    if (boss->isDead()) {
                        SoundManager::playSong("shipExplosion", false);
                        pointsPerUpdateCycle += boss->getPoints();
                        resetKillSpreeTimer(150);
                        bossHasDied();
                        bossList.erase(bossList.begin() + i);
                        delete boss; // Clean up the boss object
                        i--; // Adjust index after removal
                    }
                }
            }

        // Update projectiles for bosses
        updateEnemyBullets(boss);
    }

    // Delete marked bullets
    player->removeMarkedBullets();
    removeEnemies();


}

void EnemyManager::updateEnemyBullets(EnemyShip* enemy){
    for (unsigned int i = 0; i < enemy->getBullets().size(); i++) {
       enemy->getBullets()[i].update();

    }
}

 ofVec2f EnemyManager::getRandomEdgePoint() {
    int edge = ofRandom(4);  // Select a random edge (0: top, 1: right, 2: bottom, 3: left)
    float x, y;

    if (edge == 0) {  // Top edge
        x = ofRandomWidth();
        y = 0;
    } else if (edge == 1) {  // Right edge
        x = ofGetWidth();
        y = ofRandomHeight();
    } else if (edge == 2) {  // Bottom edge
        x = ofRandomWidth();
        y = ofGetHeight();
    } else {  // Left edge
        x = 0;
        y = ofRandomHeight();
    }

    return ofVec2f(x, y);

}


void EnemyManager::decrementKillSpreeTimer() {
    if (killSpreeTimer > 0) {
        --killSpreeTimer;
    }
}

int EnemyManager::getKillSpreeTimer() {
    return killSpreeTimer;
}

void EnemyManager::resetKillSpreeTimer(int value) {
    killSpreeTimer = value;
}

void EnemyManager::drawEnemies(){
    for(EnemyShip* e : enemyList){
        e->draw();

        if(e->getBullets().size() > 0){
            drawEnemyBullets(e);
        }
    }
    
    // Draw bosses and their health bars
    for (Boss* boss : bossList) {
        boss->draw();
        boss->showBossHealth(); // Call the method to show the boss's health bar
        if(boss->getBullets().size() > 0){
            drawEnemyBullets(boss);
        }
    }
}

void EnemyManager::drawEnemyBullets(EnemyShip* enemy){
    for(Projectiles p : enemy->getBullets()){
        p.draw();
    }
}


void EnemyManager::spawnEnemy(Player* player){
    int currentScore = player->getScore();
    int spawnInterval = whichSpawnInterval(currentScore);
    
    if (enemySpawnTimer >= spawnInterval) {
        ofPoint spawnLocation = getRandomEdgePoint();
        EnemyShip* newEnemy = nullptr;

            // Spawn regular enemy
            if (currentScore > 10000) {
                if (!ortSeen) {
                    //Spawn ORT Xibalba
                    if (!bossIsActive) {
                        Boss* ORT_Xibalba = new ORT(0, ofGetHeight() / 2, "ORT Xibalba");
                        ortSeen = true;
                        spawnBoss(ORT_Xibalba);
                    }
                }
            }

            if (currentScore > 5000) {
                if(!ufoSeen){
                    ufoSeen = true;
                    Boss* UFO_ORT = new UFO(ofGetWidth()/2 - 100, 20, "Galactica Supercell ORT");
                    spawnBoss(UFO_ORT);
                }
            }

            if (currentScore > 1500) {
                newEnemy = new EnemyVanguard(spawnLocation.x, spawnLocation.y);   
            }

            else{
                newEnemy = new EnemyCruiser(spawnLocation.x, spawnLocation.y);
            }

            if (newEnemy != nullptr) {
                enemyList.push_back(newEnemy);
                enemySpawnTimer = 0; // Reset timer after spawning
            }

        }


    }

void EnemyManager::spawnBoss(Boss* boss) {
    bossIsActive = true;
    currentBoss = boss;
    SoundManager::stopSong("battle");
    SoundManager::playSong("ORT_UFO", true);
    bossList.push_back(boss); // Add boss to the boss list
}


void EnemyManager::bossHasDied() {
    bossIsActive = false;
    currentBoss = nullptr;
}

int EnemyManager::whichSpawnInterval(int playerScore) {
    // Simplified example, adjust intervals as needed
    if (bossIsActive) return 150; // Slower spawn rate if a boss is active
    if (playerScore < 1000) return 60; // Fast spawn rate for low scores
    if (playerScore < 5000) return 80; // Slower spawn as difficulty increases
    return 100; // Default slowest spawn rate for very high scores or when a boss is likely
}


void EnemyManager::cleanUp(){
    // Clean up dynamically allocated memory, if any
    for (auto& enemy : enemyList) {
        delete enemy;
    }
    enemyList.clear();
}

void EnemyManager::removeEnemies(){
    for (EnemyShip* enemy : enemiesForDeletion) {
        auto it = std::find(enemyList.begin(), enemyList.end(), enemy);
        if (it != enemyList.end()) {
            delete *it; // Assuming dynamic allocation
            enemyList.erase(it);
        }
    }
    enemiesForDeletion.clear(); // Clear the list after deletion
}
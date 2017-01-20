#include <iostream>
#include <zconf.h>
#include <sstream>
#include "steam_api.h"

const char *strarray[] = {"random", "de_cache", "de_cbble", "de_dust2", "de_mirage", "de_nuke", "de_overpass",
                          "de_train", "training1"};

void setPresence(const char *status, const char *score, const char *mapname) {
    SteamFriends()->SetRichPresence("status", status);
    SteamFriends()->SetRichPresence("game:act", "offline");
    SteamFriends()->SetRichPresence("game:mode", "competitive");
    SteamFriends()->SetRichPresence("game:mapgroupname", "mg_active");
    SteamFriends()->SetRichPresence("game:map", mapname);
    SteamFriends()->SetRichPresence("game:score", score);
    SteamFriends()->SetRichPresence("game:server", "competitive");
    printf("Setting status to: %s\n", status);
    printf("Setting score to: %s\n", score);
    printf("Setting map to: %s\n", mapname);
}

double getIntInput(bool shouldLimit) {
    std::string line;
    int d;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        if (ss >> d) {
            if (ss.eof()) {
                if (shouldLimit) {
                    if (d <= 8 && d >= 0)
                        break;
                } else {
                    break;
                }
            }
        }
        if (!shouldLimit)
            std::cout << "Input integers only!" << std::endl;
        else
            std::cout << "Input integers between 0 and 8!" << std::endl;
    }
    return d;
}

void printMapsWithID() {
    printf("%-8s%-21s\n", "ID", "Map name");
    printf("%-8s%-21s\n", "--", "--------");
    for (int i = 0; i <= 8; i++) {
        printf("%-8i%-21s\n", i, strarray[i]);
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "CSGO played hours booster via SteamWorks API" << std::endl;
    char status[64];
    char score[64];
    int tScore;
    int ctScore;
    int mapID;

    while (!SteamAPI_Init()) {
        std::cout << "Steam is not running, please start it." << std::endl;
        std::cout << "Sleeping for 10 seconds." << std::endl;
        sleep(10);
    }
    sleep(2);
    std::cout << "Desired T score: ";
    tScore = getIntInput(false);

    std::cout << "Desired CT score: ";
    ctScore = getIntInput(false);

    printMapsWithID();
    std::cout << "Choose the ID of the desired map: ";
    mapID = getIntInput(true);

    std::cout << "Custom status: ";
    std::cin >> status;

    std::cout << std::endl;

    std::sprintf(score, "(%d:%d)", tScore, ctScore);

    setPresence(status, score, strarray[mapID]);

    std::cout << std::endl << "Running..." << std::endl;

    while (1) {
        sleep(50);
    }

    return 0;
}


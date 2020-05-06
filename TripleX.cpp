#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

void PrintIntroduction(int Level)
{
    if (Level == 1)
    {
        std::cout << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n";
        std::cout << "\nYou are a secret agent breaking into a LEVEL 1 secure server room";
        std::cout << ".\nEnter the correct code to continue...\n\n";
    }
    else
    {
        std::cout << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\\n";
        std::cout << "\nYou are now breaking into a LEVEL " << Level;
        std::cout << " secure server room.\nEnter the correct code to continue...\n\n";
    }
}

bool CheckGuess(int GuessSum, int CodeSum, int GuessProduct, int CodeProduct)
{
    if (GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        std::cout << "You cracked the code!\n\n";
        return true;
    }
    else
    {
        std::cout << "BOOM! You failed! That was the incorrect code.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\nYou now lost an access level.\n\n";

        return false;
    }
}

bool PlayGame(int LevelDifficulty)
{
    PrintIntroduction(LevelDifficulty);

    // Generate code numbers
    const int CodeA = rand() % (LevelDifficulty + 2) + LevelDifficulty;
    const int CodeB = rand() % (LevelDifficulty + 6) + LevelDifficulty;
    const int CodeD = rand() % (LevelDifficulty + 2) + LevelDifficulty;
    int GuessA, GuessB, GuessC, GuessD;

    if (LevelDifficulty < 5)
    {
        const int CodeC = rand() % (LevelDifficulty * 2) + (LevelDifficulty * 2);
        const int CodeSum = CodeA + CodeB + CodeC;
        const int CodeProduct = CodeA * CodeB * CodeC;

        std::cout << "There are 3 numbers in the code\n";
        std::cout << "+ The numbers add-up to: " << CodeSum << std::endl;
        std::cout << "x The numbers multiply to make: " << CodeProduct;
        std::cout << "\n\n\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\n";

        std::cout << "\nEnter guess: ";
        std::cin >> GuessA >> GuessB >> GuessC;

        int GuessSum = GuessA + GuessB + GuessC;
        int GuessProduct = GuessA * GuessB * GuessC;
        return CheckGuess(GuessSum, CodeSum, GuessProduct, CodeProduct);
    }
    else
    {
        const int CodeC = rand() % (LevelDifficulty + 6) + LevelDifficulty;
        const int CodeSum = CodeA + CodeB + CodeC + CodeD;
        const int CodeProduct = CodeA * CodeB * CodeC * CodeD;

        std::cout << "There are 4 numbers in the code\n";
        std::cout << "+ The numbers add-up to: " << CodeSum << std::endl;
        std::cout << "x The numbers multiply to make: " << CodeProduct;

        std::cout << "\n\nEnter guess: ";
        std::cin >> GuessA >> GuessB >> GuessC >> GuessD;

        int GuessSum = GuessA + GuessB + GuessC + GuessD;
        int GuessProduct = GuessA * GuessB * GuessC * GuessD;
        return CheckGuess(GuessSum, CodeSum, GuessProduct, CodeProduct);
    }
}

int main()
{
    srand(time(NULL)); // Create a new random sequence based on time of day.

    int LevelDifficulty = 1;
    const int MaxDifficulty = 5;

    while (LevelDifficulty > 0 && LevelDifficulty <= MaxDifficulty)
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear();                                     // Clears any errors.
        std::cin.ignore();                                    // Discards the buffer.
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Waits 2 second.

        if (bLevelComplete)
        {
            ++LevelDifficulty;
        }
        else
        {
            --LevelDifficulty;
        }
    }

    if (LevelDifficulty == 0)
    {
        std::cout << "\nGame Over!\n";
        return 0;
    }

    std::cout << "\nCongratulations, you are a master hacker!\n";

    return 0;
}

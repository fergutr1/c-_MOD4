#include <iostream>
#include <string>
#include "pokerHand.h"

using namespace std;

int main(void) {

    // Test case 1: High Card vs. High Card (Comparing high cards)
    string handStr1 = "AH 2D 3C 4H 5S";  // Ace-high
    string handStr2 = "KH JD 9H 8D 7S";  // King-high
    pokerHand hand1(handStr1);
    pokerHand hand2(handStr2);
    std::cout << "Test 1 (High Card vs. High Card):" << std::endl;
    hand1.compare(hand2);  // Expected: Hand 1 wins (Ace-high beats King-high)

    // Test case 2: One Pair vs. One Pair (Different pairs)
    handStr1 = "9H 9D 4C 3H 2S";  // Pair of Nines
    handStr2 = "8H 8D 7C 6H 5S";  // Pair of Eights
    hand1 = pokerHand(handStr1);
    hand2 = pokerHand(handStr2);
    std::cout << "Test 2 (One Pair vs. One Pair):" << std::endl;
    hand1.compare(hand2);  // Expected: Hand 1 wins (Pair of Nines beats Pair of Eights)

    // Test case 3: Two Pair vs. Two Pair (Different pairs)
    handStr1 = "KH KD 9H 9D 7C";  // Two Pair (Kings and Nines)
    handStr2 = "KS KC 8H 8D 6C";  // Two Pair (Kings and Eights)
    hand1 = pokerHand(handStr1);
    hand2 = pokerHand(handStr2);
    std::cout << "Test 3 (Two Pair vs. Two Pair):" << std::endl;
    hand1.compare(hand2);  // Expected: Hand 1 wins (Kings over Nines beats Kings over Eights)

    // Test case 4: Three of a Kind vs. Two Pair
    handStr1 = "5H 5D 5C 9H 8D";  // Three of a Kind (Fives)
    handStr2 = "8H 8D 9H 9S 2C";  // Two Pair (Nines and Eights)
    hand1 = pokerHand(handStr1);
    hand2 = pokerHand(handStr2);
    std::cout << "Test 4 (Three of a Kind vs. Two Pair):" << std::endl;
    hand1.compare(hand2);  // Expected: Hand 1 wins (Three of a Kind beats Two Pair)

    // Test case 5: Straight Flush vs. Three of a Kind
    handStr1 = "7H 8H 9H TH JH";  // Straight Flush
    handStr2 = "4C 4D 4H 9S 2S";  // Three of a Kind (Fours)
    hand1 = pokerHand(handStr1);
    hand2 = pokerHand(handStr2);
    std::cout << "Test 5 (Straight Flush vs. Three of a Kind):" << std::endl;
    hand1.compare(hand2);  // Expected: Hand 1 wins (Straight Flush beats Three of a Kind)

    // Test case 6: Flush vs. Full House
    handStr1 = "2H 5H 6H 9H KH";  // Flush
    handStr2 = "3C 3D 3H 7S 7D";  // Full House (Threes over Sevens)
    hand1 = pokerHand(handStr1);
    hand2 = pokerHand(handStr2);
    std::cout << "Test 6 (Flush vs. Full House):" << std::endl;
    hand1.compare(hand2);  // Expected: Hand 2 wins (Full House beats Flush)

    // Test case 7: Straight Flush vs. Four of a Kind
    handStr1 = "9H TH JH QH KH";  // Straight Flush
    handStr2 = "2S 2D 2H 2C 3C";  // Four of a Kind (Twos)
    hand1 = pokerHand(handStr1);
    hand2 = pokerHand(handStr2);
    std::cout << "Test 7 (Straight Flush vs. Four of a Kind):" << std::endl;
    hand1.compare(hand2);  // Expected: Hand 1 wins (Straight Flush beats Four of a Kind)

    // Test case 8: Full House vs. Four of a Kind
    handStr1 = "8H 8D 8S 9C 9D";  // Full House (Eights over Nines)
    handStr2 = "6C 6D 6H 6S 2D";  // Four of a Kind (Sixes)
    hand1 = pokerHand(handStr1);
    hand2 = pokerHand(handStr2);
    std::cout << "Test 8 (Full House vs. Four of a Kind):" << std::endl;
    hand1.compare(hand2);  // Expected: Hand 2 wins (Four of a Kind beats Full House)

    // Test case 9: Comparing two identical hands (Tie case)
    handStr1 = "KH KD 9C 9D 7H";  // Two Pair (Kings and Nines)
    handStr2 = "KH KD 9C 9D 7H";  // Two Pair (Kings and Nines)
    hand1 = pokerHand(handStr1);
    hand2 = pokerHand(handStr2);
    std::cout << "Test 9 (Identical Two Pair):" << std::endl;
    hand1.compare(hand2);  // Expected: Tie

    // Test case 10: Extreme Tie Case
    handStr1 = "AC 9H 8D 7S 6C";  // High Card Ace
    handStr2 = "AC 9D 8H 7C 6S";  // High Card Ace
    hand1 = pokerHand(handStr1);
    hand2 = pokerHand(handStr2);
    std::cout << "Test 10 (Extreme Tie High Card):" << std::endl;
    hand1.compare(hand2);  // Expected: Tie

	return 0;
}
#include "pokerHand.h"
#include <iostream>
#include <algorithm>

pokerHand::pokerHand(const std::string& handString)
{
	try 
	{
		parseHandString(handString);
		this->handString = handString;
		std::cout << "Received hand: " << getHandString() << std::endl;
		determineHandRank();
	}
	catch (const std::invalid_argument& e) 
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

void pokerHand::compare(pokerHand& otherHand)
{
	int myHand = determineHandRank();
	int yourHand = otherHand.determineHandRank();
	int iWin = 3;// Initialize to a tie state

	if (myHand > yourHand) 
	{
		iWin = 1;
	}
	else {
		// This is the tie condition.
		// Determine all ranks and quantity present in each hand
		int rankFreq1[numDifferentRanksInHand];
		int rankFreq2[numDifferentRanksInHand];
		countRankRepeats(rankFreq1);
		otherHand.countRankRepeats(rankFreq2);

		// Iterate from highest to lowest. First hand to have a lower card loses, because at this point
		// we know we both have the same rank type (flush, straight, etc...)
		for (int i = numDifferentRanksInHand - 1; i > 0; i--) {
			if (rankFreq1[i] > rankFreq2[i])
			{
				iWin = 1;
			}
		}
	}

	// Output the comparison results
	if (1 == iWin) {
		std::cout << "Hand: " << getHandString() << ", which is a " << getHandRankString() << ", ranks higher!" << std::endl;
	}
	else if (0 == iWin) {
		std::cout << "Hand: " << otherHand.getHandString() << ", which is a " << otherHand.getHandRankString() << ", ranks higher!" << std::endl;
	}
	else {
		std::cout << "Its a tie!" << std::endl;
	}
}

std::string pokerHand::getHandString() const
{
	return handString;
}

std::string pokerHand::getHandRankString() const
{
	return handRankString;
}

int pokerHand::getHandRankInt() const
{
	return handRankType;
}

void pokerHand::parseHandString(const std::string& handString)
{
	int index = 0;// Used to iterate through the ranks and suits arrays as we parse the input string
	std::string card;// Used to store a substring as we parse the input string

	// Check the length of the input string
	if (handString.length() != numInputStringChars) {
		throw std::invalid_argument("Incorrect hand size.");
	}

	//attempt to parse the string
	for (int i = 0; i < numInputStringChars; i += 3) {
		card = handString.substr(i, 2);// Each card is represented by two characters
		// Try to capture the rank
		switch (card[0]) {
		case '2': {
			ranksInHand[index] = 2;
			break;
		}
		case '3': {
			ranksInHand[index] = 3;
			break;
		}
		case '4': {
			ranksInHand[index] = 4;
			break;
		}
		case '5': {
			ranksInHand[index] = 5;
			break;
		}
		case '6': {
			ranksInHand[index] = 6;
			break;
		}
		case '7': {
			ranksInHand[index] = 7;
			break;
		}
		case '8': {
			ranksInHand[index] = 8;
			break;
		}
		case '9': {
			ranksInHand[index] = 9;
			break;
		}
		case 'T': {
			ranksInHand[index] = 10;
			break;
		}
		case 'J': {
			ranksInHand[index] = 11;
			break;
		}
		case 'Q': {
			ranksInHand[index] = 12;
			break;
		}
		case 'K': {
			ranksInHand[index] = 13;
			break;
		}
		case 'A': {
			ranksInHand[index] = 14;
			break;
		}
		default: {
			throw std::invalid_argument("Invalid hand rank.");
		}
		}// Switch
		// Try to capture the suit
		switch (card[1]) {
		case 'C': {
			suitsinHand[index] = 'C';
			break;
		}
		case 'D': {
			suitsinHand[index] = 'D';
			break;
		}
		case 'H': {
			suitsinHand[index] = 'H';
			break;
		}
		case 'S': {
			suitsinHand[index] = 'S';
			break;
		}
		default: {
			throw std::invalid_argument("Invalid hand suit.");
		}
		}// Switch
		index++;//increment the index 
	}// For
}

int pokerHand::determineHandRank()
{
	if (isFlush() && isStraight())
	{
		handRankString = "Straight Flush";
		handRankType = STRAIGHT_FLUSH;
		return handRankType;
	}
	else if (isFlush()) 
	{
		handRankString = "Flush";
		handRankType = FLUSH;
		return handRankType;
	}
	else if (isStraight()) 
	{
		handRankString = "Straight";
		handRankType = STRAIGHT;
		return handRankType;
	}

	int rankCount[numDifferentRanksInHand];
	int maxFreq1 = 0;
	int MaxFreq2 = 0;
	countRankRepeats(rankCount);

	for (int i = 0; i < numDifferentRanksInHand; i++) {
		if (rankCount[i] > maxFreq1) {
			MaxFreq2 = maxFreq1;
			maxFreq1 = rankCount[i];
		}
		else if (rankCount[i] > MaxFreq2) {
			MaxFreq2 = rankCount[i];
		}
	}

	if (maxFreq1 == 4) {
		handRankString = "Four of a kind";
		handRankType = FOUR_OF_A_KIND;
	}
	else if (maxFreq1 == 3 && MaxFreq2 == 2) {
		handRankString = "Full house";
		handRankType = FULL_HOUSE;
	}
	else if (maxFreq1 == 3) {
		handRankString = "Three of a kind";
		handRankType = THREE_OF_A_KIND;
	}
	else if (maxFreq1 == 2 && MaxFreq2 == 2) {
		handRankString = "Two pair";
		handRankType = TWO_PAIR;
	}
	else if (maxFreq1 == 2) {
		handRankString = "One pair";
		handRankType = ONE_PAIR;
	}
	else {
		handRankString = "High card";
		handRankType = HIGH_CARD;
	}
	return handRankType;
}

void pokerHand::countRankRepeats(int rankCount[numDifferentRanksInHand]) const
{
	std::memset(rankCount, 0, sizeof(int) * numDifferentRanksInHand);// Initialize array to all 0s
	for (int i = 0; i < numCardsInHand; i++) 
	{
		rankCount[ranksInHand[i] - 2]++;// Fit the ranks (2-14) into array indicies(0-12). Increment the ranks that are present
	}
}

bool pokerHand::isFourOfAKind()
{
	int rankCount[numDifferentRanksInHand];
	bool valFound = false;

	countRankRepeats(rankCount);

	// Check the formatted array and see if there are four of a kind present
	for (int i = 0; i < numDifferentRanksInHand; i++) 
	{
		if (4 == rankCount[i]) 
		{
			maxSigRank = i;
			valFound = true;
		}
		if (1 == rankCount[i]) 
		{
			maxKickerRank = i;
		}
	}

	return valFound;
}

bool pokerHand::isFlush()
{
	// Check each suit in the hand against the first suit in the hand
	for (int i = 1; i < numCardsInHand; i++) 
	{
		if (suitsinHand[0] != suitsinHand[i]) 
		{
			return false;
		}
	}

	return true;
}

bool pokerHand::isStraight() const
{
	int sortedRanksInHand[numCardsInHand];
	int temp;

	std::memcpy(sortedRanksInHand, ranksInHand, sizeof(ranksInHand));
	
	// Provide logic to sort the ranks in hand in descending order
	for (int i = 0; i < numCardsInHand; i++) 
	{
		for (int j = i+1; j < numCardsInHand; j++) {
			if (sortedRanksInHand[j] > sortedRanksInHand[i]) {
				temp = sortedRanksInHand[j];
				sortedRanksInHand[j] = sortedRanksInHand[i];
				sortedRanksInHand[i] = temp;
			}
		}
	}

	// Provide logic to determine if the hand is a straight
	for (int i = 1; i < numCardsInHand; ++i) {
		if (sortedRanksInHand[i] != sortedRanksInHand[i - 1] - 1) {
			return false;
		}
	}
	return true;
}

bool pokerHand::isThreeOfAKind() const
{
	int rankCount[numDifferentRanksInHand];

	countRankRepeats(rankCount);
	// Check the formatted array and see if there are three of a kind present
	for (int i = 0; i < numDifferentRanksInHand; i++) 
	{
		if (3 == rankCount[i]) 
		{
			return true;
		}
	}
	return false;
}

bool pokerHand::isTwoPair() const
{
	int rankCount[numDifferentRanksInHand];
	int pairCount = 0;

	countRankRepeats(rankCount);
	// Check the formatted array and see if there are two pairs
	for (int i = 0; i < numDifferentRanksInHand; i++) 
	{
		if (2 == rankCount[i]) 
		{
			pairCount++;
		}
	}
	return (2 == pairCount);
}

bool pokerHand::isOnePair() const
{
	int rankCount[numDifferentRanksInHand];
	int pairCount = 0;

	countRankRepeats(rankCount);
	// Check the formatted array and see if there are two pairs
	for (int i = 0; i < numDifferentRanksInHand; i++) 
	{
		if (2 == rankCount[i]) 
		{
			pairCount++;
		}
	}
	return (1 == pairCount);
}

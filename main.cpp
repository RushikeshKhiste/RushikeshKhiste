// #include "bot.h"
// #include "question.h"


#include<bits/stdc++.h>
// #pragma once
#include <list>
#include <fstream>
#include <iostream>
using namespace std;

class question
{
public:
	question();
	question( string query,  string answer);
	 string m_getQuery();
	 string m_getAnswer();
	~question();

private:
	 string query;
	 string answer;

};
class bot
{
public:
	bot();
	bool isQuestion( string input);
	bool check( string input);
	void reply( string input);
	void storeNewQuestion( string input);
	~bot();

private:
	 list<question> questionList;
};

bot::bot()
{
	 ifstream inputFile;
	 inputFile.open("QA.txt");
	 string tmpQ; // used for temporarily storing questions from text file
	 string tmpA; // used for temporarily storing answer from text file

	while (!inputFile.eof()) //loop until end of file is reached
	{
		getline(inputFile, tmpQ, ';');	// read each line of file one at a time until end of file
		getline(inputFile, tmpA);		// store questions and answers from file into two different variables
		question questionObj(tmpQ, tmpA); // put variables in an object
		questionList.push_back(questionObj); // store the object in a node in a doubly linked list
	}
}

bool bot::isQuestion( string input) // check if user input is formatted correctly ('?' at end of question return true if correct format, return false if inncorect format
{
	if (input.empty())
	{
		return false;
	}
	if (input.back() == '?')
	{
		return true;
	}
	else if (input.back() != '?')
	{
		return false;
	}
}

bool bot::check( string input)
{
	 list<question>::iterator it;
	it = questionList.begin();

	for (it; it != questionList.end(); it++)
	{
		if (input == it->m_getQuery())
		{
			return true;
		}
	}
	return false;
	
}

void bot::reply( string input)
{
	 list<question>::iterator it;
	it = questionList.begin();

	for (it; it != questionList.end(); it++)
	{
		if (input == it->m_getQuery())
		{
			 cout << it->m_getAnswer() <<  endl;
		}
	}
}

void bot::storeNewQuestion( string input)
{
	 string tmp;
	 cout << "Hmmm . . . that's a good question! Maybe you could help me? " <<  endl << input <<  endl;
	getline( cin, tmp); // ask user to answer the question
	question new_query(input, tmp); // store new question and answer in an object
	questionList.push_back(new_query); // store that object in a node inside of the doubly linked list
	 ofstream outputFile;
	outputFile.open("QA.txt",  ios::app);
	if (outputFile.is_open())
	{
		outputFile <<  endl << input << ";" << tmp;
	}
	else
	{
		 cout << "Error, file didn't open." <<  endl;
	}
	outputFile.close();


}

bot::~bot()
{

}

question::question()
{
	query = "";
	answer = "";
}

question::question( string query,  string answer)
{
	this->query = query;
	this->answer = answer;
}

 string question::m_getQuery()
{
	return query;
}

 string question::m_getAnswer()
{
	return answer;
}

question::~question()
{
}

int main()
{

	bot bot;
	bool loop = true;
	 string userInput;
	while (loop)
	{
		 cout << "Hello! Ask me a question!" <<  endl;
		getline( cin, userInput);
		for (int i = 0; i != userInput.length(); i++)
		{
			userInput.at(i) = tolower(userInput.at(i));
		}
		if (bot.isQuestion(userInput) == true)					// check if bot knows answer to the question.
		{														// if bot knows the answer, reply with answer if bot does not know the answer then bot will ask the same question,
			if (bot.check(userInput) == true)					//and store the users answer in the linked list as well as the text file	
			{
				bot.reply(userInput);
			}
			else
			{
				bot.storeNewQuestion(userInput);
			}
		}
		else
		{
			 cout << "You did not ask your question with the right format! Correct questions end with a '?'" <<  endl;
		}
		system("pause");
		system("cls");
	}


	system("pause");
	return 0;
}

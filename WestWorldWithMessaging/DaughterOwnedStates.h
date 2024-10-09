#ifndef DAUGHTER_OWNED_STATES_H
#define DAUGHTER_OWNED_STATES_H
#include "Common/fsm/State.h"

class Daughter;
struct Telegram;

//------------------------------------------------------------------------
// 상태에 대한 설명
//  
//  
//  
//  
//------------------------------------------------------------------------
class GoToSchool : public State<Daughter>
{
private:
  
	GoToSchool(){}

	GoToSchool(const GoToSchool&);
	GoToSchool& operator=(const GoToSchool&);
 
public:
  //this is a singleton
  static GoToSchool* Instance();

  virtual void Enter(Daughter* dt);
  virtual void Execute(Daughter* dt);
  virtual void Exit(Daughter* dt);
  virtual bool OnMessage(Daughter* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
// 
// 
// 
//------------------------------------------------------------------------
class ComeBackHome : public State<Daughter>
{
private:
  
	ComeBackHome(){}

  //copy ctor and assignment should be private
	ComeBackHome(const ComeBackHome&);
	ComeBackHome& operator=(const ComeBackHome&);
 
public:

  //this is a singleton
  static ComeBackHome* Instance();

  virtual void Enter(Daughter* dt);

  virtual void Execute(Daughter* dt);

  virtual void Exit(Daughter* dt);

  virtual bool OnMessage(Daughter* dt, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Daughter will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class PlayGame : public State<Daughter>
{
private:
  
	PlayGame(){}

  //copy ctor and assignment should be private
	PlayGame(const PlayGame&);
	PlayGame& operator=(const PlayGame&);
 
public:

  //this is a singleton
  static PlayGame* Instance();

  virtual void Enter(Daughter* dt);

  virtual void Execute(Daughter* dt);

  virtual void Exit(Daughter* dt);

  virtual bool OnMessage(Daughter* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  Daughter changes location to the saloon and keeps buying Whiskey until
//  his thirst is quenched. When satisfied he returns to the goldmine
//  and resumes his quest for nuggets.
//------------------------------------------------------------------------
class EatSomething : public State<Daughter>
{
private:
  
	EatSomething(){}

  //copy ctor and assignment should be private
	EatSomething(const EatSomething&);
	EatSomething& operator=(const EatSomething&);
 
public:

  //this is a singleton
  static EatSomething* Instance();

  virtual void Enter(Daughter* dt);

  virtual void Execute(Daughter* dt);

  virtual void Exit(Daughter* dt);

  virtual bool OnMessage(Daughter* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  this is implemented as a state blip. The Daughter eats the stew, gives
//  Elsa some compliments and then returns to his previous state
//------------------------------------------------------------------------
class EatStew : public State<Daughter>
{
private:
  
  EatStew(){}

  //copy ctor and assignment should be private
  EatStew(const EatStew&);
  EatStew& operator=(const EatStew&);
 
public:

  //this is a singleton
  static EatStew* Instance();

  virtual void Enter(Daughter* dt);

  virtual void Execute(Daughter* dt);

  virtual void Exit(Daughter* dt);

  virtual bool OnMessage(Daughter* agent, const Telegram& msg);
};




#endif
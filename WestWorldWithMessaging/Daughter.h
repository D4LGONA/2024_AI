#ifndef DAUGHTER_H
#define DAUGHTER_H
//------------------------------------------------------------------------
//
//  Name:   Daughter.h
//
//  Desc:   A class defining a Daughter
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "Common/misc/ConsoleUtils.h"
#include "Common/misc/Utils.h"
#include "DaughterOwnedStates.h"
#include "Common/fsm/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

// ----------- 상태 상수값 저장 ------------
const int MaxFatigue = 10; // 피로도 최대 10
const int Tired = 4; // 피로한지를 보기 위함
const int MaxHungry = 5; // 배고픔 최대 10
const int MaxFeeling = 10; // 기분의 중간선: 높을수록 기분이 좋은 것

class Daughter : public BaseGameEntity
{
private:
  StateMachine<Daughter>*  d_pStateMachine;
  location_type         d_Location;

  int d_Fatigue;
  int d_Hungry;
  int d_Feeling;

public:

    Daughter(int id) :d_Location(home), d_Fatigue(0),
        d_Hungry(MaxHungry), d_Feeling(MaxFeeling), BaseGameEntity(id)

    {
        // set up state machine
        d_pStateMachine = new StateMachine<Daughter>(this);

        // state 시작: 집에서 시작.
        d_pStateMachine->SetCurrentState(ComeBackHome::Instance());
    }
    ~Daughter(){delete d_pStateMachine;}

    void Update();

    virtual bool  HandleMessage(const Telegram& msg);

    StateMachine<Daughter>* GetFSM()const{return d_pStateMachine;}
  
  //-------------------------------------------------------------accessors
  location_type Location()const{return d_Location;}
  void          ChangeLocation(location_type loc){d_Location=loc;}
    
  int           GetFatigue() const {return d_Fatigue;}
  void          SetFatigue(int val) { d_Fatigue = val;}
  bool          isFatigue() { return d_Fatigue >= MaxFatigue; }
  bool          isTired() { return d_Fatigue < Tired; }

  int           GetHungry() const { return d_Hungry; }
  void          SetHungry(int val) { d_Hungry = val; }
  int           isHungry() { return d_Hungry >= 10; }

  int           GetFeeling() const { return d_Feeling; }
  void          SetFeeling(int val) { d_Feeling = val; }
  int           isFeelingGood() { return d_Feeling >= MaxFeeling / 2; }
};



#endif

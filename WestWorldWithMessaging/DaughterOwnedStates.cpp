#include "DaughterOwnedStates.h"
#include "Common/fsm/State.h"
#include "Daughter.h"
#include "Locations.h"
#include "Common/messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Common/Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
GoToSchool* GoToSchool::Instance()
{
  static GoToSchool instance;
  return &instance;
}

void GoToSchool::Enter(Daughter* dt)
{
    if (dt->Location() != school)
    {
        if (RandFloat() < 0.1) 
            cout << "\n" << GetNameOfEntity(dt->ID()) << ": 헐!! 지각이다... 뛰어!!!" << "";
        else
            cout << "\n" << GetNameOfEntity(dt->ID()) << ": 아 학교 가기 싫다. 그래도 가야지..." << "";

        dt->ChangeLocation(school);
    }
}


void GoToSchool::Execute(Daughter* dt)
{  
    if (RandFloat() < 0.3) { // 30% 확률로 농땡이 피기
        // 기분 증가
        dt->SetFeeling(dt->GetFeeling() + 1);

        // 배고픔 증가
        dt->SetHungry(dt->GetHungry() + 1);

        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "조금 쉬었다 해도 되는거 아니겠어?";

    }
    else { // 공부 열심히 하기
        // 배고픔 증가
        dt->SetHungry(dt->GetHungry() + 1);

        // 피로도 증가
        dt->SetFatigue(dt->GetFatigue() + 1);

        // 기분 감소
        dt->SetFeeling(dt->GetFeeling() - 1);

        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " 
            << GetNameOfEntity(dt->ID())<< "이는 지금 공부 중!";
    }

    // 배고프면 밥을 먹으러 간다(우선순위 1)
    if (dt->isHungry()) {
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "아웅 배고파.";

        dt->GetFSM()->ChangeState(EatSomething::Instance());
    }


    // 50% 피곤하면...
    // case 1: 기분이 5 미만일때 -> 게임을 하러 간다
    // case 2: 기분이 5 이상일때 -> 계속 공부한다
    if (dt->isTired()) {
        if (dt->GetFeeling() < 5) {
            dt->GetFSM()->ChangeState(PlayGame::Instance());
        }
    }
    
    // 공부를 더이상 못하겠다면...
    if (dt->isFatigue()) {
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "피곤하다. 그만둘래.";
        dt->GetFSM()->ChangeState(ComeBackHome::Instance());
    }
}


void GoToSchool::Exit(Daughter* dt)
{
  cout << "\n" << GetNameOfEntity(dt->ID()) << ": " 
       << "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}


bool GoToSchool::OnMessage(Daughter* dt, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for ComeBackHome

ComeBackHome* ComeBackHome::Instance()
{
  static ComeBackHome instance;

  return &instance;
}

void ComeBackHome::Enter(Daughter* dt)
{  
    if (dt->Location() != home)
    {
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "다녀왔습니다아~ 정말 힘든 하루였어!";
    }
}


void ComeBackHome::Execute(Daughter* dt)
{
    // 자는 중...
    // 피로도 -1
    // todo: 추가할것인가?

    dt->SetFatigue(dt->GetFatigue() - 1);
    cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "ZzzZZzZzZzZzzZzz..";

    // todo: 여기 수정할지 고민
    if (dt->GetFatigue() <= 0) {
        dt->GetFSM()->ChangeState(GoToSchool::Instance());
    }
}

void ComeBackHome::Exit(Daughter* dt)
{
}


bool ComeBackHome::OnMessage(Daughter* dt, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

PlayGame* PlayGame::Instance()
{
  static PlayGame instance;
  return &instance;
}

void PlayGame::Enter(Daughter* dt)
{
    cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "기분도 꿀꿀한데 오버워치 드가자~";
    dt->ChangeLocation(gameroom);

    //let the wife know I'm home
    //Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
    //                          dt->ID(),        //ID of sender
    //                          ent_Elsa,            //ID of recipient
    //                          Msg_HiHoneyImHome,   //the message
    //                          NO_ADDITIONAL_INFO);    
}

void PlayGame::Execute(Daughter* dt)
{ 
    if (RandFloat() < 0.5f) { // 50% 확률로 승패
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": "
            << "캐리요 ㅋㅋ 이지하네~";
    }
    else {
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": "
            << "아니 이걸져? 진짜 우리팀 뭐하지;;";
    }

}

void PlayGame::Exit(Daughter* dt)
{ 
    cout << "\n" << GetNameOfEntity(dt->ID()) << ": "
        << "게임 질린다. 그냥 집이나 가야지...";
}


bool PlayGame::OnMessage(Daughter* dt, const Telegram& msg)
{
   SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   switch(msg.Msg)
   {
   case Msg_StewReady:

     cout << "\nMessage handled by " << GetNameOfEntity(dt->ID()) 
     << " at time: " << Clock->GetCurrentTime();

     SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(dt->ID()) 
          << ": Okay Hun, ahm a comin'!";

     dt->GetFSM()->ChangeState(EatStew::Instance());
      
     return true;

   }//end switch

   return false; //send message to global message handler
}

//------------------------------------------------------------------------EatSomething

EatSomething* EatSomething::Instance()
{
  static EatSomething instance;

  return &instance;
}

void EatSomething::Enter(Daughter* dt)
{
  if (dt->Location() != saloon)
  {    
    dt->ChangeLocation(saloon);

    cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
  }
}

void EatSomething::Execute(Daughter* dt)
{
  dt->BuyAndDrinkAWhiskey();

  cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "That's mighty fine sippin' liquer";

  dt->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());  
}


void EatSomething::Exit(Daughter* dt)
{ 
  cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "Leaving the saloon, feelin' good";
}


bool EatSomething::OnMessage(Daughter* dt, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
  static EatStew instance;

  return &instance;
}


void EatStew::Enter(Daughter* dt)
{
  cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "Smells Reaaal goood Elsa!";
}

void EatStew::Execute(Daughter* dt)
{
  cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "Tastes real good too!";

  dt->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Daughter* dt)
{ 
  cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
}


bool EatStew::OnMessage(Daughter* dt, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}



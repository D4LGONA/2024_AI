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
            cout << "\n" << GetNameOfEntity(dt->ID()) << ": ��!! �����̴�... �پ�!!!" << "";
        else
            cout << "\n" << GetNameOfEntity(dt->ID()) << ": �� �б� ���� �ȴ�. �׷��� ������..." << "";

        dt->ChangeLocation(school);
    }
}


void GoToSchool::Execute(Daughter* dt)
{  
    if (RandFloat() < 0.3) { // 30% Ȯ���� ���� �Ǳ�
        // ��� ����
        dt->SetFeeling(dt->GetFeeling() + 1);

        // ����� ����
        dt->SetHungry(dt->GetHungry() + 1);

        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "���� ������ �ص� �Ǵ°� �ƴϰھ�?";

    }
    else { // ���� ������ �ϱ�
        // ����� ����
        dt->SetHungry(dt->GetHungry() + 1);

        // �Ƿε� ����
        dt->SetFatigue(dt->GetFatigue() + 1);

        // ��� ����
        dt->SetFeeling(dt->GetFeeling() - 1);

        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " 
            << GetNameOfEntity(dt->ID())<< "�̴� ���� ���� ��!";
    }

    // ������� ���� ������ ����(�켱���� 1)
    if (dt->isHungry()) {
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "�ƿ� �����.";

        dt->GetFSM()->ChangeState(EatSomething::Instance());
    }


    // 50% �ǰ��ϸ�...
    // case 1: ����� 5 �̸��϶� -> ������ �Ϸ� ����
    // case 2: ����� 5 �̻��϶� -> ��� �����Ѵ�
    if (dt->isTired()) {
        if (dt->GetFeeling() < 5) {
            dt->GetFSM()->ChangeState(PlayGame::Instance());
        }
    }
    
    // ���θ� ���̻� ���ϰڴٸ�...
    if (dt->isFatigue()) {
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "�ǰ��ϴ�. �׸��ѷ�.";
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
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "�ٳ�Խ��ϴپ�~ ���� ���� �Ϸ翴��!";
    }
}


void ComeBackHome::Execute(Daughter* dt)
{
    // �ڴ� ��...
    // �Ƿε� -1
    // todo: �߰��Ұ��ΰ�?

    dt->SetFatigue(dt->GetFatigue() - 1);
    cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "ZzzZZzZzZzZzzZzz..";

    // todo: ���� �������� ���
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
    cout << "\n" << GetNameOfEntity(dt->ID()) << ": " << "��е� �ܲ��ѵ� ������ġ �尡��~";
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
    if (RandFloat() < 0.5f) { // 50% Ȯ���� ����
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": "
            << "ĳ���� ���� �����ϳ�~";
    }
    else {
        cout << "\n" << GetNameOfEntity(dt->ID()) << ": "
            << "�ƴ� �̰���? ��¥ �츮�� ������;;";
    }

}

void PlayGame::Exit(Daughter* dt)
{ 
    cout << "\n" << GetNameOfEntity(dt->ID()) << ": "
        << "���� ������. �׳� ���̳� ������...";
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



#include "Daughter.h"

bool Daughter::HandleMessage(const Telegram& msg)
{
  return d_pStateMachine->HandleMessage(msg);
}

// todo: 수정하기
void Daughter::Update()
{
	SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
	
	d_pStateMachine->Update();
}

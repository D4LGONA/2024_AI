#include "Daughter.h"

bool Daughter::HandleMessage(const Telegram& msg)
{
  return d_pStateMachine->HandleMessage(msg);
}

// todo: �����ϱ�
void Daughter::Update()
{
	SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
	
	d_pStateMachine->Update();
}
